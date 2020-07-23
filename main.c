#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <sched.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_THREADS 8

void *thread_loop( void *thread_args ) {
    long t = (long) thread_args;
    int rc;
    cpu_set_t cpuset;
    pthread_t thread;
    unsigned cpu, node;

    thread = pthread_self();
    CPU_ZERO( &cpuset );
    CPU_SET( t, &cpuset );
    rc = pthread_setaffinity_np( thread, sizeof( cpu_set_t ), &cpuset );
    if ( rc ) {
	    printf( "I'm thread %2ld and Oops\n", t );
	    pthread_exit( NULL );
    }

    getcpu( &cpu, &node );
    printf( "I'm thread %2ld and I am running on cpu %2d\n", t, cpu);

    pthread_exit( NULL );
}

int main() {
    pthread_t threads[ NUM_THREADS ];
    long t, rc;
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
