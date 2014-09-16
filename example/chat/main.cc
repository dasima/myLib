#include "chat_server.h"

int main(int argc, const char *argv[])
{
    ChatServer server(InetAddress(8080));
    server.start();
    return 0;
}
