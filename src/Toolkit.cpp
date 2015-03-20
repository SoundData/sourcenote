#include <iostream>
#include <string>
#include "Toolkit.h"
	
Toolkit::Toolkit() {
	std::cout << "Initialized the Toolkit class!\n";
	isSample = false;
}

void Toolkit::playTone(std::string message) {
	std::cout << "Playing tone: '" << message << "'.\n";
}