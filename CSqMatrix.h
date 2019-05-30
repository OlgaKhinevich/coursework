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
	
public:
	// конструктор с параметром
	CSqMatrix(int m_size)
	{
		size = m_size;
		
	}

	CSqMatrix() = delete;
	
	// деструктор
	~CSqMatrix() {	
		size = 0;
		matrix.clear();
		column.clear();
	}

	// конструктор копирования объекта
	CSqMatrix(const CSqMatrix& first_matrix) :size(first_matrix.size), matrix(first_matrix.matrix), column(first_matrix.column) {}

	//оператор присваивания копированием
	CSqMatrix& operator = (const CSqMatrix& first_matrix)
	{
		if (&first_matrix == this)
			return *this;
		matrix.clear();
		column.clear();
		size = first_matrix.size;
		matrix = first_matrix.matrix;
		column = first_matrix.column;
		return *this;
	}

	//оператор присваивания перемещением
	CSqMatrix& operator=(CSqMatrix&& first_matrix)
	{
		size = std::move(first_matrix.size);
		matrix = std::move(first_matrix.matrix);
		column = std::move(first_matrix.column);
		first_matrix.size = 0;
		return *this;
		
	}

	//конструктор перемещения
	CSqMatrix(CSqMatrix&& first_matrix) :size(std::move(first_matrix.size)), matrix(std::move(first_matrix.matrix)), column(std::move(first_matrix.column))
	{
		first_matrix.size = 0;
	}

	// прототип метода ввода матрицы
	void input_matrix(std::istream& InputStream, std::ostream& OutputStream);
	
	// прототип метода вывода матрицы
	void output_matrix(std::ostream& OutputStream);

	// удаление матрицы
	void delete_matrix()
	{
		size = 0;
		matrix.clear();
		column.clear();
	}

	// получение текущего размера матрицы
	int get_size() 
	{
		return size;
	}

	// прототипа метода получения максимального и минимального элементов
	auto min_max();

	// прототип метода получения суммы элементов над главной диагональю 
	auto sum_above_diagonal();

	// прототип сортировки
	void sort_matrix();
};

// реализация метода ввода матрицы 
template<class T>
void CSqMatrix<T>::input_matrix(std::istream & InputStream, std::ostream & OutputStream)
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
					throw std::invalid_argument("Введенное значение не является числом!");
			}
			matrix.push_back(column);
		}
	}

// реализация метода вывода матрицы
template<class T>
void CSqMatrix<T>::output_matrix(std::ostream & OutputStream)
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

// реализация метода получения максимального и минимального элементов
template<class T>
auto CSqMatrix<T>::min_max()
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

// реализация метода подсчета суммы над главной диагональю
template<class T>
auto CSqMatrix<T>::sum_above_diagonal()
{
	T sum = 0;
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

// реализация метода сортировки
template<class T>
void CSqMatrix<T>::sort_matrix()
{
	std::sort(matrix.begin(), matrix.end(),
		[](const std::vector <T> & a, const std::vector <T> & b) -> bool
	{
		T sumA = 0;
		for (T item : a)
		{
			sumA += item;
		}
		T sumB = 0;
		for (T item : b)
		{
			sumB += item;
		}
		if (sumA < sumB)
		{
			return true;
		}
		else {
			return false;
		}
	});
}
	
#endif 