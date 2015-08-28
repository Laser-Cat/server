#include "control_logger.h"

control_logger::control_logger()
{

}



control_logger::~control_logger()
{
    if(file)
    {
        free(file);
        file=0;
    }
}

void control_logger::log(const string &msg)
{
      long long current_time;
     current_time=time(0);
    if(!file)
    {
        string log_file_name=global_config::LOG_PREFIX;
        append_to_string(log_file_name,current_time);
        append_to_string(log_file_name,global_config::LOG_POST_FIX);
        file=fopen(log_file_name.c_str(),"w");
        if(file==NULL)
         {
            alert(global_config::FATAL_ERROR_IO_ERROR.c_str());
            return;
        }
    }
    fprintf(file,global_config::LOG_DIVISION_PATTERN.c_str());
    fprintf(file,"%llu",current_time);
    fprintf(file,global_config::LOG_DIVISION_PATTERN.c_str());
    fprintf(file,msg.c_str());
    fprintf(file,global_config::LOG_EOF.c_str());
    fflush(file);

}
FILE* control_logger::file=NULL;
