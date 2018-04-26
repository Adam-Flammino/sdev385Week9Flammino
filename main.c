// Displays all running processes, allows user to select individual processes for more info
// based on https://stackoverflow.com/questions/33266678/how-to-extract-info-in-linux-with-a-c-code-from-proc
// Adam Flammino 4/25
// SDEV385 week 9 assignment


#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

/**
 * Takes process id, gives info from proc
 * @param argc = process id
 */
void info(int argc) {
    printf("pid = %d\n", argc);

    char filename[1000];
    sprintf(filename, "/proc/%d/stat", argc);
    FILE *f = fopen(filename, "r");

    int unused;
    char comm[1000];
    char state;
    int ppid;
    fscanf(f, "%d %s %c %d", &unused, comm, &state, &ppid);
    printf("comm = %s\n", comm);
    printf("state = %c\n", state);
    printf("parent pid = %d\n", ppid);
    fclose(f);
}


int main(){
    int process;
    int runAgain = 1;
    printf("Running processes:\n");
    system("dir /proc | grep -o '[[:digit:]]*'"); //BASH command piped with grep to only print numbers- these are the PIDs
    while (runAgain != 0){
        printf("Which process ID would you like more info on?\n");
        scanf("%d",&process);
        info(process);
        printf("Run again? 0 for no, 1 for yes\n");
        scanf("%d", &runAgain);
    }


    return 0;
}