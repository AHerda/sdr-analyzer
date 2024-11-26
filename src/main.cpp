#include <App.hpp>

#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
    App app;
    int repeat = 1;

    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            if (std::strcmp(argv[i], "--frequency") == 0 || std::strcmp(argv[i], "-f") == 0)
                app.setFrequency(std::stoi(argv[++i]));
            else if (std::strcmp(argv[i], "--description") == 0 || std::strcmp(argv[i], "-d") == 0)
                app.setDescription(argv[++i]);
            else if (std::strcmp(argv[i], "--output") == 0 || std::strcmp(argv[i], "-o") == 0)
                app.setFileName(argv[++i]);
            else if (std::strcmp(argv[i], "--time") == 0 || std::strcmp(argv[i], "-t") == 0)
                app.setDuration(std::stoi(argv[++i]));
            else if (std::strcmp(argv[i], "--repeat") == 0 || std::strcmp(argv[i], "-r") == 0)
                repeat = std::stoi(argv[++i]);
            else if (std::strcmp(argv[i], "--append") == 0 || std::strcmp(argv[i], "-a") == 0)
                app.setAppend();
        }
    }

    for (int i = 0; i < repeat; i++) {
        std::cout << "Test iteration: " << i + 1 << "/" << repeat << " (" << (float) i / (float) repeat * 100. << "%)" << std::endl; 
        app.run();
        app.reset();
        std::this_thread::sleep_for(std::chrono::seconds(15));
    }

    return 0;
}
