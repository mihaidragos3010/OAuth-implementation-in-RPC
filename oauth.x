
struct response{
    string token<>;
};

program OAUTH_PROG {
    version OAUTH_VERS {
        response REQUEST_AUTH_TOKEN(string<>) = 1;
    } = 1;
} = 0x23451112;



