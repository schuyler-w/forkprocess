/*
 This program will fork two child processes running the two programs generated in programming zero in parallel.
 Hint: You mant need to use fork(), exec() family, wait(), exit(), getpid() and etc   ...
 
 Requirements:
 

 1) Exactly two child processes are created, one to run testspecial program and the other is to run testalphabet program;
 2) When a program starts to run, print a message to the output screen showing which process (with PID) is running which program, for example:
    "CHILD <16741> process is executing testalphabet program!"
    
 3) When a program is done, the process exits and at the same time, a message should be print to the output screen showing which  process (with PID) is done with the program, for example:
    "CHILD <16741> process has done with testalphabet program !"
    
 4) The messages should match the real execution orders, i.e. when the testspecial program starts/ends, the right message should be print out. So you need to figure out how to get the starting/ending time of each 
 process.
   
   
 The expected screen print out should be similar as follows:
 
 CHILD <16741> process is executing testalphabet program!
 CHILD <16742> process is executing testspecial program!
, -> 745668
. -> 798072
... ...

CHILD <16742> process has done with testspecial program !
a -> 2973036
b -> 556908
... ...

CHILD <16741> process has done with testalphabet program !
 */

/*
 * Program 1
 * Name: Schuyler Wang
 * cssc1766@edoras.sdsu.edu
 * July 13, 2023
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

// function to run testalphabet
void runAlpha(void) {
    printf("CHILD <PID: %d> process is executing testalphabet program!\n", (int) getpid());
    char *alphaArgs[] = { "./testalphabet", NULL };
    execvp(alphaArgs[0], alphaArgs);
}

// function to run testspecial
void runSpecial(void) {
    printf("CHILD <PID: %d> process is executing testspecial program!\n", (int) getpid());
    char *specialArgs[] = { "./testspecial", NULL };
    execvp(specialArgs[0], specialArgs);
}

int main(void) {
    // creating 2 pid_t values for the two processes
    pid_t child_testAlpha, child_testSpecial;

    // Spawning first child fork
    child_testAlpha = fork();

    // Check failure
    if (child_testAlpha < 0) {
        perror("Fork failed");
    }
    // Child 1 code
    else if (child_testAlpha == 0) {
        runAlpha();
    }

    // Spawning second child fork
    else {
        child_testSpecial = fork();
        // Check failure
        if (child_testSpecial < 0) {
            perror("Fork failed");
        }
        // Child 2 code
        else if (child_testSpecial == 0) {
            runSpecial();
        }

        // parent process
        else {

            // Checking which process ended
            pid_t child_pid = wait(NULL);
            if (child_pid == child_testAlpha) {
                printf("CHILD <PID: %d> process has done with testalphabet program! See the results above!\n", (int) child_testAlpha);
            }
            else if (child_pid == child_testSpecial) {
                printf("CHILD <PID: %d> process has done with testspecial program! See the results above!\n", (int) child_testSpecial);
            }

            // checking which process ended second
            child_pid = wait(NULL);
            if (child_pid == child_testAlpha) {
                printf("CHILD <PID: %d> process has done with testalphabet program! See the results above!\n", (int) child_testAlpha);
            }
            else if (child_pid == child_testSpecial) {
                printf("CHILD <PID: %d> process has done with testspecial program! See the results above!\n", (int) child_testSpecial);
            }
        }
    }
    return 0;
}
