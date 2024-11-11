#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define WINDOW_SIZE 4

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = {.sin_family = AF_INET, .sin_addr.s_addr = INADDR_ANY, .sin_port = htons(PORT)};
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    int new_socket = accept(server_fd, NULL, NULL);
    int frame, expected_frame = 0;

    srand(time(0));

    while (1)
    {
        recv(new_socket, &frame, sizeof(frame), 0);

        if (frame == expected_frame)
        {
            printf("Received and acknowledged frame %d\n", frame);
            send(new_socket, &frame, sizeof(frame), 0);
            expected_frame++;
        }
        else
        {
            printf("Received out-of-order frame %d, expected %d\n", frame, expected_frame);
            send(new_socket, &frame, sizeof(frame), 0);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}