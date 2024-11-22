/*
 * Protocoale de comunicatii
 * Laborator 7 - TCP
 * Echo Server
 * server.c
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include "helpers.h"

// Primeste date de pe connfd1 si trimite mesajul receptionat pe connfd2, la serverul de echo connfd1 == connfd2
int receive_and_send(int connfd1, int connfd2)
{
    char buf[BUFLEN];
    int bytes_send;
    int bytes_remaining;
    int bytes_received = 0;

    // TODO 6: Receptionati un mesaj de la connfd1
    if (recv(connfd1, buf, sizeof(buf), 0) < 0){
        printf("Couldn't receive\n");
        return -1;
    }


    if (bytes_received != 0) {
        fprintf(stderr, "Received: %s", buf);
    }

    bytes_remaining = bytes_received;

    // TODO 7: Timiteti mesajul la connfd2
 
    if (send(connfd2, buf, strlen(buf), 0) < 0){
        printf("Can't send\n");
        return -1;
    }

    return bytes_received;
}

void run_echo_server(int listenfd)
{
    struct sockaddr_in client_addr;

    int bytes_received;
    int connfd = -1;
    socklen_t socket_len = sizeof(struct sockaddr_in);

    // TODO 4: Ascultati pentru un singur client pe socketul dat
    if(listen(listenfd, 1) < 0){
        printf("Error while listening\n");
        return -1;
    }



    printf("\nListening for incoming connections.....\n");
    // TODO 5: Acceptati o conexiune
    int client_size;
    client_size = sizeof(client_addr);
    connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_size);
 
    if (connfd < 0){
        printf("Can't accept\n");
        return -1;
    }
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    do {
        bytes_received = receive_and_send(connfd, connfd);
    } while (bytes_received > 0);

    // TODO 8: Inchideti conexiunea si socket-ul clientului
    close(connfd);
}

void run_chat_server(int listenfd)
{
    struct sockaddr_in client_addr1;
    struct sockaddr_in client_addr2;

    int bytes_received;
    int connfd1 = -1;
    int connfd2 = -1;
    socklen_t socket_len = sizeof(struct sockaddr_in);

    // TODO 4: Ascultati pentru doi clineti pe socketul dat
    if(listen(listenfd, 2) < 0){
        printf("Error while listening\n");
        return -1;
    }
    printf("\nListening for incoming connections.....\n");

    // TODO 5: Acceptati doua conexiuni
    int client_size1;
    client_size1 = sizeof(client_addr1);
    connfd1 = accept(listenfd, (struct sockaddr*)&client_addr1, &client_size1);
 
    if (connfd1 < 0){
        printf("Can't accept\n");
        return -1;
    }
    printf("Client1 connected at IP: %s and port: %i\n", inet_ntoa(client_addr1.sin_addr), ntohs(client_addr1.sin_port));


    int client_size2;
    client_size2 = sizeof(client_addr2);
    connfd2 = accept(listenfd, (struct sockaddr*)&client_addr2, &client_size2);
 
    if (connfd2 < 0){
        printf("Can't accept\n");
        return -1;
    }
    printf("Client2 connected at IP: %s and port: %i\n", inet_ntoa(client_addr2.sin_addr), ntohs(client_addr2.sin_port));

    do {
        bytes_received = receive_and_send(connfd1, connfd2);

        if (bytes_received == 0)
            break;

        bytes_received = receive_and_send(connfd2, connfd1);
    } while (bytes_received > 0);

    // TODO 8: Inchideti conexiunile si socketii creati
    close(connfd1);
    close(connfd2);
}

int main(int argc, char* argv[])
{
    int listenfd = -1;
    struct sockaddr_in serv_addr;
    socklen_t socket_len = sizeof(struct sockaddr_in);


    if (argc != 3) {
        printf("\n Usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    // TODO 1: Creati un socket TCP pentru receptionarea conexiunilor
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenfd < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // TODO 2: Completati in serv_addr adresa serverului pentru bind, familia de adrese si portul rezervat pentru server
    struct sockaddr_in server_addr;
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // TODO 3: Asociati adresa serverului cu socketul creat folosind bind
    if(bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");


    // run_echo_server(listenfd);
    run_chat_server(listenfd);


    // TODO 9: Inchideti socketul creat
    close(listenfd);
    return 0;
}
