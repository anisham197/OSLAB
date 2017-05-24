#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// static initialization
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER; // contains the mutex
pthread_cond_t  canProduce   = PTHREAD_COND_INITIALIZER; // condition is a sync device. threads   give up control until condition satisifed.
                                                        // signal and wait
                                                        //A condition variable must always be associated with a mutex,
                                                        //to avoid the race condition

void *producer();
void *consumer();

int item = 0;
int consumed = 0;
int buffer = 0;

#define MAX_BUFFER 3
#define MAX_ITEMS 10

int main()
{
   pthread_t thread1, thread2;

   pthread_create( &thread1, NULL, &producer, NULL); // thread, thread attribute, process, process argument
   pthread_create( &thread2, NULL, &consumer, NULL);

   pthread_join( thread2, NULL); // thread , return value
   pthread_join( thread1, NULL);

   printf("Items Produced Totally: %d\n",item);

   return 0;
}

// Producer Process
void *producer()
{
    srand(time(NULL));
    int myrand = rand();
    for(;;)
    {
      // Lock mutex, if locked block thread until mutex available
      pthread_mutex_lock( &buffer_mutex );

      // Wait while consumer() operates on buffer
      // mutex unlocked if condition varialbe in consumer() signaled.
      if(buffer==MAX_BUFFER || myrand%2)
        pthread_cond_wait( &canProduce, &buffer_mutex ); // release mutex, thread blocks on condition variable

      while(buffer < MAX_BUFFER){
          myrand = rand();
          if(myrand%2==0) break;
          item++;
          buffer++;
          printf("Produced Item: %d\n",item);
      }

      pthread_mutex_unlock( &buffer_mutex ); // release lock on mutex

      if(item >= MAX_ITEMS) return(NULL);
    }
}

// Consumer Process
void *consumer()
{
    srand(time(NULL));
    int myrand = rand();
    for(;;)
    {
       pthread_mutex_lock( &buffer_mutex );

       if(buffer == 0)
       {
           pthread_cond_signal( &canProduce );
           //unblocks at least one of the threads that are blocked on the specified condition variable
       }

       while( buffer > 0)
       {
          myrand = rand();
          if(myrand%2==0) break;

          printf("Consumed Item: %d\n",++consumed);
          buffer--;
       }
       pthread_mutex_unlock( &buffer_mutex );

       if(item >= MAX_ITEMS) return(NULL);
    }
}
// gcc -pthread prodcons.c
