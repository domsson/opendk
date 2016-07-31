#include <string>
#include <unistd.h>
#include <iostream>

#include "OpenDK.hpp"

int main() {
	char *path = getcwd(nullptr, 0);
	std::cout << "CWD: " << path << std::endl;

	OpenDK::OpenDK openDK;
	openDK.run();

	delete path;
	return 0;
}
