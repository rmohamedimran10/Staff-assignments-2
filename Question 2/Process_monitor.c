# Staff-assignments-2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    printf("Main Web Server (PID: %d) starting...\n", getpid());
    
    // 1. Create child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // CHILD PROCESS: Simulating an unresponsive state (infinite loop)
        printf("Child Process (PID: %d) handling request... but gets stuck!\n", getpid());
        while(1) { 
            sleep(1); 
        }
    } else {
        // PARENT PROCESS: Monitors the execution
        printf("Server Monitor: Tracking Child (PID: %d)\n", pid);
        
        // Wait 3 seconds to see if child finishes naturally
        sleep(3); 
        
        // 4. Terminate unresponsive child using signals
        printf("Server Monitor: Child is unresponsive. Sending SIGKILL...\n");
        kill(pid, SIGKILL);
        
        // 3. Prevent zombie processes by waiting for the killed child
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFSIGNALED(status)) {
            printf("Server Monitor: Child reaped successfully. Zombie prevented.\n");
        }
    }

    return 0;
}
