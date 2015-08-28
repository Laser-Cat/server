#include"view_global_util_alert.h"
void alert(const char* str)
{
    static QLineEdit* alert_window=0;
    if(!alert_window)
    {
        alert_window=new QLineEdit;
    }
    alert_window->setMinimumSize (500,0);

    alert_window->setWindowTitle (str);
    alert_window->setText (str);
    alert_window->show ();

}
