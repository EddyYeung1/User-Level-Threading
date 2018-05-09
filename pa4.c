#include <ucontext.h>
#include <stdio.h>
#include <ucontext.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include "pa4.h"

thread_t* current;
thread_t * head = NULL;
thread_t * tail;
int processCount = 1, firstTime = 0;

static void start_timer(int first_quantum, int repeat_quantum) {
    struct itimerval interval;
    interval.it_interval.tv_sec = repeat_quantum;
    interval.it_interval.tv_usec = 0;
    interval.it_value.tv_sec = first_quantum;
    interval.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &interval, 0);
}

void insertIntoQueue(thread_t* tcb){
  thread_t* temp = head; //create a temporary variable to keep track of head
  if (head == NULL){ //if there is nothing in the list make tcb the head
    head = tcb; //head and tail are equal to tcb because its the only item in list
    tail = tcb;
    tcb->next = tcb; //tcb's next and prev point to tcb because they are the only item in list
    tcb->prev = tcb;
    return;
  }
  //reorder list
	tail->next = tcb; //insert at end of list
	tcb->prev = tail;
	tcb->next = head;
	head->prev = tcb;
	tail = tcb;

}

static void timerHandler (){
  if (current->isConsistent == 1){ //checks flag to see if safe to swap

    thread_t* prev = current;
    current = current->next;

    start_timer(5,0);

    if (current != prev) //this checks that there is more than one thread first
    {
      printf("swapping from thread %d to thread %d\n", prev->count, current->count);
    swapcontext(&prev->context, &current->context);
    }
  }
  else{
    //process is not consistent lets check back in 5 seconds
    start_timer(5, 0);
  }
}

void* thread_create(thread_t* thread, void (*func)(void*), void * arg){

  //initialize first main thread
  if (firstTime == 0){
    struct sigaction action;
    action.sa_flags = SA_SIGINFO | SA_RESTART;
    action.sa_sigaction = timerHandler;
    sigemptyset (&action.sa_mask);
    sigaction(SIGALRM, &action, 0);

    thread_t* mainThread = (thread_t*)malloc(sizeof(thread_t));

    mainThread->prev = NULL;
    mainThread->next = NULL;
    mainThread->isConsistent = 1;
    mainThread->count = 0;
    current = mainThread;
    head = mainThread;
    tail = mainThread;
    firstTime = 1;
  }

  char* funcl_stack = (char*)malloc(16123);
  thread->context.uc_stack.ss_sp = funcl_stack;
  thread->context.uc_stack.ss_size = 16123;
  thread->context.uc_link = 0;

  getcontext(&thread->context);
  makecontext(&thread->context,(void(*)(void)) func, 1, arg);

  thread->prev = NULL;
  thread->next = NULL;
  thread->isConsistent = 1;
  thread->count = processCount;
  processCount++;
  insertIntoQueue(thread);
  start_timer(0,0);
  timerHandler();
  return thread;
}

void * thread_yield(){
  printf("current thread: thread %d is yielding, moving on to next thread..\n", current->count);
  start_timer(0,0);
  timerHandler();
}

void thread_exit() {
    printf("current thread: thread %d\n is exiting", current->count);
    current->isConsistent = 0;
    thread_t* prev = (thread_t*) current->prev;
    thread_t* next = (thread_t*) current->next;
    prev->next = current->next;
    next->prev = current->prev;
    free(current->context.uc_stack.ss_sp);
    if (current == head) {
        head = current->next;
    }
    if (current == tail) {
        tail = current->prev;
    }
    if (current == current->next) {
        exit(0);
    }
    current = current->next;
    if (setcontext(&current->context) != 0) {
        fprintf(stderr, "\x1b[3;33mError in thread_exit line %d file %s\x1b[0m\n", __LINE__, __FILE__);
    }
}
