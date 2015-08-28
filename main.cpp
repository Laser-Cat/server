#include "global_all_header.h"
#include"control_socket_server_main.h"
#include"initilalizer.h"
int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    socket_server_main server;

    initilalizer init;

    server.init_loop();

}
