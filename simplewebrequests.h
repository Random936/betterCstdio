#pragma once
#include <stdio.h>

#ifdef _WIN32
#include <WinSock2.h>
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
} http_t;

void http_get(http_t *self, char *url) {

/*#ifdef _WIN32
    WSADATA wsaData;
    SOCKET sock;
    struct hostent *host;
    struct in_addr **addr_list;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("ERROR: WSAStartup failed to run.\n");
        return;
    }
#endif
#ifdef linux
    int sock, errornum;
#endif

    struct addrinfo hints, *servinfo;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) != 0) {
        printf("ERROR: Failed to create socket.\n");
        return;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_addr->sa_data = 

    #ifdef linux
    if ((errornum = getaddrinfo(url, "80", &hints, &servinfo)) != 0) {
        printf("ERROR: Failed to getaddrinfo with error %s\n", gai_strerror(errornum));
        return;
    }
    #endif

    if ((host = gethostbyname(url)) == NULL) {
        printf("ERROR: Failed to get host by name.\n");
        return;
    }

    //if (connect(sock, (struct sockaddr *)(&hints), sizeof(hints)) != 0) {
    //    printf("ERROR: Failed to connect.\n");
    //    return;
    //}

    
    printf("IP address: %s\n", inet_ntoa();
    closesocket(sock);
    WSACleanup();
    */
}