#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUFF_SIZE 256

int SetupTCPClientSocket(char *server, char * port);

void *recv_handler(void *sock)
{
    int sockID = *((int*)sock);
    char buf[BUFF_SIZE];
    size_t readBytes;
    //printf("[Recv] Socket id: %d\n", sockID);

    while((readBytes = recv(sockID, buf, BUFF_SIZE - 1, 0))) {
        buf[readBytes] = '\0';
        printf("%s\n", buf);
    }

    return NULL;
}

int main(int argc, char **argv)
{
    if(argc != 3) {
        fprintf(stderr, "Usage:\n\t%s <host> <port>\n", argv[0]);
        exit(-1);
    }

    pthread_t recvThread;
    char *host = argv[1];
    char *port = argv[2];

    //printf("Trying to connect...\n");
    int sockID = SetupTCPClientSocket(host, port);
    if(sockID < 0)
    {
        perror("Socket unable to connect");
        exit(-1);
    }
    //printf("Connected! Spawning thread...\n");

    pthread_create(&recvThread, NULL, recv_handler, &sockID);
    //printf("Thread created! Waiting on it to finish...\n");

    char *buf = NULL;
    size_t size = 0;
    ssize_t chars = 0;
    ssize_t sendSize;
    while(1) {
        if((chars = getline(&buf, &size, stdin)) != -1) {
            if(buf[chars - 1] == '\n') {
                buf[--chars] = '\0';
            }

            if(strcmp(buf, "quit") == 0) {
                printf("Goodbye!\n");
                break;
            }
            //printf("Sending '%s'\n", buf);
            sendSize = send(sockID, buf, strlen(buf),0);
            if(sendSize <= 0) {
                perror("Failed to send");
            }
            //free(buf);
        }
    }
    sleep(2);

    pthread_cancel(recvThread);
    close(sockID);
    
    return 0;
}
