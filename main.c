#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void) {
    int server_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];
    const char *response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "Hello, world!";

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081); // Port 8081
    server_addr.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces

    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_socket);
        exit(1);
    }

    listen(server_socket, 5);
    printf("Server running on http://localhost:8081\n");

    while (1) {
        const int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("accept failed");
            continue;
        }

        read(client_socket, buffer, sizeof(buffer) - 1);
        write(client_socket, response, strlen(response));
        close(client_socket);
    }

    close(server_socket);
    return 0;
}
