#include "GameManager.h"


int main(int argc, char* argv[]) {

	// create instance of game manager
	GameManager* game = GameManager::Instance();
	game->Run();

	GameManager::Release();
	// to avoid dangling pointers
	game = NULL;
	return 0;
}