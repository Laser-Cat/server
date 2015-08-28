#ifndef GLOBAL_UTIL_ALL
#define GLOBAL_UTIL_ALL
#include<string>
#include"stdafx.h"
#include"QLineEdit"
#include"stdio.h"
#include<time.h>
#include<ctime>
#include<QScreen>
#include<QDateTime>
#include"global_config.h"

using namespace std;

const int  SMALL_BUFFER_SIZE =1000;
const int  MIDDLE_BUFFER_SIZE =1000;
const int  BIG_BUFFER_SIZE =1000;


void debug(const string &str);

void append_to_string(string& s,const int t);
void append_to_string(string& s, const long long t);
void append_to_string(string& s,const char* t);
void append_to_string(string& s,const string& t);
void append_to_string(string& s,const double t);
void append_to_sql(string& s,const int t);
void append_to_sql(string& s, const long long t);
void append_to_sql(string& s,const char* t);
void append_to_sql(string& s,const string& t);
void append_null_to_sql(string &s);
void append_to_sql(string& s,const double t);
bool is_null(const int& value);
bool is_null(const long long& value);
bool is_null(const string& value);
bool is_null(const double& value);


void get_screen_factor();
QString get_resonable_font_size(int length,int h_size,int v_size);

string to_sql_time_format(time_t time);
time_t from_sql_time_format(const string& string_time);


#endif // GLOBAL_UTIL_ALL

