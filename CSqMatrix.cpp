#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <new>
#include <stdexcept>
#include "CSqMatrix.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	CSqMatrix <int> first_matrix;


	try {

		cout << "Введите размер квадратной матрицы: ";
		first_matrix.input_matrix_size();
		cout << "\n";
		cout << "Введите элементы матрицы" << endl;
		first_matrix.input_matrix(cin, cout);
		cout << "\n";
		cout << "Текущий размер матрицы: ";
		first_matrix.get_size(cout);
		cout << "\n";
		cout << "Вывод матрицы" << endl;
		first_matrix.output_matrix(cout);
		cout << "\n";
		vector <int> A = first_matrix.min_max();
		if (A[0] == 1)
		{
			cout << "Минимальный элемент: " << A[1] << endl;
			cout << "Максимальный элемент: " << A[2] << endl;
		}
		else cout << "Матрица пуста!" << endl;
		cout << "\n";
		cout << "Сумма элементов над главной диагональю: ";
		pair <bool, int> sums = first_matrix.sum_above_diagonal();
		cout << sums
			first_matrix.row_amount();
		first_matrix.sort_matrix();
		cout << "\n";
		cout << "Матрица, отсортированная по неубыванию суммы элементов строк" << endl;
		first_matrix.output_matrix(cout);
		cout << "\n";
		cout << "Копия матрицы, созданная с помощью конструктора копирования" << endl;
		CSqMatrix <int> second_matrix(first_matrix);
		second_matrix.output_matrix(cout);
		first_matrix.delete_matrix();

	}
	catch (const length_error&)
	{
		cout << "Размер меньше нуля!" << endl;
	}
	catch (const bad_array_new_length&)
	{
		cout << "Ошибка ввода матрицы!" << endl;
	}
	catch (const exception &ex)
	{
		cout << "Ошибка!" << ex.what() << endl;
	}

	//CSqMatrix <int> third_matrix = first_matrix;
	system("pause");
}
