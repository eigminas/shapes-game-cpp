#include <string>
#include "Point.h"

#ifndef SHAPE_H
#define SHAPE_H

using namespace std;

/*
	Shape abstact class is a base class for concrete shapes Circle and Square.
*/
class Shape
{
public:
	/* Constructor initializes name */
	Shape(string name);
	/* Virtual destructor */
	virtual ~Shape();
	/* Move shape by given point */
	virtual void move(Point p) = 0;
	/* Get Point. For Circle it is center, for Square top left corner */
	virtual Point getPoint() const = 0;
	/* Get length. For Circle it is radius, for Square length */
	virtual int getLength() const = 0;
	/* Return string describing this shape */
	virtual string details() const = 0;
	/*  Get name of the shape */
	string getName() const;

protected:
	/* Name of the shape */
	string name;
};
#endif 