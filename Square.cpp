#include "Square.h"
#include <iostream>

Square::Square(Point tl, int length) : Shape("Square") // Call base class constructor to initiliaze name
{
    if (length > 0)
    {
        this->tl = tl; // Initialize top left point
        this->length = length; // Initialize length
    }
    else
    {
        throw "length cannot be negative or zero";
    }
}

/* Empty destructor ( no dynamic memory is used ) */
Square::~Square()
{
}

void Square::move(Point p)
{
    tl = tl + p; // Update top left point
}

Point Square::getPoint() const
{
    return tl;
}

int Square::getLength() const
{
    return length;
}

string Square::details() const
{
    return ("[ name: " + name + ", top lef corner: " + tl.details() + ", length: " + to_string(length) + " ]");
}