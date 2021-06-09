#include "Server.h"

int main()
{
    try {
        Server server;
        server.Start();
    } catch(std::string se) {
        std::cout << se;
    } catch(int en) {
        std::cout << strerror(en);
    }
    return 0;
}
