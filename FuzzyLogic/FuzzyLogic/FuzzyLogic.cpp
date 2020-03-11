#include "FuzzyLogic.h"

double FuzzyLogic::FuzzyAND(double a, double b)
{
	return std::min(a, b);
}

double FuzzyLogic::FuzzyOR(double a, double b)
{
	return std::max(a, b);
}

double FuzzyLogic::FuzzyNOT(double a)
{
	return 1.0 - a;
}
