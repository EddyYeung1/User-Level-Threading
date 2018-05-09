# User-Level-Threading

My last PA for Operating System's where I implement my thread_create, thread_yield, and thread_exit to create a preemptive scheduler. The purpose of the assignment was to practice using getcontext(), setcontext(), makecontext(), and swapcontext() to switch between threads. The scheduler is designed using a round robin algorithm or simply a circular doubly linked list. Threads would switch context based upon either a thread_yield or thread_exit being invoked on the current calling thread, or the timer runs out (SIGALRM). 

The main.c driver program does not do too much, but it properly shows the correct implementation of the functions. When threads are created they are associated with a processFunction that is pretty much just an infinite loop to show that the signal handler does properly handle the SIGALRM to swap contexts to another thread giving a fair share of time to each thread. 
