#include "Shape.h"

Shape::Shape(string name)
{
    this->name = name; // Initialize name
}

/* Empty destructor ( no dynamic memory is used ) */
Shape::~Shape()
{
}

string Shape::getName() const
{
    return name;
}