#pragma once
class FuzzyMembership
{
public:
	static double FuzzyGrade(double value, double x0, double x1);
	static double FuzzyTriangle(double value, double x0, double x1);
	static double FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3);
};

