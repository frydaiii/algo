#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{   
    char *cat = "/bin/cat";
    if (argc < 2 ) {
        printf(" Please type a file name. \n ");
        return 1 ;
    }
    char *command = malloc( strlen(cat) + strlen(argv[1]) + 2);
    sprintf(command, "%s %s" , cat , argv[1]);
    printf("Before: %s \n", command);
    
    //santinize input
    int len = strlen(command);
    int i = 0;
    int j = 0;
    for (; i < len; i++) {
        if (command[i] == ';') break;
        else if (command[i] == ' ') {
            j++;
            if (j == 2) break;
        }
    }
    char * cmd2 = malloc(i);
    for (j = 0; j < i; j++) cmd2[j] = command[j];
    
    printf("After: %s \n", cmd2);
    
    //unsafe
    system(cmd2);
    
    return 0;
    
    
    
    
    
    //safe API
    char *v[3] ;
    v[0] = "/bin/cat";
    v[1] = argv[1];
    v[2] = 0;

    execve(v[0], v, 0);
    
    
    return 0;
}