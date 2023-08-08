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
