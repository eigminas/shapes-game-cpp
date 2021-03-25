#include <iostream>
#include <string>
#include "Shape.h"
#include "Square.h"
#include "Circle.h"
#include <list>
#include <random>

using namespace std;

/* Play the game */
void play(int size);
/* Check if 2 shapes collide with each other */
bool collide(Shape* sptr1, Shape* sptr2);
/* Clamp function is used within collide function */
int clamp(int value, int min, int max);
/*
	For 3D version we would need to include the third coordinate ( int z )

	Whenever I check for collisions/overlaping I would neet to check from the third's
	coordinates perspective as well.

	Moving this game to 3D would require adding int z coordinate to Point class.
	When detecting collision we would need to check also if there is not collision from int z view.

	Also when randomly generating shapes we would need to take the third coordinate into account.
	
*/
int main()
{
	/*
		Sometimes program can end up in infinite loop when generating shapes.
		It is rear but if it happens just rebuild and run again. The algorithm I came up
		with for randomly generating shapes is not perfect!!! It works fine most of the time, though!
	*/

	play(20); // let's play :)
}

void play(int size)
{
	/*	We have to make sure size is greater or equal to 20.
		If size is less than 20 we will run into troubles when
		randomly generating shapes.*/
	if (size < 20)
	{
		throw "size must be greater or equal to 20";
		return;
	}

	/*	Independently how big the grid is - max length of the
		square shape cannot be bigger than 5.*/
	int max_length_sq = 5;

	/*	If size of the grid is less than 50 we determine
		the max length of the square by dividing the size by 8*/
	if (size < 50)
		max_length_sq = size / 8;

	/*	Max length of circle will always be half of the max
		length of the square. This is so, because circle is drawn
		from its center point meanwhile square is drawn from its
		top left point. Hence, for the same length circle would
		be 2x larger than square.*/
	int max_length_cr = max_length_sq / 2;

	/*	Determine how many shapes can logically fit within the grid*/
	int no_shapes = (size * size) / 80;
	/*	For huge grids we would get insanely many shapes and this
		becomes a problem since we generate shapes randomly
		( we place them in random locations within the grid ).*/
	if (no_shapes > 41)
	{
		/* The algorithm can easily deal with up to 41 shapes*/
		no_shapes = 41;
	}
	/*	We do not want even number of shapes because we want to have
		one shape which wins the game. It would also be possible
		to have even number of shapes but then most of the time
		there would be no winner.*/
	else if (no_shapes % 2 == 0)
	{
		no_shapes++;
	}

	/*	Setting things up for generating random numbers within
		given range*/
/*--------------------------------------------------------------------------------------------------*/
	random_device rd;

	mt19937 gen(rd());

	uniform_int_distribution<> distr_cor(max_length_sq + 1, size - max_length_sq - 1);
	uniform_int_distribution<> distr_len_sq(1, max_length_sq);
	uniform_int_distribution<> distr_len_cr(1, max_length_cr);
	uniform_int_distribution<> distr_sh(0, 1);
/*--------------------------------------------------------------------------------------------------*/

	/*	This list will contain all the shapes.
		I chose to use double linked list because this game
		requires many deletions.*/
	list <Shape*> shapes;

	/*	Generate shapes*/
	for (int i = 0; i < no_shapes; i++)
	{
		/*	This flag controls the while loop
			If the flag is equal to false it means
			we have found the new shape which does not
			collide to already existing shapes*/
		bool flag = true;

		/*	Randomly choose between 0 and 1.
			0 means square, 1 means circle*/
		int bit = distr_sh(gen);
		if (bit == 0)
		{
			/*	x, y coordinates*/
			int x_rand, y_rand, len;
			do
			{
				x_rand = distr_cor(gen); // randomly choose x coordinate
				y_rand = distr_cor(gen); // randomly choose y coordinate
				len = distr_len_sq(gen); // randomly choose length

				/*	We need to check if newly generated shape will not collide
					with already existing shapes within the grid*/
				if (!shapes.empty())
				{
					/*	Candidate shape.*/
					Shape* temp = new Square(Point(x_rand, y_rand), len);
					/*	If we detect collision this variable will switch to true*/
					bool collision = false;
					/*	Iterate through already existing shapes and check if newly
						generated shape collides to any of them*/
					for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
					{
						/*	Collision detected*/
						if (collide(temp, *it) == 1)
							collision = true;
					}
					/*	no collision - go ahead add this shape to the list*/
					if (!collision)
					{
						flag = false;
					}
					delete temp;	// delete temp
				}
				else
				{
					flag = false;
				}

			} while (flag);
			
			/*	Create Point*/
			Point p_rand = Point(x_rand, y_rand);

			/*	Push newly generated shape to the list*/
			shapes.push_back(new Square(p_rand, len));
		}
		else if (bit == 1)
		{
			/*	x, y coordinates*/
			int x_rand, y_rand, len;
			do
			{
				x_rand = distr_cor(gen);		// randomly choose x coordinate
				y_rand = distr_cor(gen);		// randomly choose y coordinate
				len = distr_len_cr(gen);		// randomly choose length

				/*	We need to check if newly generated shape will not collide
					with already existing shapes within the grid*/
				if (!shapes.empty())
				{
					/*	Candidate shape.*/
					Shape* temp = new Circle(Point(x_rand, y_rand), len);
					/*	If we detect collision this variable will switch to true*/
					bool collision = false;
					/*	Iterate through already existing shapes and check if newly
						generated shape collides to any of them*/
					for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
					{
						/*	Collision detected*/
						if (collide(temp, *it) == 1)
							collision = true;
					}
					/*	no collision - go ahead add this shape to the list*/
					if (!collision)
					{
						flag = false; // no collision - go ahead add this shape to the list
					}
					delete temp;	// delete temp
				}
				else
				{
					flag = false;
				}

			} while (flag);
			
			/*	Create Point*/
			Point p_rand = Point(x_rand, y_rand);

			/*	Push newly generated shape to the list*/
			shapes.push_back(new Circle(p_rand, len));
		}
	}

	/*	Print all the shapes that we generated. We are going to play with them.*/
/*----------------------------------------------------------------------------------------------------*/
	
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "Shapes in the beginning" << endl;
	cout << endl;
	for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
		cout << (*it)->details() << endl;
	}
	
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << endl;
/*----------------------------------------------------------------------------------------------------*/

	/*	We have generated a list of shapes now we will play the game as follows:
			1) We will move the one shape from the list at the time by random point (x, y)
			2) We will check if moved shape collides with other shapes
				YES ? -> we will remove all colliding shapes from the list
				NO  ? -> we will continue
			3) Repeat this until there is at most 1 shape left (winner) or no shapes left (all losers)*/
	
	/*	Prepare to randomly generate number
		for point (x, y)*/
/*----------------------------------------------------------------------------------------------------*/
	random_device rd_p;
	mt19937 gen_p(rd_p());
	uniform_int_distribution<> distr_p(-5, 5); // Range can be changed
/*----------------------------------------------------------------------------------------------------*/
	/*	Keep playing as long as we have more than 1 shape in the list*/
	while (shapes.size() > 1)
	{
		/*	Set up the iterator*/
		list<Shape*>::iterator shape = shapes.begin();
		/*	Start iterating thourgh the list of shapes*/
		while (shape != shapes.end())
		{
			/*	x,y coordinates*/
			int x_rand = 0, y_rand = 0;
			/*	flag controls the while loop.
				True means we have not found the point yet*/
			bool flag = true;
			do
			{
				x_rand = distr_p(gen_p); // randomly choose x coordinate
				y_rand = distr_p(gen_p); // randomly choose y coordinate

				/*	Let us simulate moving the shape by this randomly generated point*/
				Point temp = (*shape)->getPoint() + Point(x_rand, y_rand);

				/*	Hey shape, are you Square ??*/
				if ((*shape)->getName() == "Square")
				{
					/*	Let's check if candidate point does not move square out of
						the grid or make it touch the grid*/
					if (temp.getX() > 0 &&
						temp.getX() + (*shape)->getLength() < size &&
						temp.getY() - (*shape)->getLength() > 0 &&
						temp.getY() < size)
					{
						flag = false; // Square is within the grid
					}
				}
				/*	Circle ?? Is it you?*/
				else if ((*shape)->getName() == "Circle")
				{
					/*	Let's check if candidate point does not move circle out of
						the grid or make it touch the grid*/
					if (temp.getX() - (*shape)->getLength() > 0 &&
						temp.getX() + (*shape)->getLength() < size &&
						temp.getY() - (*shape)->getLength() > 0 &&
						temp.getY() + (*shape)->getLength() < size)
					{
						flag = false; // Circle is within the grid
					}
				}

			} while (flag);

			/*	Move the shape*/
			(*shape)->move(Point(x_rand, y_rand));
			
			/*	Print the shapes including the moved shape.*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
			cout << endl;
			cout << "------------------------------------------------------------------" << endl;
			cout << endl;
			cout << "Game" << endl;
			cout << endl;
			for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
			{
				/* I want to indicate which shape has been recently moved*/
				if (*shape == *it)
				{
					cout << (*it)->details() << " <-- MOVED by " << Point(x_rand, y_rand).details() << endl;
				}
				else
				{
					cout << (*it)->details() << endl;
				}
				
			}
			cout << endl;
			cout << "------------------------------------------------------------------" << endl;
			cout << endl;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
			/*	Now that we moved the shape, we need to check this shape collides with other shapes*/

			/* If collision is equal to true - we detected collision*/
			bool collision = false;
			/*	Set up the iterator*/
			list<Shape*>::iterator it = shapes.begin();
			/*  Iterate through the list of shapes*/
			while (it != shapes.end())
			{
				/* Check if moved shape collides with the current shape*/
				if (*shape != *it && collide(*shape, *it) == 1)
				{
					/*	Print details about collision*/
/*--------------------------------------------------------------------------------------------------------------------------------------*/
					cout << endl;
					cout << "Collision happened:" << endl;
					cout << "------------------------------------------------------------------" << endl;
					cout << (*shape)->details() << endl;
					cout << (*it)->details() << endl;
					cout << "------------------------------------------------------------------" << endl;
					cout << endl;
/*--------------------------------------------------------------------------------------------------------------------------------------*/
					/*	Remove colliding shape*/
					Shape* toBeDeleted = *it;
					it = shapes.erase(it++);
					delete toBeDeleted;
					collision = true;
				}
				/*	Increment iterator*/
				else
				{
					++it;
				}
			}

			/*	We also need to remove the moved shape if any collision was detected in the inner loop*/
			if (collision)
			{
				Shape* toBeDeleted = *shape;
				shape = shapes.erase(shape++); // remove
				delete toBeDeleted;
			}
			/*	Increment iterator*/
			else
			{
				++shape;
			}
		}
	}
/*	Announce the outcome of the game*/
/*----------------------------------------------------------------------------------------------------------------------*/
	cout << endl;
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << endl;
	/* If list is empty - all shapes have collided. We have no winner.*/
	if (shapes.empty())
	{
		cout << "All shapes collided. No winner!" << endl;
		cout << endl;
	}
	else
	{
		cout << "The Winner:" << endl;
		cout << endl;
		cout << shapes.back()->details() << endl;
	}
	cout << "------------------------------------------------------------------" << endl;
/*----------------------------------------------------------------------------------------------------------------------*/
}

bool collide(Shape* sptr1, Shape* sptr2)
{
	/*	Square - Square*/
	if (sptr1->getName() == "Square" && sptr2->getName() == "Square")
	{
		/*	Get top lef and bottom right points*/
		Point tl1 = sptr1->getPoint();
		Point br1 = Point(tl1.getX() + sptr1->getLength(), tl1.getY() - sptr1->getLength());
		Point tl2 = sptr2->getPoint();
		Point br2 = Point(tl2.getX() + sptr2->getLength(), tl2.getY() - sptr2->getLength());

		/*	Check if there is collision from x - axis point of view*/
		if (tl1.getX() > br2.getX() || tl2.getX() > br1.getX())
			return false; // no collision detected

		/*	Check if there is collision from y - axis point of view*/
		if (tl1.getY() < br2.getY() || tl2.getY() < br1.getY())
			return false; // no collision detected

		return true; // collision detected
	}
	/*	Circle - Circle*/
	if (sptr1->getName() == "Circle" && sptr2->getName() == "Circle")
	{
	/*
		1) Calculate distance between two Circles's centers and square it
		2) Calculate sum of two Circles's radius and square it
		3) if 1) == 2) -> Circles touch, if 1) < 2) Circles overlap, if 1) > 2) Circles do not touch or overlap
	*/

		Point c1 = sptr1->getPoint();
		Point c2 = sptr2->getPoint();

		int distsq = (c1.getX() - c2.getX()) * (c1.getX() - c2.getX());
		int radsumsq = (sptr1->getLength() + sptr2->getLength()) * (sptr1->getLength() + sptr2->getLength());

		return distsq <= radsumsq; // returns true if circles overlap or touch to each other
	}
	/*	Square - Circle*/
	if (sptr1->getName() == "Square" && sptr2->getName() == "Circle")
	{
		/*	Calculate width and height of square*/
		int length = sptr1->getLength();
		Point tl = sptr1->getPoint();

		int closestX = clamp(sptr2->getPoint().getX(), tl.getX(), tl.getX() + length);
		int closestY = clamp(sptr2->getPoint().getY(), tl.getY() - length, tl.getY());

		int distanceX = sptr2->getPoint().getX() - closestX;
		int distanceY = sptr2->getPoint().getY() - closestY;

		return pow(distanceX, 2) + pow(distanceY, 2) <= pow(sptr2->getLength(), 2);
	}
	/*	Circle - Square*/
	if (sptr1->getName() == "Circle" && sptr2->getName() == "Square")
	{
		/*	Calculate width and height of square/*/
		int length = sptr2->getLength();
		Point tl = sptr2->getPoint();

		int closestX = clamp(sptr1->getPoint().getX(), tl.getX(), tl.getX() + length);
		int closestY = clamp(sptr1->getPoint().getY(), tl.getY() - length, tl.getY());

		int distanceX = sptr1->getPoint().getX() - closestX;
		int distanceY = sptr1->getPoint().getY() - closestY;

		return pow(distanceX, 2) + pow(distanceY, 2) <= pow(sptr1->getLength(), 2);
	}
	return false;
}

int clamp(int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}
