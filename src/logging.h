#ifndef LOGGING_H
#define LOGGING_H

#define TRACE_DEBUG      "DEBUG"
#define TRACE_INFO       "INFOR"
#define TRACE_WARNING    "WARNI"
#define TRACE_ERROR      "ERROR"
#define TRACE_FATAL      "FATAL"

void initLoggingFile (const char *path);
void logging (const char *tag, const char *format, ...);
void closeLoggingFile ();

#endif /* LOGGING_H */