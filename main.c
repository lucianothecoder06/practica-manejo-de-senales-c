#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("Received signal %d\n", sig);
    exit(0);
}

int main(int argc, char *argv[])
{

    
    return 0;
}
