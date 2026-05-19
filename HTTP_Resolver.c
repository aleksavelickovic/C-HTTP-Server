//
// Created by aleksa on 11/10/25.
//

#include "HTTP_Resolver.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *resolveMethod(const char *request) {
    char *method = malloc(10);
    method[9] = '\0';
    for (int i = 0; i < strlen(request); i++) {
        if (isspace(request[i])) {
            break;
        }
        method[i] = request[i];
    }
    return method;
}

char *resolvePath(const char *request) {
    size_t len = strlen(request);
    char *path = malloc(len + 1);
    memcpy(path, request, len);
    path[len] = '\0';
    char *URI = malloc(len + 1);
    int counter = 0;
    int index = 0;
    for (int i = 0; i < strlen(request); i++) {
        if (counter > 2) {
            break;
        }
        if (isspace(request[i])) {
            counter++;
            continue;
        }
        if (counter == 1) {
            URI[index] = request[i];
            index++;
        }
    }
    return URI;
}
