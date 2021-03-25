#include <ostream>

#ifndef POINT_H
#define POINT_H
/*
	For 3D int z must be included
*/
using namespace std;
/*
	Point class represents point on 2D surface.
*/
class Point
{
public:
	/* Default constructor */
	Point();
	/* Constructor initializes x and y */
	Point(int x, int y);
	/* Destructor */
	~Point();
	
	/* Get x coordinate */
	int getX() const;
	/* Get y coordinate */
	int getY() const;
	/* Return string describing this point */
	string details() const;

	/* Assignement operator */
	Point& operator=(const Point& rhs);
	/* Equality operator */
	bool operator==(const Point& rhs);
	/* Addition operator */
	Point operator+(const Point& rhs);

private:
	/* Coordinates x and y */
	int x, y;
};
#endif
