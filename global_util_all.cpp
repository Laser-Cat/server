#include "global_util_all.h"
void append_to_string(string& s,const int t)
{
    char buffer[SMALL_BUFFER_SIZE];
    sprintf(buffer,"%d",t);
    s+=buffer;
}
void append_to_string(string& s, const long long t)
{
    char buffer[SMALL_BUFFER_SIZE];
    sprintf(buffer,"%llu",t);
    s+=buffer;
}
void append_to_string(string& s,const char* t)
{
    s+=t;
}
void append_to_string(string& s,const string& t)
{
    s+=t;
}
void append_to_string(string& s,const double t)
{
    char buffer[SMALL_BUFFER_SIZE];
    sprintf(buffer,"%lf",t);
    s+=buffer;
}
void append_to_sql(string& s,const int t)
{
    char buffer[SMALL_BUFFER_SIZE];
    sprintf(buffer,"%d",t);
    s+=buffer;
    s+=",";
}
void append_to_sql(string& s, const long long t)
{
    char buffer[SMALL_BUFFER_SIZE];
    sprintf(buffer,"%llu",t);
    s+=buffer;
    s+=",";
}
void append_to_sql(string& s,const char* t)
{

  s+="'";
    s+=t;

    s+="'";
    s+=",";
}
void append_to_sql(string& s,const string& t)
{

  s+="'";
    s+=t;

    s+="'";
    s+=",";
}
void append_null_to_sql(string &s)
{
    s+="NULL";
    s+=",";
}
void append_to_sql(string& s,const double t)
{
    char buffer[SMALL_BUFFER_SIZE];
    sprintf(buffer,"%lf",t);
    s+=buffer;
    s+=",";
}
string to_sql_time_format (const time_t the_time)
{
        string str;
        tm* time_struct;
        time_struct=localtime(&the_time);
        if(!time_struct)
          {
            return "1900 00 00 12:00:00";
          }
        char buff[BIG_BUFFER_SIZE];
        strftime(buff,BIG_BUFFER_SIZE-1,"%Y %m %d %H:%M:%S",time_struct);

        str=buff;
     //   free( time_struct);
        return str;
}
time_t from_sql_time_format(const string& string_time)
{
    tm time_struct;
    QDateTime time_converter;
    time_converter.fromString(string_time.c_str(),"%Y %m %d %H:%M:%S");
    return time_converter.toTime_t();

}

void debug(const string &str)
{
  QLineEdit* edit=new QLineEdit;
  edit->setText(str.c_str());
  edit->show();
}
void get_screen_factor ()
{
  //  QScreen* scr=new QScreen();
   // SCREEN_DPI_FACTOR=scr.physicalDotsPerInch ();
  //  SCREEN_DPI_FACTOR/=100;
}
bool is_null(const int& value)
{
    return value==global_config::INT_NULL_INDICATOR;
}
bool is_null(const long long& value)
{
    return value==global_config::LONGLONG_NULL_INDICATOR;
}

bool is_null(const string& value)
{
    return value==global_config::STRING_NULL_INDICATOR;
}

bool is_null(const double& value)
{
    return value==global_config::DOUBLE_NULL_INDICATOR;
}

