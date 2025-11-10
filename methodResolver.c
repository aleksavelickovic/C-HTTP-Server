//
// Created by aleksa on 11/10/25.
//

#include "methodResolver.h"

#include <ctype.h>
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
