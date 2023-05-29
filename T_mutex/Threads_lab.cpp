#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//global variables
string list[6];
pthread_t Thread_one;
pthread_t Thread_two;
pthread_mutex_t signal;

void* t1_func(void* arg)
{
    pthread_mutex_lock(&signal);
    //create the streams to read from and write in file
    ofstream put_value;
    ifstream get_value;

    get_value.open("File_to_reading_and_writing.txt");

    for(int k=0;k<3;k++)
    {
        getline(get_value,list[k]);
        cout<<list[k]<<endl;
    }

    get_value.close();

    cout<<"first stream has closed file for reading"<<endl;

    cout<<"first stream started writing"<<endl;
    put_value.open("File_to_reading_and_writing.txt",std::ios::app);

    put_value<<"Added line from first stream"<<endl;

    put_value.close();
    pthread_mutex_unlock(&signal);

    return NULL;
}

void* t2_func(void* arg)
{
    ofstream put_value;
    ifstream get_value;

    pthread_mutex_lock(&signal);
    get_value.open("File_to_reading_and_writing.txt");

    for(int k=5;k>2;k--)
    {
        getline(get_value,list[k]);
        cout<<list[k]<<endl;
    }

    get_value.close();

    cout<<"second stream has closed file for reading"<<endl;

    cout<<"second stream has started writing"<<endl;
    put_value.open("File_to_reading_and_writing.txt",std::ios::app);
    
    put_value<<"From second stream"<<endl;
    pthread_mutex_unlock(&signal);

    cout<<"The end";

    return NULL;
}

int main()
{
    for(int i=0;i<6;i++)
    {
        list[i]="opa";
    }

    //initialize the mutex and the threads
    pthread_mutex_init(&signal,NULL);
    pthread_create(&Thread_one,NULL,t1_func,NULL);
    pthread_create(&Thread_two,NULL,t2_func,NULL);
    pthread_join(Thread_two,NULL);
    ofstream file;
    file.open("File_to_reading_and_writing.txt",std::ios::app);
    for(int i=0;i<6;i++)
    {
        file<<list[i]<<endl;
    }
}