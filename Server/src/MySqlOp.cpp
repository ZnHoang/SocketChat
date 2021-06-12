#include "MySqlOp.h"

MYSQL* MySqlOp::ms = nullptr;
bool MySqlOp::isConnecting = false;
std::shared_mutex MySqlOp::mt;

MySqlOp::~MySqlOp()
{
    if(isConnecting)
    {

    }
}

void MySqlOp::Connect(const DbInfo dbInfo)
{
    if(ms = mysql_init(nullptr); ms == nullptr)
    {
        throw "MySql init failed\n";
    }
    if(auto res = mysql_real_connect(ms, dbInfo.host.c_str(), dbInfo.user.c_str(), dbInfo.passwd.c_str(), dbInfo.db.c_str(), dbInfo.port, dbInfo.unix_socket.c_str(), dbInfo.clientFlag); res == nullptr)
    {
        throw "MySql connect failed\n";
    }
    if(auto res = mysql_autocommit(ms, false); res != 0)
    {
        throw "MySql set not auto commit failed\n";
    }
    isConnecting = true;
}

bool MySqlOp::checkUser(const std::string& nickname, const std::string& password)
{
    return false;
}