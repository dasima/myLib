#include <echo/tcp_server.h>
#include <iostream>

using namespace std;

void onConnection(const TcpConnectionPtr &conn)
{
    cout << "client " << conn->getPeerAddr().toIp()
        << " port " << conn->getPeerAddr().toPort() << endl;
    conn->sendString("Hello\r\n");
}

void onMessage(const TcpConnectionPtr &conn)
{
    string s(conn->receiveString());
    conn->sendString("ACK\r\n");
}

int main(int argc, const char *argv[])
{
    TcpServer server(InetAddress(8080));
    server.setConnection(&onConnection);
    server.setMessage(&onMessage);
    server.start();
    return 0;
}
