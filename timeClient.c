#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define PORT 8080

struct sockaddr_in server_address;
int client_socket;
char buffer[1024] = {0};
socklen_t len = sizeof(server_address);

void *recieveMessage(void *args)
{
    while (1)
    {
        memset(&buffer, 0, sizeof(buffer));
        int n = recvfrom(client_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_address, &len);
        if (n < 0)
        {
            perror("Receive failed");
            close(client_socket);
        }
        buffer[n] = '\0';
        printf("Messages: %s\n", buffer);
    }
    return NULL;
}

int main()
{
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    char *hello = "Time";
    if (client_socket < 0)
    {
        perror("Socket creation failed");
        return 1;
    }
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    sendto(client_socket, hello, sizeof(hello), 0, (struct sockaddr *)&server_address, len);
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, recieveMessage, NULL);
    pthread_join(thread_id, NULL);
    close(client_socket);
    return 0;
}