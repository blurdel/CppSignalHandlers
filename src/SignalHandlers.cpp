
#include <chrono>
#include <iostream>
#include <thread>
#include <signal.h>
#include <unistd.h>
#include <wait.h>


bool running = true;
int count = 8;

// Catch CTRL+C to tell application to shutdown
inline void stopHandler(int)
{
	running = false;
	std::cout << "Got signal to shutdown." << std::endl;
}

inline void userHandler(int sig)
{
	std::cout << "Got user signal " << sig << ", count = " << count << std::endl;
}

inline void setupSignalHandlers()
{
	signal(SIGINT,  stopHandler);
	signal(SIGTERM, stopHandler);
	signal(SIGUSR1, userHandler); // USR
}

int main()
{
	std::cout << "Press CTRL+C to signal shutdown" << std::endl;

	setupSignalHandlers();

	while (running) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "or quitting in " << count << " seconds ..." << std::endl;

		if (--count == 0) {
			pid_t parent = getppid();
			kill(parent, SIGUSR1);
		}
	}

	std::cout << "Done." << std::endl;
	return 0;
}
