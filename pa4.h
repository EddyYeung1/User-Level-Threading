#ifndef PA4_H
#define PA4_H

#include <ucontext.h>

typedef struct
thread_t{
  void* prev;
  void* next;
  ucontext_t context;
  int count;
  int isConsistent;
}thread_t;

void* thread_create(thread_t* thread, void (*func)(void*), void * arg);
void* thread_yield();
void thread_exit();

#endif /*PA4_H*/
