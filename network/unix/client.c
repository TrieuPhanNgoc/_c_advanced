#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    int32_t header;
    u_int8_t data;
} Message;

#define error_message(msg) \
    do { perror(msg); exit(EXIT_FAILURE); }while(0)


int main()
{
    int sock_fd = 0;
    struct sockaddr_in address_of_server;

    int ins = socket(AF_INET, SOCK_STREAM, 0);
    if (ins == -1)
    {
        error_message("socket");
    }

    address_of_server.sin_family = AF_INET;
    address_of_server.sin_port = htons(PORT);
    address_of_server.sin_addr.s_addr = INADDR_ANY;
    
    // Convert IPv4 and IPv6 address from text to binary form
    // if (inet_pton(AF_INET,"127.0.0.1", &address_of_server.sin_addr) == -1)
    // {
    //    error_message("inet_pton");
    // }
    
    // Connecting to server
    ins = connect(sock_fd, (struct sockaddr*)&address_of_server, sizeof(address_of_server));
    if ( ins == -1)
    {
        error_message("connect");
    }

    while (1)
    {
        const char* message = "Hello from client!";
        send(sock_fd, message, strlen(message), 0);

        char * buffer;
        memset(buffer, 0, 255);
        read(sock_fd, buffer, 255);
        printf("received message: %s\n", buffer);

        if (memcmp(buffer, "exit", 4) == 0)
        {
            break;
        }

        if (buffer != NULL)
        {
            free(buffer);
        }
    }


    close(sock_fd);

    return 0;
}
