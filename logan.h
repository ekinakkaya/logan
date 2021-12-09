#ifndef LOGAN_H
#define LOGAN_H


/* TODO:
 * use os detection and make the program cross-platform
 */


/* definitions for os detection */
#define LOGAN_OS_UNKNOWN   -1
#define LOGAN_OS_LINUX     0
#define LOGAN_OS_MAC       1
#define LOGAN_OS_WINDOWS   2

#ifdef _WIN32
    #define LOGAN_OS LOGAN_OS_WINDOWS
#elif __linux
    #define LOGAN_OS LOGAN_OS_LINUX
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #define LOGAN_OS LOGAN_OS_MAC
    #else
        #define LOGAN_OS LOGAN_OS_UNKNOWN
    #endif
#else
    #define LOGAN_OS LOGAN_OS_UNKNOWN
#endif

#include <stdio.h>
#include <stdlib.h>

// use something else for windows, OBVIOUSLY
// https://stackoverflow.com/questions/2150938/can-i-get-unixs-pthread-h-to-compile-in-windows
#include <pthread.h>



typedef struct logan_s_ {
    char *filename;
    int id;

    FILE *logfile;
    int isopen;

    pthread_mutex_t lock;
} logan_s;


/* initiates logger, which is logan_s */
void logan(logan_s *logger, char *filename);


/* writes log message to logfile */
void logan_log(logan_s *logger, char *logmessage);


/* frees logan_s structure and it's content from memory*/
void logan_free(logan_s *logger);


/* print error message to console and quit(1) */
void logan_error(char *errormessage);



#endif
