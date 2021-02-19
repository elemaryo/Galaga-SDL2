#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#endif

#include <sdl2/SDL.h>
#include <stdio.h>

class Graphics {
	// public variables for screen size
	public:
		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 600;

	// private variables
	private:
		// graphics is a single instance class
		static Graphics* sInstance;
		// boolean to check if graphics is initalized correctly
		static bool sInitialized;

		SDL_Window* mWindow;
		SDL_Surface* mBackBuffer;

	// public functions
	public:
		// returns our instance
		static Graphics* Instance();
		// clear memory after finish
		static void Release();
		static bool Initalized();
		// refresh background to draw to screen
		void Render();

	private:
		// constructor
		Graphics();
		// destructor
		~Graphics();
		// initializer
		bool Init();
};
