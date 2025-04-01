#include <iostream>
using namespace std;
typedef struct stack
{
    int value[100];
    int index;
    int maxindex;
} stack;
stack ringbuffer;
void ringbuffer_init(int size)
{
    ringbuffer.maxindex = size;
}
int ringbuffer_add(int value)
{
    int index = ringbuffer.index;
    if (index < ringbuffer.maxindex)
    {
        ringbuffer.value[index] = value;
        ringbuffer.index++;
        return 0;
    }
    return -1;
}
int ringbuffer_is_full()
{
    if (ringbuffer.maxindex == ringbuffer.index)
    {
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
int ringbuffer_remove(int value)
{
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
        return -1;
    }
    else
    {
        for (int i = pos; i < ringbuffer_size(); i++)
        {
            int tmp = ringbuffer.value[i + 1];
            ringbuffer.value[i] = tmp;
        }
        ringbuffer.index--;
        return 0;
    }
}
int main()
{
    ringbuffer_init(5);

    ringbuffer_add(10);
    ringbuffer_add(20);
    ringbuffer_add(30);
    cout<<ringbuffer_remove(10)<<endl;
    cout<<ringbuffer_is_empty()<<endl;
    cout<<ringbuffer_is_full()<<endl;
    for(int i = 0; i < ringbuffer_size();i++){
        cout<<ringbuffer.value[i]<<endl;
    }
    
}