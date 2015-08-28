#include"dao_base.h"

QSqlDatabase dao_base::database;
QSqlQuery dao_base::query_set;
string dao_base::sql;
database_argument dao_base::arguments;
int dao_base::connection_established;
bool dao_base::get_one_core(const global_base& selector,global_base& target_info)
{
    vector<global_base> vec;
    string sql;
    sql="";
    sql+="select * from ";
    sql+=target_info.get_table_name();
    sql+=" where 1=1 ";
    const vector<string> *const schema=target_info.get_schema ();
    for(int i=0;i<schema->size ();i++)
    {
        string value;
        selector.get_property_as_sql_item (schema->at (i),value);
        if(value=="null")
        {
            continue;
        }
        sql+=" and ";
        sql+=schema->at (i);
        sql+=" = ";
        sql+=value;
    }
    qDebug()<<sql.c_str ()<<"\n";
    query_set.exec (sql.c_str());
    if(query_set.next ())
    {
        for(int i=0;i<schema->size ();i++)
        {
            target_info.set_property_with_string (schema->at (i),query_set.value (schema->at (i).c_str ()).toString ().toStdString ());
        }
    }

    else
    {
        return false;
    }
    return true;
}
bool dao_base::update_core(const global_base &selector, global_base &target_info )
{
    dao_base::delete_core (selector);
    dao_base::add_one_core (target_info);
    return true;
}
bool dao_base::delete_core(const global_base&  item_info )
{

    sql="";
    sql+="delete from ";
    sql+=item_info.get_table_name();
    sql+=" where 1=1 ";
    const vector<string> *const  schema=item_info.get_schema ();
    for(int i=0;i<schema->size ();i++)
    {
        string value;
        item_info.get_property_as_sql_item (schema->at (i),value);
        if(value=="null")
        {
            continue;
        }
        sql+=" and ";
        sql+=schema->at (i);
        sql+=" = ";
        sql+=value;
    }
    qDebug()<<sql.c_str ()<<"\n";
    query_set.exec (sql.c_str());

    return true;
}
bool dao_base::add_one_core(const global_base &item_info )
{

    sql="";
    sql+="insert into ";
    sql+=item_info.get_table_name();
    sql+="(";
    const vector<string> *const  schema=item_info.get_schema ();
    int flag=0;

    for(int i=0;i<schema->size ();i++)
    {
        string value;
        item_info.get_property_as_sql_item (schema->at (i),value);
        if(value=="null")
        {
            continue;
        }
        if(flag)
        {
            sql+=",";
        }
        flag=1;
        sql+=schema->at (i);
    }
    sql+=")values (";
    flag=0;
    for(int i=0;i<schema->size ();i++)
    {
        string value;
        item_info.get_property_as_sql_item (schema->at (i),value);
        if(value=="null")
        {
            continue;
        }
        if(flag)
        {
            sql+=",";
        }
        flag=1;
        sql+=value;
    }
    sql+=")";
    qDebug()<<sql.c_str ()<<"\n";
    query_set.exec (sql.c_str());
}


bool dao_base::refresh_connection() {
}

bool dao_base::set_connect_factor(database_argument &arguments) 
{
    dao_base::arguments=arguments;
}

bool dao_base::connect_database()
{
    database=QSqlDatabase::addDatabase(arguments.database_type.c_str());
    database.setUserName(arguments.database_user_name.c_str());
    database.setHostName(arguments.database_server_host_name.c_str());
    database.setPassword(arguments.database_password.c_str());
    database.setDatabaseName(arguments.database_name.c_str());
    database.setPort(arguments.port_number);

    if(database.open())
    {
         connection_established=1;
         query_set=QSqlQuery(database);
         return 1;
    }
    control_logger::log(global_config::FATAL_ERROR_DATABASE_FAIL);
    return 0;
}
void dao_base::exec_sql( vector<string>& dst, const string& src)
{
    dst.clear();
    query_set.exec(src.c_str());
    string str;
    while(query_set.next())
      {
        for(int i=0;i<query_set.record().count();i++)
          {
            str=query_set.value(i).toString().toStdString();
            append_to_string(str,global_config::SQL_QUERY_RESULT_COLUMN_DELIMITER);
            dst.push_back(str);
          }
      }

}
