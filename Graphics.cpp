#include "Graphics.h"

//type header file method
Graphics* Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

// Static functions
Graphics* Graphics::Instance() {
	if (sInstance == NULL) {
		sInstance = new Graphics();
	}

	return sInstance;
}

void Graphics::Release() {
	delete sInstance;
	sInstance = NULL;
	sInitialized = false;
}

bool Graphics::Initalized() {
	return sInitialized;
}

// Constructor
Graphics::Graphics() {
	mBackBuffer = NULL;
	sInitialized = Init();
}

// Destructor
Graphics::~Graphics() {
	//destroy window
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	// close sdl
	SDL_Quit();
}

// Initializer function
bool Graphics::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Initialization Error: $s\n", SDL_GetError());
		return false;
	}
	// paramter is window title, x, y , width, height, show flag
	mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (mWindow == NULL) {
		printf("Window Creation Error: $s\n", SDL_GetError());
		return false;
	}
	// show all textures at once
	mBackBuffer = SDL_GetWindowSurface(mWindow);

	return true;
}

void Graphics::Render() {
	// refreshes the back buffer of the window
	SDL_UpdateWindowSurface(mWindow);
}
