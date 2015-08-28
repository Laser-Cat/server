#ifndef ENUMS
#define ENUMS
enum enum_datatype
{
    enum_datatype_int,
    enum_datatype_string,
    enum_datatype_double,
    enum_datatype_long_long

};

enum enum_server_command_action
{
    enum_response_command_ack_group_list,
    enum_response_command_ack_group_infotatus,
    enum_response_command_ack_query,
    enum_response_command_ack_affair_list,
    enum_response_command_ack_affair,
    enum_response_command_ack_start_session,
    enum_response_command_ack_login,
    enum_response_command_ack_information_list,
    enum_response_command_ack_information,
    enum_response_command_ack_bad_request

};
enum enum_client_command_action
{
    enum_query_command_get_group_list,
    enum_query_command_get_group_list_by_user,
    enum_query_command_get_group_detail,
    enum_query_command_add_to_group,
    enum_query_command_remove_from_group,
    enum_query_command_reset_password,
    enum_query_command_unfreeze_user,
    enum_query_command_undo_affair,
    enum_query_command_get_affair_list,
    enum_query_command_get_affair_by_id,
    enum_query_command_start_session,
    enum_query_command_login,
    enum_query_command_alter_tel,
    enum_query_command_create_file_app,
    enum_query_command_create_contract_app,
    enum_query_command_create_seal_app,
    enum_query_command_create_leaving_app,
    enum_query_command_cancel_leaving,
    enum_query_command_get_application_list_by_user,
    enum_query_command_get_apartment_list,
    enum_query_command_approval_application,
    enum_query_command_create_info,
    enum_query_command_assign_info_to_group,
    enum_query_command_get_information_list_by_user_id,
    enum_query_command_get_information_by_id,
    enum_query_command_confirm_information_by_id,
///////////////////////////////////////////////////////////////////////////
///// client irrelevant commands///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
    enum_query_command_add_user,
    enum_query_command_add_user_group,
    enum_query_command_exec_sql
};
enum status_value
{
    enum_status_succeeded,
    enum_status_error_no_such_user,
    enum_status_error_no_such_applicant,
    enum_status_error_repetitive_operation,
    enum_status_error_access_denined,
    enum_status_error_already_exist,
    enum_status_error_wrong_verification_code,
    enum_status_error_password_username_mismatch,
    enum_status_error_frozen_user,
    enum_status_error_command_not_implemented,
};


enum enum_type_id
{
    id_data_file,
    id_user,
    id_user_group,
    id_seal,
    id_contract_applicantion,
    id_seal_applicantion,
    id_file_applicantion,
    id_leaving_applicantion,
    id_information,
    id_email
};
enum enum_data_file_status
{
    data_file_status_deleted,
    data_file_status_hidden,
    data_file_status_visible
};
enum enum_user_status
{
    user_status_frozen,
    user_status_removed
};
enum enum_user_group_status
{
    user_group_status_department,
    user_group_status_generalized_group
};
enum enum_contract_applicantion_status
{
    contract_applicantion_status_created,
    contract_applicantion_status_assigned_to_person,
    contract_applicantion_status_rejected,
    contract_applicantion_status_accepted
};
enum enum_seal_status
{
    seal_status_hidden,
    seal_status_visible
};
enum enum_seal_applicantion_status
{
    seal_applicantion_status_created,
    seal_applicantion_status_assigned_to_person,
    seal_applicantion_status_rejected,
    seal_applicantion_status_accepted
};
enum enum_file_applicantion_status
{
    file_applicantion_status_created,
    file_applicantion_status_assigned_to_person,
    file_applicantion_status_rejected,
    file_applicantion_status_accepted
};
enum enum_leaving_applicantion_status
{
    leaving_applicantion_status_created,
    leaving_applicantion_status_assigned_to_person_to_activate,
    leaving_applicantion_status_rejected,
    leaving_applicantion_status_accepted,
    leaving_applicantion_status_activated,
    leaving_applicantion_status_assigned_to_person_to_deactivate,
    leaving_applicantion_status_deactivated
};
enum enum_information_status
{
    information_status_created,
    information_status_sent,
    information_status_valid,
    information_status_expired
};
enum enum_email_status
{
    email_status_read,
    email_status_not_read,
    email_status_removed
};
#endif // ENUM_TYPE_ID
