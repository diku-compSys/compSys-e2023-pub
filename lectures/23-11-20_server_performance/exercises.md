# Exercises for performant servers

## Theory tasks

### Q1

How many “Example” lines does this program print?

    void try()
    {
        if (fork() == 0) {
            fork(); 
            fork();
            printf("Example\n");
            return;
        }
        return;
    }
    
    int main()
    {
        try();
        printf("Example\n");
    }

### Q2

One of your colleagues is thinking of using signals to allow a parent process to count events that occur in a child process. The idea is to notify the parent each time an event occurs by sending it a signal and letting the parent’s signal handler increment a global counter variable, which the parent can then inspect after the child has terminated. However, when he runs the test program shown below, he discovers that when the parent calls printf, counter always has a value of 2, even though the child has sent five signals to the parent. Perplexed, he comes to you for help. Can you explain the bug?

    int counter = 0;

    void handler(int sig)
    {
        counter++;
        sleep(1); /* Do some work in the handler */
        return;
    }

    int main()
    {
        int i;
        signal(SIGUSR2, handler);

        if (fork() == 0) { /* Child */
            for (i = 0; i < 5; i++) {
                kill(getppid(), SIGUSR2);
                printf("sent SIGUSR2 to parent\n");
            }
            exit(0);
        }
        wait(NULL);
        printf("counter=%d\n", counter);
        exit(0);
    }

### Q3

The program below has a bug. The thread is supposed to sleep for 1 second and then print a string. However, when we run it on our system, nothing prints. Why?

    /* WARNING: This code is buggy! */
   void *thread(void *vargp);
    
    int main()
    {
        pthread_t tid;
        pthread_create(&tid, NULL, thread, NULL);
        exit(0);
    }

    /* Thread routine */
    void *thread(void *vargp)
    {
        sleep(1);
        printf("Hello, world!\n");
        return NULL;
    }

### Q4

You can fix the code in Q3 by replacing the main functions exit function with one of two different Pthreads function calls. Which ones?


### Q5

Using the progress graph in progress.png, classify the following three trajectories as either safe or unsafe.

A. H2, L2, U2, H1, L1, S2, U1, S1, T1, T2
B. H2, H1, L1, U1, S1, L2, T1, U2, S2, T2
C. H1, L1, H2, L2, U2, S2, U1, S1, T1, T2

### Q6

Some network programming texts suggest the following approach for reading and writing sockets: Before interacting with the client, open two standard I/O streams on the same open connected socket descriptor, one for reading and one for writing:

    FILE *fpin, *fpout;

    fpin = fdopen(sockfd, "r");
    fpout = fdopen(sockfd, "w");

When the server finishes interacting with the client, close both streams as follows:

    fclose(fpin);
    fclose(fpout);

However, if you try this approach in a concurrent server based on threads, you will create a deadly race condition. Explain.

### Q7

Can the following program deadlock? Why or why not?

    Initially: a = 1, b = 1, c = 1.
        Thread 1:       Thread 2:
            P(a);           P(c);
            P(b);           P(b);
            V(b);           V(b);
            P(c);           V(c);
            V(c);
            V(a);

## Programming task
In C, create a peer that can act as a client and server at the same time. A Python example has been included which will both send and recieve messages concurrently. Your client should be able to do the same. 

Messages sent between the peers have a simple format. The only element in the header is 4 bytes giving the length of the following body. 