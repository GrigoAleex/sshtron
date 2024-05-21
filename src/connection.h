#ifndef connection_h
#define connection_h

#include <vector>
#include <string>

namespace sshtron {
    class Connection {
    public:
        std::string nickname;
        std::string user;
        std::string ipAddress;

        Connection() = default;

        Connection(const std::string& nick, const std::string& usr, const std::string& ip)
            : nickname(nick), user(usr), ipAddress(ip) {}

        friend std::ostream& operator<<(std::ostream& os, const Connection& conn);
        friend std::istream& operator>>(std::istream& is, Connection& conn);
        
        static std::vector<Connection> all(const std::string& filename) {
            std::vector<Connection> connections;
            std::ifstream infile(filename);
            
            if (infile) {
                Connection conn;
                while (infile >> conn) {
                    connections.push_back(conn);
                }
                infile.close();
            }
            
            return connections;
        }
        
        static void writeConnectionsToFile(const std::string& filename, const std::vector<Connection>& connections) {
            std::ofstream outfile(filename);
            for (const auto& conn : connections) {
                outfile << conn << std::endl;
            }
            outfile.close();
        }
    };

    std::ostream& operator<<(std::ostream& os, const Connection& conn) {
        os << conn.nickname << " " << conn.user << " " << conn.ipAddress;
        return os;
    }

    std::istream& operator>>(std::istream& is, Connection& conn) {
        is >> conn.nickname >> conn.user >> conn.ipAddress;
        return is;
    }
}

#endif /* connection_h */
