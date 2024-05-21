
/**
 * Learn to publish such apps
 * Create a SRL
 * Anti crack software
 * Installation menu for windows, mac and linux
 * Installation guide
 * Website
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "connection.h"

#define FILENAME "saved_connections"
#define PLACHOLDER_CHAR 'P'
#define ART_WIDTH 68

static void displayConnectionsMenu(const std::vector<sshtron::Connection>& connections, size_t selectedIndex);
static void printWelcomeDialog();
void displayMainMenu(size_t selectedIndex);
static void printAllConnections();
static void registerMainMenuInput(char ch, size_t selectedIndex);

void printTitle(const std::string& title) {
    int padding = (ART_WIDTH - title.length()) / 2;
    if (padding < 0) {
        padding = 0;  // In case the title is longer than ART_WIDTH
    }
    std::cout << std::string(padding, ' ') << title << std::endl;
    std::cout << std::endl;
}

static void printWelcomeDialog() {
    std::cout << "  /$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$$/$$$$$$$   /$$$$$$  /$$   /$$\n";
    std::cout << " /$$__  $$/$$__  $$| $$  | $$|__  $$__/ $$__  $$ /$$__  $$| $$$ | $$\n";
    std::cout << "| $$  \\__/ $$  \\__/| $$  | $$   | $$  | $$  \\ $$| $$  \\ $$| $$$$| $$\n";
    std::cout << "|  $$$$$$|  $$$$$$ | $$$$$$$$   | $$  | $$$$$$$/| $$  | $$| $$ $$ $$\n";
    std::cout << " \\____  $$\\____  $$| $$__  $$   | $$  | $$__  $$| $$  | $$| $$  $$$$\n";
    std::cout << " /$$  \\ $$/$$  \\ $$| $$  | $$   | $$  | $$  \\ $$| $$  | $$| $$\\  $$$\n";
    std::cout << "|  $$$$$$/  $$$$$$/| $$  | $$   | $$  | $$  | $$|  $$$$$$/| $$ \\  $$\n";
    std::cout << " \\______/ \\______/ |__/  |__/   |__/  |__/  |__/ \\______/ |__/  \\__/\n";
    std::cout << "                                                                    \n";
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) {
        // Print error message to stderr instead of stdout
        perror ("read()");
        fprintf(stderr, "Error reading character from terminal.\n");
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}

void sshConnect(const std::string& username, const std::string& ipAddress) {
    system("clear");
    printWelcomeDialog();
    printTitle("Connecting to " + username + "@" + ipAddress);
    std::string command = "ssh " + username + "@" + ipAddress;
    int result = system(command.c_str());

    if (result == -1) {
        std::cout << std::endl;
        std::cerr << "Error: failed to execute SSH command." << std::endl;
    } else {
        std::cout << std::endl;
        std::cout << "SSHtron: SSH command executed, return code: " << result << std::endl;
    }
}


static void registerInput(char ch, size_t selectedIndex, std::vector<sshtron::Connection> connections) {
    switch (ch) {
        case 'A': // Up arrow
            selectedIndex = (selectedIndex == 0) ? connections.size() - 1 : selectedIndex - 1;
            displayConnectionsMenu(connections, selectedIndex);
            break;
        case 'B': // Down arrow
            selectedIndex = (selectedIndex == connections.size() - 1) ? 0 : selectedIndex + 1;
            displayConnectionsMenu(connections, selectedIndex);
            break;
        case 'd': // Delete
            connections.erase(connections.begin() + selectedIndex);
            if (selectedIndex >= connections.size()) {
                selectedIndex = connections.size() - 1;
            }
            sshtron::Connection::writeConnectionsToFile(FILENAME, connections);
            displayConnectionsMenu(connections, selectedIndex);
            break;
        case 'q':
            return;
            
        case ' ': // Space
            sshConnect(connections[selectedIndex].user, connections[selectedIndex].ipAddress);
            return;
            
        default:
            break;
    }
    
    char c = getch();
    registerInput(c, selectedIndex, connections);
}


void registerNewConnection() {
    system("clear");
    printWelcomeDialog();
    printTitle("Creating a new connection");
    std::cout << std::endl;
    
    std::string ipAddress, username, nickname;

    std::cout << "Enter IP address: ";
    std::cin >> ipAddress;
    
    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter nickname (leave blank for default 'user@ipaddress'): ";
    std::cin.ignore();  // Ignore the newline left in the buffer
    std::getline(std::cin, nickname);

    if (nickname.empty()) {
        nickname = username + "@" + ipAddress;
    }

    sshtron::Connection newConnection(nickname, username, ipAddress);
    std::vector<sshtron::Connection> connections = sshtron::Connection::all(FILENAME);
    connections.push_back(newConnection);
    sshtron::Connection::writeConnectionsToFile(FILENAME, connections);

    std::cout << "Connection registered successfully!\n";
    std::cout << "Press any key to return to the main menu...";
    getch();

    displayMainMenu(0);
    registerMainMenuInput('P', 0);
}



static void registerMainMenuInput(char ch, size_t selectedIndex) {
    switch (ch) {
        case 'A': // Up arrow
            selectedIndex = (selectedIndex == 0) ? 1 : 0;
            displayMainMenu(selectedIndex);
            break;
        case 'B': // Down arrow
            selectedIndex = (selectedIndex == 1) ? 0 : 1;
            displayMainMenu(selectedIndex);
            break;
        case ' ': // Space
            if (selectedIndex == 0) {
                printAllConnections();
            } else {
                registerNewConnection();
            }
            return;
            break;
            
        case 'q':
            return;
            
        default:
            break;
    }
    
    char c = getch();
    registerMainMenuInput(c, selectedIndex);
}


static void printAllConnections() {
    std::vector<sshtron::Connection> connections = sshtron::Connection::all(FILENAME);
    if (connections.size() == 0)  {
        system("clear");
        printWelcomeDialog();
        
        std::cout << std::endl;
        std::cout << std::endl;
        
        printTitle("You have no connections created.");
        
        std::cout << std::endl;
        std::cout << std::endl;
        
        return;
    }
    
    displayConnectionsMenu(connections, 0);
    registerInput('P', 0, connections);
}

void displayConnectionsMenu(const std::vector<sshtron::Connection>& connections, size_t selectedIndex) {
    system("clear");
    printWelcomeDialog();
    
    printTitle("Connect to a server");
    
    std::cout << "Select a connection:" << std::endl;
    for (size_t i = 0; i < connections.size(); ++i) {
        if (i == selectedIndex) {
            std::cout << " > " << connections[i].nickname << std::endl;
        } else {
            std::cout << "   " << connections[i].nickname << std::endl;
        }
    }
    std::cout << " use arrows to move, space to select, d to delete and q to quit" << std::endl;
}

void displayMainMenu(size_t selectedIndex) {
    system("clear");
    printWelcomeDialog();
    printTitle("Main menu");
    
    std::vector<std::string> connections;
    connections.push_back("Connect to a server");
    connections.push_back("Create a new connection");
    
    std::cout << "What would you like to do?:" << std::endl;
    for (size_t i = 0; i < connections.size(); ++i) {
        if (i == selectedIndex) {
            std::cout << " > " << connections[i] << std::endl;
        } else {
            std::cout << "   " << connections[i] << std::endl;
        }
    }
    std::cout << " * use arrows to move, space to select and q to quit" << std::endl;
}

int main(int argc, const char * argv[]) {
    displayMainMenu(0);
    registerMainMenuInput(PLACHOLDER_CHAR, 0);
    return 0;
}
