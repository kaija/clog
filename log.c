#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include "log.h"

static char curr_time[32];
static int  cam_log_screen = 1;
static int  cam_log_file;
static char cam_log_file_name[128];
static FILE *cam_log_fp = NULL;

struct {
    char text[8];
    char ctext[16];
}cam_log_text[]={
    {"DEBUG", "\033[1;32mDEBUG"},
    {"INFO",  "\033[1;36mINFO"},
    {"WARN",  "\033[1;33mWARNING"},
    {"ERROR", "\033[1;35mERROR"},
    {"FATAL", "\033[1;31mFATAL"}
};

static char *print_lv_text(int lv, int color){
    if(color) return cam_log_text[lv].ctext;
    else return cam_log_text[lv].text;
}
static char *print_time()
{
    time_t now;
    struct timeval tv;
    struct tm *nowtm;
    gettimeofday(&tv, NULL);
    now = tv.tv_sec;
    nowtm = localtime(&now);
    char timebuf[32];
    strftime(timebuf, 32, "%Y-%m-%d %H:%M:%S", nowtm);
    snprintf(curr_time, 32, "%s %06ld",timebuf, tv.tv_usec);
    return curr_time;
}
static int cam_open_file()
{
    cam_log_fp = fopen(cam_log_file_name, "w");
    LOG(LOG_INFO, "Log file save to %s", cam_log_file_name);
    return 0;
}
int cam_set_log_file(char *file){
    strncpy(cam_log_file_name, file, 128);
    cam_log_file = 1;
    cam_open_file();
    return 0;
}
void cam_print(int level, char *file, int line, char *fmt, ...)
{
    char buf[1024];
    va_list vl;
    va_start(vl, fmt);
    vsnprintf(buf, sizeof(buf),fmt, vl);
    va_end(vl);
    if(cam_log_screen){
#ifdef COLOR_LOG
        fprintf(stderr, "%16s| %s | %s:%d | %s", print_lv_text(level, 1), print_time(), file, line, buf);
        fprintf(stderr, "\033[0m");
#else
        fprintf(stderr, "%16s| %s | %s:%d | %s", print_lv_text(level, 0), print_time(), file, line, buf);
#endif
    }
    if(cam_log_file && cam_log_fp){
        fprintf(cam_log_fp, "%s| %s %s:%d |%s", print_lv_text(level, 0), print_time(), file, line, buf);
    }
}

