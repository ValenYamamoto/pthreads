#include <linux/getcpu.h>
#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 8

void *thread_loop( void *thread_args ) {
    int t = (int) thread_args;
    unsigned cpu, node;

    getcpu( &cpu, &node, NULL)
    printf( "I'm thread %2d and I am running on cpu %2d on node %2d\n", t, cpu, node);

    pthread_exit( NULL );
}

int main() {
    pthread_t thread[ NUM_THREADS ];
    int t, rc;
    void *status;

    for( t = 0; t < NUM_THREADS; t++ ) {
        rc = pthread_create( &threads[ t ], NULL, thread_loop, ( void * )t );
        if ( rc ) {
            exit( -1 );
        }
    }
    
    for( t = 0; t < NUM_THREADS; t++ ) {
        rc = pthread_join( threads[ t ], &status );
        if ( rc ) {
            exit( -1 );
        }
    }
    pthread_exit( NULL );
}