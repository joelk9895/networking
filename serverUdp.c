#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENT 100

struct sockaddr_in server_address, client_address[MAX_CLIENT];
int server_socket;
socklen_t len = sizeof(client_address);
int client_count = 0;

void *handle_client_message(void *args)
{
    char buffer[1024] = {0};
    while (1)
    {
        memset(&buffer, 0, sizeof(buffer));
        int n = recvfrom(server_socket, buffer, 1024, 0, (struct sockaddr *)&client_address[client_count], &len);
        if (n > 0)
        {
            buffer[n] = '\0';
            printf("%s\n", buffer);
            client_count++;
            for (int i = 0; i < client_count; i++)
            {
                int m = sendto(server_socket, buffer, strlen(buffer), 0, (const struct sockaddr *)&client_address[i], len);
            }
        }
    }
    return NULL;
}

int main()
{
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    char *hello = "Hello from server";
    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, handle_client_message, NULL);
    pthread_join(thread_id, NULL);
    close(server_socket);
}