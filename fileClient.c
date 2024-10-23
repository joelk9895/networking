#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

struct sockaddr_in server_address;

int main()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        printf("Socket creation failed\n");
        return 1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8090);
    server_address.sin_addr.s_addr = INADDR_ANY;
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        printf("Server not found!\n");
        close(socket_fd);
        return 1;
    }

    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("Connection Failed!");
        return 1;
    }
    const char *hello = "joel.txt";
    send(socket_fd, hello, strlen(hello), 0);
    printf("Message Send Successfully\n");
    char buffer[1024] = {0};
    int byte_rec = recv(socket_fd, buffer, sizeof(buffer), 0);
    if (byte_rec > 0)
    {
        printf("Reveresed string: %s", buffer);
    }
    close(socket_fd);
    return 0;
}