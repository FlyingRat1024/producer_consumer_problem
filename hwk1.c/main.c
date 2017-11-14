#include <stdio.h>
#include <pthread.h>

#define N 35
int count=0;

pthread_mutex_t mutex;
pthread_cond_t condpro,condcon;

void *produce(){
    for(int i=0;i<60;i++){
        pthread_mutex_lock(&mutex);
        while(count==N) {
            printf("缓冲区已满,生产者休眠\n");
            pthread_cond_wait(&condpro, &mutex);
        }
        printf("当前缓冲区数目为:%d,生产者生产，增加一个\n",count);
        count++;
        if(count==1) {
            printf("生产者生产了一个，缓冲区数目为:%d,唤醒消费者\n",count);
            pthread_cond_signal(&condcon);
        }
        pthread_mutex_unlock(&mutex);

    }
}

void *consume(){
    for(int i=0;i<60;i++){
        pthread_mutex_lock(&mutex);
        while(count==0) {
            printf("缓冲区以空,消费者休眠\n");
            pthread_cond_wait(&condcon, &mutex);
        }
        printf("当前缓冲区数目为：%d,消费者消费,减少一个\n",count);
        count--;
        if(count==N-1) {
            printf("消费者消费掉了一个，缓冲区个数为:%d,唤醒生产者\n",count);
            pthread_cond_signal(&condpro);
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t consumer,producer;//线程标识符long int

    pthread_mutex_init(&mutex,NULL);//初始化锁

    pthread_cond_init(&condpro,NULL);//初始化条件属性
    pthread_cond_init(&condcon,NULL);

    pthread_create(&producer,NULL,produce,NULL);
    pthread_create(&consumer,NULL,consume,NULL);//线程标识符，线程属性，线程运行函数起始地址，运行函数的参数

    pthread_join(consumer,NULL);
    pthread_join(producer,NULL);

    pthread_cond_destroy(&condcon);
    pthread_cond_destroy(&condpro);
    pthread_mutex_destroy(&mutex);

    return 0;
}