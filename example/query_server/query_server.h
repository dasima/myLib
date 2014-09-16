#ifndef _QUERY_SERVER_H_
#define _QUERY_SERVER_H_

#include <echo/tcp_server.h>
#include <echo/thread_pool.h>
#include "text_query.h"
class QueryServer : NonCopyable
{
    public:
        QueryServer(const InetAddress &, const std::string & );
        void start();
    private:
        void onConnection(const TcpConnectionPtr &);
        void onMessage(const TcpConnectionPtr &);
        void onClose(const TcpConnectionPtr &);

        void runQuery(const std::string &, const TcpConnectionPtr &);

        TcpServer server_;
        TextQuery query_;
        ThreadPool pool_;
};

#endif  /*_QUERY_SERVER_H_*/
