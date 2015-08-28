#ifndef CONTROL_LOGGER_H
#define CONTROL_LOGGER_H
#include"stdafx.h"
#include"global_util_all.h"
#include"global_config.h"
#include"view_global_util_alert.h"
using namespace std;
class control_logger
{

public:
    static FILE* file;
    static void log(const string & msg);
    control_logger();
    ~control_logger();
};

#endif // CONTROL_LOGGER_H
