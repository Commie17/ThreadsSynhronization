#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//global variables
long int da=0;
long int variable=2;
bool isUp=false;
pthread_cond_t cond;
pthread_mutex_t mt;
pthread_t Thread_one;
pthread_t Thread_two;
fstream file;

void* t1_func(void* arg)
{
    pthread_mutex_lock(&mt);
    for(int i=1;i<7;i++)
    {
        variable*=2;
        file<<variable<<" ";
    }
    file<<endl;
    if(pthread_cond_signal(&cond)==0)
    variable=3;
    pthread_mutex_unlock(&mt);
    return NULL;
}

void* t2_func(void* arg)
{
    while(variable!=3)
    {
        pthread_cond_wait(&cond,&mt);
    }
    pthread_mutex_lock(&mt);
    for(int i=0;i<6;i++)
    {
        variable*=3;
        file<<variable<<" ";
    }
    pthread_mutex_unlock(&mt);
    return NULL;
}

int main()
{
    file.open("Output.txt",std::ios::app);
    //initialize the mutex and the threads
    pthread_mutex_init(&mt,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&Thread_one,NULL,t1_func,NULL);
    pthread_create(&Thread_two,NULL,t2_func,NULL);
    pthread_join(Thread_two,NULL);
}