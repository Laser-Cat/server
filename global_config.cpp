#include "global_config.h"
global_config::global_config()
{
}
int global_config::BUFFER_LENGTH=1024;
int global_config::SERVER_PORT_NUMBER=4869;
int global_config::MAX_WAITING_QUEUE_LENGTH =10;
int global_config::SESSION_LOOP_PEROID =2147483600;

int global_config::MAXIUM_COMMAND_SET_SIZE=100;


string global_config::LOG_PREFIX="log_";
string global_config::LOG_POST_FIX=".html";


string global_config::FATAL_ERROR_IO_ERROR="FATAL IO ERROR";
string global_config::FATAL_ERROR_DATABASE_FAIL="FATAL cannot connect database";


string global_config::INFO_INCOMMING_TRASSMISSION="Incoming transmission...";
string global_config::INFO_SESSION_ENDED="SESSION ENDED";


string global_config::LOG_EOF="<br></br>";
string global_config::LOG_DIVISION_PATTERN="&nbsp;---&nbsp;";

string global_config::PROTOCOL_ARGS_DELIMITER="##";
string global_config::PROTOCOL_COMMAND_DELIMITER="\r\n";

string global_config::DATABASE_ARGUMENT_DATABASE_TYPE="QMYSQL";
string global_config::DATABASE_ARGUMENT_DATABASE_SERVER_HOST_NAME="localhost";
string global_config::DATABASE_ARGUMENT_DATABASE_USER_NAME="lasercat";
string global_config::DATABASE_ARGUMENT_DATABASE_NAME="oa_database";
string global_config::DATABASE_ARGUMENT_DATABASE_PASSWORD="meowing007";
int global_config::DATABASE_ARGUMENT_PORT_NUMBER=3306;

string global_config::SQL_QUERY_RETURNED_WITH_NO_RESULT="empty set ^_^";
string global_config::SQL_QUERY_RESULT_ROW_DELIMITER="<br></br>";
string global_config::SQL_QUERY_RESULT_COLUMN_DELIMITER="##";


string  global_config:: STRING_NULL_INDICATOR="NULL";
double global_config:: DOUBLE_NULL_INDICATOR=-1e30;
long long global_config:: LONGLONG_NULL_INDICATOR=-(1LL<<61);
int global_config:: INT_NULL_INDICATOR=-(1<<29);

 int global_config::VERIFICATION_CODE_MAX=10000;
