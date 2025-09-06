#include <fcntl.h>
#include "compat.h"
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef MAX_CONNECTION_STRING_LENGTH
#define MAX_CONNECTION_STRING_LENGTH 512  // sigur pentru "nickname: user@host"
#endif

// forward
Connection* connection_create(const char* nickname, const char* user, const char* host);

static void rstrip(char *s) {
    size_t n = strlen(s);
    while (n && (s[n-1] == '\n' || s[n-1] == '\r' || s[n-1] == ' ' || s[n-1] == '\t')) {
        s[--n] = '\0';
    }
}

static void lstrip(char *s) {
    size_t n = 0, len = strlen(s);
    while (n < len && (s[n] == ' ' || s[n] == '\t')) n++;
    if (n) memmove(s, s + n, len - n + 1);
}

static void strip(char *s) { rstrip(s); lstrip(s); }

// Parsează "nickname: user@host"
static int parse_line(const char *line_in, char *out_nick, size_t n1, char *out_user, size_t n2, char *out_host, size_t n3) {
    char buf[MAX_CONNECTION_STRING_LENGTH];
    strncpy(buf, line_in, sizeof(buf)-1);
    buf[sizeof(buf)-1] = '\0';

    strip(buf);
    if (buf[0] == '\0') return 0; // linie goală

    // caută ':'
    char *colon = strchr(buf, ':');
    if (!colon) return 0;

    *colon = '\0';
    char *nick = buf;
    char *rest = colon + 1;
    strip(nick);
    strip(rest);

    // așteptăm "user@host" în rest
    char *at = strchr(rest, '@');
    if (!at) return 0;

    *at = '\0';
    char *user = rest;
    char *host = at + 1;
    strip(user);
    strip(host);

    if (nick[0] == '\0' || user[0] == '\0' || host[0] == '\0') return 0;

    strncpy(out_nick, nick, n1-1); out_nick[n1-1] = '\0';
    strncpy(out_user, user, n2-1); out_user[n2-1] = '\0';
    strncpy(out_host, host, n3-1); out_host[n3-1] = '\0';
    return 1;
}

Connections* connections_load(const char *filename) {
    printf("Reading from file %s\n", filename);

    FILE *f = fopen(filename, "rb");   // text is fine; rb is harmless
    Connections *connections = (Connections*)calloc(1, sizeof(Connections));
    if (!connections) return NULL;

    if (!f) {
        // fișierul nu există încă → listă goală
        connections->connections = NULL;
        connections->size = 0;
        return connections;
    }

    char line[MAX_CONNECTION_STRING_LENGTH];
    size_t cap = 0, used = 0;
    Connection **vec = NULL;

    while (fgets(line, sizeof(line), f)) {
        char nickname[256], user[128], host[256];
        if (!parse_line(line, nickname, sizeof(nickname), user, sizeof(user), host, sizeof(host))) {
            continue; // sar peste liniile invalide
        }

        Connection *c = connection_create(nickname, user, host);
        if (!c) continue;

        if (used == cap) {
            size_t newcap = cap ? cap * 2 : 8;
            Connection **tmp = (Connection**)realloc(vec, newcap * sizeof(*tmp));
            if (!tmp) { /* out of memory */ break; }
            vec = tmp; cap = newcap;
        }
        vec[used++] = c;
    }

    fclose(f);

    connections->connections = vec;
    connections->size = (uint16_t)used; // dacă ai nevoie de uint16_t

    return connections;
}


int connections_save_to_file(const char *filename, const Connections *connections) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    assert(fd != -1);

    if (connections == NULL) {
        write(fd, 0, sizeof(uint16_t));
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
    for (uint16_t i = 0; i < connections->size; i++) {
        if (strcmp(connections->connections[i]->nickname, nickname) == 0) {
            Connection_destroy(connections->connections[i]);
            for (uint16_t j = i; j < connections->size - 1; j++) {
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
