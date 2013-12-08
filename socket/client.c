#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "common.h"

int main(int argc, char *argv[])
{
    int sockfd = 0;
    char buff[BUFF_LENGTH];
    struct sockaddr_in serv_addr;
    
    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }
    
    memset(buff, 0, sizeof(buff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }
    
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }
    
    ssize_t readlen, writelen;
    while (1)
    {
        memset(buff, 0, sizeof(buff));
        scanf("%s", buff);
        
        writelen = write(sockfd, buff, strlen(buff));
        switch (writelen)
        {
            case -1:
                // couldn't send
                perror("Send to socket error. ");
                exit(EXIT_SUCCESS);
            default:
                break;
        }
        
        readlen = read(sockfd, buff, sizeof(buff));
        switch (readlen) {
            case -1:
                // couldn't read
                perror("Read from socket error. ");
                exit(EXIT_SUCCESS);
            default:
                break;
        }

        printf("%s\n", buff);
    }
}
