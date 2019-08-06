/**
 * error.c
 *
 * Wraps up error reporting functions
 */

#include "error.h"

/**
 * error_report_with_message
 *
 * Reports an error with the given message, and terminates banter
 */
void error_report_with_message(char *msg) {
    printf("[error] \n%s\n", msg);
    exit(1);
    
}
