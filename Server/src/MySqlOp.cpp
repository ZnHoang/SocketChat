#include "MySqlOp.h"

MYSQL* MySqlOp::ms = nullptr;
bool MySqlOp::isConnecting = false;

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
    isConnecting = true;
}