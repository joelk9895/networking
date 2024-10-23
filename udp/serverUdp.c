#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

struct sockaddr_in server_address, client_address;
int server_socket;
socklen_t len = sizeof(client_address);

int main()
{
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    char buffer[1024] = {0};

    int n = recvfrom(server_socket, buffer, 1024, 0, (struct sockaddr *)&client_address, &len);
    buffer[n] = '\0';
    printf("Received from client: %s\n", buffer);

    sendto(server_socket, buffer, n, 0, (struct sockaddr *)&client_address, len);

    close(server_socket);
    return 0;
}