#include "chat_server.h"
using namespace std;
using namespace placeholders;

ChatServer::ChatServer(const InetAddress &addr)
    :server_(addr)
{
    server_.setConnection(bind(&ChatServer::onConnection, this, _1));
    server_.setMessage(bind(&ChatServer::onMessage, this, _1));
    server_.setClose(bind(&ChatServer::onClose, this, _1));
}

void ChatServer::start()
{
    server_.start();
}

void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if(clients_.size() >= kMaxClients)
    {
        conn->sendString("Sorry, Chat Server is full, Please try later...\r\n");
        conn->shutdown();
        return;
    }
    cout << conn->getPeerAddr().toIp() << " port " 
        << conn->getPeerAddr().toPort() << endl;
    clients_.insert(conn);
    conn->sendString("Welcome to Chat Server...\r\n");
}

void ChatServer::onMessage(const TcpConnectionPtr &conn)
{
    string s(conn->receiveString());
    for(set<TcpConnectionPtr>::iterator it = clients_.begin(); it != clients_.end(); ++it)
    {
        (*it)->sendString(s);
    }
}

void ChatServer::onClose(const TcpConnectionPtr &conn)
{
    clients_.erase(conn);
    conn->shutdown();
}
