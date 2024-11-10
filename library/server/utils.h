#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_USED_ID_LENGTH 16

#define MAX_RIGHTS 5
#define MAX_FILE_LENGTH 30 
#define MAX_PERMISSIONS 100

#define TOKEN_LEN 15

typedef struct {
    char file[MAX_FILE_LENGTH];
    char rights[MAX_RIGHTS + 1];
} Permission;

typedef struct {
    char *id;
    char *access_token;
    char *refresh_token;
    int ttl;
    Permission *permissions;
} User;


void readUsersAllowed(char* filename);
void removeNewline(char* str);
void readPermissionsFile(char* filename);

Permission* getNextPossiblePermission();
char* appendAuthTokenAndClientPermissions(char *auth_token, Permission *clientPermissions);
void generateSecretKey();
char* encrypt(char* data);
char* decrypt(char* data);
int getAuthTokenAndClientPermissions(char *unsigned_token, char** auth_token, Permission **clientPermissions);
bool isIdAllowed(char* idClient);
bool isAcceptedByUsed(Permission* clientPermissions);