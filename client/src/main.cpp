#include <iostream>
#include "../includes/Game.hh"
#include "SystemFactory.hh"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	SystemFactory &factory = Singleton<SystemFactory>::Instance();
	srand(time(NULL));
	/*if (getenv("HOME") == NULL)
	{
		std::cerr << "Cannot start the program because of missing env variables" << std::endl;
		return (EXIT_FAILURE);
	}*/

	try
	{

		factory.createGraphics("rtype", 1360, 768);
		Game::initGame();

	}
	catch (std::exception &e)
	{
		return (EXIT_FAILURE);
	}
	return (engine::Instance().run());
}