/*************************************************************************
 *  @file logging_color_def.h
 *  @author Kevin
 *  @date 2020-08-10
 *  @note
 ************************************************************************/

#ifndef LOGGING_COLOR_DEF_H
#define LOGGING_COLOR_DEF_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "logging_config.h"

#if (LOGGING_INTERFACE == SEGGER_RTT || LOGGING_INTERFACE == INTERFACE_BOTH)
#include "segger_rtt/SEGGER_RTT.h"
#else
#include <stdio.h>
/******************************************************************
 * Copied from RTT
 * ***************************************************************/
#define RTT_CTRL_RESET                "[0m"         // Reset to default colors
#define RTT_CTRL_CLEAR                "[2J"         // Clear screen, reposition cursor to top left

#define RTT_CTRL_TEXT_BLACK           "[2;30m"
#define RTT_CTRL_TEXT_RED             "[2;31m"
#define RTT_CTRL_TEXT_GREEN           "[2;32m"
#define RTT_CTRL_TEXT_YELLOW          "[2;33m"
#define RTT_CTRL_TEXT_BLUE            "[2;34m"
#define RTT_CTRL_TEXT_MAGENTA         "[2;35m"
#define RTT_CTRL_TEXT_CYAN            "[2;36m"
#define RTT_CTRL_TEXT_WHITE           "[2;37m"

#define RTT_CTRL_TEXT_BRIGHT_BLACK    "[1;30m"
#define RTT_CTRL_TEXT_BRIGHT_RED      "[1;31m"
#define RTT_CTRL_TEXT_BRIGHT_GREEN    "[1;32m"
#define RTT_CTRL_TEXT_BRIGHT_YELLOW   "[1;33m"
#define RTT_CTRL_TEXT_BRIGHT_BLUE     "[1;34m"
#define RTT_CTRL_TEXT_BRIGHT_MAGENTA  "[1;35m"
#define RTT_CTRL_TEXT_BRIGHT_CYAN     "[1;36m"
#define RTT_CTRL_TEXT_BRIGHT_WHITE    "[1;37m"

#define RTT_CTRL_BG_BLACK             "[24;40m"
#define RTT_CTRL_BG_RED               "[24;41m"
#define RTT_CTRL_BG_GREEN             "[24;42m"
#define RTT_CTRL_BG_YELLOW            "[24;43m"
#define RTT_CTRL_BG_BLUE              "[24;44m"
#define RTT_CTRL_BG_MAGENTA           "[24;45m"
#define RTT_CTRL_BG_CYAN              "[24;46m"
#define RTT_CTRL_BG_WHITE             "[24;47m"

#define RTT_CTRL_BG_BRIGHT_BLACK      "[4;40m"
#define RTT_CTRL_BG_BRIGHT_RED        "[4;41m"
#define RTT_CTRL_BG_BRIGHT_GREEN      "[4;42m"
#define RTT_CTRL_BG_BRIGHT_YELLOW     "[4;43m"
#define RTT_CTRL_BG_BRIGHT_BLUE       "[4;44m"
#define RTT_CTRL_BG_BRIGHT_MAGENTA    "[4;45m"
#define RTT_CTRL_BG_BRIGHT_CYAN       "[4;46m"
#define RTT_CTRL_BG_BRIGHT_WHITE      "[4;47m"
#endif

#ifdef __cplusplus
}
#endif
#endif //LOGGING_COLOR_DEF_H
