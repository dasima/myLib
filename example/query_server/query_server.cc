#include "query_server.h"
using namespace std;
using namespace std::placeholders;

QueryServer::QueryServer(const InetAddress &addr, 
                       const std::string &filename)
    :server_(addr), 
    query_(filename),
    pool_(1000, 4)
{
    server_.setConnection(bind(&QueryServer::onConnection, this, _1));
    server_.setMessage(bind(&QueryServer::onMessage, this, _1));
    server_.setClose(bind(&QueryServer::onClose, this, _1));
}

void QueryServer::start()
{
    pool_.start();
    server_.start();
}

void QueryServer::onConnection(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port "
        << conn->getPeerAddr().toPort() << endl;
    conn->sendString("Welcome, please input the word:\r\n");
}

void QueryServer::onMessage(const TcpConnectionPtr &conn)
{
    string word(conn->receiveString());
    pool_.addTask(bind(&QueryServer::runQuery, this, word, conn));
}

void QueryServer::runQuery(const string &s, const TcpConnectionPtr &conn)
{
    string word = s;
    if(word.substr(word.size()-2, 2) == "\r\n")
    {
        word.erase(word.size()-1);
        word.erase(word.size()-1);
    }
    string res = query_.runQuery(word);
    conn->sendString(res + "\r\n");
}

void QueryServer::onClose(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port "
        << conn->getPeerAddr().toPort() << "close" << endl; 
    conn->shutdown();
}
