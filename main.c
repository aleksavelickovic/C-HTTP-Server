#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h> // For realpath()
#include <limits.h> // For PATH_MAX
#include <setjmp.h>

#include "HTTP_Resolver.h"
jmp_buf jmp_buffer;
char *html = NULL;

void resolve(const char *path) {
    char html_absolute_path[PATH_MAX];
    char dest[500] = "../";
    const char *src = path;
    strcat(dest, src);
    if (setjmp(jmp_buffer) != 0) {
        strcpy(dest, "../resources/html/notfound.html");
    }
    if (strcmp(dest, "..//") == 0) {
        strcat(dest, "/resources/html/landing.html");
    }
    printf("PATH is: %s \n", dest);
    realpath(dest, html_absolute_path);

    FILE *fptr = fopen(html_absolute_path, "rb");
    if (fptr == NULL) {
        printf("Error! Could not open file!\n");
        longjmp(jmp_buffer, 1);
    }
    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    rewind(fptr);

    html = malloc(size + 1);

    if (html == NULL) {
        printf("Memory allocation failed!\n");
        fclose(fptr);
    }

    fread(html, 1, size, fptr);
}

int main(void) {
    struct sockaddr_in server_addr;
    char buffer[1024];


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
        printf("Request accepted!\n");

        read(client, buffer, sizeof(buffer) - 1);

        // if (setjmp(jmp_buffer) == 0) {
        const char *path = resolvePath(buffer);
        resolve(path);
        // } else {
        //     html = "<h1> 404 Not Found! </h1>";
        // }


        char response[1024 * 1024];
        snprintf(
            response,
            sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "\r\n"
            "%s",
            html
        );

        char *method2 = resolveMethod(buffer);
        printf("HTTP Method is: %s\n", method2);
        free(method2);
        char absolute_path[PATH_MAX];
        realpath("../temp/request.txt", absolute_path);

        FILE *file = fopen(absolute_path, "w+");
        fprintf(file, "%s", buffer);
        fclose(file);

        write(client, response, strlen(response));
        close(client);
        printf("Response sent!\n");
    }

    close(server);
    return 0;
}
