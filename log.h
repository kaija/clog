#ifndef __LOG_H
#define __LOG_H

#define LOG_FATAL   4
#define LOG_ERROR   3
#define LOG_WARN    2
#define LOG_INFO    1
#define LOG_DEBUG   0
void log_print(int level, char *file, int line, char *fmt, ...);
#define LOG(level, fmt, args...) log_print(level, __FILE__,__LINE__, fmt, ##args)

int log_set_file(char *file);
int log_close_file();
#endif
