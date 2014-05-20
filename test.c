#include <stdio.h>
#include "log.h"
int main()
{
    LOG(LOG_DEBUG, "line1\n");
    LOG(LOG_INFO, "line2\n");
    LOG(LOG_WARN, "line3\n");
    LOG(LOG_ERROR, "line4\n");
    LOG(LOG_FATAL, "line5\n");
    return 0;
}
