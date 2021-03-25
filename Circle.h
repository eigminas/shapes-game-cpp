#include <ostream>
#include "Shape.h"

#ifndef CIRCLE_H
#define CIRCLE_H

/*
	Circle class represents circle on 2D surface.
	This class is derived from abstact class Shape
*/
class Circle : public Shape
{
public:
	/* Constructor initializes center and radius */
	Circle(Point center, int radius);
	/* Destructor */
	~Circle();

	/* Move circle by given point */
	void move(Point p);
	/* Get center of the circle */
	Point getPoint() const;
	/* Get radius of the circle */
	int getLength() const;
	/* Return string describing this circle */
	string details() const;

private:
	/* Center of this circle */
	Point center;
	/* Radius of this circle */
	int radius;
};
#endif
