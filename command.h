#ifndef COMMAND_H
#define COMMAND_H
#include "global_all_header.h"
class command
{
protected:
    vector<string> arguments;
public:
    int command_action_code;
    command() ;
    ~command();
    bool from_json(const string& json);
    bool to_json(string& json);
    bool clear();
    bool add_argument(const int & argument);
    bool add_argument(const double & argument);
    bool add_argument(const  long long & argument);
    bool add_argument(const string & argument);
    bool get_argument(int &target,const int id_seq);
    bool get_argument(double &target,const int id_seq);
    bool get_argument(string &target,const int id_seq);
    bool get_argument(long long &target,const int id_seq);
    void abort(int error_code);


};
#endif
