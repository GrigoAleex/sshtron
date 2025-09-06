#ifndef CONNECTION_H
#define CONNECTION_H

#define MAX_STRING_LENGTH 255
#define MAX_CONNECTION_STRING_LENGTH (MAX_STRING_LENGTH * 2 + 15 + 3)

#include <stdint.h>

typedef struct {
    char nickname[MAX_STRING_LENGTH];
    char user[MAX_STRING_LENGTH];
    char ipAddress[15];
} Connection;

typedef struct {
    Connection **connections;
    uint16_t size;
} Connections;

/** Initializes a ssh session for the given connection */
int connection_init(const Connection *);

/** Creates a connection */
Connection* connection_create(const char*, const char*, const char*);

/** Destroys a connection */
void Connection_destroy(Connection *);

/** Returns the connection string with the format: "nickname user ipAddress" */
char* connection_string(const Connection *);

/** Reads an array of connections from a file */
Connections* connections_load(const char *filename);

/** Saves an array of connections to a file */
int connections_save_to_file(const char *filename, const Connections *connections);

/** Pushes a connection to the end of the array */
Connections* connections_push_back(Connections *connections, Connection *connection);

/** Removes a connection from the array */
Connections* connections_remove(Connections *connections, const char* nickname);

#endif // CONNECTION_H
