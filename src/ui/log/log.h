#ifndef IMG_LOG_H
#define IMG_LOG_H

#include <imgui.h>

class Logger {
    ImGuiTextBuffer m_buf;
public:
    Logger();
    void Clear();
    void Logf(const char *fmt, ...) IM_FMTARGS(2);
    void Logln(const char *msg);
    void ShowLog(bool *show_log);
};

#endif /* IMG_LOG_H */
