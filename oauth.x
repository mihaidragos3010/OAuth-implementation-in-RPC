

program OAUTH_PROG {
    version OAUTH_VERS {
        ResponseAuthToken REQUEST_AUTH_TOKEN(string<>) = 1;
        ResponseSignedToken REQUEST_SIGNED_TOKEN(string<>) = 2;
        ResponseBearerToken REQUEST_BEARER_TOKEN(string<>) = 3;
    } = 1;
} = 0x23451112;


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