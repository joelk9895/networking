#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = {.sin_family = AF_INET, .sin_addr.s_addr = INADDR_ANY, .sin_port = htons(PORT)};
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    int new_socket = accept(server_fd, NULL, NULL);
    int frame;

    srand(time(0));

    while (1)
    {
        recv(new_socket, &frame, sizeof(frame), 0);
        printf("Received frame %d\n", frame);

        int success = rand() % 2;
        if (success)
        {
            int ack = 1;
            printf("Acknowledgment sent for frame %d\n", frame);
            send(new_socket, &ack, sizeof(ack), 0);
        }
        else
        {
            printf("Simulated timeout for frame %d\n", frame);
            int ack = 0;
            send(new_socket, &ack, sizeof(ack), 0);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}