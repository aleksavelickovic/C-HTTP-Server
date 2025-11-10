#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void) {
    struct sockaddr_in server_addr;
    char buffer[1024];
    const char *response =
            "HTTP/0.9 200 OK\n"
            "Content-Type: text/plain\n"
            "Content-Length: 13\n"
            "\n"
            "Hello, world!";

    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int optval = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server);
        exit(EXIT_FAILURE);
    }

    listen(server, 5);
    printf("Server running on http://localhost:8081\n");

    while (true) {
        const int client = accept(server, NULL, NULL);
        if (client < 0) {
            perror("accept failed");
            continue;
        }

        read(client, buffer, sizeof(buffer) - 1);
        write(client, response, strlen(response));
        close(client);
    }

    close(server);
    return 0;
}
