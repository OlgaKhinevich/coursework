#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <new>
#include <numeric>
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
		first_matrix.input_matrix_size(cin);
		cout << "\n";

		cout << "Введите элементы матрицы" << endl;
		first_matrix.input_matrix(cin, cout);
		cout << "\n";

		first_matrix.get_size();
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
		else cout << "   " << endl;
		cout << "\n";


		pair <bool, int> sums = first_matrix.sum_above_diagonal();
		cout << "Сумма элементов над главной диагональю: " << sums.second;
		cout << "\n";

		first_matrix.sort_matrix();
		cout << "\n";
		cout << "Матрица, отсортированная по неубыванию суммы элементов строк" << endl;
		first_matrix.output_matrix(cout);
		cout << "\n";

		CSqMatrix <int> second_matrix;
		cout << "Введите размер квадратной матрицы для демонстрации копирования: ";
		second_matrix.input_matrix_size(cin);
		cout << "\n";

		cout << "Введите элементы матрицы:" << endl;
		second_matrix.input_matrix(cin, cout);
		cout << "\n";
		cout << "Матрица до копирования" << endl;
		second_matrix.output_matrix(cout);
		cout << "\n";

		cout << "Присваивание копированием" << endl;
		second_matrix = first_matrix;
		second_matrix.output_matrix(cout);
		cout << "\n";
		cout << "Вызов конструктора копирования" << endl;
		CSqMatrix <int> third_matrix = first_matrix;
		third_matrix.output_matrix(cout);
		cout << "\n";
		cout << "Вызов конструктора перемещения" << endl;
		CSqMatrix <int> fourth_matrix = move(first_matrix);
		fourth_matrix.output_matrix(cout);
		cout << "\n";
		cout << "Присваивание перемещением" << endl;
		CSqMatrix <int> fifth_matrix;
		fifth_matrix = move(second_matrix);
		fifth_matrix.output_matrix(cout);
		cout << "\n";
		first_matrix.delete_matrix();
	}
	catch (const underflow_error &ex)
	{
		cout << ex.what() << endl;
	}
	catch (const invalid_argument &ex)
	{
		cout << ex.what() << endl;
	}

	system("pause");
}
