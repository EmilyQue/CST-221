#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * Thread 1 function.
 *
 * @param a Not used.
 * @return Always null.
 */
void *thread1(void *a)
{
    int x;
    for(x = 0;x < 10;++x)
    {
        // Print a message to the console and sleep for awhile
        printf("This is Thread 1 ..... %d\n", x);
        sleep(1);
    }
    return NULL;
}

/**
 * Thread 2 function.
 *
 * @param a Not used.
 * @return Always null.
 */
void *thread2(void *a)
{
    //pauses for 10 seconds so it does not interfere with the first thread
    sleep(10);
    int x;
    for(x = 0;x < 20;++x)
    {
	//begins at 10 
	if (x > 9) {
	// Print a message to the console and sleep for awhile
        printf("This is Thread 2 ..... %d\n", x);
        sleep(2);
	}
	else {
	//continues loop
	continue;
	}
    }
    return NULL;
}

/**
 * Main application entry point to create some threads.
 *
 * @return 1 if error or 0 if OK returned to code the caller.
 */
int main()
{
    pthread_t tid1, tid2;

    // Create 2 threads
    if(pthread_create(&tid1, NULL, thread1, NULL))
    {
        printf("\n ERROR creating thread 1");
        exit(1);
    }
    if(pthread_create(&tid2, NULL, thread2, NULL))
    {
        printf("\n ERROR creating thread 2");
        exit(1);
    }

    // Wait for both threads to finish
    if(pthread_join(tid1, NULL))
    {
        printf("\n ERROR joining thread 1");
        exit(1);
    }
    if(pthread_join(tid2, NULL))
    {
        printf("\n ERROR joining thread 2");
        exit(1);
    }

    // Thread creation cleanup
    pthread_exit(NULL);
}

