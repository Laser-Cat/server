#ifndef DAO_BASE_H
#define DAO_BASE_H
#include "global_all_header.h"
class dao_base
{

protected:
    static QSqlDatabase  database;
    static QSqlQuery  query_set;
    static string sql;
    static database_argument arguments;
    static int connection_established;
public:
    static bool get_one_core(const global_base& selector , global_base& target_info);
    static bool update_core(const global_base& selector,global_base& target_info);
    static bool delete_core(const global_base& item_info );
    static bool add_one_core(const global_base& item_info );
    template< typename T>
    static bool get_list_core(const global_base& item_info ,vector<T> &item_info_list)
    {
        string sql;
        sql="";
        sql+="select * from ";
        sql+=item_info.get_table_name();
        sql+=" where 1=1 ";
        const vector<string> *const schema=item_info.get_schema ();
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
        T tmp_info;
        while(query_set.next ())
        {
            for(int i=0;i<schema->size ();i++)
            {
                tmp_info.set_property_with_string (schema->at (i),query_set.value (schema->at (i).c_str ()).toString ().toStdString ());
            }
            item_info_list.push_back (tmp_info);
        }

        return true;
    }

    static bool refresh_connection();
    static bool set_connect_factor(database_argument &arguments);

    static bool connect_database();
    static void exec_sql(vector<string> &dst, const string& src);

};


#endif //DAO_BASE_H
