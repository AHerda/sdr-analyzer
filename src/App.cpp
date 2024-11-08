#include <App.hpp>

void App::run() {
    airSpy.startRx(&dataProcessor);

    while (true) {
    }
}
