#include "condition.h"
#include "mutex_lock.h"

Condition::Condition(MutexLock &mutex)
    :mutex_(mutex)
{
    pthread_cond_init(&cond_, NULL);
}

Condition::~Condition()
{
    pthread_cond_destroy(&cond_);
}

void Condition::wait()
{
    assert(mutex_.isLocked());
    pthread_cond_wait(&cond_, mutex_.getMutexPtr());
}

void Condition::notify()
{
    pthread_cond_signal(&cond_);
}

void Condition::notifyAll()
{
    pthread_cond_broadcast(&cond_);
}
