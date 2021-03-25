#include "Circle.h"
#include <iostream>

Circle::Circle(Point center, int radius) : Shape("Circle")	// Call base class constructor to initiliaze name
{
	if (radius > 0)
	{
		this->center = center; // Initialize center
		this->radius = radius; // Initialize radius
	}
	else
	{
		throw "radius cannot be negative or zero";
	}
}

/* Empty destructor ( no dynamic memory is used ) */
Circle::~Circle()
{
}

void Circle::move(Point p)
{
	center = center + p; // Update center
}

Point Circle::getPoint() const
{
	return center;
}

int Circle::getLength() const
{
	return radius;
}

string Circle::details() const
{
	return ("[ name: " + name + ", center: " + center.details() + ", radius: " + to_string(radius) + " ]");
}