#ifndef _ECHO_SERVER_H_
#define _ECHO_SERVER_H_

#include <echo/tcp_server.h>
#include <echo/thread_pool.h>
#include <echo/non_copyable.h>

class EchoServer : NonCopyable
{
    public:
        EchoServer(const InetAddress &);
        void start();
    private:
        void onConnection(const TcpConnectionPtr &);
        void onMessage(const TcpConnectionPtr &);
        void onClose(const TcpConnectionPtr &);

        void compute(const std::string &, const TcpConnectionPtr &);

        TcpServer server_;
        ThreadPool pool_;
};

#endif  /*_ECHO_SERVER_H_*/
