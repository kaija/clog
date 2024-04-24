#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include "log.h"

#define TIME_LEN 64

static char curr_time[TIME_LEN];
static int  log2screen = 1;
static int  log2file;
static char log_file_name[128];
static FILE *log_fp = NULL;
static int  log_level = DEBUG;

struct {
    char text[8];
    char ctext[16];
}log_text[]={
    {"DEBUG", "\033[1;32mDEBUG"},
    {"INFO",  "\033[1;36mINFO"},
    {"WARN",  "\033[1;33mWARNING"},
    {"ERROR", "\033[1;35mERROR"},
    {"FATAL", "\033[1;31mFATAL"}
};

static char *print_lv_text(int lv, int color){
    if(color) return log_text[lv].ctext;
    else return log_text[lv].text;
}

static char *print_time()
{
    time_t now;
    struct timeval tv;
    struct tm *nowtm;
    gettimeofday(&tv, NULL);
    now = tv.tv_sec;
    nowtm = localtime(&now);
    char timebuf[TIME_LEN];
    strftime(timebuf, TIME_LEN, "%Y-%m-%d %H:%M:%S", nowtm);
    snprintf(curr_time, TIME_LEN + 32, "%s %06ld",timebuf, (long)tv.tv_usec);
    return curr_time;
}

int log_set_level(int level)
{
    if(level < DEBUG || level > FATAL) return -1;
    log_level = level;
    return 0;
}
int log_set_opt(int opt);

static int log_open_file()
{
    log_fp = fopen(log_file_name, "w");
    LOG(INFO, "Log file save to %s\n", log_file_name);
    return 0;
}

int log_set_file(char *file)
{
    strncpy(log_file_name, file, 128);
    log2file = 1;
    log_open_file();
    return 0;
}

int log_close_file()
{
    if(log_fp){
        fclose(log_fp);
        log_fp = NULL;
    }
    return 0;
}

void log_print(int level, char *file, int line, char *fmt, ...)
{
    char buf[1024];
    va_list vl;
    va_start(vl, fmt);
    vsnprintf(buf, sizeof(buf),fmt, vl);
    va_end(vl);
    if(log2screen){
		if(level < log_level) return;
#ifdef COLOR_LOG
        fprintf(stderr, "%16s| %s ( %s:%d ) %s", print_lv_text(level, 1), print_time(), file, line, buf);
        fprintf(stderr, "\033[0m");
#else
        fprintf(stderr, "%8s| %s ( %s:%d ) %s", print_lv_text(level, 0), print_time(), file, line, buf);
#endif
    }
    if(log2file && log_fp){
		if(level < log_level) return;
        fprintf(log_fp, "%s %s ( %s:%d ) %s", print_lv_text(level, 0), print_time(), file, line, buf);
    }
}

