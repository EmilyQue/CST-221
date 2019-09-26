#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include  <signal.h>
#include <sys/mman.h>
#include <errno.h>

//Emily Quevedo
//CST-221
//This is my own work. Starter code provided by instructor.
//Resources used: https://embeddedartistry.com/blog/2017/4/6/circular-buffers-in-cc

// Constants
int MAX = 100;
int WAKEUP = SIGUSR1;
int SLEEP = SIGUSR2;

// The Child PID if the Parent else the Parent PID if the Child
pid_t otherPid;

// A Signal Set
sigset_t sigSet;

// Shared Circular Buffer
struct CIRCULAR_BUFFER
{
    int count;          // Number of items in the buffer
    int lower;          // Next slot to read in the buffer
    int upper;          // Next slot to write in the buffer
    int buffer[100];
};
struct CIRCULAR_BUFFER *buffer = NULL;

/****************************************************************************************************/

// This method will put the current Process to sleep forever until it is awoken by the WAKEUP signal
void sleepAndWait()
{
    int nSig;

    printf("Sleeping...........\n");
    // TODO: Sleep until notified to wake up using the sigwait() method
    sigwait(&sigSet, &nSig);
    
    printf("Awoken\n");
}

// This method will signal the Other Process to WAKEUP
void wakeupOther()
{
	// TODO: Signal Other Process to wakeup using the kill() method
	kill(otherPid, WAKEUP);
}

// Gets a value from the shared buffer
int getValue()
{
    // TODO: Get a value from the Circular Buffer and adjust where to read from next
    int value = buffer->buffer[buffer->lower];
    buffer->lower = (buffer->lower + 1) % 100;
    buffer->count--;
    return value;
}

// Puts a value in the shared buffer
void putValue(struct CIRCULAR_BUFFER* buffer, int value)
{
    // TODO: Write to the next available position in the Circular Buffer and adjust where to write next
    buffer->buffer[buffer->upper] = value;
    buffer->upper = (buffer->upper + 1) % 100;
    buffer->count++;
    printf("Producer value: %i\n", value);
    
}

/****************************************************************************************************/

/**
 * Logic to return a random number (out of 20) from the buffer
 **/
int produce() {
    return rand() % 20;
}

/**
 * Logic to print the consumer value
 **/
void consume(int i) {
    printf("Consumer value: %i\n", i);
}

/**
 * Logic to run to the Consumer Process
 **/
void consumer()
{
    sigemptyset(&sigSet);
    sigaddset(&sigSet, WAKEUP);
    sigaddset(&sigSet, SLEEP);
    
    // Run the Consumer Logic
    printf("Running Consumer Process.....\n");
    
    // TODO: Implement Consumer Logic (see page 129 in book)
    int i;
    while (1) {
        wakeupOther();
        sleepAndWait();
        i = getValue();
        consume(i);
    }
    
    // Exit cleanly from the Consumer Process
    _exit(1);
}

/**
 * Logic to run to the Producer Process
 **/
void producer()
{
    // Buffer value to write
    int value;

    // Set Signal Set to watch for WAKEUP signal
    sigemptyset(&sigSet);
    sigaddset(&sigSet, WAKEUP);
    sigaddset(&sigSet, SLEEP);

    // Run the Producer Logic
    printf("Running Producer Process.....\n");
    
    // TODO: Implement Producer Logic (see page 129 in book)
    while(1) {
        value = produce();
        putValue(buffer, value);
        wakeupOther();
        sleepAndWait();
    }

    // Exit cleanly from the Consumer Process
    _exit(1);
}

/**
 * Logic for sleep signal
 **/
void signalSleep(int num){
    printf("Sleep signal: %d\n", num);
}

/**
 * Logic for wakeup signal
 **/
void signalWakeup(int num) {
    printf("Wakeup signal: %d\n", num);
}

/**
 * Main application entry point to demonstrate forking off a child process that will run concurrently with this process.
 *
 * @return 1 if error or 0 if OK returned to code the caller.
 */
int main(int argc, char* argv[])
{
    pid_t  pid;

    //Wakeup and sleep signals are registered
    signal(SLEEP, signalSleep);
    signal(WAKEUP, signalWakeup);
    
    // Create shared memory for the Circular Buffer to be shared between the Parent and Child  Processes
    buffer = (struct CIRCULAR_BUFFER*)mmap(0,sizeof(buffer), PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    buffer->count = 0;
    buffer->lower = 0;
    buffer->upper = 0;

    // Use fork()
    pid = fork();
    if (pid == -1)
    {
        // Error: If fork() returns -1 then an error happened (for example, number of processes reached the limit).
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    // OK: If fork() returns non zero then the parent process is running else child process is running
    if (pid == 0)
    {
        // Run Producer Process logic as a Child Process
        otherPid = getppid();
        producer();
    }
    else
    {
        // Run Consumer Process logic as a Parent Process
        otherPid = pid;
        consumer();
    }

    // Return OK
    return 0;
}
