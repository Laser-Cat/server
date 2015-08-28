#include "control_server_base.h"

server_base::server_base(int port_number)
{
    database_argument argument;
    argument.database_type=global_config::DATABASE_ARGUMENT_DATABASE_TYPE;
    argument.database_server_host_name=global_config::DATABASE_ARGUMENT_DATABASE_SERVER_HOST_NAME;
    argument.database_user_name=global_config::DATABASE_ARGUMENT_DATABASE_USER_NAME;
    argument.database_name=global_config::DATABASE_ARGUMENT_DATABASE_NAME;
    argument.database_password=global_config::DATABASE_ARGUMENT_DATABASE_PASSWORD;
    argument.port_number=global_config::DATABASE_ARGUMENT_PORT_NUMBER;
    dao_base::set_connect_factor(argument);
    if(!dao_base::connect_database())
    {
        control_logger::log(global_config::FATAL_ERROR_DATABASE_FAIL);
    }
    socket_file_descriptor=socket(AF_INET,SOCK_STREAM,0);
    int reuse=1;
    if (setsockopt(socket_file_descriptor, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
    {
        char tmp[1000];
        sprintf(tmp,"Reuse port Error : %s\n", strerror(errno));
        control_logger::log(tmp);
    }
    buffer_in=new char[global_config::BUFFER_LENGTH];
    buffer_out=new char[global_config::BUFFER_LENGTH];
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=INADDR_ANY;
    server_address.sin_port=htons(port_number);
    string debug_str;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(bind(socket_file_descriptor,(sockaddr*)&server_address,sizeof(server_address))==-1)
    {
        debug_str=strerror(errno);
    }
}
