// Задание : Вычисление интегралов методом Монте-Карло

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <cmath>

using namespace std;

void Monte_Karlo(double N)
{
	double x_min = 0;
	double x_max = 4;
	double y_min = -4;
	double y_max = 4;
	double n = 0;
	double S1 = (x_max - x_min) * (y_max - y_min);
	srand(time(NULL));
	double sum = 0;
	for (int i = 0; i < N; i++)
	{
		double r1 = double(rand()) / RAND_MAX; 
		double r2 = double(rand()) / RAND_MAX; 
		// случайные координаты 
		double x = x_min + r1 * (x_max - x_min); 
		double y = y_min + r2 * (y_max - y_min); 
		if (x > 0  && pow(x, 2) + pow(y, 2) < 4)
		{
			sum += 1; // 1 т,к, F(x,y)=1
			n = n + 1;
		}
	}
	double F = sum / n;
	double S = S1 * n / N;

	double V = F * S;
	double PI = S / 2;   
	cout << " V = " << V << endl;
	cout << " Pi = " << PI << endl;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	for (;;)
	{
		int N = 0;
		cout << " Ведите число итераций: ";
		cin >> N;
		Monte_Karlo(N);
	}
}