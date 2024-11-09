#include "utils.h"


int readUsersAllowed(char* filename, char*** users) {

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open the file");
        return -1;
    }

    char line[MAX_USED_ID_LENGTH];
    fgets(line, sizeof(line), file);
    int nrUsers = atoi(line);

    (*users) = calloc(nrUsers, sizeof(char*));

    int index = 0;
    while (fgets(line, sizeof(line), file)) {

        (*users)[index] = calloc(1, MAX_USED_ID_LENGTH);
        memcpy((*users)[index], line, MAX_USED_ID_LENGTH-1);
        (*users)[index][MAX_USED_ID_LENGTH - 1] = '\0';

        fgets(line, sizeof(line), file);
        
        index++;
    }

    fclose(file);

    return nrUsers;
}

void removeNewline(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != '\n') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}


int readPermissionsFile(char* filename, Permission*** permissions){

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open the file");
    }

    (*permissions) = calloc(10, sizeof(Permission**));

    if (*permissions == NULL) {
        perror("Failed to allocate memory for output array");
        fclose(file);
    }


    int row = 0;
    char* line = NULL;
    size_t len;
    while (getline(&line, &len, file) != -1) {

		removeNewline(line);

        int column = 0;
        (*permissions)[row] = calloc(10, sizeof(Permission));
        

        char *token = NULL;
        do{
		
            if(token == NULL)
                token = strtok(line, ",");
            else
                token = strtok(NULL, ",");

            if(token != NULL)
                strcpy((*permissions)[row][column].file, token);

            token = strtok(NULL, ",");
            if(token != NULL)
                strcpy((*permissions)[row][column].rights, token);

            column++;

        }while (token != NULL);
        
        row++;
    }

    fclose(file);

    return row;
}

static int indexGlobalPermissions = 0;
Permission* getNextPossiblePermission(Permission **permissions, int length) {
    
    if(indexGlobalPermissions < length){
        return permissions[indexGlobalPermissions++];
    }
    
    return NULL;
}

