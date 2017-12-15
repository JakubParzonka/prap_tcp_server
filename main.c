#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv) {
    system("clear");
    if (argc != 2) {
        puts("Give me more arguments!");
        exit(1);
    }

    int socketIsAwesome;
    int newSocketIsAwesome;
    int portNumber;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    socklen_t clientAddress;
    char buffer[256];
    int n;

    socketIsAwesome = socket(AF_INET, SOCK_STREAM, 0);
    if (socketIsAwesome < 0) {
        perror("Problem during socket creation => ");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    portNumber = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNumber);

    if (bind(socketIsAwesome, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        puts("Problem during binding => ");
        exit(1);
    }

    if (listen(socketIsAwesome, 5) < 0)
        perror("Problem during listing => ");
    clientAddress = sizeof(cli_addr);


    int pid;
    while (1) {
        newSocketIsAwesome = accept(socketIsAwesome, (struct sockaddr *) &cli_addr, &clientAddress);
        if (newSocketIsAwesome < 0) {
            puts("accept() error");
            exit(1);
        }
            puts("Connection with client established!");
            printf("Current socket: %d\n", newSocketIsAwesome);
    }

    return 0;
}