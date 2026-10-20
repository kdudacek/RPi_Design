/* ------------------------------------------------------------------------------------------ */
/*                                                                                            */
/*                                                                                            */
/*                                  Trace.h                                                   */
/*                                                                                            */
/*                                                                                            */
/*                                                                                            */
/* ------------------------------------------------------------------------------------------ */

/* ------------ --- ------------------------------------------------------------------------- */

#ifndef __TRACE_H__
#define __TRACE_H__

int trace_init(const char *trace_file_name) ;

int trace_f(const char *t_format) ;

int trace_fi(const char *t_format, int i) ;

int trace_fii(const char *t_format, int i, int j) ;

int trace_fiii(const char *t_format, int i, int j, int k) ;

int trace_fiiii(const char *t_format, int i, int j, int k, int l) ;

int trace_fs(const char *t_format, char *s) ;

int trace_fis(const char *t_format, int i, char *s) ;

int trace_fsis(const char *t_format, char *s1, int i, char *s2) ;

int trace_fd(const char *t_format, double d) ;

int trace_fddd(const char *t_format, double d1, double d2, double d3) ;

void trace_close(void) ;

void internal_error(const char *fn, int line_nr, const char *txt) ;

/* ------------------------------------------------------------------------------------------ */

#endif

/* ------------ END ------------------------------------------------------------------------- */
