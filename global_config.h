#ifndef GLoBAL_CONFIG_H
#define GLoBAL_CONFIG_H
#include"stdafx.h"
using namespace std;
class global_config
{
public:
    static int BUFFER_LENGTH;
    static int SERVER_PORT_NUMBER;
    static int MAX_WAITING_QUEUE_LENGTH;
    static int SESSION_LOOP_PEROID;

    static  int MAXIUM_COMMAND_SET_SIZE;

    static string LOG_PREFIX;
    static string LOG_POST_FIX;
    static string FATAL_ERROR_IO_ERROR;
    static string FATAL_ERROR_DATABASE_FAIL;

    static string INFO_INCOMMING_TRASSMISSION;
    static string INFO_SESSION_ENDED;

    static string LOG_EOF;
    static string LOG_DIVISION_PATTERN;

    static string PROTOCOL_ARGS_DELIMITER;
    static string PROTOCOL_COMMAND_DELIMITER;


    static string DATABASE_ARGUMENT_DATABASE_TYPE;
    static string DATABASE_ARGUMENT_DATABASE_DSN;
    static string DATABASE_ARGUMENT_DATABASE_SERVER_HOST_NAME;
    static string DATABASE_ARGUMENT_DATABASE_USER_NAME;
    static string DATABASE_ARGUMENT_DATABASE_NAME;
    static string DATABASE_ARGUMENT_DATABASE_PASSWORD;
    static int DATABASE_ARGUMENT_PORT_NUMBER;

    static string SQL_QUERY_RETURNED_WITH_NO_RESULT;
    static string SQL_QUERY_RESULT_ROW_DELIMITER;
    static string SQL_QUERY_RESULT_COLUMN_DELIMITER;

    static string STRING_NULL_INDICATOR;
    static double DOUBLE_NULL_INDICATOR;
    static  long long LONGLONG_NULL_INDICATOR;
    static int INT_NULL_INDICATOR;

    static int VERIFICATION_CODE_MAX;


    global_config();
};
#endif // GLoBAL_CONFIG_H
