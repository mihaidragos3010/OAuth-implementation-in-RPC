#include "utils.h"


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
    return index;  // Return the number of successfully read input clients
}