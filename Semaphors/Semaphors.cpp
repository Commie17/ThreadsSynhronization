#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <semaphore.h>
#include <string>
#include <fstream>

using namespace std;

//global variables
long int variable=0;
sem_t semaphore_t1;
sem_t semaphore_t2;
pthread_t Thread_one;
pthread_t Thread_two;
fstream file;

void* t1_func(void* arg)
{
    for(int k=1;k<11;k++)
    {
        variable=k;
        file<<variable<<" ";
        sem_post(&semaphore_t2);
        sem_wait(&semaphore_t1);
    }

    return NULL;
}

void* t2_func(void* arg)
{
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&semaphore_t2);
        variable=variable*variable;
        file<<variable<<endl;
        sem_post(&semaphore_t1);
    }
    
    return NULL;
}

int main()
{
    file.open("Output.txt",std::ios::app);
    //initialize the mutex and the threads
    sem_init(&semaphore_t2,0,0);
    sem_init(&semaphore_t1,0,0);
    pthread_create(&Thread_one,NULL,t1_func,NULL);
    pthread_create(&Thread_two,NULL,t2_func,NULL);
    pthread_join(Thread_two,NULL);
}