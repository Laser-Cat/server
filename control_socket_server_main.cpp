#include "control_socket_server_main.h"
void socket_server_main::init_loop()
{
    listen(socket_file_descriptor,global_config::MAX_WAITING_QUEUE_LENGTH);
    while(true)
    {
       socklen_t socket_length=sizeof(client_address);
       file_descriptor=accept(socket_file_descriptor,(sockaddr*)&client_address,&socket_length);
       if(file_descriptor==-1)
       {
           string tmp= strerror(errno);
           continue;
       }
       posix_new_session(file_descriptor);
    }
}
void* socket_server_main::posix_session(void *argument)
{
    posix_session_arg_info* real_args=(posix_session_arg_info*)argument;
    session* new_session=new session(session_count++);
    session_count%=global_config::SESSION_LOOP_PEROID;
    new_session->init_session(real_args);
}
socket_server_main::socket_server_main(int port_number):server_base(port_number)
{

}

bool socket_server_main::remove_session()
{

}

socket_server_main::~socket_server_main()
{

}
bool socket_server_main::posix_new_session(int file_descriptor)
{
    posix_session_arg_info* info=new posix_session_arg_info();
    pthread_t t;
    info->file_descriptor=file_descriptor;
    pthread_create(&t,0,posix_session,info);
    return 0;
}
int socket_server_main::session_count=0;
