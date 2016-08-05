#include <stdafx.h>
#include "TywEngine\framework\Engine.h"



int main(int argc, const char * const *argv)
{
	Engine::getInstance().Init(argc, argv, nullptr, 800, 600);
	while (1)
	{
		Engine::getInstance().Frame();

	}

	return 0;
}