#include <stdio.h>

#include "src/connection.h"
#include "src/cli.h"

#define FILENAME "build/saved_connections"

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("SSHTron starting...\n");

    printf("READING FILES FROM: %s", FILENAME);
    Connections *connections = connections_load(FILENAME);

    printf("SSHTron loaded connections...\n");

    CLIManager cli = { .connections = connections };


    printf("SSHTron Starting UI...\n");
    cli_print_menu(&cli, 0);

    return 0;
}
