#ifndef IMG_APP_H
#define IMG_APP_H

#include "renderer/renderer.h"
#include "png/png.h"
#include "png/chunks/chunk.h"

#include "ui/log/logger.h"
#include "ui/chunklist/chunklist.h"
#include "ui/chunkinspector/chunkinspector.h"

#define DEFAULT_WIDTH 1000
#define DEFAULT_HEIGHT 800

class App {
    Renderer* m_renderer;
    Logger* m_logger;
    Png* m_png;
    bool m_showList;
    bool m_showInspector;
    int m_inspectorIndex;
    bool m_showDemo;
    bool m_showInternals;
    bool m_showLogger;
    bool m_vsync;
public:
    App();
    ~App();
    void run();
private:
    void update();
    void showInternals(bool *p_open);
    void drawMainMenu();
};

#endif //IMG_APP_H
