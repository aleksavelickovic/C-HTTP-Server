//
// Created by aleksa on 5/19/26.
//

#ifndef HTTP_SERVER_HTTP_HEADER_MANAGER_H
#define HTTP_SERVER_HTTP_HEADER_MANAGER_H
#include "external/uthash/src/uthash.h"

struct HTTP_Header {
    char key[1000];
    char value[1000];
    UT_hash_handle hh;
};

void add_header(struct HTTP_Header *s);

struct HTTP_Header *get_header(const char *key);

void delete_header(const struct HTTP_Header *header);

#endif //HTTP_SERVER_HTTP_HEADER_MANAGER_H
