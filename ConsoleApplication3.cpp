#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <new>
#include <climits>
#include <stdexcept>
#include <numeric>
using namespace std;

template <class T>
class CSqMatrix
{
private:
	int size;
	vector <vector<T>> matrix;
	vector <T> column;
	vector <T> sum_rows;
public:
	// конструктор 
	CSqMatrix() {}

	//конструктор копирования
	CSqMatrix(const CSqMatrix& first_matrix) :size(first_matrix.size), matrix(first_matrix.matrix), column(first_matrix.column)
	{
		if (matrix.size() <= 0)
			throw exception("Невозможно создать конструктор!");
		cout << "Конструктор копирования сработал!" << endl;
	}

	/*
	CSqMatrix& operator=(const CSqMatrix& first_matrix)
	{
		size = first_matrix.size;
		matrix = first_matrix.matrix;
		column = first_matrix.column;
		return *this;
	}
	*/


	/* оператор присваивания пермещением
	CSqMatrix& operator=(CSqMatrix&& first_matrix)
	{
		first_matrix.size = 0;
		first_matrix.column = nullptr;
		first_matrix.matrix = nullptr;

		return *this;
	}*/


	/*конструктор перемещения
	CSqMatrix(CSqMatrix&& second_matrix) :size(second_matrix.size), matrix(second_matrix.matrix), column(second_matrix.column)
	{
		second_matrix.size = 0;
		second_matrix.matrix = nullptr;
		second_matrix.column = nullptr;
		cout << "Конструктор перемещения сработал!" << endl;
	}*/


	// ввод размера матрицы
	int input_matrix_size()
	{
		size = 0;
		cout << "Введите размер квадратной матрицы: ";
		cin >> size;
		if (cin.fail() || size <= 0)
		{
			throw length_error("");
		}
		return size;
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
					throw exception("Элемент не введен!");
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

	// удаление матрицы
	void delete_matrix()
	{

	}

	// получение текущего размера матрицы
	void get_size()
	{
		int i = 0,
			j = 0;
		if (matrix.size() <= 0)
		{
			throw exception("Размер матрицы неверный!");
		}

		cout << "Создана квадратная матрица размером: " << matrix[i].size() << "x" << matrix[j].size() << endl;
	}

	// максимальный и минимальный элементы
	void min_max()
	{
		T min = matrix[0][0];
		T max = min;
		vector <T> min_elements;
		vector <T> max_elements;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
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
		T sum = 0;
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

	// сумма элементов строки
	auto row_amount()
	{
		for (int i = 0; i < size; i++)
		{
			T row_sum = 0;
			for (int j = 0; j < size; j++)
			{
				row_sum += matrix[i][j];
			}
			sum_rows.push_back(row_sum);
		}
		return sum_rows;
	}

	// сортировка
	void sort_matrix()
	{
		for (int i = 0; i < size; i++) {
			// Вытаскиваем строку
			auto value = matrix[i];
			// Сумма первой строки
			auto current_sum = sum_rows[i];
			// Перемещаемся по cтрокам, суммы которых перед вытащенной строкой
			int k = i - 1;
			for (; k >= 0; k--) {
				auto prev_sum = sum_rows[k];
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

	}
};

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	CSqMatrix <int> first_matrix;


	try {
		first_matrix.input_matrix_size();
		cout << "\n";
		first_matrix.input_matrix();
		cout << "\n";
		first_matrix.get_size();
		cout << "\n";
		first_matrix.output_matrix();
		cout << "\n";
		first_matrix.min_max();
		cout << "\n";
		first_matrix.sum_above_diagonal();
		first_matrix.row_amount();
		first_matrix.sort_matrix();
		cout << "\n";
		first_matrix.output_matrix();
		//first_matrix.delete_matrix();
		CSqMatrix <int> second_matrix(first_matrix);
		cout << "\n";
		second_matrix.output_matrix();
		CSqMatrix <int> third_matrix;
		third_matrix = first_matrix;
		cout << "\n";
		third_matrix.output_matrix();

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

	//CSqMatrix <int> third_matrix = move(second_matrix);
	system("pause");
}
