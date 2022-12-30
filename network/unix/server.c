#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


// Port for communicating
#define PORT 5000
// number of connections
#define QUEUE_LENGTH 50
#define MY_SOCK_PATH "/tmp/"

#define error_handler(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

int main()
{
    int socket_id;
    int opt = 1;
    struct sockaddr_in my_address, peer_address;
    
    // Creating socket
    if ((socket_id = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        error_handler("socket");
    }

    if (setsockopt(socket_id, SOL_SOCKET,
                   SO_REUSEADDR, &opt,
                   sizeof(opt))) {
        error_handler("setsockopt");
    }

    // Bind socket
    memset(&my_address, 0, sizeof(my_address));

    // Setting address of socket for server
    my_address.sin_family= AF_INET; // setting internet protocol
    my_address.sin_port = htons(PORT);
    my_address.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(socket_id, (struct sockaddr *)&my_address, sizeof(my_address)) == -1)
    {
        error_handler("Bind");
    }

    // Listening the connections
    if (listen(socket_id, QUEUE_LENGTH) == -1)
    {
        error_handler("listen");
    }
    
    int count_of_sending = 0;
    while (1)
    {
        // Setting address of socket for client
        socklen_t peer_size = sizeof(peer_address);
        if ((accept(socket_id, (struct sockaddr*)&peer_address, &peer_size)) == -1)
        {
            error_handler("accept");
        }
        
        char* buffer;
        memset(buffer, 0, 255);
        read(socket_id, buffer, 255);
        printf("received message: %s\n", buffer);

        char* message;
        memset(message, 0, 255);
        if (count_of_sending == 10)
        {
            memcpy(message, "exit", 4);
        }
        else
        {
            memcpy(message, "Hello from server", 17);
        }
        send(socket_id, message, strlen(message), 0);

        // Deallocating
        free(buffer);
        free(message);
    }

    close(socket_id);
}
