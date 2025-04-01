#include <iostream>
#include <thread>
#include <mutex>
#define BOUND 1000
typedef struct ring
{
    int value[BOUND];
    int index;
    int maxindex;
    std::mutex mtx;
} ring;
ring ringbuffer;
void ringbuffer_init(int size)
{
    ringbuffer.index = 0;
    if (size > BOUND)
    {
        ringbuffer.maxindex = BOUND;
    }
    else
    {
        ringbuffer.maxindex = size;
    }
}

int ringbuffer_is_full()
{
    if (ringbuffer.maxindex == ringbuffer.index)
    {
        ringbuffer.mtx.unlock();
        return 1;
    }
    return 0;
}
int ringbuffer_is_empty()
{
    if (ringbuffer.index == 0)
    {
        return 1;
    }
    return 0;
}
int ringbuffer_size()
{
    return ringbuffer.index;
}
int ringbuffer_add(int value)
{
    ringbuffer.mtx.lock();
    int index = ringbuffer.index;
    if (ringbuffer_is_full()  == 0)
    {
        ringbuffer.value[index] = value;
        ringbuffer.index++;
        ringbuffer.mtx.unlock();
        return 0;
    }
    ringbuffer.mtx.unlock();
    return -1;
}
int ringbuffer_remove(int value)
{
    ringbuffer.mtx.lock();
    int pos = 0;
    while (pos < ringbuffer_size())
    {
        if (ringbuffer.value[pos] == value)
        {
            break;
        }
        pos++;
    }
    if (pos == ringbuffer_size())
    {
        ringbuffer.mtx.unlock();
        return -1;
    }
    else
    {
        for (int i = pos; i < ringbuffer_size(); i++)
        {
            int tmp = ringbuffer.value[i + 1];
            ringbuffer.value[i] = tmp;
        }
        if (ringbuffer.index > 0)
        {
           ringbuffer.index--;
        }
        ringbuffer.mtx.unlock();
        return 0;
    }
}