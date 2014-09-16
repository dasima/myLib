#ifndef _CHAT_SERVER_H_
#define _CHAT_SERVER_H_

#include <echo/non_copyable.h>
#include <echo/tcp_server.h>
#include <set>

class ChatServer : NonCopyable
{
    public:
        ChatServer(const InetAddress &);
        void start();
    private:
        void onConnection(const TcpConnectionPtr &);
        void onMessage(const TcpConnectionPtr &);
        void onClose(const TcpConnectionPtr &);

        TcpServer server_;
        std::set<TcpConnectionPtr> clients_;

        const static size_t kMaxClients = 3;
};

#endif  /*_CHAT_SERVER_H_*/
