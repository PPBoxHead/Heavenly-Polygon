#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// save this, is for later 
// https://stackoverflow.com/questions/19472398/opening-a-new-terminal-window-in-c

/* 
* C format specifiers for printf:
    %s for strings(char*)
    %d or % i for integers
    %f for floating - point numbers
    %c for characters
    %p for pointers
    %x for hexadecimal integers
*/

typedef enum {
	C_INFO,
	C_WARNING,
	C_ERROR
} logType;

// Print values to the console specified by logType in <log>
//      C_INFO <- prints a BLUE log
//      C_WARNING <- prints a YELLOW log
//      C_ERROR <- prints a RED log
// Followed by the console text you want to print on <format>. For debug variable values use the C format specifiers
//    % s for strings(char*)
//    % d or % i for integers
//    % f for floating - point numbers
//    % c for characters
//    % p for pointers
//    % x for hexadecimal integers
static void console_print(logType log, const char* format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];  // Adjust buffer size as needed
    vsnprintf(buffer, sizeof(buffer), format, args);

    switch (log) {
        case C_ERROR:
            fprintf(stderr, "\033[0;38;5;196m[ERROR]::\033[0m%s\033[0m\n", buffer);
            break;
        case C_WARNING:
            fprintf(stderr, "\033[0;38;5;214m[WARNING]::\033[0m%s\033[0m\n", buffer);
            break;
        case C_INFO:
            fprintf(stdout, "\033[0;38;5;44m[INFO]::\033[0m%s\033[0m\n", buffer);
            break;
    }

    va_end(args);
}


// Note, some links with references about the colors on the console:
// https://en.wikipedia.org/wiki/ANSI_escape_code
// https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences

#endif // CONSOLE_LOGGER_H
