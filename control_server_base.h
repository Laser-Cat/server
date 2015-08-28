#ifndef SERVER_BASE_H
#define SERVER_BASE_H
#include"global_all_header.h"
#include"dao_base.h"
class server_base
{

protected:
    sockaddr_in server_address;
    sockaddr_in client_address;
    int socket_file_descriptor;
    int file_descriptor;
    char*buffer_in;
    char*buffer_out;
    int port_number;
public:
    server_base(int port_number);
};
#endif // SERVER_BASE_H
