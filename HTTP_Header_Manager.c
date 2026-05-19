//
// Created by aleksa on 5/19/26.
//

#include "HTTP_Header_Manager.h"
#include "external/uthash/src/uthash.h"

struct HTTP_Header {
    char key[1000];
    char value[1000];
    UT_hash_handle hh;
};

struct HTTP_Header *headers = NULL;

void add_header(struct HTTP_Header *s) {
    HASH_ADD_STR(headers, key, s);
}

struct HTTP_Header *get_header(char key) {
    struct HTTP_Header *s;
    HASH_FIND_STR(headers, &key, s);
    return s;
}

void delete_header(struct HTTP_Header *header) {
    HASH_DEL(headers, header);
}
