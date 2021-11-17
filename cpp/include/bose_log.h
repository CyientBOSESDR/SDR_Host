
#ifndef __BOSELOG_H__
#define __BOSELOG_H__

#include <stdarg.h>

enum {
	LOG_ERR=1,
	LOG_WARN,
	LOG_INFO,
	LOG_DBG,
};


#define BOSE_LOG(log_level, fmt, ...) \
		bose_log(log_level,fmt,##__VA_ARGS__)

extern FILE *log_fp;
extern int log_level;
extern void bose_log(int level, char *fmt, ...);

#endif /* __BOSELOG_H__ */
