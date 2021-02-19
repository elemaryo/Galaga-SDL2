#ifndef _MATH_HELPER_H
#define _MATH_HELPER_H


#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

struct Vector2
{
	float x;
	float y;

	// constructor for struct
	Vector2(float _x = 0.0f, float _y = 0.0f): x(_x), y(_y){}

	float MagnitudeSqr(){
		return x * x + y * y;
	}

	float Magnitude() {
		return (float)sqrt(x * x + y * y);
	}

	// returns vector2 normalized i.e just directional vector
	Vector2 Normalized() {
		float mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}

};

//& means reference here
inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2 RotateVector(Vector2& vec, float angle) {
	//angle in radians because math.h cosine/sine use radians
	float radAngle = (float)(angle * DEG_TO_RAD);
	return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle))));
}

#endif // !MATH_HELPER_H
