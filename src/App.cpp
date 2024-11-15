#include <App.hpp>
#include <utils.hpp>

#include <iostream>
#include <thread>

void App::run() {
    // AirSpy::counter = 0;
    airSpy.startRx(&dataProcessor);

    std::thread timerThread([&]() {
        int time = 120;
        std::cout << "this thread will work for " << time << " minutes\n";
        std::this_thread::sleep_for(std::chrono::minutes(120)); // Wait for 60 seconds
        airSpy.stopRx(); // Stop receiving after the wait
        std::cout << "Stopped receiving after 1 minute." << std::endl;
    });

    // Main loop (keep the program alive or do other tasks)
    // while (true) {
    //     // Perform any other tasks or keep the application alive
    //     // Optional: break out if needed based on a condition or state
    // }

    // Join the timer thread (optional, in case the program ends)
    timerThread.join();

    // auto min = dataProcessor.getMin();
    // auto max = dataProcessor.getMax();
    std::cout << "RESULTS OF WHOLE APP\n";
    auto avgs = dataProcessor.getAvgs();

    logStatsOfVec(avgs, "balkon-3:00", "../data/godzinny-test-3-4.csv");
}
