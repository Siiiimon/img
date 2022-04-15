#ifndef IMG_APP_H
#define IMG_APP_H

#include "renderer/renderer.h"

#define DEFAULT_WIDTH 1000
#define DEFAULT_HEIGHT 800

class App {
    Renderer* m_renderer;
    bool m_showDemo;
    bool m_showInternals;
    bool m_vsync;
public:
    App();
    ~App();
    void run();
private:
    void update();
};

#endif //IMG_APP_H
