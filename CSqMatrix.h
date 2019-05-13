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
	// ����������� 
	inline CSqMatrix() {}

	// ����������� �����������
	inline CSqMatrix(const CSqMatrix& first_matrix) :size(first_matrix.size), matrix(first_matrix.matrix), column(first_matrix.column)
	{
		if (matrix.size() <= 0)
			throw std::exception("���������� ������� �����������");
		std::cout << "����������� ����������� ��������!" << std::endl; // ������ ��� �������� ������ ������������
	}

	//�������� ������������ ������������
	inline CSqMatrix& operator=(const CSqMatrix& first_matrix)
	{
		// �������� �� ����������������
		if (&first_matrix == this)
			return *this;
		// ������� ��, ��� ����� ������� ��������� �� ����� �������
		delete matrix;
		delete column;

		// �������� ������������ ������
		matrix = new std::vector<std::vector<T>>;
		*matrix = *first_matrix.matrix;
		column = new std::vector<T>;
		*column = *first_matrix.column;

		return *this;
	}

	//�������� ������������ ������������
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

	//����������� �����������
	inline CSqMatrix(CSqMatrix&& first_matrix) :size(first_matrix.size), matrix(first_matrix.matrix), column(first_matrix.column)
	{
		first_matrix.size = 0;
		first_matrix.matrix = nullptr;
		first_matrix.column = nullptr;
		std::cout << "����������� ����������� ��������!" << std::endl;
	}


	// ���� ������� �������
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

	// ���� �������
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
					throw std::exception("������� �� ������!");
			}
			matrix.push_back(column);
		}
	}

	// ����� �������
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

	// �������� �������
	inline void delete_matrix()
	{
		size = 0;
		matrix.clear();
		column.clear();
	}

	// ��������� �������� ������� �������
	inline void get_size(std::ostream& OutputStream)
	{
		int i = 0,
			j = 0;
		if (matrix.size() <= 0)
		{
			throw std::exception("������ ������� ��������!");
		}

		OutputStream << matrix[i].size() << "x" << matrix[j].size() << std::endl;
	}

	// ������������ � ����������� ��������
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


	// ����� ��������� ��� ������� ���������� 
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

	// ����� ��������� ������
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

	// ����������
	inline void sort_matrix()
	{
		for (int i = 0; i < size; i++) {
			// ����������� ������
			auto value = matrix[i];
			// ����� ������ ������
			auto current_sum = sum_rows[i];
			// ������������ �� c������, ������� ����� ���������� �������
			int k = i - 1;
			for (; k >= 0; k--) {
				auto prev_sum = sum_rows[k];
				// ���� �������� ��������, ����� �������� ������� � ����������� ������� � ������� ������ ������
				if (current_sum < prev_sum) {
					matrix[k + 1] = matrix[k];
				}
				else {
					// ���� ���������� ������� ������ � ���������������
					break;
				}
			}
			// � �������������� ����� ��������� ���������� ��������
			matrix[k + 1] = value;
		}
	}
};

#endif 
