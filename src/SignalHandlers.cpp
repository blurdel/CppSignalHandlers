
#include <chrono>
#include <iostream>
#include <thread>
#include <signal.h>


bool running = true;

// Catch CTRL+C to tell application to shutdown
inline void stopHandler(int)
{
	running = false;
	std::cout << "Got signal to shutdown." << std::endl;
}

inline void setupSignalHandlers()
{
	signal(SIGINT,  stopHandler);
	signal(SIGTERM, stopHandler);
}

int main()
{
	std::cout << "Press CTRL+C to signal shutdown" << std::endl;

	setupSignalHandlers();

	while (running) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "running ..." << std::endl;
	}

	std::cout << "Done." << std::endl;
	return 0;
}
