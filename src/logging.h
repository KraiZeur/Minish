#ifndef LOGGING_H
#define LOGGING_H

#define TRACE_DEBUG      "DEBUG"
#define TRACE_INFO       "INFO"
#define TRACE_WARNING    "WARNING"
#define TRACE_ERROR      "ERROR"
#define TRACE_FATAL      "FATAL"

void initLoggingFile (const char *path);
void logging (const char *tag, const char *format, ...);

#endif /* LOGGING_H */