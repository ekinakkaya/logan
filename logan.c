#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logan.h"

/* global variables */
int logan_biggest_id = -1;



/* TODO: add different error messages. think about how to
 * handle different errors. maybe a func for every error?
 */


void logan_error(char *errormessage) {
    printf("%s\n", errormessage);
    exit(1);
}



void logan(logan_s *logger, char *filename) {
    logger->filename = malloc(sizeof(char) * strlen(filename) + 1);
    if (logger->filename == NULL)
        logan_error("LOGAN: Allocation failed to logger->filename\n");

    strcpy(logger->filename, filename);


    logger->id = logan_biggest_id + 1;
    logan_biggest_id++;


    pthread_mutex_lock( &(logger->lock) );


    logger->logfile = fopen(filename, "w");
    if (logger->logfile == NULL)
        logan_error("LOGAN: failed to open logfile\n");

    fprintf(logger->logfile, "Created at TIME, DATE by PROCESSNAME PROCESSID\n");
    fclose(logger->logfile);
    

    pthread_mutex_unlock( &(logger->lock) );
}



void logan_log(logan_s *logger, char *logmessage) {
    logger->logfile = fopen(logger->filename, "a");
    if (logger->logfile == NULL)
        logan_error("LOGAN: failed to open logfile\n");


    fprintf(logger->logfile, "%s\n", logmessage);
    fclose(logger->logfile);
}



void logan_free(logan_s *logger) {
    free(logger->filename);
}

/* TODO: seperate the main() from this file to a test.
 * write tests.
 */


int main() {
    /* TODO: change this program to be used with a pointer type. such as:
     * logan_s *logger;
     *
     * to do this, just allocate memory for *logger too. and free *logger itself.
     * and you're good.
     */


    logan_s logger;
    logan(&logger, "logfile.txt");

    logan_log(&logger, "Hello!!!");
    logan_log(&logger, "Hello!!!");
    logan_log(&logger, "Hello!!!");

    logan_free(&logger);

    return 0;
}
