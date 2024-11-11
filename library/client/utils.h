#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_CLIENT_COMMAND 100
#define MAX_INPUT_COMMAND_LENGTH 256
#define ID_SIZE 16
#define COMMAND_SIZE 21
#define ARGUMENTS_SIZE 21
#define TOKEN_SIZE 16
#define MAX_CLIENTS_ACCEPTED 100

typedef struct {
    char id[ID_SIZE];
    char command[COMMAND_SIZE];
    char arguments[ARGUMENTS_SIZE];
} InputClient;

typedef struct {
    char id[ID_SIZE];
    char access_token[TOKEN_SIZE];
    char refresh_token[TOKEN_SIZE];
    int ttl;
} ClientCredentials;

int readInputClientFile(char* filename, InputClient** inputs);
void addClientCredentials(char* id, char *access_token, char* refresh_token, int ttl, ClientCredentials **credentials);
ClientCredentials *getClientCredentials(char *id, ClientCredentials *credentials);