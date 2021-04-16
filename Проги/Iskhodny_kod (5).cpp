#include "math.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

//Очистка
void clear(double **arr, int n)  
{
	for (int i = 0; i < n; i++)
		delete[] arr[i];
	delete[] arr;
}
//создать копию массива
double** clone(double **arr, int n)
{
	double **newArr = new double*[n];
	for (int row = 0; row < n; row++)
	{
		newArr[row] = new double[n];
		for (int col = 0; col < n; col++)
			newArr[row][col] = arr[row][col];
	}
	return newArr;
}
//Детерменант квадратной матрицы 
double det(double **matrix, int n) 
{
	double **B = clone(matrix, n);
	//приведение матрицы к верхнетреугольному виду
	for (int step = 0; step < n - 1; step++)
		for (int row = step + 1; row < n; row++)
		{
			double coeff = -B[row][step] / B[step][step]; //метод Гаусса
			for (int col = step; col < n; col++)
				B[row][col] += B[step][col] * coeff;
		}
	//Рассчитать определитель как произведение элементов главной диагонали
	double Det = 1;
	for (int i = 0; i < n; i++)
		Det *= B[i][i];
	//Очистить память
	clear(B, n);
	return Det;
}

void main()
{
	setlocale(LC_ALL, "Russian");
	int n = 8;
	double** A = new double*[n];   
	//выделяем память для основной матрицы 
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];   
		
	}
	//выделяем память для матрицы R
	double **R = new double *[n];
	for (int i = 0; i < n; i++)            
	{
		R[i] = new double[2 * n];
	}
	double **R1 = new double *[n];
	for (int i = 0; i < n; i++)
	{
		R1[i] = new double[2 * n];
	}
	//обратная матрица B
	double **B = new double *[n];
	for (int i = 0; i < n; i++)
	{
		B[i] = new double[n];
	}
	// матрицы H=A*B
	double **H = new double *[n];
	for (int i = 0; i < n; i++)
	{
		H[i] = new double[n];
	}
	
	//Вывод основной матрицы 
	cout << "Матрица A" << endl;
	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n; j++)
		{
			A[i][j] = 1 / pow(cos(i - j), 2);
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << endl;
	// составление матрицы R
		for (int i = 0; i < n; i++)
	{

		for (int j = 0; j <2 * n; j++)
		{
			if (j<n)R[i][j] = A[i][j];
			else
			{
				if (i + n == j)R[i][j] = 1;
				else R[i][j] = 0;
			}
		}
	}
//////////////////////////Метод Гаусса-Жордана
		for (int k = 0; k < n; k++)
		{
			for (int i = k; i < n; i++)
			{
				for (int j = 0; j < 2 * n; j++)
				{
					if (i == k) R1[k][j] = R[k][j] / R[k][k];
					else R1[i][j] = R[i][j] - (R[i][k] * R1[k][j]);
				}
			}
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < 2 * n; j++)
				{
					R1[i][j] = R[i][j] - (R[i][k] * R1[k][j]);
				}
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < 2 * n; j++)
				{
					R[i][j] = R1[i][j];
					R1[i][j] = 0;
				}
			}
		}
		//Отделяем от общей матрицы
		cout << "Обратная матрица" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				B[i][j] = R[i][j + n];
				cout << B[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl << endl;
///////////////////////////////////////////////
		/// Умножение матриц 
		cout << "Матрица H" << endl;
		// запись в файл
		ofstream f_write("result.txt");
		f_write << "Матрица H" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				double S = 0;
				for (int q = 0; q < n; q++)
				{
					S = S + A[i][q] * B[q][j]; 
				}
			H[i][j] = S;
				cout << scientific << H[i][j] << "\t";
				f_write << scientific << H[i][j] << "\t";
			}
			cout << endl;
			f_write << endl;
		}
		cout << endl << endl;
		f_write << endl << endl;
	
//////////////////////////////////////
		// вычисление и вывод числа обусловленности

		double normA = 0; //норма матрицы А
		double normA1 = 0; //норма матрицы B
		double condA = 0; //число обусловленности
		for (int i = 0; i < n; i++)
		{
			double a = 0;
			double a1 = 0;
			for (int j = 0; j < n; j++)
			{
				a = a + abs(A[i][j]);
				a1 = a1 + abs(B[i][j]);
			}
			if (i == 0)
			{
				normA = a;
				normA1 = a1;
			}
			else
			{
				if (a > normA) normA = a;
				if (a1 > normA1) normA1 = a1;
			}
		}
		condA = normA*normA1;

		cout << "норма А: " << normA << endl;
		cout << "норма B: " << normA1 << endl;
		cout << "Число обусловленности: " << condA << endl;
/////////////////////////////////////

	double d = det(A, n); 
	cout <<"Детерменант матрицы A =" <<d << endl;//Вывод детерменанта
	
	
	clear(A, n);
	clear(R, n);
	clear(B, n);
	clear(R1, n);
}