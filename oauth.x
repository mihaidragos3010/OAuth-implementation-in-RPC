struct ResponseAuthToken{
    string header<>;
    string auth_token<>;
};

struct ResponseSignedToken{
    string header<>;
    string signed_token<>;
};

struct ResponseBearerToken{
    string header<>;
    string access_token<>;
    string refresh_token<>;
    int ttl;
};

struct ExecuteDatabaseAction{
    string file<>;
    string action<>;
    string access_token<>;
};

struct ResponseDatabaseAction{
    string header<>;
};


program OAUTH_PROG {
    version OAUTH_VERS {
        ResponseAuthToken REQUEST_AUTH_TOKEN(string<>) = 1;
        ResponseSignedToken REQUEST_SIGNED_TOKEN(string<>) = 2;
        ResponseBearerToken REQUEST_BEARER_TOKEN(string<>) = 3;
        ResponseBearerToken REQUEST_NEW_BEARER_TOKEN(string<>) = 4;
        ResponseDatabaseAction EXECUTE_DATABASA_ACTION(ExecuteDatabaseAction) = 5;
    } = 1;
} = 0x23451112;