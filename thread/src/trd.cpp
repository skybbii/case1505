#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>

#include <signal.h>
#include <unistd.h>

#include <unistd.h>  
#include <pthread.h>  

using namespace std;
  
static pthread_mutex_t mutex;  
static pthread_cond_t cond;  
static int flag = 0;  
  
void srpthread_init()  
{  
    pthread_mutex_init(&mutex,NULL);  
    pthread_cond_init(&cond,NULL);  
}  
  
void srpthread_suspend()  
{  
    pthread_mutex_lock(&mutex);  
    flag--;  
    pthread_mutex_unlock(&mutex);  
}  
  
  
void srpthread_resume()  
{  
    pthread_mutex_lock(&mutex);  
    flag++;  
    pthread_cond_signal(&cond);  
    pthread_mutex_unlock(&mutex);  
}  
  
void *thread_run(void* args)  
{  
    while(1)  
    {  
        pthread_mutex_lock(&mutex);  
        while(flag<=0)  
        {  
            pthread_cond_wait(&cond,&mutex);  
        }  
  
        pthread_mutex_unlock(&mutex); 

        sleep(2);
  
        //actual work  
        printf("i am running!\n");  
    }  
  
}  
  
int main(int argc,char *argv[])  
{  
    char ch;  
    pthread_t p1;  
    srpthread_init();  
    pthread_create(&p1,NULL,thread_run,NULL);  
  
    while(1)  
    {  
        scanf("%c",&ch);  
        switch(ch)  
        {  
            case 's':  
                srpthread_suspend();  
                break;  
            case 'r':  
                srpthread_resume();  
                break;  
            default:  
                break;  
        }  
    }  
#if 0  
    printf("1111\n");  
    srpthread_resume();  
    printf("2222\n");  
    sleep(3);  
    printf("3333\n");  
    srpthread_suspend();  
    printf("4444\n");  
#endif  
    return 1;  
}  