#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "html.h"

char* parse_tag(const char* html, const char* tag) {
    char open_tag[32], close_tag[32];
    sprintf(open_tag, "<%s>", tag);
    sprintf(close_tag, "</%s>", tag);

    const char* start = strstr(html, open_tag);
    const char* end = strstr(html, close_tag);

    if (start && end) {
        start += strlen(open_tag);
        size_t len = end - start;

        char* content = malloc(len + 1);
        strncpy(content, start, len);
        content[len] = '\0';

        return content; // caller frees this
    }
    return NULL; // tag not found
}
