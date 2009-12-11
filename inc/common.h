#ifndef COMMON_H
#define COMMON_H

#include "flogger.h"

const TUid KApplicationUid = { 0x100098e6 };

#define LOG(MSG) do {							\
	RFileLogger logger;						\
	logger.Connect();						\
	logger.CreateLog(_L("log"), _L("log"), EFileLoggingModeAppend);	\
	logger.Write(_L(MSG));						\
	logger.CloseLog();						\
	logger.Close();							\
} while(0);

#define LOGNUM(MSG) do {						\
	RFileLogger logger;						\
	logger.Connect();						\
	logger.CreateLog(_L("log"), _L("log"), EFileLoggingModeAppend);	\
	logger.WriteFormat(_L("%d"), MSG);				\
	logger.CloseLog();						\
	logger.Close();							\
} while(0);

#endif /* COMMON_H */
