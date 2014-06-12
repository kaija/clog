#ifndef __LOG_H
#define __LOG_H

#define FATAL   4
#define ERROR   3
#define WARN    2
#define INFO    1
#define DEBUG   0
void log_print(int level, char *file, int line, char *fmt, ...);
#define LOG(level, fmt, args...) log_print(level, __FILE__,__LINE__, fmt, ##args)

#define LOG_DEBUG(fmt, args...) log_print(DEBUG, __FILE__,__LINE__, fmt, ##args)
#define LOG_INFO(fmt, args...) log_print(INFO, __FILE__,__LINE__, fmt, ##args)
#define LOG_WARN(fmt, args...) log_print(WARN, __FILE__,__LINE__, fmt, ##args)
#define LOG_ERROR(fmt, args...) log_print(ERROR, __FILE__,__LINE__, fmt, ##args)
#define LOG_FATAL(fmt, args...) log_print(FATAL, __FILE__,__LINE__, fmt, ##args)


int log_set_file(char *file);
int log_close_file();

int	log_set_level(int level);
int	log_set_opt(int opt);

#endif
