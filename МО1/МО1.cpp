#include <iostream>
#include <iomanip>
#include <fstream>

#define T true
#define x0 1

#if T
typedef double type;
#else
typedef float type;
#endif

using namespace std;

type F(type x)
{
	return pow(x - x0, 2);
}

void DichotomyMethod()
{
	ofstream fout("outDichotomy.txt");

	type a, b, xLeft, xRight, eps, h, a_prev, b_prev;
	a = a_prev = -2;
	b = b_prev = 20;
	eps = 10e-7;
	h = eps / 2;

	int iteration = 1;

	while (abs(a - b) > eps)
	{
		xLeft = (a + b - h) / 2;
		xRight = (a + b + h) / 2;

		type yLeft = F(xLeft);
		type yRight = F(xRight);

		yLeft < yRight ? b = xRight : a = xLeft;

		fout << iteration << (iteration >= 10 ? " | " : "  | ");
		fout << fixed << setprecision(7)
			<< xLeft << " | "
			<< xRight << " | "
			<< yLeft << " | "
			<< yRight << " | "
			<< a << " | "
			<< b << " | "
			<< b - a << " | "
			<< (b_prev - a_prev) / (b - a) << endl;

		a_prev = a;
		b_prev = b;
		++iteration;
	}

	type x = (a + b) / 2;
	cout << "min = " << setprecision(7) << x << endl;
	cout << "F min = " << setprecision(7) << F(x) << endl;
}

void GoldenRatioMethod()
{
	ofstream fout("outGolden.txt");

	type a = -2;
	type b = 20;
	type eps = 1e-7;

	const type Fconst = (3 - sqrt(5.0)) / 2;
	type len = abs(b - a);

	type xLeft = a + Fconst * (b - a);
	type xRight = b - Fconst * (b - a);
	type yLeft = F(xLeft);
	type yRight = F(xRight);

	int iteration = 1;
	bool flag;

	while (abs(b - a) > eps)
	{
		fout << iteration << (iteration >= 10 ? " | " : "  | ");
		fout << fixed << setprecision(7)
			<< xLeft     << " | "
			<< xRight    << " | "
			<< yLeft     << " | "
			<< yRight    << " | "
			<< a		 << " | "
			<< b		 << " | "
			<< len		 << " | ";

		if (yLeft > yRight)
		{
			a = xLeft;
			xLeft = xRight;
			yLeft = yRight;

			flag = false;
		}
		else
		{
			b = xRight;
			xRight = xLeft;
			yRight = yLeft;

			flag = true;
		}

		fout << len / (b - a) << endl;
		len = b - a;

		if (flag)
		{
			xLeft = a + Fconst * (b - a);
			yLeft = F(xLeft);
		}
		else
		{
			xRight = b - Fconst * (b - a);
			yRight = F(xRight);
		}
		++iteration;
	}

	type x = (a + b) / 2;
	cout << "min = " << setprecision(7) << x << endl;
	cout << "F min= " << setprecision(7) << F(x) << endl;
}

int main()
{
	DichotomyMethod();
	GoldenRatioMethod();
}