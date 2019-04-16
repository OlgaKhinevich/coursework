#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <new>
#include <climits>
#include <numeric>
using namespace std;

template <class T>
class CSqMatrix
{
private:
	int size;
	vector <vector<T>> matrix;
	vector <T> column;
public:
	// конструктор 
	CSqMatrix() {}

	//конструктор копирования
	CSqMatrix(const CSqMatrix &first_matrix) :size(first_matrix.size), matrix(first_matrix.matrix), column(first_matrix.column)
	{
		cout << "Конструктор сработал!" << endl;
	}
	/* void operator = (const A &a);  // оператор присваивания */

	// ввод размера матрицы
	bool input_matrix_size()
	{
		size = 0;
		cout << "Введите размер квадратной матрицы: ";
		cin >> size;
		if (cin.fail())
			return false;
		return size > 0;
	}

	// ввод матрицы
	void input_matrix()
	{
		T col;
		for (int i = 0; i < size; i++)
		{
			column.clear();
			for (int j = 0; j < size; j++)
			{
				cout << "M[" << i + 1 << "][" << j + 1 << "] = ";
				cin >> col;
				column.push_back(col);
				if (cin.fail())
					throw exception();
			}
			matrix.push_back(column);
		}
	}

	// вывод матрицы
	void output_matrix()
	{
		if (!matrix.empty())
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					cout << matrix[i][j] << '\t';
				}
				cout << endl;
			}
		}
	}

	// получение текущего размера матрицы
	void get_size()
	{
		int i = 0,
			j = 0;
		cout << "Создана квадратная матрица размером: " << matrix[i].size() << "x" << matrix[j].size() << endl;
	}

	// максимальный и минимальный элементы
	void min_max()
	{
		T min = matrix[0][0];
		T max = min;
		vector <T> min_elements;
		vector <T> max_elements;

		for (int i = 1; i < size; i++)
		{
			for (int j = 1; j < size; j++)
			{
				if (matrix[i][j] < min)
					min = matrix[i][j];
				else if (matrix[i][j] > max)
					max = matrix[i][j];
				else continue;
			}
			min_elements.push_back(min);
			max_elements.push_back(max);
		}
		auto min_result = min_element(min_elements.begin(), min_elements.end());
		auto max_result = max_element(max_elements.begin(), max_elements.end());
		cout << "Минимальный элемент: " << *min_result << endl;
		cout << "Максимальный элемент: " << *max_result << endl;
	}


	// сумма элементов над главной диагональю 
	void sum_above_diagonal()
	{
		auto sum = 0;
		matrix.resize(size, vector<T>(size));
		if (!matrix.empty())
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (j > i)
					{
						sum += matrix[i][j];
					}
					else continue;
				}
			}
			cout << "Сумма над главной диагональю: " << sum << endl;
		}
		else {
			cout << "Матрица пуста" << endl;
		}
	}

	/* сумма элементов строки
	auto row_amount(matrix)
	{
		int i;
		T row_sum = 0;
		for (int j = 0; j < size; j++)
		{
			row_sum += matrix[i][j];
		}
		return row_sum;
	}

	// сортировка
	void sort_matrix() 
	{		
		for (int i = 0; i < size; i++) {
			// Вытаскиваем строку
			int value = matrix[i];
			// Сумма первой строки 
			auto current_sum = row_amount(matrix[i]);
			// Перемещаемся по элементам, суммы которых перед вытащенным элементом
			int k = i - 1;
			for (; k >= 0; k--) {
				auto prev_sum = row_amount(matrix[k]);
				// Если вытащили значение, сумма которого меньшее — передвигаем элемент с большей суммой дальше
				if (current_sum < prev_sum) {
					matrix[k + 1] = matrix[k];
				}
				else {
					// Если вытащенный элемент больше — останавливаемся
					break;
				}
			}
			// В освободившееся место вставляем вытащенное значение
			matrix[k + 1] = value;
		}
		
	}*/
};

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	CSqMatrix <int> first_matrix;
	
	first_matrix.input_matrix_size();
	try {
		first_matrix.input_matrix();
		first_matrix.get_size();
		first_matrix.output_matrix();
		first_matrix.sum_above_diagonal();
		first_matrix.min_max();
		//first_matrix.sort_matrix();
	}
	catch (bad_array_new_length&)
	{
		cerr << "Ошибка";
		return -1;
	}
	catch (exception&)
	{
		cerr << "Ошибка";
		return -2;
	}
	CSqMatrix <int> second_matrix(first_matrix);
	second_matrix.output_matrix();

}


