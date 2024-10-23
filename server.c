#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct sockaddr_in server_address;
struct sockaddr_in client_address;

int main()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int clientlen = sizeof(client_address);
    if (socket_fd == -1)
    {
        printf("Socket creation failed\n");
        return 1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8090);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("Bind Failed!\n");
        close(socket_fd);
        return 1;
    }
    if (listen(socket_fd, 5) < 0)
    {
        printf("Listen Failed!\n");
        return 1;
    }
    printf("Server Listening...\n");
    int client_socket = accept(socket_fd, (struct sockaddr *)&client_address, (socklen_t *)&clientlen);
    if (client_socket < 0)
    {
        printf("Accept Failed!");
        return 1;
    }
    printf("Client Request Accepted...\n");
    char buffer[1024] = {0};
    int byte_rec = recv(client_socket, buffer, sizeof(buffer), 0);
    if (byte_rec > 0)
    {
        printf("%s\n", buffer);
    }
    char *message = (char *)malloc(byte_rec + 1);
    for (int i = 0; i < byte_rec; i++)
    {
        message[i] = buffer[byte_rec - 1 - i];
    }
    message[byte_rec] = '\0';
    send(client_socket, message, strlen(message), 0);
    close(socket_fd);
    close(client_socket);
    return 0;
}