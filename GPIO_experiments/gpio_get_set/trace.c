/* ------------------------------------------------------------------------------------------ */
/*                                                                                            */
/*                                                                                            */
/*                              Trace.c                                                       */
/*                                                                                            */
/*                     Utilities for output to trace file.                                    */
/*                                                                                            */
/* ------------------------------------------------------------------------------------------ */

#include    <time.h>
#include    <sys/time.h>            /* settimeofday */
#include    <unistd.h>
#include    <sys/types.h>
#include    <stdio.h>
#include    <stdlib.h>              /* exit() */
#include    <stdint.h>
#include    <fcntl.h>               /* O_RDWR */
#include    <string.h>              /* memcpy */

#include    "config.h"
#include    "trace.h"

/* ------------------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------------------ */

FILE                *trace_file;                            /* file for trace output */
int                 rv;

/* ------------ trace_init ------------------------------------------------------------------ */

int trace_init(const char *trace_file_name) {

time_t      now;

//    trace_file = fopen(trace_file_name, "a");               /* open file for trace output (append) */
    trace_file = fopen(trace_file_name, "w");               /* open file for trace output */
    if(trace_file == NULL) {
        internal_error(__FILE__, __LINE__, (const char *)"cannot open trace file");
        return(1);
    }

    now = time(NULL);
//    fprintf(trace_file, "File %s opened: %s\n", trace_file_name, ctime(&now));
    fflush(trace_file);
    return(0);

}

/* ------------ trace_f --------------------------------------------------------------------- */

int trace_f(const char *t_format) {

    if(trace_file == NULL) {                                /* trace file is not opened */
        rv = printf(t_format);
    }
    else {                                                  /* trace file opened */
        rv = fprintf(trace_file, t_format);
        fflush(trace_file);
    }

    return(rv);

}

/* ------------ trace_fi -------------------------------------------------------------------- */

int trace_fi(const char *t_format, int i) {

    if(trace_file == NULL) {                                /* trace file is not opened */
        rv = printf(t_format, i);
    }
    else {                                                  /* trace file opened */
        rv = fprintf(trace_file, t_format, i);
        fflush(trace_file);
   }

    return(rv);

}

/* ------------ trace_fii ------------------------------------------------------------------- */

int trace_fii(const char *t_format, int i, int j) {

    if(trace_file == NULL) {                                /* trace file is not opened */
        rv = printf(t_format, i, j);
    }
    else {                                                  /* trace file opened */
        rv = fprintf(trace_file, t_format, i, j);
        fflush(trace_file);
    }

    return(rv);

}

/* ------------ trace_fiii ------------------------------------------------------------------ */

int trace_fiii(const char *t_format, int i, int j, int k) {

    if(trace_file == NULL) {                                /* trace file is not opened */
        rv = printf(t_format, i, j, k);
    }
    else {                                                  /* trace file opened */
        rv = fprintf(trace_file, t_format, i, j, k);
        fflush(trace_file);
    }

    return(rv);

}

/* ------------ trace_fiiii ----------------------------------------------------------------- */

int trace_fiiii(const char *t_format, int i, int j, int k, int l) {

    if(trace_file == NULL) {                                /* trace file is not opened */
        rv = printf(t_format, i, j, k, l);
    }
    else {                                                  /* trace file opened */
        rv = fprintf(trace_file, t_format, i, j, k, l);
        fflush(trace_file);
    }

    return(rv);

}

/* ------------ trace_fs -------------------------------------------------------------------- */

int trace_fs(const char *t_format, char *s) {

    if(trace_file == NULL) {                                /* trace file is not opened */
        rv = printf(t_format, s);
    }
    else {                                                  /* trace file opened */
        rv = fprintf(trace_file, t_format, s);
        fflush(trace_file);
    }

    return(rv);

}

/* ------------ trace_fis ------------------------------------------------------------------- */

int trace_fis(const char *t_format, int i, char *s) {

    if(trace_file == NULL) {                                /* trace file is not opened */
        rv = printf(t_format, i, s);
    }
    else {                                                  /* trace file opened */
        rv = fprintf(trace_file, t_format, i, s);
        fflush(trace_file);
    }

    return(rv);

}

/* ------------ trace_fsis ------------------------------------------------------------------- */

int trace_fsis(const char *t_format, char *s1, int i, char *s2) {

    if(trace_file == NULL) {                                /* trace file is not opened */
        rv = printf(t_format, s1, i, s2);
    }
    else {                                                  /* trace file opened */
        rv = fprintf(trace_file, t_format, s1, i, s2);
        fflush(trace_file);
    }

    return(rv);

}

/* ------------ trace_fd -------------------------------------------------------------------- */

int trace_fd(const char *t_format, double d) {

    if(trace_file == NULL) {                                /* trace file is not opened */
        rv = printf(t_format, d);
    }
    else {                                                  /* trace file opened */
        rv = fprintf(trace_file, t_format, d);
        fflush(trace_file);
   }

    return(rv);

}

/* ------------ trace_fddd ------------------------------------------------------------------ */

int trace_fddd(const char *t_format, double d1, double d2, double d3) {

    if(trace_file == NULL) {                                /* trace file is not opened */
        rv = printf(t_format, d1, d2, d3);
    }
    else {                                                  /* trace file opened */
        rv = fprintf(trace_file, t_format, d1, d2, d3);
        fflush(trace_file);
   }

    return(rv);

}

/* ------------ trace_close ----------------------------------------------------------------- */

void trace_close(void) {

    if(trace_file != NULL) {                                /* close trace file */
        fclose(trace_file);
    }

}

/* ------------ internal_error -------------------------------------------------------------- */

void internal_error(const char *fn, int line_nr, const char *txt) {

struct timespec delay;

    trace_fsis("\n>>> Internal error: %s[%i]: %s <<<\n\n", (char *)fn, line_nr, (char *)txt);

}

/* ------------ END ------------------------------------------------------------------------- */
