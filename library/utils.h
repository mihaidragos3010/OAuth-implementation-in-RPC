#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_CLIENT_COMMAND 100
#define MAX_INPUT_COMMAND_LENGTH 256
#define MAX_COMMAND_LENGTH 20

typedef struct {
    char id[50];
    char command[50];
    char arguments[50];
} InputClient;


int readInputClientFile(char* filename, InputClient** inputs);
