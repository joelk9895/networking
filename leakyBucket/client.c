#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr = {.sin_family = AF_INET, .sin_port = htons(PORT)};
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int bucket_size, output_rate, packet_size, input;

    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);
    send(sock, &bucket_size, sizeof(bucket_size), 0);

    printf("Enter output rate: ");
    scanf("%d", &output_rate);
    send(sock, &output_rate, sizeof(output_rate), 0);

    printf("Enter number of packets: ");
    scanf("%d", &packet_size);
    send(sock, &packet_size, sizeof(packet_size), 0);

    for (int i = 0; i < packet_size; i++)
    {
        printf("Enter packet %d: ", i + 1);
        scanf("%d", &input);
        send(sock, &input, sizeof(input), 0);
    }

    close(sock);
    return 0;
}