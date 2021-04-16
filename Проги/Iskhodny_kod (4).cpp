
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// метод Лагранжа
double lagrange(double *x1, double *y, const short n, const double _x)
{
	double result = 0;
	for (short i = 0; i < n; i++)
	{
		double P = 1;
		for (short j = 0; j < n; j++)
		{
			if (j != i)
				P*= (_x - x1[j]) / (x1[i] - x1[j]);
		}
		result += P * y[i];
	}
	return result;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	const short N = 10; // количество точек
	double a = 0, b = 2;  // нач точка
	double h = (b - a) / N; // шаг
	double* xi = new double[N+1];
	double* Fi = new double[N+1];
	double xj = 0;
	double f = 0;


	cout << "Значения х" << "\t" << "Значения y" << "\t" << "Лагранж" << "\t" << "  Дельта" << "\t" << endl;

	for (int t = 0; t < N + 1; t++)
	{
		xi[t] = a + h * t;
		Fi[t] = sin(pow(xi[t], 3));

	}

	// запись в файл
	ofstream f_write("result.dot", ios_base::trunc);
	f_write << "Значения х" << "\t" << "Значения y" << "\t" << "Лагранж" << "\t" << "Дельта" << "\t" << endl;

	for (int w = 0; w < 26; w++)
	{
		xj = a + 0.08 * w;
		f = sin(pow(xj, 3));
		cout << fixed << showpoint << setprecision(6);
		cout << xj << "\t" << f << "\t" << lagrange(xi, Fi, N+1, xj)<< "\t" << f - lagrange(xi, Fi, N+1, xj) << endl;
		f_write << xj << "\t" << f << "\t" << lagrange(xi, Fi, N+1, xj) << "\t" << f - lagrange(xi, Fi, N+1, xj) << endl;
	}

	f_write.close();


	// очистка массивов данных
	delete[] xi;
	delete[] Fi;
}