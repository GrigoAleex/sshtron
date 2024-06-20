#include <stdio.h>

#include "src/connection.h"
#include "src/cli.h"

#define FILENAME "build/saved_connections"

int main(void) {
    Connections *connections = connections_load(FILENAME);
    CLIManager cli = { .connections = connections };
    
    cli_print_menu(&cli, 0);

    return 0;
}
