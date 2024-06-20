#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "connection.h"
// TODO: Move this to a config file 
#define FILENAME "build/saved_connections" 

int connection_init(const Connection *c) {
    char command[5 + MAX_STRING_LENGTH + 15];
    snprintf(command, sizeof(command), "ssh %s@%s", c->user, c->ipAddress);
    printf("%s", command);
    return system(command); 
}

/**
 * Creates a new connection
 * 
 * @param nick The nickname of the connection
 * @param usr The username of the connection
 * @param ip The ip address of the connection
 * 
 * @return A pointer to new connection
 */
Connection* connection_create(const char *nick, const char *usr, const char *ip) {
    Connection* conn = (Connection *)malloc(sizeof(Connection));

    strncpy(conn->nickname, nick, MAX_STRING_LENGTH);
    strncpy(conn->user, usr, MAX_STRING_LENGTH);
    strncpy(conn->ipAddress, ip, 15);

    return conn;
}

void Connection_destroy(Connection *conn) {
    free(conn);
}

char* connection_string(const Connection *conn) {
    char *buffer = (char*)calloc(MAX_CONNECTION_STRING_LENGTH, sizeof(char));
    
    snprintf(
        buffer, MAX_CONNECTION_STRING_LENGTH,
        "%s: %s@%s", 
        conn->nickname, conn->user, conn->ipAddress
    );

    return buffer;
}

Connections* connections_load(const char *filename) {
    int fd = open(filename, O_RDONLY | O_CREAT, 0644);
    assert(fd != -1);
    
    u_int16_t cappacity;
    read(fd, &cappacity, sizeof(cappacity));
    Connections *connections = (Connections *)malloc(sizeof(Connections));

    if (cappacity == 0) {
        close(fd);
        connections->connections = NULL;
        connections->size = 0;
        return connections;
    }

    connections->size = cappacity;
    connections->connections = (Connection **)malloc(sizeof(Connection *) * cappacity);

    char line[MAX_CONNECTION_STRING_LENGTH];
    while (cappacity > 0) {
        read(fd, line, MAX_CONNECTION_STRING_LENGTH);

        char *nickname = strtok(line, ":");
        char *user = strtok(NULL, "@");
        char *ipAddress = strtok(NULL, "\0");


        connections->connections[--cappacity] = connection_create(nickname, user, ipAddress);
    }

    close(fd);
    return connections;
}


int connections_save_to_file(const char *filename, const Connections *connections) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    assert(fd != -1);

    if (connections == NULL) {
        write(fd, 0, sizeof(u_int16_t));
        close(fd);
        return 0;
    }
    write(fd, &connections->size, sizeof(connections->size));

    for (int i = connections->size - 1; i >= 0; i--) {
        char *conn_str = connection_string(connections->connections[i]);
        write(fd, conn_str, MAX_CONNECTION_STRING_LENGTH);
    }

    close(fd);
    return 0;
}

Connections* connections_push_back(Connections *connections, Connection *connection) {
    connections->connections = (Connection **)realloc(connections->connections, sizeof(Connection *) * (connections->size++));
    connections->connections[connections->size - 1] = connection;

    return connections;
}

Connections* connections_remove(Connections *connections, const char* nickname) {
    for (u_int16_t i = 0; i < connections->size; i++) {
        if (strcmp(connections->connections[i]->nickname, nickname) == 0) {
            Connection_destroy(connections->connections[i]);
            for (u_int16_t j = i; j < connections->size - 1; j++) {
                connections->connections[j] = connections->connections[j + 1];
            }
            
            if (connections->size == 1) {
                free(connections->connections);
                connections->connections = NULL;
                connections->size = 0;
                break;;
            }

            connections->connections = (Connection **)realloc(connections->connections, sizeof(Connection *) * (--connections->size));
            break;
        }
    }

    connections_save_to_file(FILENAME, connections);

    return connections;
}
