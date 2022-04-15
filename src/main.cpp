#include "renderer/renderer.h"

#define DEFAULT_WIDTH 1000
#define DEFAULT_HEIGHT 800

int main() {

    Renderer renderer(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    renderer.render();

    return 0;
}
