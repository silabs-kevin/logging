/*************************************************************************
    > File Name: logging.h
    > Author: Kevin
    > Created Time: 2020-08-10
    > Description:
 ************************************************************************/

#ifndef LOGGING_H
#define LOGGING_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "logging_config.h"
#include "logging_color_def.h"

/* UTILS */
#ifndef   MIN
  #define MIN(a, b)         (((a) < (b)) ? (a) : (b))
#endif

#ifndef   MAX
  #define MAX(a, b)         (((a) > (b)) ? (a) : (b))
#endif

#if (LOGGING_CONFIG == LIGHT_WEIGHT)

#if (TIME_ON != 0)
#include "sl_sleeptimer.h"
#define TIME_INIT() sl_sleeptimer_init()
#define TIME_GET()  sl_sleeptimer_get_time()
#else
#define TIME_INIT()
#define TIME_GET()  0
#endif

#if (LOGGING_INTERFACE == SEGGER_RTT)
#define LOG(...)                SEGGER_RTT_printf(0, __VA_ARGS__)

#define INIT_LOG(x)                                                    \
  do{                                                                  \
    SEGGER_RTT_Init();                                                 \
    TIME_INIT();                                                       \
    LOGI("Project Boots, Compiled at %s - %s.\n", __DATE__, __TIME__); \
  }while (0)

#elif (LOGGING_INTERFACE == VCOM)
#define LOG(...)                printf(__VA_ARGS__)

#define INIT_LOG(x)                                                    \
  do{                                                                  \
    TIME_INIT();                                                       \
    LOGI("Project Boots, Compiled at %s - %s.\n", __DATE__, __TIME__); \
  }while (0)
#elif (LOGGING_INTERFACE == INTERFACE_BOTH)
#define LOG(...)                       \
  do {                                 \
    printf(__VA_ARGS__);               \
    SEGGER_RTT_printf(0, __VA_ARGS__); \
  } while (0)

#define INIT_LOG(x)                                                    \
  do{                                                                  \
    SEGGER_RTT_Init();                                                 \
    TIME_INIT();                                                       \
    LOGI("Project Boots, Compiled at %s - %s.\n", __DATE__, __TIME__); \
  }while (0)
#else
#define LOG(...)
#define INIT_LOG(x)
#endif

#if (LOGGING_INTERFACE == SEGGER_RTT)
#elif (LOGGING_INTERFACE == VCOM)
#elif (LOGGING_INTERFACE == INTERFACE_BOTH)
#else
#endif

static inline void __fill_file_line(char *in,
                                    uint8_t in_len,
                                    const char *file_name,
                                    unsigned int line)
{
  char *p, *n, *posend;
  char tmp[FILE_NAME_LENGTH] = { 0 };

  if (!file_name || !in) {
    return;
  }

  p = in;

  n = strrchr(file_name, '/');
  if (!n) {
    n = strrchr(file_name, '\\');
  }
  n = (n ? n + 1 : (char *)file_name);
  posend = strchr(n, '.');

  memcpy(tmp,
         n,
         MIN(FILE_NAME_LENGTH, posend - n));

  snprintf(p,
           in_len,
           "[%10.10s:%-5d]",
           tmp,
           line);
  return;
}

#define __LOG_FILL_HEADER(flag)                                          \
  char exclusive_buf__[PREF_LEN] = { 0 };                                \
  char exclusive_buf__1[FILE_LINE_LEN] = { 0 };                          \
  uint32_t t = TIME_GET();                                               \
  __fill_file_line(exclusive_buf__1, FILE_LINE_LEN, __FILE__, __LINE__); \
  sprintf(exclusive_buf__, FMT_PREF,                                     \
          t / (24 * 60 * 60),                                            \
          (t % (24 * 60 * 60)) / (60 * 60),                              \
          (t % (60 * 60)) / (60),                                        \
          t % 60,                                                        \
          exclusive_buf__1,                                              \
          (flag)                                                         \
          );                                                             \

#define LOGF(__fmt__, ...)                             \
  do {                                                 \
    __LOG_FILL_HEADER(FTL_FLAG);                       \
    LOG("%s" __fmt__, exclusive_buf__, ##__VA_ARGS__); \
    abort();                                           \
  } while (0)

#define LOGE(__fmt__, ...)                               \
  do {                                                   \
    if (LOGGING_LEVEL >=  LOGGING_ERROR) {               \
      __LOG_FILL_HEADER(ERR_FLAG);                       \
      LOG("%s" __fmt__, exclusive_buf__, ##__VA_ARGS__); \
    }                                                    \
  } while (0)

#define LOGW(__fmt__, ...)                               \
  do {                                                   \
    if (LOGGING_LEVEL >=  LOGGING_WARNING) {             \
      __LOG_FILL_HEADER(WRN_FLAG);                       \
      LOG("%s" __fmt__, exclusive_buf__, ##__VA_ARGS__); \
    }                                                    \
  } while (0)

#define LOGI(__fmt__, ...)                               \
  do {                                                   \
    if (LOGGING_LEVEL >=  LOGGING_IMPORTANT_INFO) {      \
      __LOG_FILL_HEADER(IPM_FLAG);                       \
      LOG("%s" __fmt__, exclusive_buf__, ##__VA_ARGS__); \
    }                                                    \
  } while (0)

#define LOGH(__fmt__, ...)                               \
  do {                                                   \
    if (LOGGING_LEVEL >=  LOGGING_DEBUG_HIGHTLIGHT) {    \
      __LOG_FILL_HEADER(DHL_FLAG);                       \
      LOG("%s" __fmt__, exclusive_buf__, ##__VA_ARGS__); \
    }                                                    \
  } while (0)

#define LOGD(__fmt__, ...)                               \
  do {                                                   \
    if (LOGGING_LEVEL >=  LOGGING_DEBUG) {               \
      __LOG_FILL_HEADER(DBG_FLAG);                       \
      LOG("%s" __fmt__, exclusive_buf__, ##__VA_ARGS__); \
    }                                                    \
  } while (0)

#define LOGV(__fmt__, ...)                               \
  do {                                                   \
    if (LOGGING_LEVEL >=  LOGGING_VERBOSE) {             \
      __LOG_FILL_HEADER(VER_FLAG);                       \
      LOG("%s" __fmt__, exclusive_buf__, ##__VA_ARGS__); \
    }                                                    \
  } while (0)
#else // #if (LOGGING_CONFIG == LIGHT_WEIGHT)
void logging_init(uint8_t level_threshold);
void log_n(void);
void logging_level_threshold_set(uint8_t l);
int __log(const char *file_name, unsigned int line,
          int lvl,
          const char *fmt, ...);
void hex_dump(const uint8_t *array_base,
              size_t len,
              uint8_t align);

#define INIT_LOG(x) logging_init(x)

#define LOG(lvl, fmt, ...) __log(__FILE__, __LINE__, (lvl), (fmt), ##__VA_ARGS__)
#define LOGN() log_n()

#define HEX_DUMP_8(array_base, len)  hex_dump((array_base), (len), 8)
#define HEX_DUMP_16(array_base, len)  hex_dump((array_base), (len), 16)
#define HEX_DUMP_32(array_base, len)  hex_dump((array_base), (len), 32)

/*
 * Below 7 LOGx macros are used for logging data in specific level.
 */
#define LOGF(fmt, ...) \
  do { LOG(LOGGING_FATAL, (fmt), ##__VA_ARGS__); abort(); } while (0)
#define LOGE(fmt, ...) LOG(LOGGING_ERROR, (fmt), ##__VA_ARGS__)
#define LOGW(fmt, ...) LOG(LOGGING_WARNING, (fmt), ##__VA_ARGS__)
#define LOGI(fmt, ...) LOG(LOGGING_IMPORTANT_INFO, (fmt), ##__VA_ARGS__)
#define LOGH(fmt, ...) LOG(LOGGING_DEBUG_HIGHTLIGHT, (fmt), ##__VA_ARGS__)
#define LOGD(fmt, ...) LOG(LOGGING_DEBUG, (fmt), ##__VA_ARGS__)
#define LOGV(fmt, ...) LOG(LOGGING_VERBOSE, (fmt), ##__VA_ARGS__)

#define LOGBGE(what, err) LOGE(what " returns Error[0x%04x]\n", (err))

#endif // #if (LOGGING_CONFIG > LIGHT_WEIGHT)

void logging_demo(void);
#ifdef __cplusplus
}
#endif
#endif //LOGGING_H
