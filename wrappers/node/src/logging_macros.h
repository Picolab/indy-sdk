
// loudest
#if INDY_LOG_LEVEL == 0

#define INDY_LOG_DEBUG 1
#define INDY_LOG_INFO 1
#define INDY_LOG_WARN 1
#define INDY_LOG_ERROR 1

// loud
#elif INDY_LOG_LEVEL == 1

#define INDY_LOG_INFO 1
#define INDY_LOG_WARN 1
#define INDY_LOG_ERROR 1

// quieter
#elif INDY_LOG_LEVEL == 2

#define INDY_LOG_WARN 1
#define INDY_LOG_ERROR 1

// quietest
#elif INDY_LOG_LEVEL == 3

#define INDY_LOG_ERROR 1

#else

#define INDY_LOG_WARN 1
#define INDY_LOG_ERROR 1

#endif