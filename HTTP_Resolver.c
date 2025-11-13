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

// char *resolvePath(const char *data) {
//     char *path = malloc(sizeof(data));
//     path[sizeof(data) - 1] = '\0';
//     return NULL;
// }
