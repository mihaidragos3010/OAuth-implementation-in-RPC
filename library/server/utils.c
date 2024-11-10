#include "utils.h"

extern User *users;
extern int nrUsers;

extern Permission **permissions;
extern int nrPermissions;

void readUsersAllowed(char* filename) {

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open the file");
        return;
    }

    char line[MAX_USED_ID_LENGTH];
    fgets(line, sizeof(line), file);
    nrUsers = atoi(line);

    users = calloc(nrUsers, sizeof(User));

    int index = 0;
    while (fgets(line, sizeof(line), file)) {

        users[index].id = calloc(1, MAX_USED_ID_LENGTH);
        memcpy(users[index].id, line, MAX_USED_ID_LENGTH-1);
        users[index].id[MAX_USED_ID_LENGTH - 1] = '\0';

        users[index].access_token = calloc(1, MAX_USED_ID_LENGTH);
        users[index].refresh_token = calloc(1, MAX_USED_ID_LENGTH);
        users[index].permissions = calloc(10, sizeof(Permission));
        
        fgets(line, sizeof(line), file);
        
        index++;
    }

    fclose(file);
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


void readPermissionsFile(char* filename){

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open the file");
    }

    permissions = calloc(10, sizeof(Permission**));

    if (permissions == NULL) {
        perror("Failed to allocate memory for output array");
        fclose(file);
    }


    int row = 0;
    char* line = NULL;
    size_t len;
    while (getline(&line, &len, file) != -1) {

		removeNewline(line);

        int column = 0;
        permissions[row] = calloc(10, sizeof(Permission));
        

        char *token = NULL;
        do{
		
            if(token == NULL)
                token = strtok(line, ",");
            else
                token = strtok(NULL, ",");

            if(token != NULL)
                strcpy(permissions[row][column].file, token);

            token = strtok(NULL, ",");
            if(token != NULL)
                strcpy(permissions[row][column].rights, token);

            column++;

        }while (token != NULL);
        
        row++;
    }

    nrPermissions = row;

    fclose(file);
}

static int indexGlobalPermissions = 0;
Permission* getNextPossiblePermission() {
    
    if(indexGlobalPermissions < nrPermissions){
        return permissions[indexGlobalPermissions++];
    }
    
    return NULL;
}

char* appendAuthTokenAndClientPermissions(char *auth_token, Permission *clientPermissions){

    char *result = calloc(1, sizeof(auth_token) + 10 * sizeof(Permission));

    memcpy(result, auth_token, 15);

    int i = 0;
    while(clientPermissions != NULL 
        && strlen(clientPermissions[i].file) > 0 
        && strlen(clientPermissions[i].rights) > 0){
        
        sprintf(result, "%s,%s,%s",result,clientPermissions[i].file, clientPermissions[i].rights);

        i++;
    }

    return result;
}


static int key;
void generateSecretKey(){
    key = 15;
}

char* encrypt(char* data){


    for(int i = 0; i < strlen(data); i++){
        data[i] += key;
    }

    return data;
}

char* decrypt(char* data){

    for(int i = 0; i < strlen(data); i++){
         data[i] -= key;
    }

    return data;
}

int getAuthTokenAndClientPermissions(char *unsigned_token, char** auth_token, Permission **clientPermissions){

    char *token = strtok(unsigned_token, ",");
    (*auth_token) = calloc(1, TOKEN_LEN + 1);
    memcpy((*auth_token), token, TOKEN_LEN);

    (*clientPermissions) = calloc(10, sizeof(Permission));

    int index = 0;
    do{
        token = strtok(NULL, ",");
        if(token != NULL)
            strcpy((*clientPermissions)[index].file, token);

        token = strtok(NULL, ",");
        if(token != NULL)
            strcpy((*clientPermissions)[index].rights, token);
        
        index++;
    }
    while(token != NULL);

    return index - 1;
}

bool isIdAllowed(char* idClient){

    for(int i=0; i < nrUsers; i++)
        if(strcmp(idClient, users[i].id) == 0)
            return true;

    return false;
}

bool isAcceptedByUsed(Permission* clientPermissions){

    return strcmp(clientPermissions[0].file, "*") != 0 
        || strcmp(clientPermissions[0].rights, "-") != 0;
}