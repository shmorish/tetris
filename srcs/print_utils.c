#include "tetris.h"

// printfを使うためのラッパー関数
int printfwrapper(const char* format, va_list args) {
    return vprintf(format, args);
}

// printwを使うためのラッパー関数（ncurses用）
int printwwrapper(const char* format, va_list args) {
    return vwprintw(stdscr, format, args);
}

// 汎用の出力関数
int output(OutFunc outFunc, const char* format, ...) {
    va_list args;
    int len;

    va_start(args, format);
    len = outFunc(format, args);
    va_end(args);
    return len;
}
