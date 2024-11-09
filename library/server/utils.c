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


int readPermissionsFile(char* filename, Permission** permissions){

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open the file");
    }

    (*permissions) = calloc(100, sizeof(Permission));

    if (*permissions == NULL) {
        perror("Failed to allocate memory for output array");
        fclose(file);
    }


    int index = 0;
    char* line = NULL;
    size_t len;
    while (getline(&line, &len, file) != -1) {

		removeNewline(line);      

        char *token = NULL;
        do{
		
            if(token == NULL)
                token = strtok(line, ",");
            else
                token = strtok(NULL, ",");

            if(token != NULL)
                strcpy((*permissions)[index].file, token);

            token = strtok(NULL, ",");
            if(token != NULL)
                strcpy((*permissions)[index].rights, token);
        
            if(token != NULL)
                index++;

        }while (token != NULL);
        
    }

    fclose(file);

    return index;
}

static int indexGlobalPermissions = 0;
Permission* getNextPossiblePermission(Permission *permissions, int length) {
    
    
    if(indexGlobalPermissions < length){
        Permission *permission = calloc(1, sizeof(Permission));
        memcpy(permission, &(permissions[indexGlobalPermissions]), sizeof(Permission));
        indexGlobalPermissions++;
        return permission;
    }
    
    return NULL;
}