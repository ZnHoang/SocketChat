#ifndef MY_SQL_OP_H
#define MY_SQL_OP_H

#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <mutex>
#include <shared_mutex>

using DbInfo = struct DbInfo
{
    std::string host = "127.0.0.1";
    std::string user = "root";
    std::string passwd = "";
    std::string db = "";
    int port = 3306;
    std::string unix_socket = "";
    unsigned long clientFlag = 0;
};

class MySqlOp
{
public:
    MySqlOp() = delete;
    ~MySqlOp();
    static void Connect(const DbInfo dbInfo);
    static bool checkUser(const std::string& nickname, const std::string& password);

private:
    static MYSQL* ms;
    static bool isConnecting;
    static std::shared_mutex mt;
};

#endif