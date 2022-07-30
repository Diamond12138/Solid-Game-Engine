#include <iostream>
#include "../SolidGameEngine/Utils/Log.hpp"

int main()
{
	Solid::Utils::Log log(true);
	log.d("debug1","test1");
	log.setIsOutputToConsole(false);
	log.d("debug2","test2");
	std::cout << "----------" << std::endl;
	log.output_all_to_console();
	
	std::cout << "----------" << std::endl;
	Solid::Utils::log("debug log","debug log");
	Solid::Utils::logd("debug log 2","debug log 2");
	return 0;
}
