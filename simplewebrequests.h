#pragma once
#include <stdio.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#endif

#ifdef linux
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

typedef struct website_s {
    int status;
    int port;
    char *host;
    char *directory;
    char *cookies;
    char *headers;
    char *content;
} website;

void website_parseUrl(website *self, char *url) {
    
}

typedef struct http_s {
    struct website_s website;
    void (*get)(struct http_s *self, char *url);
    void (*post)(struct http_s *self, char *url, char *postfields);
} http;

void http_get(http *self, char *url) {



#ifdef _WIN32
    
    WSADATA wsaData;
    SOCKET sock;
    struct hostent *host;
    
    
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("ERROR: WSAStartup failed to run.\n");
        return;
    }

    struct addrinfo hints;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) != 0) {
        printf("ERROR: Failed to create socket.\n");
        return;
    }

    host = gethostbyname(url);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo()


    if (connect(sock, (struct sockaddr *)(&hints), sizeof(hints)) != 0) {
        printf("ERROR: Failed to connect.\n");
        return;
    }

    printf("success");
    closesocket(sock);
    WSACleanup();

#endif

}