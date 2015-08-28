#ifndef SERVER_DATA_TYPE
#define SERVER_DATA_TYPE
#include "stdafx.h"
#include"enums.h"
#include"global_util_all.h"
using namespace std;
struct global_base
{

private:
    map<string,enum_datatype >data_type;
    map<string,int > data_location;
    vector<int *> int_properties;
    vector<string *> string_properties;
    vector<long long * >long_long_properties;
    vector<double *>double_properties;
    string table_name;
    vector<string > schema;


protected:

    void register_property(const string & name,string& data_ref)
    {
        if(data_location.find(name)!=data_location.end())
        {
            return;
        }
        schema.push_back(name);
        data_location[name]=string_properties.size();
        data_type[name]=enum_datatype_string;
        string_properties.push_back(&data_ref);
    }
    void register_property(const string & name,int& data_ref)
    {
        if(data_location.find(name)!=data_location.end())
        {
            return;
        }
        schema.push_back(name);

        data_location[name]=int_properties.size();
        data_type[name]=enum_datatype_int;
        int_properties.push_back(&data_ref);
    }
    void register_property(const string & name,long long& data_ref)
    {
        if(data_location.find(name)!=data_location.end())
        {
            return;
        }
        schema.push_back(name);

        data_location[name]=long_long_properties.size();
        data_type[name]=enum_datatype_long_long;
        long_long_properties.push_back(&data_ref);
    }
    void register_property(const string & name,double& data_ref)
    {
        if(data_location.find(name)!=data_location.end())
        {
            return;
        }
        schema.push_back(name);

        data_location[name]=double_properties.size();
        data_type[name]=enum_datatype_double;
        double_properties.push_back(&data_ref);
    }

    bool get_property(const string & name, string & target) const
    {
        try
        {
           target=*string_properties[data_location.at (name)];
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
    bool get_property(const string & name, int & target)const
    {
        try
        {
           target=*int_properties[data_location.at (name)];
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
    bool get_property(const string & name, double & target)const
    {
        try
        {
           target=*double_properties[data_location.at (name)];
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
    bool get_property(const string & name, long long & target)const
    {
        try
        {
           target=*long_long_properties[data_location.at (name)];
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
    bool set_property(const string & name,const string & value)
    {
        try
        {
           *string_properties[data_location[name]]=value;
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
    bool set_property(const string & name,const int & value)
    {
        try
        {
           *int_properties[data_location[name]]=value;
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
    bool set_property(const string & name,const double & value)
    {
        try
        {
           *double_properties[data_location[name]]=value;
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
    bool set_property(const string & name,const long long & value)
    {
        try
        {
           *long_long_properties[data_location[name]]=value;
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
public:
    global_base()
    {

    }
    global_base(const global_base& stuff)
    {
        assign_with (stuff);
    }
    global_base operator=(const global_base& stuff)
    {
        assign_with (stuff);
        return *this;
    }
    const vector<string >* const get_schema()const
    {
        const vector<string >* const ptr=&schema;
        return ptr;
    }
    void set_table_name(const string &table_name )
    {
        this->table_name= table_name;
    }
    string get_table_name()const
    {
        return table_name;
    }
    bool set_property_with_string(const string & name,const string & value)
    {
        if(data_type.find(name)==data_type.end())
        {
            return false;
        }
        bool result=0;
        switch (data_type[name])
        {
        case enum_datatype_string:
        {
            result=set_property(name,value);
            break;
        }
        case enum_datatype_int:
        {
            int tmp;
            tmp=boost::lexical_cast<int>(value);
            set_property(name,value);
            break;
        }
        case enum_datatype_double:
        {
            double tmp;
            tmp=boost::lexical_cast<double>(value);
            result=set_property(name,value);
            break;
        }
        case enum_datatype_long_long:
        {
            long long tmp;
            tmp=boost::lexical_cast<long long>(value);
            result=set_property(name,value);
            break;
        }
        default:
            break;
        }
        return result;
    }
    bool get_property_as_string(const string &name, string &target) const
    {
        if(data_type.find(name)==data_type.end())
        {
            return false;
        }
        bool result=0;
        switch (data_type.at (name))
        {
        case enum_datatype_string:
        {
            result=get_property(name,target);
            break;
        }
        case enum_datatype_int:
        {
            int tmp;
            result=get_property(name,tmp);
            target=boost::lexical_cast<string>(tmp);
            break;
        }
        case enum_datatype_double:
        {
            double tmp;
            result=get_property(name,tmp);
            target=boost::lexical_cast<string>(tmp);
            break;
        }
        case enum_datatype_long_long:
        {
            long long tmp;
            result=get_property(name,tmp);
            target=boost::lexical_cast<string>(tmp);
            break;
        }
        default:
            break;
        }
        return result;
    }
    bool get_property_as_sql_item(const string &name, string &target) const
    {
        if(data_type.find(name)==data_type.end())
        {
            return false;
        }
        bool result=0;
        switch (data_type.at (name))
        {
        case enum_datatype_string:
        {

            result=get_property(name,target);
            if(is_null(target))
            {
                target="null";
                break;
            }

            target="'"+target;
            target+="'";
            break;
        }
        case enum_datatype_int:
        {
            int tmp;
            result=get_property(name,tmp);
            target=boost::lexical_cast<string>(tmp);
            if(is_null(tmp))
            {
                target="null";
            }
            break;
        }
        case enum_datatype_double:
        {
            double tmp;
            result=get_property(name,tmp);
            target=boost::lexical_cast<string>(tmp);
            if(is_null(tmp))
            {
                target="null";
            }
            break;
        }
        case enum_datatype_long_long:
        {
            long long tmp;
            result=get_property(name,tmp);
            target=boost::lexical_cast<string>(tmp);
            if(is_null(tmp))
            {
                target="null";
            }
            break;
        }
        default:
            break;
        }
        return result;
    }

    bool assign_with( const global_base& b)
    {
        const vector<string >* const
        current_schema= b.get_schema ();
        if(current_schema->size ()!=schema.size ())
        {
            return false;
        }
        for(int i=0;i<schema.size ();i++)
        {
            if((*current_schema)[i]!=schema[i])
            {
                return false;
            }
        }
        for(int i=0;i<schema.size ();i++)
        {
            string tmp_string;
            b.get_property_as_string (schema[i],tmp_string);
            set_property_with_string (schema[i],tmp_string);
        }
    }
    bool get_data_type(const string &name,enum_datatype& type)const
    {
        if(data_type.find (name)==data_type.end ())
        {
            return false;
        }
        type=data_type.at (name);
        return true;

    }
    bool to_json(string& json)const
    {
        boost::property_tree::ptree tree;
        string value;
        for(int i=0;i<schema.size ();i++)
        {
            get_property_as_string (schema[i],value);
            tree.put(schema[i],value);
        }
        ostringstream buf;
        boost::property_tree::write_json(buf, tree,false);
        json = buf.str();
    }
    bool from_json(const string& json)
    {
        boost::property_tree::ptree tree;
        std::istringstream is (json);
        boost::property_tree::read_json (is, tree);
        string value;
        for(int i =0;i<schema.size ();i++)
        {
            tree.get<string>(schema[i],value);
            set_property_with_string (schema[i],value);
        }
    }

    bool set_as_null(const string& name )
    {
        if(data_type.find(name)==data_type.end())
        {
            return false;
        }
        bool result=0;
        switch (data_type.at (name))
        {
        case enum_datatype_string:
        {
            result=set_property(name,global_config::STRING_NULL_INDICATOR);
            break;
        }
        case enum_datatype_int:
        {
            int tmp;
            result=set_property(name,global_config::INT_NULL_INDICATOR);
            break;
        }
        case enum_datatype_double:
        {
            double tmp;
            result=set_property(name,global_config::DOUBLE_NULL_INDICATOR);
            break;
        }
        case enum_datatype_long_long:
        {
            long long tmp;
            result=set_property(name,global_config::LONGLONG_NULL_INDICATOR);
            break;
        }
        default:
            break;
        }
        return result;

    }

    bool to_null()
    {
        for(int i=0;i<schema.size ();i++)
        {
            set_as_null (schema[i]);
        }
    }
};

struct item_info:public global_base
{
    int type_id  ;
    int id  ;
    string description;
    int current_status;
    item_info()
    {
        set_table_name("item");
        register_property("type_id",type_id);
        register_property("id",id);
        register_property("description",description);
        register_property("current_status",current_status);
    }

};

struct data_file_info:public item_info
{
    int current_status  ;
    int type   ;
    string content;
    data_file_info()
    {
            set_table_name("data_file");

//        register_property("current_status",current_status);
        register_property("type",type);
        register_property("content",content);
    }
};
struct user_info:public item_info
{
    //enum_user_status current_status  ;
    string password;
    string phone_number;
    string name;
    string email_address;
    string rank;
    string position;
    user_info()
    {
                set_table_name("user");

//        register_property("current_status",current_status);
        register_property("password",password);
        register_property("phone_number",phone_number);
        register_property("name",name);
        register_property("email_address",email_address);
        register_property("rank",rank);
        register_property("position",position);
    }
};
struct user_group_info:public item_info
{
    //enum_user_group_status current_status  ;

    string name;
    int member_count  ;


    user_group_info()
    {
                set_table_name("user_group");

        register_property("name",name);
        register_property("member_count",member_count);
    }
};
struct seal_info:public item_info
{

    //enum_seal_status current_status  ;
    string seal_type;
    string code;
    seal_info()
    {
                set_table_name("seal");

//        register_property("current_status",current_status);
        register_property("seal_type",seal_type);
        register_property("code",code);
    }
};
struct application_info:public item_info
{
    int current_person_id  ;
    application_info()
    {
                    set_table_name("application");

        register_property("current_person_id",current_person_id);
    }
};

struct contract_applicantion_info:public application_info
{
    //enum_contract_applicantion_status current_status  ;

    int signing_group_id  ;
    int leader_id  ;
    string content ;
    contract_applicantion_info()
    {
        set_table_name("contract_applicantion");
//        register_property("current_status",current_status);
        register_property("signing_group_id",signing_group_id);
        register_property("leader_id",leader_id);
        register_property("content",content);
    }
};
struct seal_applicantion_info:public application_info
{
    //enum_seal_applicantion_status current_status  ;

    int current_person_id  ;
    int applicant_id  ;
    long long application_date;
    int applicant_group_id  ;
    long long confirmation_date;
    int seal_id  ;
    int time_of_stamping  ;
    string seal_for;
    string memo;
    seal_applicantion_info()
    {
        set_table_name("seal_applicantion");
//        register_property("current_status",current_status);
        register_property("current_person_id",current_person_id);
        register_property("applicant_id",applicant_id);
        register_property("application_date",application_date);
        register_property("applicant_group_id",applicant_group_id);
        register_property("confirmation_date",confirmation_date);
        register_property("seal_id",seal_id);
        register_property("time_of_stamping",time_of_stamping);
        register_property("seal_for",seal_for);
        register_property("memo",memo);
    }
};
struct file_applicantion_info:public application_info
{
    //enum_file_applicantion_status current_status  ;

    string receive_id;
    long long receive_date;
    string file_from;
    string incoming_file_id;
    long long incoming_file_date;
    string emergency;
    string deadline;
    string copy_number;
    string distributed_number;
    string content;
    file_applicantion_info()
    {
        set_table_name("file_applicantion");
//        register_property("current_status",current_status);
        register_property("receive_id",receive_id);
        register_property("receive_date",receive_date);
        register_property("file_from",file_from);
        register_property("incoming_file_id",incoming_file_id);
        register_property("incoming_file_date",incoming_file_date);
        register_property("emergency",emergency);
        register_property("deadline",deadline);
        register_property("copy_number",copy_number);
        register_property("distributed_number",distributed_number);
        register_property("content",content);
    }
};
struct leaving_applicantion_info:public application_info
{
    //enum_leaving_applicantion_status current_status  ;

    int type;
    int applicant_id  ;
    long long application_date;
    int applicant_group_id  ;
    string leaving_reason_type;
    string leaving_type;
    string leaving_for;
    long long leaving_on;
    long long leaving_until;
    int leaving_duration  ;
    string leaving_reason;
    int substitute_person_id  ;
    leaving_applicantion_info()
    {
        set_table_name("leaving_applicantion");
//        register_property("current_status",current_status);
        register_property("type",type);
        register_property("applicant_id",applicant_id);
        register_property("application_date",application_date);
        register_property("applicant_group_id",applicant_group_id);
        register_property("leaving_reason_type",leaving_reason_type);
        register_property("leaving_type",leaving_type);
        register_property("leaving_for",leaving_for);
        register_property("leaving_on",leaving_on);
        register_property("leaving_until",leaving_until);
        register_property("leaving_duration",leaving_duration);
        register_property("leaving_reason",leaving_reason);
        register_property("substitute_person_id",substitute_person_id);
    }
};
struct information_info:public item_info
{

};
struct email_info:public item_info
{
    int current_status  ;

    string sender_address;
    string reception_address;
    email_info()
    {
        set_table_name("email");
//        register_property("current_status",current_status);
        register_property("sender_address",sender_address);
        register_property("reception_address",reception_address);
    }
};
struct access_priviledge_info:public global_base
{
    int item_id  ;
    int type_id  ;
    int user_group_id  ;
    access_priviledge_info()
    {
        set_table_name("access_priviledge");
        register_property("item_id",item_id);
        register_property("type_id",type_id);
        register_property("user_group_id",user_group_id);
    }
};
struct user_assigned_item_info:public global_base
{
    int item_id  ;
    int item_type  ;
    int user_id  ;
    string comment;
    user_assigned_item_info()
    {
        set_table_name("user_assigned_item");
        register_property("item_id",item_id);
        register_property("item_type",item_type);
        register_property("user_id",user_id);
        register_property("comment",comment);
    }
};
struct user_done_operation_info:public global_base
{
    int item_id  ;
    int item_type  ;
    int user_id  ;
    int operation_id  ;
    user_done_operation_info()
    {
        set_table_name("user_done_operation");
        register_property("item_id",item_id);
        register_property("item_type",item_type);
        register_property("user_id",user_id);
        register_property("operation_id",operation_id);
    }
};
struct user_belongs_to_user_group_info:public global_base
{
    int user_id  ;
    int user_group_id  ;
    user_belongs_to_user_group_info()
    {
    set_table_name("user_belongs_to_user_group");
        register_property("user_id",user_id);
        register_property("user_group_id",user_group_id);
    }
};
struct database_argument
{
    string database_type;
    string database_server_host_name;
    string database_user_name;
    string database_name;
    string database_password;
    int port_number;


};

#endif // SERVER_DATA_TYPE
