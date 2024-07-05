// This code is GPLed by Yan Shoshitaishvili

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "logging.h"

int log_level = 50;

void vexc_debug(const char *fmt, ...)
{
    if (log_level > 10)
        return;

    fprintf(stderr, "[[vex_c]]\tDEBUG:\t");
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fflush(stdout);
}

void vexc_info(const char *fmt, ...)
{
    if (log_level > 20)
        return;

    fprintf(stderr, "[[vex_c]]\tINFO:\t");
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fflush(stdout);
}

void vexc_error(const char *fmt, ...)
{
    if (log_level > 40)
        return;

    fprintf(stderr, "[[vex_c]]\tERROR:\t");
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fflush(stderr);
}