//
//  SimpleServer.c
//  CommandLineApp
//
//  Created by Guo Jiazhen on 12/2/13.
//  Copyright (c) 2013 Guo Jiazhen. All rights reserved.
//

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#include "common.h"

#define TIME_LENGTH 24
#define SLEEP_INTERVAL 1


int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char buff[BUFF_LENGTH];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error(listenfd, "socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(buff, 0, sizeof(buff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    const int op = 1;
    handle_error(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &op, 4),
                 "setsockopt");

    handle_error(bind(listenfd, (struct sockaddr*)&serv_addr,
                      sizeof(serv_addr)), "bind");

    handle_error(listen(listenfd, 10), "listen");

    ssize_t readlen = 0, writelen = 0;
    char sendBuff[BUFF_LENGTH + TIME_LENGTH];

    while (1)
    {
         // waiting for connection
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        handle_error(connfd, "accept");

        // connection established
        bool connection_loop = true;
        while(connection_loop)
        {
            readlen = read(connfd, buff, sizeof(buff));
            switch (readlen)
            {
                case -1:
                    // client error
                    perror("Read from client failed. Terminating connection.");
                    connection_loop = false;
                    break;
                case 0:
                    // client down
                    printf("Peer down. Terminating connection.");
                    connection_loop = false;
                    break;
                default:
                    break;
            }

            if (!connection_loop)
            {
                close(connfd);
                break;
            }

            if (buff[0] == 'q' || buff[0] == 'Q')
            {
                // client request of closing connection
                printf("Peer request of closing connection accepted.");
                connection_loop = false;
                char byeMessage[10];
                writelen = write(connfd, "Bye", strlen(byeMessage));
                close(connfd);
                break;
            }

            // get the time add to echo
            ticks = time(NULL);
            memset(sendBuff, 0, sizeof(sendBuff));
            snprintf(sendBuff, sizeof(sendBuff), "%.24s: ", ctime(&ticks));
            strcat(sendBuff, buff);

            writelen = write(connfd, sendBuff, strlen(sendBuff));
            switch (writelen)
            {
                case -1:
                    // write error
                    printf("Server write error. Terminating connection.");
                    connection_loop = false;
                    break;
                case 0:
                    // wait for next loop to write
                    break;
                default:
                    break;
            }
            if (!connection_loop)
            {
                close(connfd);
                break;
            }

            //sleep(SLEEP_INTERVAL);
        }
    }
}
