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

int main()
{
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    char *message = "Hello from client";
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    int n = recvfrom(client_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_address, &len);
    buffer[n] = '\0';
    printf("Received time from server: %s\n", buffer);
    close(client_socket);
    return 0;
}