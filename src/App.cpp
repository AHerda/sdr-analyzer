#include <App.hpp>
#include <utils.hpp>

#include <iostream>
#include <thread>

void App::run() {
    // AirSpy::counter = 0;
    // in minutes
    std::time_t startTime = std::time(0);
    airSpy.startRx(&dataProcessor);

    std::thread timerThread([&]() {
        std::cout << "this thread will work for " << duration << " second" << (duration != 1 ? "s\n" : "\n");
        std::this_thread::sleep_for(std::chrono::seconds(duration));
        airSpy.stopRx();
        std::cout << "Stopped receiving after 1 minute." << std::endl;
    });

    timerThread.join();

    logData(startTime);

    setAppend();
}

void App::logData(std::time_t startTime) {
    // auto min = dataProcessor.getMin();
    // auto max = dataProcessor.getMax();
    std::cout << "RESULTS OF WHOLE APP\n";
    auto avgs = dataProcessor.getAvgs();

    logStatsOfVec(
        avgs,
        Info {
            description,
            fileName,
            startTime,
            frequency,
            duration,
            append
        }
    );
}

void App::reset() {
    dataProcessor.reset();
}

void App::setDescription(std::string description_) {
    description = description_;
}

void App::setFileName(std::string fileName_) {
    fileName = fileName_;
}

void App::setDuration(uint32_t duration_) {
    duration = duration_;
}

void App::setAppend() {
    append = true;
}

void App::setFrequency(uint32_t frequency_) {
    frequency = frequency_ * 1000;
    airSpy.setFrequency(frequency * 1000);
}
