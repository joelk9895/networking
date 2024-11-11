#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr = {.sin_family = AF_INET, .sin_port = htons(PORT)};
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int total_frames;
    printf("Enter the number of frames to send: ");
    scanf("%d", &total_frames);

    int frame = 0;

    while (frame < total_frames)
    {
        printf("Sending frame %d\n", frame);
        send(sock, &frame, sizeof(frame), 0);

        int ack;
        recv(sock, &ack, sizeof(ack), 0);

        if (ack)
        {
            printf("Acknowledgment received for frame %d\n", frame);
            frame++;
        }
        else
        {
            printf("Timeout for frame %d, resending\n", frame);
        }
    }

    close(sock);
    return 0;
}