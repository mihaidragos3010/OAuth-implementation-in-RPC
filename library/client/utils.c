#include "utils.h"

// Function get path of client input filename and create a struct that contains parsed information
// It retunrs number of inputs
int readInputClientFile(char* filename, InputClient** inputs) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open the file");
        return -1;
    }

    (*inputs) = malloc(sizeof(InputClient) * MAX_INPUT_CLIENT_COMMAND);
    if (*inputs == NULL) {
        perror("Failed to allocate memory for output array");
        fclose(file);
        return -1;
    }

    int index = 0;
    char line[MAX_INPUT_COMMAND_LENGTH];
    while (fgets(line, sizeof(line), file)) {

        char *token = strtok(line, ",");
        int len = strlen(token);
        memcpy((*inputs)[index].id, token, len);
        (*inputs)[index].id[len] = '\0';
        

        token = strtok(NULL, ",");
        len = strlen(token);
        memcpy((*inputs)[index].command, token, len);
        (*inputs)[index].command[len] = '\0';
        

        token = strtok(NULL, "\n");
        len = strlen(token);
        memcpy((*inputs)[index].arguments, token, len);
        (*inputs)[index].arguments[len] = '\0';
        
        index++;
    }

    fclose(file);
    return index;
}

void addClientCredentials(char* id, char *access_token, char* refresh_token, int ttl, ClientCredentials **credentials){

    for(int i = 0; i < MAX_CLIENTS_ACCEPTED; i++){

        if(strlen((*credentials)[i].id) == 0){
            strcpy((*credentials)[i].id, id);
            strcpy((*credentials)[i].access_token, access_token);
            strcpy((*credentials)[i].refresh_token, refresh_token);
            (*credentials)[i].ttl = ttl;
            return;
        }

        if(strcmp((*credentials)[i].id, id) == 0){
            strcpy((*credentials)[i].access_token, access_token);
            strcpy((*credentials)[i].refresh_token, refresh_token);
            (*credentials)[i].ttl = ttl;
            return;
        }
    }


}

ClientCredentials *getClientCredentials(char *id, ClientCredentials *credentials){

    for(int i = 0; i < MAX_CLIENTS_ACCEPTED; i++){

        if(strcmp(credentials[i].id, id) == 0){
            return &(credentials[i]);
        }
    }

    ClientCredentials *dummy = calloc(1, sizeof(ClientCredentials));
    strcpy(dummy->id, id);
    memset(dummy->access_token, 0 , TOKEN_SIZE);
    memset(dummy->refresh_token, 0 , TOKEN_SIZE);
    dummy->ttl = 0;

    return dummy;
}