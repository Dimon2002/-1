#include <iostream>
#include <iomanip>
#include <fstream>

#define x0 1
typedef double type;

using namespace std;

type F(type x)
{
	return pow(x - x0, 2);
}

void DichotomyMethod()
{
	ofstream fout("outDichotomy.txt");

	/// <summary>
	/// Input data
	/// </summary>
	type a = -2;
	type b = 20;
	type eps = 10e-7;

	type xLeft, xRight;

	type h = eps / 2;
	type a_prev = a;
	type b_prev = b;

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
			<< xLeft  << " | "
			<< xRight << " | "
			<< yLeft  << " | "
			<< yRight << " | "
			<< a	  << " | "
			<< b	  << " | "
			<< b - a  << " | "
			<< (b_prev - a_prev) / (b - a) << endl;

		a_prev = a;
		b_prev = b;
		++iteration;
	}

	type x = (a + b) / 2;
	fout << "x = " << setprecision(7) << x << endl;
	fout << "F(x) = " << setprecision(7) << F(x) << endl;
}

void GoldenRatioMethod()
{
	ofstream fout("outGolden.txt");

	/// <summary>
	/// Input data
	/// </summary>
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
			<< xLeft  << " | "
			<< xRight << " | "
			<< yLeft  << " | "
			<< yRight << " | "
			<< a      << " | "
			<< b      << " | "
			<< len    << " | ";

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
	fout << "x = " << setprecision(7) << x << endl;
	fout << "F(x) = " << setprecision(7) << F(x) << endl;
}

void IntervalContainingMinimumFunctions(type xstart)
{
	ofstream fout("outInterval.txt");

	/// <summary>
	/// Input data
	/// </summary>
	/// <param name="xstart"> Start point </param>
	const type eps = 1e-7;

	type h = eps / 2;
	type x1 = xstart + h;

	type y1 = F(xstart);
	type y2 = F(x1);

	int iteration = 1;

	if (y1 < y2)
	{
		x1 = xstart - h;

		type ytmp = F(x1);

		if (ytmp > y1)
		{
			fout << iteration << (iteration >= 10 ? " | " : "  | ")
				<< x1 + (2 * h) << " | " << F(x1 + (2 * h)) << endl;
			fout << "Интервал, содержащий минимум: [" << x1 << "," << x1 + (2 * h) << "]" << "|x0 - x| = " << abs(x1 - (x1 + 2 * h)) << endl;
			return;
		}

		h = -h;
	}

	type x;
	while (true)
	{
		h *= 2;
		x = x1 + h;

		y1 = F(x1);
		y2 = F(x);

		fout << noshowpos << iteration << (iteration >= 10 ? " | " : "  | ");
		fout << showpos << fixed << setprecision(7) << x << " | " << y2 << endl;

		if (y1 < y2) break;
		xstart = x1;
		x1 = x;
		y1 = y2;

		++iteration;
	}

	if (x < xstart)
	{
		type tmp = x;
		x = xstart;
		xstart = tmp;
	}

	fout << noshowpos << "Интервал, содержащий минимум: [" << xstart << "," << x << "]" << " |x0 - x| = " << abs(xstart - x) << endl;

}

type BinetFormula(int n)
{
	return (pow((1 + sqrt(5)) / 2, n) - pow((1 - sqrt(5)) / 2, n)) / sqrt(5.0);
}

void FibonacciMethod()
{
	ofstream fout("outFibonacci.txt");

	/// <summary>
	/// Input data
	/// </summary>
	type a = -2;
	type b = 20;
	type eps = 1e-7;

	int n = 1;

	type len = b - a;
	const type сondition = len / eps;

	while (BinetFormula(n + 2) < сondition)
		++n;

	type xLeft = a + len * BinetFormula(n) / BinetFormula(n + 2);
	type xRight = a + len * BinetFormula(n + 1) / BinetFormula(n + 2);

	type yLeft = F(xLeft);
	type yRight = F(xRight);
	 
	for (size_t k = 1; k < n; ++k)
	{
		if (yLeft > yRight)
		{
			a = xLeft;
			xLeft = xRight;
			yLeft = yRight;

			xRight = a + (b - a) * BinetFormula(n - k + 2) / BinetFormula(n - k + 3);
			yRight = F(xRight);
		}
		else
		{
			b = xRight;
			xRight = xLeft;
			yRight = yLeft;

			xLeft = a + (b - a) * BinetFormula(n - k + 1) / BinetFormula(n - k + 3);
			yLeft = F(xLeft);
		}

		fout << k << (k >= 10 ? " | " : "  | ");
		fout << fixed << setprecision(7)
			<< xLeft  << " | "
			<< xRight << " | "
			<< yLeft  << " | "
			<< yRight << " | "
			<< a      << " | "
			<< b      << " | "
			<< b - a  << " | "
			<< len / (b - a) << endl;

		len = b - a;
	}

	yLeft <= F(xLeft + eps) ? b = xLeft : a = xLeft;
	
	type x = (a + b) / 2;
	fout << "x = " << setprecision(7) << x << endl;
	fout << "F(x) = " << setprecision(7) << F(x) << endl;
}

int main()
{
	setlocale(0, "ru");

	DichotomyMethod();
	GoldenRatioMethod();
	FibonacciMethod();
	IntervalContainingMinimumFunctions(-1);
}