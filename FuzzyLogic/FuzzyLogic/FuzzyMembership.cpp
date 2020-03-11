#include "FuzzyMembership.h"

double FuzzyMembership::FuzzyGrade(double value, double x0, double x1)
{
	double result = 0;
	double x = value;

	if (x <= x0)
	{
		result = 0;
	}
	else if (x > x1)
	{
		result = 1;
	}
	else
	{
		result = ((x - x0) / (x1 - x0));
	}

	return result;
}

double FuzzyMembership::FuzzyTriangle(double value, double x0, double x1)
{
	double result = 0;
	double x = value;

	if (x <= 0)
	{
		result = 1;
	}
	else if (x > x1)
	{
		result = 0;
	}
	else
	{
		result = ((x1 - x) / (x1 - x0));
	}

	return result;
}

double FuzzyMembership::FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3)
{
	double result = 0;
	double x = value;

	if ((x <= x0) || (x >= x3))
	{
		result = 0;
	}
	else if ((x >= x1) && (x <= x2))
	{
		result = 1;
	}
	else if ((x > x0) && (x < x1))
	{
		result = ((x - x0) / (x1 - x0));
	}
	else
	{
		result = ((x3 - x) / (x3 - x2));
	}
	return result;
}
