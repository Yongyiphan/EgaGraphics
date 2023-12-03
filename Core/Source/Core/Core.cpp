#include <epch.h>
#include "Core.h"

#include <iostream>

namespace Core {

				void PrintHelloWorld()
				{
								std::cout << "Hello World!\n";
								std::cin.get();
				}

				void SetDriver(Core::Driver SelectedDriver) {
								CurrentDriver = SelectedDriver;
				}
}