#include "Point.h"
#include <iostream>
#include <string>

Point::Point()
{
	x = 0; // x defaults to 0
	y = 0; // y defaults to 0
}

Point::Point(int x, int y)
{
	this->x = x; // Initialize x
	this->y = y; // Initialize y
}

/* Empty destructor ( no dynamic memory is used ) */
Point::~Point()
{
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

Point& Point::operator=(const Point& rhs)
{
	x = rhs.x; // Update x value
	y = rhs.y; // Update y value

	return *this; // Return updated self
}

bool Point::operator==(const Point& rhs)
{
	/* Two points are equal if their corresponding x and y coordinates are equal */
	return (x == rhs.x && y == rhs.y);
}

Point Point::operator+(const Point& rhs)
{
	/* Return new point which represents sum of two added points */
	return Point(x+rhs.x, y+rhs.y);
}

string Point::details() const
{
	return ( "( " + to_string(x) + ", " + to_string(y) + " )" );
}