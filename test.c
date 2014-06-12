#include <stdio.h>
#include "log.h"
int main()
{
    //Set log file to /tmp/a.log
    log_set_file("/tmp/a.log");
    LOG(DEBUG, "line1\n");
    LOG(INFO, "line2\n");
    LOG(WARN, "line3\n");
    LOG(ERROR, "line4\n");
    LOG(FATAL, "line5\n");

    //use another method log
    LOG_DEBUG("line1\n");
    LOG_INFO("line2\n");
    LOG_WARN("line3\n");
    LOG_ERROR("line4\n");
    LOG_FATAL("line5\n");

    //set log level to warning
    log_set_level(WARN);
    LOG_DEBUG("line1\n");
    LOG_INFO("line2\n");
    LOG_WARN("line3\n");
    LOG_ERROR("line4\n");
    LOG_FATAL("line5\n");

    log_close_file();
    return 0;
}
