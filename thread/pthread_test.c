#include <pthread.h>
#include <stdio.h>

#define BUFSIZE 1024;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;
pthread_cond_t notempty = PTHREAD_COND_INITIALIZER;
int in, out, count;

int buffer[1024];
int capacity = BUFSIZE;

void put(int fd);
int take();

int main()
{
    put(1);
    put(2);

    int x = take();
    int y = take();

    printf("x: %d, y: %d, z: %d, w: %d, k: %d\n", x, y);
    return 0;
}

void put(int fd)
{
    // buffer 요소와 count에 대한 락
    pthread_mutex_lock(&m);
    while (count == capacity)
        pthread_cond_wait(&notfull, &m);
    buffer[in] = fd;
    in = (in + 1) % capacity;
    count++;
    pthread_cond_signal(&notempty);
    pthread_mutex_unlock(&m);
}

int take()
{
    int data;
    pthread_mutex_lock(&m);
    while (count == 0)
        pthread_cond_wait(&notempty, &m);
    data = buffer[out];
    out = (out + 1) % capacity;
    count--;

    pthread_cond_signal(&notfull);
    pthread_mutex_unlock(&m);
    return data;
}