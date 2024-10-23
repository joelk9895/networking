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
    FILE *file = fopen(buffer, "rb");
    char *message;
    if (file == NULL)
    {
        message = "File Not Found";
        send(client_socket, message, strlen(message), 0);
    }

    while (1)
    {
        int byteread = fread(buffer, 1, 1024, file);
        send(client_socket, buffer, strlen(buffer), 0);
        if (byteread < 1024)
        {
            if (feof(file))
            {
                printf("File transfered complete");
            }
            if (ferror(file))
            {
                printf("File Error");
            }
            break;
        }
    }

    close(socket_fd);
    close(client_socket);
    return 0;
}