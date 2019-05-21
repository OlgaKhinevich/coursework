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
	// конструктор 
	CSqMatrix() {}

	// деструктор
	~CSqMatrix() {	
		size = 0;
		matrix.clear();
		column.clear();
	}

	// конструктор копировани€ объекта
	CSqMatrix(const CSqMatrix& first_matrix) :size(first_matrix.size), matrix(first_matrix.matrix), column(first_matrix.column)
	{
		std::cout << " онструктор копировани€ сработал!" << std::endl;
	}

	//оператор присваивани€ копированием
	CSqMatrix& operator = (const CSqMatrix& first_matrix)
	{
		if (&first_matrix == this)
			return *this;
		matrix.clear();
		column.clear();
		size = first_matrix.size;
		matrix = first_matrix.matrix;
		column = first_matrix.column;
		std::cout << "ќператор присваивани€ копированием сработал!" << std::endl;
		return *this;
	}

	//оператор присваивани€ перемещением
	CSqMatrix& operator=(CSqMatrix&& first_matrix)
	{
		size = std::move(first_matrix.size);
		matrix = std::move(first_matrix.matrix);
		column = std::move(first_matrix.column);
		first_matrix.size = 0;
		std::cout << "ќператор присваивани€ перемещением сработал!" << std::endl;
		return *this;
		
	}

	//конструктор перемещени€
	CSqMatrix(CSqMatrix&& first_matrix) :size(std::move(first_matrix.size)), matrix(std::move(first_matrix.matrix)), column(std::move(first_matrix.column))
	{
		first_matrix.size = 0;
		std::cout << " онструктор перемещени€ сработал!" << std::endl;
	}

	// ввод размера матрицы
	void input_matrix_size (std::istream& InputStream)
	{
		InputStream >> size;
		if (InputStream.fail() || size <= 0)
		{
			throw std::underflow_error("–азмер матрицы имеет недопустимое значение!");
		}
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

	// прототипа метода получени€ максимального и минимального элементов
	auto min_max();

	// прототип метода получени€ суммы элементов над главной диагональю 
	auto sum_above_diagonal();

	// прототип метода получени€ суммы элементов строки
	auto row_amount(int row_number);

	// прототип сортировки
	void sort_matrix();
};

// реализаци€ метода ввода матрицы 
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
					throw std::invalid_argument("¬веденное значение не €вл€етс€ числом!");
			}
			matrix.push_back(column);
		}
	}

// реализаци€ метода вывода матрицы
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

// реализаци€ метода получени€ максимального и минимального элементов
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

// реализаци€ метода подсчета суммы над главной диагональю
template<class T>
auto CSqMatrix<T>::sum_above_diagonal()
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

// реализаци€ метода дл€ подсчета суммы строки
template<class T>
auto CSqMatrix<T>::row_amount(int row_number)
{
	T row_sum;
	std::vector<T> sum_row;
	if (!matrix.empty() and row_number <= size)
	{
		for (int j = 0; j < size; j++)
			sum_row.push_back(matrix[row_number][j]);
	}
	row_sum = std::accumulate(sum_row.begin(), sum_row.end(), T(0));
	return row_sum;
}

// реализаци€ метода сортировки
template<class T>
void CSqMatrix<T>::sort_matrix()
{
	for (int i = 0; i < size; i++) {
		auto value = matrix[i];
		auto current_sum = row_amount(i);
		int k = i - 1;
		for (; k >= 0; k--) {
			auto prev_sum = row_amount(k);
			if (current_sum < prev_sum) {
				matrix[k + 1] = matrix[k];
			}
			else {
				break;
			}
		}
		matrix[k + 1] = value;
	}
}
#endif 