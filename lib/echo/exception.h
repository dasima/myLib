#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>
#include <exception>

//编译时使用-rdynamic选项，确保stacktrace带有名字信息

class Exception : public std::exception
{
    public:
        explicit Exception(const char*);
        explicit Exception(const std::string &);
        virtual ~Exception() throw();//这个函数不抛出异常
        virtual const char *what() const throw();
        const char *stackTrace() const throw();
    private:
        void fillStackTrace();//填充栈痕迹

        std::string message_;//异常名字
        std::string stack_;//栈痕迹
};

#endif  /*_EXCEPTION_H_*/
