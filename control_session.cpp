#include "control_session.h"
session::session(int new_id)
{
    buffer_in=new char[global_config::BUFFER_LENGTH];
    buffer_out=new char[global_config::BUFFER_LENGTH];
    to_destroy=0;
    all_stopted=0;
    eol_count=0;
    logged_in=0;

    command_socket[enum_query_command_get_group_list]=&session::get_group_list;
    command_socket[enum_query_command_get_group_list_by_user]=&session::get_group_list_by_user;
    command_socket[enum_query_command_get_group_detail]=&session::get_group_detail;
    command_socket[enum_query_command_add_to_group]=&session::add_to_group;
    command_socket[enum_query_command_remove_from_group]=&session::remove_from_group;
    command_socket[enum_query_command_reset_password]=&session::reset_password;
    command_socket[enum_query_command_unfreeze_user]=&session::unfreeze_user;
    command_socket[enum_query_command_undo_affair]=&session::undo_affair;
    command_socket[enum_query_command_get_affair_list]=&session::get_affair_list;
    command_socket[enum_query_command_get_affair_by_id]=&session::get_affair_by_id;
    command_socket[enum_query_command_start_session]=&session::start_session;
    command_socket[enum_query_command_login]=&session::login;
    command_socket[enum_query_command_alter_tel]=&session::alter_tel;
    command_socket[enum_query_command_create_file_app]=&session::create_file_app;
    command_socket[enum_query_command_create_contract_app]=&session::create_contract_app;
    command_socket[enum_query_command_create_seal_app]=&session::create_seal_app;
    command_socket[enum_query_command_create_leaving_app]=&session::create_leaving_app;
    command_socket[enum_query_command_cancel_leaving]=&session::cancel_leaving;
    command_socket[enum_query_command_get_application_list_by_user]=&session::get_application_list_by_user;
    command_socket[enum_query_command_get_apartment_list]=&session::get_apartment_list;
    command_socket[enum_query_command_approval_application]=&session::approval_application;
    command_socket[enum_query_command_create_info]=&session::create_info;
    command_socket[enum_query_command_assign_info_to_group]=&session::assign_info_to_group;
    command_socket[enum_query_command_get_information_list_by_user_id]=&session::get_information_list_by_user_id;
    command_socket[enum_query_command_get_information_by_id]=&session::get_information_by_id;
    command_socket[enum_query_command_confirm_information_by_id]=&session::confirm_information_by_id;
    command_socket[enum_query_command_add_user]=&session::add_user;
    command_socket[enum_query_command_add_user_group]=&session::add_user_group;
    command_socket[enum_query_command_exec_sql]=&session::exec_sql;
}
command session::add_user()
{
     command result;


     return result;
}
command session::add_user_group()
{
     command result;


     return result;
}
command session::exec_sql()
{
     command result;


     return result;
}
bool session::fetch_raw_command()
{
    int  msg_size=recv(file_descriptor,buffer_in,global_config::BUFFER_LENGTH,0);
    if(msg_size<0)
    {
        string err_msg=strerror(errno);
        control_logger::log(err_msg);
        return false;
    }
    if(msg_size==0)
    {
        to_destroy=1;
        return true;
    }
    buffer_queue+=buffer_in;
    vector<string > tmp_cmd_list;
    QString Q_tmps=buffer_queue.c_str ();
    QStringList Q_tmp_list=Q_tmps.split (global_config::PROTOCOL_COMMAND_DELIMITER.c_str ());

    for(int i=0;i<Q_tmp_list.size ();i++)
    {
        tmp_cmd_list.push_back (Q_tmp_list[i].toStdString());
    }

    if(buffer_queue.size()<global_config::PROTOCOL_COMMAND_DELIMITER.size()||
            buffer_queue.substr(buffer_queue.size()-global_config::PROTOCOL_COMMAND_DELIMITER.size())!=global_config::PROTOCOL_COMMAND_DELIMITER)
    {
        buffer_queue=tmp_cmd_list[tmp_cmd_list.size()-1];
        tmp_cmd_list.pop_back();
    }
    buffer_queue.clear();
    for(int i=0;i<tmp_cmd_list.size();i++)
    {
        command_queue.push(tmp_cmd_list[i]);
    }
    return true;
}
bool session::read_command()
{
    memset(buffer_in,0,global_config::BUFFER_LENGTH);
    if(to_destroy)
    {
        return false;
    }

    if(command_queue.empty())
    {
        if(!fetch_raw_command())
        {
            return false;
        }
    }
    while(!command_queue.empty())
    {
        if(incoming_command.from_json(command_queue.front()))
        {
            command_queue.pop();
            return true;
        };
        command_queue.pop();
    }
    return false;

}

void session::command_loop()
{
        while(1)
        {
            while (!read_command())
            {
                if(to_destroy==1)
                {
                    return;
                }
                sleep(1);
            }
            command result= exec_command(incoming_command);
            string result_json;
            result.to_json(result_json);
            result_json+=global_config::PROTOCOL_COMMAND_DELIMITER;
            send(file_descriptor,result_json.c_str(),result_json.size()+1,0);
            sleep(1);
        }
}
void session::init_session(posix_session_arg_info* argument)
{
    control_logger::log(global_config::INFO_INCOMMING_TRASSMISSION);
    this->file_descriptor=argument->file_descriptor;
    command_loop();
    shutdown(file_descriptor,SHUT_RDWR);
    close(file_descriptor);
     control_logger::log(global_config::INFO_SESSION_ENDED);
    all_stopted=1;
}

bool session::test_priviledge (int user_id, int item_id)
{
    bool result=0;

    user_belongs_to_user_group_info groups_selector;
    groups_selector.to_null ();
    groups_selector.user_id=user_id;
    access_priviledge_info previledge;
    vector<user_belongs_to_user_group_info> groups;
    vector<access_priviledge_info>previledges;
    dao_base::get_list_core<user_belongs_to_user_group_info>( groups_selector,groups);
    for(int i=0;i<groups.size ();i++)
    {
        previledge.item_id=item_id;
        previledge.user_group_id=groups[i].user_group_id;
        dao_base::get_list_core<access_priviledge_info>( previledge,previledges);
        if(previledges.size ()>=1)
        {
            return 1;
        }
    }
    return 0;
}
session::~session()
{
    to_destroy=1;
    while(!all_stopted)
    {
    }
    delete buffer_in;
    delete buffer_out;
}
void session::destory_session()
{

}

command session::get_group_list()
{
    command result;
    result.clear();
    group_info tmp_info;
    tmp_info.to_null ();
    vector<group_info> all_groups;
    result.command_action_code=enum_response_command_ack_login;
    if(!logged_in)
    {
        result.abort (enum_status_error_access_denined);
        return result;
    }
    if(!dao_base::get_list_core (tmp_info,all_groups))
    {
        return result;
    }
    result.clear ();
    for(int i=0;i<all_groups.size();i++)
    {    
        string json;
        all_groups[i].to_json (json);
        result.add_argument (json);
    }
    return result;
}
command session::get_group_list_by_user()
{
    command result;
    result.clear();
    group_info tmp_info;
    tmp_info.to_null ();
    user_belongs_to_user_group_info groups_selector;
    groups_selector.to_null ();
    vector<user_belongs_to_user_group_info> groups;
    dao_base::get_list_core<user_belongs_to_user_group_info>( groups_selector,groups);
    result.clear();
    result.command_action_code=enum_response_command_ack_login;


    if(!incoming_command.get_argument (groups_selector.user_id,0))
    {
        result.abort (enum_status_error_command_not_implemented);
        return result;
    };   
    if(!logged_in)
    {
        result.abort (enum_status_error_access_denined);
        return result;
    }

    for(int i=0;i<groups.size ();i++)
    {
	  tmp_info.to_null();
        tmp_info.id=groups[i].group_id;
        dao_base::get_one_core(tmp_info,tmp_info);
	  string json;
        tmp_info.to_json(json);
        result.add_argument(json);
    }
    return result;
}
command session::get_group_detail()
{
    command result;
    


    return result;
}
command session::add_to_group()
{
    command result;
    user_belongs_to_user_group_info target;
    if(!incoming_command.get_argument(target.user_id,0))
    {
        result.abort(0);
    }


    return result;
}
command session::remove_from_group()
{
    command result;
    user_belongs_to_user_group_info selector;
    incoming_command.get_argument(selector.user_id,0);
    if(!incoming_command.get_argument(selector.user_group_id,1))
    {
        result.abort(0);
    }

    return result;
}
command session::reset_password()
{
    command result;
    user_info selector,target;
    if(!incoming_command.get_argument(selector.id,0))
    {
        abort(0);
    }
    dao_base::get_one_core(selector,target);
    target.password="TMP_PASSWORD";
    dao_base::update_core(selector,target);
    result.command_action_code=enum_response_command_ack_query;
    result.add_argument(enum_status_succeeded);
    return result;
}
command session::unfreeze_user()
{
    command result;



    return result;
}
command session::undo_affair()
{
    command result;



    return result;
}
command session::get_affair_list()
{
    command result;



    return result;
}
command session::get_affair_by_id()
{
    command result;

    affair_info tmp_info;
    tmp_info.to_null ();
    int verification_code;
    if(incoming_command.get_argument (tmp_info.id,0))
    {
        result.abort (enum_status_error_command_not_implemented);
        return result;
    };
    result.command_action_code=enum_response_command_ack_login;
    if(!logged_in)
    {
        result.abort (enum_status_error_access_denined);
        return result;
    }
    if(!dao_base::get_one_core (tmp_info,tmp_info))
    {
        result.abort (enum_status_error_password_username_mismatch); 
        return result;
    }
    if(verification_code!=this->verification_code)
    {
        result.abort (enum_status_error_wrong_verification_code);
        return result;
    }
    logged_in=1;
    result.clear ();
    string json;
    tmp_info.to_json (json);
    result.add_argument (json);

    return result;
}
command session::start_session()
{
    command result;
    verification_code=rand()%global_config::VERIFICATION_CODE_MAX;
    result.clear ();
    result.command_action_code =enum_response_command_ack_start_session;
    result.add_argument (session_id);
    result.add_argument (verification_code);
    return result;
}
command session::login()
{
    command result;
    user_info tmp_info;
    vector<user_info> users;
    tmp_info.to_null ();
    int verification_code;
    incoming_command.get_argument (tmp_info.id,0);
    incoming_command.get_argument (tmp_info.password,1);

    if(!incoming_command.get_argument (verification_code,2))
    {
        result.abort (enum_status_error_command_not_implemented);
        return result;
    };
    result.command_action_code=enum_response_command_ack_login;
    if(logged_in)
    {
        result.abort (enum_status_error_repetitive_operation);
        verification_code=rand ()%global_config::VERIFICATION_CODE_MAX;
        return result;
    }
    if(!dao_base::get_one_core (tmp_info,agent))
    {
        result.abort (enum_status_error_password_username_mismatch);
        verification_code=rand ()%global_config::VERIFICATION_CODE_MAX;

        return result;
    }

    if(verification_code!=this->verification_code)
    {
        result.abort (enum_status_error_wrong_verification_code);
        verification_code=rand ()%global_config::VERIFICATION_CODE_MAX;
        return result;
    }
    logged_in=1;
    result.clear ();
    string json;
    agent=users[0];
    agent.to_json (json);
    result.add_argument (json);
    return result;

}
command session::alter_tel()
{
    command result;



    return result;
}
command session::create_file_app()
{
    command result;



    return result;
}
command session::create_contract_app()
{
    command result;



    return result;
}
command session::create_seal_app()
{
    command result;



    return result;
}
command session::create_leaving_app()
{
    command result;



    return result;
}
command session::cancel_leaving()
{
    command result;



    return result;
}
command session::get_application_list_by_user()
{
    command result;


    return result;
}
command session::get_apartment_list()
{
    command result;



    return result;
}
command session::approval_application()
{
    command result;



    return result;
}
command session::create_info()
{
    command result;



    return result;
}
command session::assign_info_to_group()
{
    command result;



    return result;
}
command session::get_information_list_by_user_id()
{
    command result;
    int user_id;
    if(!incoming_command.get_argument(0,user_id))
    {
        result.abort(0);
        return result;
    }
    vector<information_info> info_list;
    information_info selector;
    information_info target;

    vector<user_assigned_item_info> selector_list;
    user_assigned_item_info tmp_selector;
    tmp_selector.to_null();
    tmp_selector.user_id=id;
    tmp_selector.item_type=id_information;
    dao_base::get_list_core<user_assigned_item_info>(tmp_selector,selector_list);
    selector.to_null();

    for(int i=0;i<selector_list.size();i++)
    {
        selector.id=selector_list[i].item_id;
        dao_base::get_one_core(selector,target);
        string json;
        target.to_json(json);
        result.add_argument(json);
    }
    return result;
}
command session::get_information_by_id()
{
    command result;
    information_info tmp_info;
    tmp_info.to_null ();
    int verification_code;
    if(incoming_command.get_argument (tmp_info.id,0))
    {
        result.abort (enum_status_error_command_not_implemented);
        return result;
    };
    result.command_action_code=enum_response_command_ack_login;
    if(!logged_in)
    {
        result.abort (enum_status_error_access_denined);
        return result;
    }
    if(!dao_base::get_one_core (tmp_info,tmp_info))
    {
        result.abort (enum_status_error_password_username_mismatch); 
        return result;
    }
    if(verification_code!=this->verification_code)
    {
        result.abort (enum_status_error_wrong_verification_code);
        return result;
    }
    logged_in=1;
    result.clear ();
    string json;
    tmp_info.to_json (json);
    result.add_argument (json);
    return result;
}
command session::confirm_information_by_id()
{
    command result;



    return result;
}
command session::exec_command(command &cmd)
{
    command result;
    if(cmd.command_action_code<0||cmd.command_action_code>=global_config::MAXIUM_COMMAND_SET_SIZE)
    {
        result.command_action_code=enum_response_command_ack_bad_request;
        result.clear ();
        result.add_argument ("0");
        return result;

    }
    if(command_socket[cmd.command_action_code]==NULL)
    {
        result.command_action_code=enum_response_command_ack_bad_request;
        result.clear ();
        result.add_argument ("0");
        return result;
    }
    result=(this->*command_socket[cmd.command_action_code])();


    return result;
}
