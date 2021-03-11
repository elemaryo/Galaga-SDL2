#ifndef _STAR_H
#define _STAR_H
#include "Timer.h"
#include "Texture.h"

using namespace QuickSDL;

class Star : public Texture {

private:

	static bool sScroll;

	Timer* mTimer;

	// true if star is visible, used for flickering
	bool mVisible;

	float mFlickerTimer;

	float mFlickerSpeed;

	// scroll stars on screen
	float mScrollSpeed;

public:
	// Galaga has three star layers that define star size
	Star(int layer);
	~Star();

	static void Scroll(bool b);

	void Update();
	void Render();

private:
	void ScrollStar();

};
#endif // !1

