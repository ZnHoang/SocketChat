#include "Server.h"

int main()
{
    try {
        Server server;
        server.Start();
    } catch(int en) {
        std::cout << strerror(en);
    }
    return 0;
}
