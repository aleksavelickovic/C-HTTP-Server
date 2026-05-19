//
// Created by aleksa on 11/10/25.
//

#ifndef HTTP_SERVER_METHODRESOLVER_H
#define HTTP_SERVER_METHODRESOLVER_H

struct HTTP_Header;

char *resolveMethod(const char *request);

char *resolvePath(const char *request);

struct HTTP_Header *resolveHeaders(const char *request);

#endif //HTTP_SERVER_METHODRESOLVER_H
