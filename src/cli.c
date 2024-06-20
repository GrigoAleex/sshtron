#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "cli.h"

#define ART_WIDTH 68
#define UP_ARROW 65
#define DOWN_ARROW 66

// TODO: Move this to a config file
#define FILENAME "build/saved_connections"

char getch(void) {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);

    // Get the terminal attributes
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");

    // Disable canonical mode and echo
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

    // Set the new terminal attributes
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");

    // Read a single character from the terminal
    if (read(0, &buf, 1) < 0) {
        // Print error message to stderr instead of stdout
        perror("read()");
        fprintf(stderr, "Error reading character from terminal.\n");
    }

    // Restore the old terminal attributes
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");

    return buf;
}

void cli_print_brand(void) {
    printf("  /$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$$/$$$$$$$   /$$$$$$  /$$   /$$\n");
    printf(" /$$__  $$/$$__  $$| $$  | $$|__  $$__/ $$__  $$ /$$__  $$| $$$ | $$\n");
    printf("| $$  \\__/ $$  \\__/| $$  | $$   | $$  | $$  \\ $$| $$  \\ $$| $$$$| $$\n");
    printf("|  $$$$$$|  $$$$$$ | $$$$$$$$   | $$  | $$$$$$$/| $$  | $$| $$ $$ $$\n");
    printf(" \\____  $$\\____  $$| $$__  $$   | $$  | $$__  $$| $$  | $$| $$  $$$$\n");
    printf(" /$$  \\ $$/$$  \\ $$| $$  | $$   | $$  | $$  \\ $$| $$  | $$| $$\\  $$$\n");
    printf("|  $$$$$$/  $$$$$$/| $$  | $$   | $$  | $$  | $$|  $$$$$$/| $$ \\  $$\n");
    printf(" \\______/ \\______/ |__/  |__/   |__/  |__/  |__/ \\______/ |__/  \\__/\n");
    printf("                                                                    \n");
}

void cli_print_title(const char *title) {
    int padding = (ART_WIDTH - sizeof(title)) / 2;
    if (padding < 0) {
        padding = 0;
    }
    
    for (int i = 0; i < padding; i++)
    {   
        printf(" ");
    }

    printf("%s\n\n", title);
}

/**
 * @brief Wait for user input and handle it
 * @returns 1 if user selected an option, 0 for arrow movement, -1 for q and charCode for any other key
 */
int cli_select(int *selectedIndex, const int maxIndex) {
    char c = getch();
    switch (c) {
        case UP_ARROW:
            *selectedIndex = (*selectedIndex - 1 + maxIndex) % maxIndex;
            return 0;
        case DOWN_ARROW:
            *selectedIndex = (*selectedIndex + 1) % maxIndex;
            return 0;
        case ' ':
            return 1;
        case 'q': 
            return -1;
        default:
            return c;
            break;
    }

    return 0;
}

void cli_print_menu(CLIManager *cli, int selectedIndex) {
#if defined(_WIN32) || defined(WIN32) 
    system("cls");
#else
    system("clear");
#endif
    cli_print_brand();
    cli_print_title("Main Menu");

    char *mainMenuOptions[3] = {
        "Connect to a server",
        "Register a new connection",
        "Exit"
    };

    printf("What would you like to do?\n");

    for (int i = 0; i < 3; ++i) {
        printf(" %c %s\n", i == selectedIndex ? '>' : ' ', mainMenuOptions[i]);
    }
    printf(" * use arrows to move, space to select and q to quit\n");

    int keyPressed;
wait_for_input:
    keyPressed = cli_select(&selectedIndex, 3);
    
    if (keyPressed == -1) {
        exit(0);
    }

    if (keyPressed == 0) {
        cli_print_menu(cli, selectedIndex);
        return;
    }

    if (keyPressed != 1) {
        goto wait_for_input;
    }

    switch (selectedIndex) {
        case 0:
            cli_print_connectoins(cli, 0);
            break;
        case 1:
            cli_print_register(cli);
            break;
        case 2:
            exit(0);
    }
}

void cli_print_connectoins(CLIManager *cli, int selectedIndex) {
#if defined(_WIN32) || defined(WIN32) 
    system("cls");
#else
    system("clear");
#endif
    cli_print_brand();
    cli_print_title("Saved Connections");

    if (cli->connections->size == 0) {
        printf("No saved connections\n");
        return;
    }

    for (int i = 0; i < cli->connections->size; ++i) {
        printf(" %c %s\n", i == selectedIndex ? '>' : ' ', cli->connections->connections[i]->nickname);
    }
    printf(" * use arrows to move, space to select and q to quit\n");
    int keyPressed;

wait_for_input:
    keyPressed = cli_select(&selectedIndex, cli->connections->size);
    
    if (keyPressed == -1) {
        exit(0);
    }

    if (keyPressed == 0) {
        cli_print_connectoins(cli, selectedIndex);
        return;
    }

    if (keyPressed == 'd') {
        cli->connections = connections_remove(cli->connections, cli->connections->connections[selectedIndex]->nickname);
        cli_print_connectoins(cli, selectedIndex);
        return;
    }

    if (keyPressed != 1) {
        goto wait_for_input;
    }

#if defined(_WIN32) || defined(WIN32) 
    system("cls");
#else
    system("clear");
#endif
    connection_init(cli->connections->connections[selectedIndex]);
}


void cli_print_register(CLIManager *cli) {
#if defined(_WIN32) || defined(WIN32) 
    system("cls");
#else
    system("clear");
#endif
    cli_print_brand();
    cli_print_title("Creating a new connection");
    
    char nickname[MAX_STRING_LENGTH];
    char user[MAX_STRING_LENGTH];
    char ipAddress[15];

    puts("Enter IP address: ");
    scanf(" %s", ipAddress);
    
    puts("Enter username: ");
    scanf(" %s", user);

    puts("Enter nickname (leave blank for default 'user@ipaddress'): ");
    scanf(" %s", nickname);

    if (strlen(nickname) == 0) {
        snprintf(nickname, strlen(user) + 1 + strlen(ipAddress), "%s@%s", user, ipAddress);
    }

    Connection *conn = connection_create(nickname, user, ipAddress);
    cli->connections = connections_push_back(cli->connections, conn);

#ifdef FILENAME
    connections_save_to_file(FILENAME, cli->connections);
#else
    puts("No filename defined to save the connections. Next time you run the program, the connection will not be available.");
#endif
    puts("Connection registered successfully!\nPress any key to return to the main menu...");
    getch();

    cli_print_menu(cli, 0); 
}
