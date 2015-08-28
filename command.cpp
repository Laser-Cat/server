#include "command.h"
command::command()
{
    command_action_code=enum_status_error_command_not_implemented;
    arguments.clear();
}

command::~command() {
}

bool command::from_json(const string& json)
{
    clear();
    QString tmp=json.c_str ();
    QStringList t=tmp.split (global_config::PROTOCOL_ARGS_DELIMITER.c_str ());
    for(int i=0;i<t.size ();i++)
    {
        add_argument (t[i].toStdString());
    }
    try
    {
        command_action_code=boost::lexical_cast<int >(arguments[0]);
    }
    catch(const boost::bad_lexical_cast &)
    {
        return false;
    }
    return true;
}

bool command::to_json(string& json)
{
    json.clear();
    stringstream sout;
    sout<<command_action_code<<global_config::PROTOCOL_ARGS_DELIMITER<<arguments.size();
    for(int i=0;i<arguments.size();i++)
    {
        sout<<global_config::PROTOCOL_ARGS_DELIMITER<<arguments[i];
    }
    json=sout.str();
}

bool command::add_argument(const int &argument)
{
    string tmp_string;
    append_to_string(tmp_string,argument);
    arguments.push_back(tmp_string);
    return true;

}

bool command::add_argument(const string &argument)
{
    arguments.push_back(argument);
    return true;

}

bool command::add_argument(const  long long &argument)
{
    string tmp_string;
    append_to_string(tmp_string,argument);
    arguments.push_back(tmp_string);
    return true;

}

bool command::add_argument(const double &argument)
{
    string tmp_string;
    append_to_string( tmp_string,argument);
    arguments.push_back(tmp_string);
    return true;

}
bool command::clear ()
{
    arguments.clear ();
    return true;

}

bool command::get_argument(int &target, int id_seq)
{
    try
    {
        id_seq+=2;
        if(id_seq<2)
        {
            return false;
        }
        target=boost::lexical_cast<int >(arguments[id_seq]);
    }
    catch(...)
    {
        return false;
    }
    return true;
}
bool command::get_argument(double &target, int id_seq)
{
    try
    {
        id_seq+=2;
        if(id_seq<2)
        {
            return false;
        }
        if(id_seq>arguments.size ())
        {
            return false;
        }
        target=boost::lexical_cast<double >(arguments[id_seq]);
    }
    catch(...)
    {
        return false;
    }
    return true;
}
bool command::get_argument(string &target, int id_seq)
{
    try
    {
        id_seq+=2;
        if(id_seq<2)
        {
            return false;
        }
        target=boost::lexical_cast<string >(arguments[id_seq]);
    }
    catch(...)
    {
        return false;
    }
    return true;
}
bool command::get_argument(long long &target, int id_seq)
{
    try
    {
        id_seq+=2;
        if(id_seq<2)
        {
            return false;
        }
        target=boost::lexical_cast<long long  >(arguments[id_seq]);
    }
    catch(...)
    {
        return false;
    }
    return true;
}
void command::abort (int error_code)
{
    arguments.clear ();
    add_argument (error_code);
}
