#include "timer.h"
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

Timer::Timer()
    :is_started_(false)
{
    timerfd_ = ::timerfd_create(CLOCK_REALTIME, 0);
    if(timerfd_ == -1)
        ERR_EXIT("timerfd_create");
    memset(&howlong_, 0, sizeof(howlong_));
}

Timer::~Timer()
{
    ::close(timerfd_);
}

void Timer::setTimer(int val, int interval)
{
    howlong_.it_value.tv_sec = val;
    howlong_.it_interval.tv_sec = interval;
}

void Timer::setTimerCallback(const TimerCallback &tc)
{
    timerCallback_ = tc;
}

void Timer::runTimer()
{
    struct pollfd event[1];
    event[0].fd = timerfd_;
    event[0].events = POLLIN;
    char buf[1024];
    int nready;

    if(timerfd_settime(timerfd_, 0, &howlong_, NULL) == -1)
        ERR_EXIT("settime");
    is_started_ = true;

    while(is_started_)
    {
        nready = poll(event, 1, 10000);
        if(nready == -1)
            ERR_EXIT("poll");
        else if(nready == 0)
            printf("poll\n");
        else
        {
            if(read(timerfd_, buf, sizeof(buf)) == -1)
                ERR_EXIT("read");
            timerCallback_();//调用用户逻辑
        }
    }
}

void Timer::cancelTimer()
{
    memset(&howlong_, 0, sizeof(howlong_));
    if(timerfd_settime(timerfd_, 0, &howlong_, NULL) == -1)
        ERR_EXIT("timerfd_settime");
    is_started_ = false;
}
