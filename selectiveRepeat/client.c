#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define WINDOW_SIZE 4

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr = {.sin_family = AF_INET, .sin_port = htons(PORT)};
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int total_frames;
    printf("Enter the total number of frames to send: ");
    scanf("%d", &total_frames);

    int frame = 0;
    int window_start = 0;
    int acks[WINDOW_SIZE] = {0};

    while (window_start < total_frames)
    {
        for (int i = 0; i < WINDOW_SIZE && (window_start + i) < total_frames; i++)
        {
            printf("Sending frame %d\n", window_start + i);
            send(sock, &frame, sizeof(frame), 0);
            frame++;
        }

        for (int i = 0; i < WINDOW_SIZE && (window_start + i) < total_frames; i++)
        {
            int ack;
            recv(sock, &ack, sizeof(ack), 0);

            if (ack >= window_start)
            {
                printf("Acknowledgment received for frame %d\n", ack);
                acks[ack % WINDOW_SIZE] = 1;
            }
        }

        for (int i = 0; i < WINDOW_SIZE && (window_start + i) < total_frames; i++)
        {
            if (!acks[(window_start + i) % WINDOW_SIZE])
            {
                printf("No acknowledgment for frame %d, resending\n", window_start + i);
                frame = window_start + i;
                break;
            }
        }

        window_start++;
    }

    close(sock);
    return 0;
}