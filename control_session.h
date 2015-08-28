#ifndef SESSION_H
#define SESSION_H
#include"global_all_header.h"
#include"control_logger.h"
#include"control_server_base.h"
#include"command.h"

class session
{
    bool fetch_raw_command();

protected:
    string buffer_queue;
    queue<string> command_queue;

    int eol_count;
    char*buffer_in;
    char*buffer_out;
    int file_descriptor;
    int to_destroy;
    int logged_in;
    int verification_code;
    int all_stopted;
    int session_id;
    command incoming_command;
    user_info agent;

    bool test_priviledge(int user_id,int item_id);

    

    command exec_command(command& cmd);
    command get_group_list();
    command get_group_list_by_user();
    command get_group_detail();
    command add_to_group();
    command remove_from_group();
    command reset_password();
    command unfreeze_user();
    command undo_affair();
    command get_affair_list();
    command get_affair_by_id();
    command start_session();
    command login();
    command alter_tel();
    command create_file_app();
    command create_contract_app();
    command create_seal_app();
    command create_leaving_app();
    command cancel_leaving();
    command get_application_list_by_user();
    command get_apartment_list();
    command approval_application();
    command create_info();
    command assign_info_to_group();
    command get_information_list_by_user_id();
    command get_information_by_id();
    command confirm_information_by_id();
    command add_user();
    command add_user_group();
    command exec_sql();


    typedef command (session::*command_function)()  ;
    command_function *command_socket=new command_function[ global_config::MAXIUM_COMMAND_SET_SIZE];



public:
    bool read_command();
    void command_loop();
    void init_session(posix_session_arg_info *argument);
    void destory_session();

    ~session();
    session(int new_id);
};
#endif // SESSION_H
