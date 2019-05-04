// ABC_quadratic_equation.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include "xmmintrin.h"
#include "emmintrin.h"

double* solve_sse(double a, double b, double c);

void main()
{
	double a;
	double b;
	double c;
	double* result = (double*)_aligned_malloc(16, 8);

	std::cout << "ax^2 + bx + c = 0\n";
	std::cout << "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;
	std::cout << "c = ";
	std::cin >> c;

	result = solve_sse(a, b, c);

	if (result == 0)
		std::cout << "No solutions (D < 0)";

	else if (result[0] != result[1])
	{
		std::cout << "x1 = " << result[0];
		std::cout << "\nx2 = " << result[1];
	}
	else if (result[0] == result[1])
	{
		std::cout << "x = " << result[0];
	}

	std::cin >> a;
}

double* solve_sse(double a, double b, double c)
{
	double D = b * b - 4 * a * c;

	if (D >= 0)
	{
		__m128d Ds = _mm_set_pd(D, D);
		Ds = _mm_sqrt_pd(Ds);

		double* Ds_double = (double*)_aligned_malloc(16, 8);
		_mm_storeu_pd(Ds_double, Ds);

		Ds = _mm_set_pd(Ds_double[0], -Ds_double[1]);

		__m128d Bs = _mm_set_pd(-b, -b);

		__m128d denominator = _mm_set_pd(a, a);
		__m128d twos = _mm_set_pd(2.0, 2.0);
		denominator = _mm_mul_pd(denominator, twos);

		__m128d result_sse = _mm_div_pd(_mm_add_pd(Bs, Ds), denominator);

		double* result = (double*)_aligned_malloc(16, 8);
		_mm_storeu_pd(result, result_sse);
		return result;
	}
	else
		return 0;
}


