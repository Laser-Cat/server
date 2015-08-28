#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T14:16:47
#
#-------------------------------------------------
QT       += core gui
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = server
TEMPLATE = app

#QMAKE_CXXFLAGS += -stdlib=libstdc++


#_BOOST_PATH=/opt/local
INCLUDEPATH += /usr/local/Cellar/boost/1.58.0/include
#    LIBS +=-L/usr/local/Cellar/boost/1.58.0/lib -lboost_regex
SOURCES += main.cpp\
        main_window.cpp \
    global_config.cpp \
    global_define.cpp \
    command.cpp \
    user.cpp \
    global_util_all.cpp \
    q_global_util.cpp \
    view_global_util_alert.cpp \
    control_logger.cpp \
    control_session.cpp \
    control_server_base.cpp \
    #control_socket_server_client.cpp \
    control_socket_server_main.cpp \
    #all_da_stuff.cpp \
    #control_server_data_type.cpp \
    #dao_access_priviledge.cpp \
    dao_base.cpp \
    #dao_contract_applicantion.cpp \
    #dao_data_file.cpp \
    #dao_email.cpp \
    #dao_file_applicantion.cpp \
    #dao_information.cpp \
    #dao_leaving_applicantion.cpp \
    #dao_seal.cpp \
    #dao_seal_applicantion.cpp \
    #dao_user.cpp \
    #dao_user_assigned_item.cpp \
    #dao_user_belongs_to_user_group.cpp \
    #dao_user_done_operation.cpp \
    #dao_user_group.cpp \
    enums.cpp \
    global_all_header.cpp \
    #json_support.cpp \
    #model_application.cpp \
    #model_contract_application.cpp \
    #model_file_application.cpp \
    #model_group.cpp \
    #model_group_set.cpp \
    #model_information.cpp \
    #model_item.cpp \
    #model_item_list.cpp \
    #model_leaving_application.cpp \
    #model_seal.cpp \
    #model_seal_application.cpp \
    #model_user.cpp \
    stdafx.cpp \
    initilalizer.cpp
HEADERS  += main_window.h \
    stdafx.h \
    global_config.h \
    global_all_header.h \
    global_define.h \
    command.h \
    #model_user.h \
    #model_seal.h \
    #model_item_list.h \
    #model_item.h \
    #model_group_set.h \
    #model_group.h \
    #json_support.h \
    #user.cpp.autosave \
    #user.h.autosave \
    #session.h.autosave \
    #model_contract_application.h \
    #model_file_application.h \
    #model_leaving_application.h \
    #model_seal_application.h \
    #model_application.h \
    enums.h \
    #dao_user_belongs_to_user_group.h \
    #dao_contract_applicantion.h \
    #dao_leaving_applicantion.h \
    #dao_user_done_operation.h \
    #dao_user_assigned_item.h \
    #dao_seal_applicantion.h \
    #dao_file_applicantion.h \
    #dao_access_priviledge.h \
    #dao_information.h \
    #dao_user_group.h \
    #dao_data_file.h \
    #dao_email.h \
    #dao_user.h \
    #dao_seal.h \
    dao_base.h \
    global_util_all.h \
    q_global_util.h \
    view_global_util_alert.h \
    #model_information.h \
    global_all_header.h \
    control_logger.h \
    control_server_base.h \
    control_server_data_type.h \
    control_session.h \
    control_socket_server_client.h \
    #control_socket_server_main.h \
    all_da_stuff.h \
    initilalizer.h
DISTFILES += \
    protocol_define.txt \
    server.pro.user \
    protocol_define.md.autosave
QTPLUGIN += qsqlmysql
