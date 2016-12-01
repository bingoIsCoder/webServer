#include "get_time.h"
#include <stdio.h>
#include <string.h>

char * get_time_str(char *time_buf)
{
    time_t now_sec;
    struct tm *time_now;

    if (-1 == time(&now_sec))
    {
        perror("time() error: in get_time.c");
        return NULL;
    }
    if (NULL == (time_now = gmtime(&now_sec)))
    {
        perror("gmtime() error: in get_time.c");
        return NULL;
    }
    char *str_ptr = NULL;
    if (NULL == (str_ptr = asctime(time_now)))
    {
        perror("asctime() in get_time.c");
        return NULL;
    }
    strcat(time_buf, str_ptr);
    return time_buf;
}
