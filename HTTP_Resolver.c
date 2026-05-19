//
// Created by aleksa on 11/10/25.
//

#include "HTTP_Resolver.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "external/uthash/src/uthash.h"
#include "HTTP_Header_Manager.h"

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
    URI[index] = '\0';
    return URI;
}

struct HTTP_Header *resolveHeaders(const char *request) {
    struct HTTP_Header *headers = NULL;

    char *line = strtok(request, "\r\n");
    if (!line) return NULL;

    line = strtok(NULL, "\r\n");

    while (line != NULL) {
        if (strlen(line) == 0) break;

        printf("HEADER: %s\n", line);

        char *colon = strchr(line, ':');
        if (!colon) {
            line = strtok(NULL, "\r\n");
            continue;
        }

        struct HTTP_Header *h1 = malloc(sizeof(struct HTTP_Header));

        size_t key_len = colon - line;
        strncpy(h1->key, line, key_len);
        h1->key[key_len] = '\0';

        char *value_start = colon + 1;
        while (*value_start == ' ') value_start++;

        strncpy(h1->value, value_start, sizeof(h1->value) - 1);
        h1->value[sizeof(h1->value) - 1] = '\0';

        add_header(h1);

        line = strtok(NULL, "\r\n");
    }

    return headers;
}
