#include <ostream>
#include "Shape.h"

#ifndef SQUARE_H
#define SQUARE_H

/*
	Square class represents square on 2D surface.
	This class is derived from abstact class Shape
*/
class Square : public Shape
{
public:
	/* Constructor initializes top left point and length */
	Square(Point tl, int length);
	/* Destructor */
	~Square();

	/* Move square by given point */
	void move(Point p);
	/* Get top left point of the square */
	Point getPoint() const;
	/* Get length of the square */
	int getLength() const;
	/* Return string describing this square */
	string details() const;

private:
	/* Top left point of this square */
	Point tl;
	/* Length of this square */
	int length;
};
#endif