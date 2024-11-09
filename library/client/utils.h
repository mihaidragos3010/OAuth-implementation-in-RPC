#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_CLIENT_COMMAND 100
#define MAX_INPUT_COMMAND_LENGTH 256
#define ID_SIZE 16
#define COMMAND_SIZE 21
#define ARGUMENTS_SIZE 21

typedef struct {
    char id[ID_SIZE];
    char command[COMMAND_SIZE];
    char arguments[ARGUMENTS_SIZE];
} InputClient;


int readInputClientFile(char* filename, InputClient** inputs);
