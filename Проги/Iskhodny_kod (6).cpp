//Решение системы нелинейных уравнений

#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>
#define eps 0.000001

using namespace std;


double F(double x, double y)//функция 1
{
	return pow(2, x - y) - y - 1;
}
double G(double x, double y) // функция 2
{
	return y*y*y + x*x - 6 * x + 6;
}

void Nuton(double x, double y)   //Метод Ньютона
{

	int n = 0;
	double det;
	for (int i = 0; i <= 100; i++)
	{
		double W[2][2];// матрица Якоби
		double W1[2][2];// обратная матрица 
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (i == 0 && j == 0)W[i][j] = (x - y) * 2;
				if (i == 0 && j == 1)W[i][j] = -(x - y) * 2;
				if (i == 1 && j == 0)W[i][j] = 2 * x - 6;
				if (i == 1 && j == 1)W[i][j] = 3 * pow(y, 2);
			}
		}

		det = W[0][0] * W[1][1] - W[0][1] * W[1][0];//детерминант
		//////////////////////////////////////////////
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (i == 0 && j == 0)W1[i][j] = W[1][1] / det;
				if (i == 0 && j == 1)W1[i][j] = -W[0][1] / det;
				if (i == 1 && j == 0)W1[i][j] = -W[1][0] / det;
				if (i == 1 && j == 1)W1[i][j] = W[0][0] / det;
			}
		}

		double dx = W1[0][0] * F(x, y) + W1[0][1] * G(x, y);
		double dy = W1[1][0] * F(x, y) + W1[1][1] * G(x, y);
		x -= dx;
		y -= dy;
		n++;
		if (abs(dx) < eps && abs(dy) < eps)
		{
			break;
		}
	}
	cout << "X=" << x << "\t" << "Y=" << y << endl;
	cout << "F = " << F(x, y) << endl;
	cout << "G = " << G(x, y) << "\n" << endl;
	cout << "количество итераций:" << n << "\n" << endl;

}
void main()
{
	setlocale(LC_ALL, "Russian");
	double x = 0;
	double y = 0;
	for (;;)
	{
		cout.setf(std::ios::fixed);
		cout << setprecision(6);
		cout << "Введите координаты x:" << endl;
		cin >> x;
		cout << "Введите координаты y:" << endl;
		cin >> y;
		if (x != y)
		{
			cout << "Решение" << endl;
			Nuton(x, y);
		}
		else(cout << "Выберите другие координаты!" << endl);
	}
}