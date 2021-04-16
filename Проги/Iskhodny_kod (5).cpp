#include "math.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

//�������
void clear(double **arr, int n)  
{
	for (int i = 0; i < n; i++)
		delete[] arr[i];
	delete[] arr;
}
//������� ����� �������
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
//����������� ���������� ������� 
double det(double **matrix, int n) 
{
	double **B = clone(matrix, n);
	//���������� ������� � ������������������ ����
	for (int step = 0; step < n - 1; step++)
		for (int row = step + 1; row < n; row++)
		{
			double coeff = -B[row][step] / B[step][step]; //����� ������
			for (int col = step; col < n; col++)
				B[row][col] += B[step][col] * coeff;
		}
	//���������� ������������ ��� ������������ ��������� ������� ���������
	double Det = 1;
	for (int i = 0; i < n; i++)
		Det *= B[i][i];
	//�������� ������
	clear(B, n);
	return Det;
}

void main()
{
	setlocale(LC_ALL, "Russian");
	int n = 8;
	double** A = new double*[n];   
	//�������� ������ ��� �������� ������� 
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];   
		
	}
	//�������� ������ ��� ������� R
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
	//�������� ������� B
	double **B = new double *[n];
	for (int i = 0; i < n; i++)
	{
		B[i] = new double[n];
	}
	// ������� H=A*B
	double **H = new double *[n];
	for (int i = 0; i < n; i++)
	{
		H[i] = new double[n];
	}
	
	//����� �������� ������� 
	cout << "������� A" << endl;
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
	// ����������� ������� R
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
//////////////////////////����� ������-�������
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
		//�������� �� ����� �������
		cout << "�������� �������" << endl;
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
		/// ��������� ������ 
		cout << "������� H" << endl;
		// ������ � ����
		ofstream f_write("result.txt");
		f_write << "������� H" << endl;
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
		// ���������� � ����� ����� ���������������

		double normA = 0; //����� ������� �
		double normA1 = 0; //����� ������� B
		double condA = 0; //����� ���������������
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

		cout << "����� �: " << normA << endl;
		cout << "����� B: " << normA1 << endl;
		cout << "����� ���������������: " << condA << endl;
/////////////////////////////////////

	double d = det(A, n); 
	cout <<"����������� ������� A =" <<d << endl;//����� ������������
	
	
	clear(A, n);
	clear(R, n);
	clear(B, n);
	clear(R1, n);
}