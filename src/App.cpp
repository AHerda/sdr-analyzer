#include <App.hpp>
#include <utils.hpp>

#include <ctime>
#include <iostream>
#include <thread>

void App::run() {
    // AirSpy::counter = 0;
    // in minutes
    int time = 1;
    std::time_t startTime = std::time(0);
    airSpy.startRx(&dataProcessor);

    std::thread timerThread([&]() {
        std::cout << "this thread will work for " << time << " minute" << (time != 1 ? "s\n" : "\n");
        std::this_thread::sleep_for(std::chrono::minutes(time));
        airSpy.stopRx();
        std::cout << "Stopped receiving after 1 minute." << std::endl;
    });
    timerThread.join();

    // auto min = dataProcessor.getMin();
    // auto max = dataProcessor.getMax();
    std::cout << "RESULTS OF WHOLE APP\n";
    auto avgs = dataProcessor.getAvgs();

    logStatsOfVec(
        avgs,
        Info {
            "",
            "../data/pokoj.csv",
            startTime,
            time * 60,
            true
        }
    );
}
