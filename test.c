#include <stdio.h>
#include "log.h"
int main()
{
    log_set_file("/tmp/a.log");
    LOG(LOG_DEBUG, "line1\n");
    LOG(LOG_INFO, "line2\n");
    LOG(LOG_WARN, "line3\n");
    LOG(LOG_ERROR, "line4\n");
    LOG(LOG_FATAL, "line5\n");
    log_close_file();
    return 0;
}
