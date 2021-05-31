#include "Server.h"

int main()
{
    try {
        Server server;
    } catch(int en) {
        std::cout << strerror(en);
    }
    
    return 0;
}
