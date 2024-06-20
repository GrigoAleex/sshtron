#ifndef _CLI_H_
#define _CLI_H_

#include "connection.h"

typedef struct {
    Connections *connections;
} CLIManager;

void cli_print_menu(CLIManager*, int);
void cli_print_connectoins(CLIManager*, int);
void cli_print_register(CLIManager*);

#endif // _CLI_H_
