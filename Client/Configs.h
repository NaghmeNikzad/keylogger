#ifndef CONFIGS_HEADER
#define CONFIGS_HEADER


/** SERVER CONFIGS **/

#define SERVER_IP_ADDRESS "127.0.0.1"

#define SERVER_CONECCTION_PORT "8080"

/** VICTIM CONFIGS **/

#define CONNECTION_CHECKING_INTERVAL 10 * 1000 // in miliseconds

#define CONECTING_RETRY_DELAY 10 // in miliseconds

#define MINIMUM_SENDING_CAPTURED_LENGTH 10 // when captured  data length is lower than this size client should not send it

#endif