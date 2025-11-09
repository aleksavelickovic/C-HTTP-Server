#include <stdio.h>
#include <sys/socket.h>

int main(void) {
    printf("Hello, World!\n");

    int sock_status = socket(AF_INET, SOCK_STREAM, 0);


    return 0;
}
