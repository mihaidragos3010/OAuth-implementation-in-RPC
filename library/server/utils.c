#include "utils.h"

extern User *users;
extern int nrUsers;

extern Permission **permissions;
extern int nrPermissions;

extern char **resourcesFiles;
extern int nrResourcesFiles;

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

        users[index].auth_token = calloc(1, MAX_USED_ID_LENGTH);
        users[index].access_token = calloc(1, MAX_USED_ID_LENGTH);
        users[index].refresh_token = calloc(1, MAX_USED_ID_LENGTH);
        users[index].permissions = calloc(10, sizeof(Permission));
        users[index].ttl = 2;

        fgets(line, sizeof(line), file);
        
        index++;
    }

    fclose(file);
}

void readResourceFiles(char *filename){

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open the file");
        return;
    }

    char line[MAX_RESOURCES_FILE_LENGTH];
    fgets(line, sizeof(line), file);
    nrResourcesFiles = atoi(line);

    resourcesFiles = calloc(nrResourcesFiles, sizeof(char*));

    int index = 0;
    while (fgets(line, sizeof(line), file)) {

        removeNewline(line);
        resourcesFiles[index] = calloc(1, MAX_RESOURCES_FILE_LENGTH);
        strcpy(resourcesFiles[index], line);
        
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

void saveAuthToken(char *id, char *auth_token, bool isAutoRefreshActivated){
    for(int i=0; i<nrUsers; i++){
        if(strcmp(users[i].id, id) == 0){
            strcpy(users[i].auth_token, auth_token);
            users[i].isAutoRefreshActivated = isAutoRefreshActivated;
            // printf("!%s!\n", users[i].auth_token);
        }
    }
}

void saveBearerToken(char *auth_token, char *access_token, char *refresh_token, int ttl, Permission *clientPermissions){
    for(int i=0; i<nrUsers; i++){

        if(strcmp(users[i].auth_token, auth_token) == 0){
            strcpy(users[i].access_token, access_token);
            strcpy(users[i].refresh_token, refresh_token);
            users[i].ttl = ttl;
            users[i].permissions = clientPermissions;
            // printf("!%s!\n", users[i].access_token);
            // printf("!%s!\n", users[i].refresh_token);
            // printf("!%d!\n\n", users[i].ttl);
        }
    }
}

void saveBearerTokenUsingRefreshToken(char *old_refresh_token, char *access_token, char *refresh_token, int ttl){
    for(int i=0; i<nrUsers; i++){
        if(strcmp(users[i].refresh_token, old_refresh_token) == 0){
            strcpy(users[i].access_token, access_token);
            strcpy(users[i].refresh_token, refresh_token);
            users[i].ttl = ttl;
            // printf("!%s!\n", old_refresh_token);
            // printf("!%s!\n", users[i].access_token);
            // printf("!%s!\n", users[i].refresh_token);
            // printf("!%d!\n\n", users[i].ttl);
        }
    }

}

bool isResourcesFile(char *file){
    for(int i = 0; i<nrResourcesFiles; i++){
        if(strcmp(resourcesFiles[i], file) == 0)
            return true;
    }
    return false;
}

bool isAccessTokenRecognized(char *access_token){

    if(strlen(access_token) > 0){
        for(int i=0; i<nrUsers; i++){
            // printf("|%s|\n", users[i].access_token);
            // printf("|%s|\n\n", access_token);
            if(strcmp(users[i].access_token, access_token) == 0)
                return true;
        }
    }
    // printf("\n\n");
    return false;
}

bool isAccessTokenExpired(char *access_token){
    for(int i=0; i<nrUsers; i++){
        if(strcmp(users[i].access_token, access_token) == 0){
            // printf("!%s!\n", users[i].access_token);
            // printf("!%s!\n", users[i].refresh_token);
            // printf("!%d!\n\n", users[i].ttl);
            return users[i].ttl < 0;
        }
    }

    return false;
}

bool isAccessTokenAllowedToExecutThisAction(char *access_token, char *action, char *file){
    
    for(int indexUser = 0; indexUser<nrUsers; indexUser++){
        if(strcmp(users[indexUser].access_token, access_token) == 0){

            int indexPermission = 0;
            for(indexPermission = 0; strcmp(users[indexUser].permissions[indexPermission].file, file) != 0 && indexPermission < 10; indexPermission++);
            printf("!%s!\n", action);
            printf("!%s!\n", access_token);
            printf("!%d!\n", indexPermission);
            printf("!%s!\n", users[indexUser].permissions[indexPermission].file);
            printf("!%s!\n\n", users[indexUser].permissions[indexPermission].rights);

            if(strcmp(action, "READ") == 0 && strchr(users[indexUser].permissions[indexPermission].rights, 'R') != NULL)
                return true;
            
            if(strcmp(action, "INSERT") == 0 && strchr(users[indexUser].permissions[indexPermission].rights, 'I') != NULL){
                printf("ok\n\n\n");
                return true;
            }
            if(strcmp(action, "MODIFY") == 0 && strchr(users[indexUser].permissions[indexPermission].rights, 'M') != NULL)
                return true;

            if(strcmp(action, "DELETE") == 0 && strchr(users[indexUser].permissions[indexPermission].rights, 'D') != NULL)
                return true;

            if(strcmp(action, "EXECUTE") == 0 && strchr(users[indexUser].permissions[indexPermission].rights, 'X') != NULL)
                return true;
            // for(int i = 0; i<strlen(users[indexUser].permissions[indexPermission].rights); i++)
            //     if(strchr(action, users[indexUser].permissions[indexPermission].rights[i]) != NULL)
            //         return true;
        }
    }

    return false;
}

bool isAutoRefreshTokenUser(char *auth_token){
    for(int i=0; i<nrUsers; i++){
        if(strcmp(users[i].auth_token, auth_token) == 0){
            return users[i].isAutoRefreshActivated;
        }
    }

    return false;
}
