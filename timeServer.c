#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define PORT 8080
#define MAX_CLIENT 100

struct sockaddr_in server_address, client_address;
int server_socket;
socklen_t len = sizeof(client_address);
int client_count = 0;
char buffer[1024] = {0};

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
    int n = recvfrom(server_socket, &buffer, 1024, 0, (struct sockaddr *)&client_address, &len);
    time_t currentTime = time(NULL);
    char *timeStr = ctime(&currentTime);
    int m = sendto(server_socket, timeStr, strlen(timeStr), 0, (const struct sockaddr *)&client_address, len);
    close(server_socket);
}