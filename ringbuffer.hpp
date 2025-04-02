#include <iostream>
#include <thread>
#include <mutex>
#define bound 256
typedef struct ring{
    int head;
    int tail;
    int count;
    int size;
    int value[bound];
    std::mutex mtx;
}ring ;
ring rb;
void ringbuffer_init(int size){
    rb.size = size;
    rb.head = 0;
    rb.tail = 0;
    rb.count = 0;
    for (int i = 0; i < bound; i++)
    {
        rb.value[i] = 0;
    }
}
int ringbuffer_is_full(){
    if (rb.count == rb.size)
    {
        return 1;
    }
    return 0;
} 
int ringbuffer_is_empty(){
    if (rb.count == 0)
    {
        return 1;
    }
    return 0;
}
int ringbuffer_size(){
    return rb.count;
}

int ringbuffer_add(int value){
    rb.mtx.lock();
    if (ringbuffer_is_full() == 1)
    {
        rb.mtx.unlock();
        return -1;
    }
    rb.value[rb.tail] = value;
    rb.tail = (rb.tail+1) % rb.size;
    rb.count++;
    rb.mtx.unlock();
    return 0;
}
int ringbuffer_remove(int* value){
    rb.mtx.lock();
    if (ringbuffer_is_empty())
    {
        rb.mtx.unlock();
        return -1;
    }
    *value = rb.value[rb.head];
    rb.head = (rb.head+1)%rb.size;
    rb.count--;
    rb.mtx.unlock();
    return 0;
}
