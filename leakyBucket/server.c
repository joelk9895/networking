#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = {.sin_family = AF_INET, .sin_addr.s_addr = INADDR_ANY, .sin_port = htons(PORT)};
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    int new_socket = accept(server_fd, NULL, NULL);
    int bucket_size, output_rate, packet_size, input, buffer = 0;

    recv(new_socket, &bucket_size, sizeof(bucket_size), 0);
    recv(new_socket, &output_rate, sizeof(output_rate), 0);
    recv(new_socket, &packet_size, sizeof(packet_size), 0);

    for (int i = 0; i < packet_size; i++)
    {
        recv(new_socket, &input, sizeof(input), 0);

        if (input + buffer > bucket_size)
            printf("Packet %d dropped\n", i + 1);
        else
            buffer += input;

        printf("Buffer size after packet %d: %d\n", i + 1, buffer);

        if (buffer >= output_rate)
            buffer -= output_rate;
        else
            buffer = 0;

        printf("Buffer size after output: %d\n", buffer);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}