#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_USERS 100
#define MAX_USED_ID_LENGTH 16

#define MAX_RIGHTS 5
#define MAX_FILE_LENGTH 30 
#define MAX_PERMISSIONS 100

typedef struct {
    char file[MAX_FILE_LENGTH];
    char rights[MAX_RIGHTS + 1];
} Permission;


int readUsersAllowed(char* filename, char*** users);

void removeNewline(char* str);
int readPermissionsFile(char* filename, Permission*** permissions);
Permission* getNextPossiblePermission(Permission **permissions, int length);