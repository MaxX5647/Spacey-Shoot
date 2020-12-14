
#include "MyGame.h"

int main( int argc, char* argv[] )
{

	if(argc!=2){
		std::cerr<<"Usage: "<<argv[0]<<" *.txt"<<std::endl;
		return 1;
	}

	SPACEYSHOOT::MyGame * game = new SPACEYSHOOT::MyGame(960,960);
	assert(game);
	SPACEYSHOOT::setMyGame(game);

	//Start up SDL and create window
	if( !game->init("SpaceyShoot") )
	{
		std::cerr<<"ERROR: Failed to initialize!"<<std::endl;
	}
	else
	{
		//Load media
		if( !game->loadMedia(argv[1]) )
		{
			std::cerr<<"ERROR: Failed to load media!"<<std::endl;
		}
		else
		{
			game->run();
		}
	}

	game->close();

	delete game;

	return 0;
}
