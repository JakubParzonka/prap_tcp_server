#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "functions.h"

const int buffer_size = 1024;

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
    char *buffer;
    int x;

    buffer = (char *) malloc(buffer_size);

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


        pid = fork();

        if (pid < 0) {
            perror("fork operation error ");
            exit(1);
        } else if (pid == 0) {
            while (1) {
                x = (int) read(newSocketIsAwesome, buffer, buffer_size);
                if (x < 0) {
                    perror("read operation error ");
                    exit(1);
                }

                if (x == 0) {
                    printf("socket nr: %d closed\n", newSocketIsAwesome);
                    close(newSocketIsAwesome);
                    break;
                }
                printf("Message from client %d: %s\n", newSocketIsAwesome, buffer);

                /**
                 * Spliting message from client
                 */
                char **tempMessage = str_split(buffer, '\n');
                char **splittedMessage = str_split(tempMessage[0], ' ');
                free(tempMessage);
                int size = getMessageSize(splittedMessage);

                char *preparedMessage = pickOneOperation(splittedMessage, size);
                free(splittedMessage);

                printf("\nSize = %d\nMessage to server: %s\n", size,preparedMessage);

                puts("\n\n=======================================================================\n\n");
                x = (int) write(newSocketIsAwesome, preparedMessage, buffer_size);
                if (x < 0) {
                    perror("write operation error ");
                    exit(1);
                }
            }
        }

    }

    return 0;
}
