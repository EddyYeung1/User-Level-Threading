#include <ucontext.h>
#include <stdio.h>
#include <ucontext.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include "pa4.h"
#include <ctype.h>

int count=1;


void processFunction(void* arg){
  printf("Process created \n \n \n");
  while(1){
    int running = 1;
    int threadNumber = 0;
    while (running == 1){
        char functionCall[10];

        printf("Enter your instructions:\n");
        scanf("%s", functionCall);
        if ((tolower(functionCall[0])) == 's'){
            running = 0;
        }else{
            switch (tolower(functionCall[0])){
            case 'y':
                thread_yield();
                break;
            case 'e':
                thread_exit();
                break;
            default:
                printf("I couldn't understand your function call! \n");
            }
        }
    }

  }
  //count++;
}

int main() {

    thread_t thread1;
    thread_t thread2;
    thread_t thread3;
    thread_t thread4;
    thread_t thread5;
    thread_t thread6;
    thread_t thread7;
    thread_t thread8;
    thread_t thread9;
    thread_t thread10;

    thread_t Threads[] = {thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9, thread10};

    printf("Welcome to the User-Level Thread Implemtation program. \n By: Ethan, Eddie, Alex, Ali, and Omer \n \n");

    printf("This is how this is going to work: \n");
    printf("You can play(create, yield, and exit) with up to 10 threads, and to call the functions simply enter 'c', 'y', or 'e', for the respective call \n\n");


    printf("As always, the safe word is 'STOP' to end the program. \n \n");


    int running = 1;
    int threadNumber = 0;
    while (running == 1){
        char functionCall[10];

        printf("Enter your instructions:\n");
        scanf("%s", functionCall);
        if ((tolower(functionCall[0])) == 's'){
            running = 0;
        }else{
            switch (tolower(functionCall[0])){
            case 'c':
                thread_create(&Threads[threadNumber], processFunction, 0);
                threadNumber += 1;
                break;
            case 'y':
                thread_yield();
                break;
            case 'e':
                thread_exit();
                break;
            default:
                printf("I couldn't understand your function call! \n");
            }
        }
    }


    printf(" \n \n ---Program ended--- \n \n");


    return 0;
}
