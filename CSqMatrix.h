#pragma once
#ifndef CSQMATRIX_H
#define CSQMATRIX_H
template <class T>

class CSqMatrix
{
private:
	int size;
	std::vector <std::vector<T>> matrix;
	std::vector <T> column;
	std::vector <T> sum_rows;
public:
	// конструктор 
	inline CSqMatrix() {}

	// конструктор копирования
	inline CSqMatrix(const CSqMatrix& first_matrix) :size(first_matrix.size), matrix(first_matrix.matrix), column(first_matrix.column)
	{
		if (matrix.size() <= 0)
			throw std::exception("Невозможно создать конструктор");
		std::cout << "Конструктор копирования сработал!" << std::endl; // строка для проверки работы конструктора
	}

	//оператор присваивания копированием
	inline CSqMatrix& operator=(const CSqMatrix& first_matrix)
	{
		// проверка на самоприсваивание
		if (&first_matrix == this)
			return *this;
		// Удаляем всё, что может хранить указатель до этого момента
		delete matrix;
		delete column;

		// Копируем передаваемый объект
		matrix = new std::vector<std::vector<T>>;
		*matrix = *first_matrix.matrix;
		column = new std::vector<T>;
		*column = *first_matrix.column;

		return *this;
	}

	//оператор присваивания перемещением
	inline CSqMatrix& operator=(CSqMatrix&& first_matrix)
	{
		size = move(first_matrix.size);
		matrix = move(first_matrix.matrix);
		column = move(first_matrix.column);
		first_matrix.size = 0;
		first_matrix.column = nullptr;
		first_matrix.matrix = nullptr;

		return *this;
	}

	//конструктор перемещения
	inline CSqMatrix(CSqMatrix&& first_matrix) :size(first_matrix.size), matrix(first_matrix.matrix), column(first_matrix.column)
	{
		first_matrix.size = 0;
		first_matrix.matrix = nullptr;
		first_matrix.column = nullptr;
		std::cout << "Конструктор перемещения сработал!" << std::endl;
	}


	// ввод размера матрицы
	inline int input_matrix_size()
	{
		size = 0;
		std::cin >> size;
		if (std::cin.fail() || size <= 0)
		{
			throw std::length_error("");
		}
		return size;
	}

	// ввод матрицы
	inline void input_matrix(std::istream& InputStream, std::ostream& OutputStream)
	{
		T col;
		for (int i = 0; i < size; i++)
		{
			column.clear();
			for (int j = 0; j < size; j++)
			{
				OutputStream << "M[" << i + 1 << "][" << j + 1 << "] = ";
				InputStream >> col;
				column.push_back(col);
				if (InputStream.fail())
					throw std::exception("Элемент не введен!");
			}
			matrix.push_back(column);
		}
	}

	// вывод матрицы
	inline void output_matrix(std::ostream& OutputStream)
	{
		if (!matrix.empty())
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					OutputStream << matrix[i][j] << '\t';
				}
				OutputStream << std::endl;
			}
		}

	}

	// удаление матрицы
	inline void delete_matrix()
	{
		size = 0;
		matrix.clear();
		column.clear();
	}

	// получение текущего размера матрицы
	inline void get_size(std::ostream& OutputStream)
	{
		int i = 0,
			j = 0;
		if (matrix.size() <= 0)
		{
			throw std::exception("Размер матрицы неверный!");
		}

		OutputStream << matrix[i].size() << "x" << matrix[j].size() << std::endl;
	}

	// максимальный и минимальный элементы
	inline auto min_max()
	{
		T min = matrix[0][0];
		T max = min;
		std::vector <T> min_elements;
		std::vector <T> max_elements;
		std::vector <T> results;
		
		T min_result;
		T max_result;

		if (!matrix.empty())
		{
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
			min_result = *min_element(min_elements.begin(), min_elements.end());
			max_result = *max_element(max_elements.begin(), max_elements.end());
			results.push_back(1);
			results.push_back(min_result);
			results.push_back(max_result);
			return results;
		}
		else
		{
			results.push_back(0);
			results.push_back(0);
			results.push_back(0);
			return results;
		}
	}


	// сумма элементов над главной диагональю 
	inline auto sum_above_diagonal()
	{
		T sum = 0;
		matrix.resize(size, std::vector<T>(size));
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
			return std::make_pair(true, sum);
		}
		else {
			return std::make_pair(false, sum);
		}
	}

	// сумма элементов строки
	inline auto row_amount()
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
	inline void sort_matrix()
	{
		for (int i = 0; i < size; i++) {
			// Вытаскиваем строку
			auto value = matrix[i];
			// Сумма первой строки
			auto current_sum = sum_rows[i];
			// Перемещаемся по cтрокам, которые перед вытащенной строкой
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

#endif 
