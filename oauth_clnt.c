/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "oauth.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

ResponseAuthToken *
request_auth_token_1(char **argp, CLIENT *clnt)
{
	static ResponseAuthToken clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, REQUEST_AUTH_TOKEN,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_ResponseAuthToken, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

ResponseSignedToken *
request_signed_token_1(char **argp, CLIENT *clnt)
{
	static ResponseSignedToken clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, REQUEST_SIGNED_TOKEN,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_ResponseSignedToken, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

ResponseBearerToken *
request_bearer_token_1(char **argp, CLIENT *clnt)
{
	static ResponseBearerToken clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, REQUEST_BEARER_TOKEN,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_ResponseBearerToken, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

ResponseBearerToken *
request_new_bearer_token_1(char **argp, CLIENT *clnt)
{
	static ResponseBearerToken clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, REQUEST_NEW_BEARER_TOKEN,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_ResponseBearerToken, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

ResponseDatabaseAction *
execute_databasa_action_1(ExecuteDatabaseAction *argp, CLIENT *clnt)
{
	static ResponseDatabaseAction clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, EXECUTE_DATABASA_ACTION,
		(xdrproc_t) xdr_ExecuteDatabaseAction, (caddr_t) argp,
		(xdrproc_t) xdr_ResponseDatabaseAction, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
