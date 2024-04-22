#include <fstream>
#include <iostream>
#include <vector>
#include <variant>
#include <string>
#include <algorithm>

#include "column.hpp"
#include "dataframe.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

typedef std::variant<vector<string>, vector<int>, vector<double>, vector<bool>> col_type;

int DataFrame::find_column_position(const std::string &col_name)
{

	auto it = std::find(DataFrame::column_names.begin(), DataFrame::column_names.end(), col_name);
	if (it != DataFrame::column_names.end())
	{
		return std::distance(DataFrame::column_names.begin(), it); // Calculate the index
	}
	else
	{
		throw std::runtime_error("The given column" + col_name + "doesn't exist in the dataframe"); // Value not found
		return -1;
	}
}

string::size_type width(vector<string>& inp) {
    string::size_type maxlen = 0;
    for (const auto& s : inp) maxlen = std::max(maxlen, s.size());
    return maxlen;
}

void DataFrame::print_dataframe()
{	
	cout << "\n";
	// cout << "I am before print stmt" << endl;
	/*try
	{
		cout << "row size :" << row_n << " col size :" << col_n << endl;
		for (int i = 0; i < col_n; i++)
		{
			// cout << "I am in for loop print stmt" << endl;
			col_type temp = columns[i].column_data;
			if (std::holds_alternative<vector<int>>(temp))
			{
				for (int j = 0; j < row_n; j++)
				{
					cout << std::get<vector<int>>(temp)[j] << ' ';
				}
				cout << endl;
			}
			else if (std::holds_alternative<vector<double>>(temp))
			{

				for (int j = 0; j < row_n; j++)
				{
					cout << (int)std::get<vector<double>>(temp)[j] << ' ';
				}
				cout << endl;
			}
			else if (std::holds_alternative<vector<string>>(temp))
			{

				for (int j = 0; j < row_n; j++)
				{
					cout << std::get<vector<string>>(temp)[j] << ' ';
				}
				cout << endl;
			}
			else if (std::holds_alternative<vector<bool>>(temp))
			{
				std::cout << std::boolalpha;
				for (int j = 0; j < row_n; j++)
				{
					cout << std::get<vector<bool>>(temp)[j] << ' ';
				}
				cout << endl;
			}
			else
			{
				// error
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}*/
	vector<string> Oggy(row_n+1);
	if(row_names){
		Oggy[0] = "";
		for(int i = 0 ; i<row_n ; i++)
		{
			Oggy[i+1] = ind.index_names[i];
		}
	} else{
		Oggy[0] = "";
		for(int i = 0 ; i<row_n ; i++)
		{
			Oggy[i+1] = std::to_string(i);
		}
	}
	string::size_type maxlen = width(Oggy);
	for(int i = 0 ; i <= row_n ; i++){
		Oggy[i] += string(maxlen - Oggy[i].size(), ' ');
	}
	
	for(int i = 0 ; i < col_n ; i++)
	{	
		vector<string> temp(row_n+1);
		if(col_names)
			temp[0] = column_names[i];
		else temp[0] = std::to_string(i);
		if (std::holds_alternative<vector<int>>(columns[i].column_data))
		{	
			vector<int> temp_col = std::get<vector<int>>(columns[i].column_data);
			for (int j = 0; j < row_n; j++)
			{
				temp[j+1] = std::to_string(temp_col[j]);
			}
		} else if (std::holds_alternative<vector<string>>(columns[i].column_data)){	
			vector<string> temp_col = std::get<vector<string>>(columns[i].column_data);
			for (int j = 0; j < row_n; j++)
			{
				temp[j+1] = temp_col[j];
			}
		} else if (std::holds_alternative<vector<bool>>(columns[i].column_data)){	
			vector<bool> temp_col = std::get<vector<bool>>(columns[i].column_data);
			for (int j = 0; j < row_n; j++)
			{	if(temp_col[j]) 
					temp[j+1] = "true";
				else
					temp[j+1] = "false";
			}
		} else if (std::holds_alternative<vector<double>>(columns[i].column_data)){	
			vector<double> temp_col = std::get<vector<double>>(columns[i].column_data);
			for (int j = 0; j < row_n; j++)
			{
				temp[j+1] = std::to_string(temp_col[j]);
			}
		} else {
			// do nothing
		}
		string::size_type maxlen = width(temp);
		for(int i = 0 ; i <= row_n ; i++){
			temp[i] += string(maxlen - temp[i].size(), ' ');
		}
		for(int i = 0 ; i <= row_n ; i++){
			Oggy[i] += "  " + temp[i];
		}
	}
	
	// print the dataframe
	for(int i = 0 ; i <= row_n ; i++){
		cout << Oggy[i] << endl;
	}

	cout << "\n";
	cout << "row size :" << row_n << " col size :" << col_n << endl;
	cout << endl;


}

DataFrame DataFrame::operator[](vector<string> list)
{
	DataFrame df = DataFrame();
	int k = 0;
	for (int i = 0; i < list.size(); i++)
	{

		if (if_colname_exists(list[i]))
		{
			df.append_column(columns[find_column_position(list[i])], list[i]);
		}
	}
	df.row_n = this->row_n;
	return df;
}

void DataFrame::append_column(Column c, string name)
{
	columns.push_back(c);
	column_names.push_back(name);
	col_n += 1;
}

bool DataFrame::if_colname_exists(string colu_name)
{
	if (col_names)
	{
		for (int i = 0; i < col_n; i++)
		{
			if (colu_name == column_names[i])
				return true;
		}
	}

	return false;
}

vector<string> DataFrame::get_col_names()
{
	return column_names;
}

Column DataFrame::get_column(int i)
{
	return columns[i];
}

DataFrame DataFrame::operator+(DataFrame &rhs)
{

	try
	{
		if ((this->row_n == rhs.row_n) && (this->col_names && rhs.col_names))
		{
			vector<string> colu_namus = rhs.get_col_names();
			for (int i = 0; i < rhs.col_n; i++)
			{
				if (!this->if_colname_exists(colu_namus[i]))
				{
					this->append_column(rhs.get_column(i), colu_namus[i]);
				}else {
					throw std::invalid_argument("duplicate column names found from operator+");
				}
			}
		}
		else if ((this->row_n == rhs.row_n) && (!this->col_names && !rhs.col_names))
		{
			for (int i = 0; i < rhs.col_n; i++)
			{
				this->columns.push_back(rhs.get_column(i));
				this->col_n += 1;
			}
		}
		else
		{
			throw std::runtime_error("dataframe size doesnt match or column headers are absent in either of the dataframe ");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	return *this;
}

DataFrame DataFrame::operator[](string c)
{
	DataFrame df = DataFrame();

	if (if_colname_exists(c))
	{
		df.append_column(columns[find_column_position(c)], c);
		df.row_n = this->row_n;
	}
	return df;
}

void DataFrame::sort_by_column_names()
{

	auto comp = []<typename T>(T a, T b)
	{
		return a > b;
	};

	int pos;
	for (int i = 0; i < col_n; i++)
	{
		pos = i;
		for (int j = i; j < col_n; j++)
		{
			if (comp(column_names[pos], column_names[j]))
				pos = j;
		}

		if (pos != i)
		{
			string temp = column_names[i];
			Column Temp = columns[i];

			columns[i] = columns[pos];
			column_names[i] = column_names[pos];

			columns[pos] = Temp;
			column_names[pos] = temp;
		}
	}
}

void DataFrame::drop_column(int j)
{
	try
	{

		if (j < col_n)
		{	
			if(col_names){
				for (int i = j; i < col_n - 1; i++)
				{
					column_names[i] = column_names[i + 1];
					columns[i] = columns[i + 1];
				}
				column_names.resize(col_n);
			} else {
				for (int i = j; i < col_n - 1; i++)
				{
					
					columns[i] = columns[i + 1];
				}
			}
				
			col_n -= 1;
			columns.resize(col_n);
		}
		else
		{
			throw std::out_of_range("column index out of range");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void DataFrame::drop_column(string c)
{
	try
	{
		if (if_colname_exists(c))
		{
			int i = find_column_position(c);
			drop_column(i);
		}
		else
		{
			throw std::out_of_range("Column name doesnt exist");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void DataFrame::drop_row(int k)
{	
	try
	{
		
		if (k < row_n)
		{
			row_n -= 1;
			for (int i = 0; i < col_n; i++)
			{
				
				if (std::holds_alternative<vector<int>>(columns[i].column_data))
				{

					for (int j = k; j < row_n; j++)
					{
						std::get<vector<int>>(columns[i].column_data)[j] = std::get<vector<int>>(columns[i].column_data)[j + 1];
					}
					std::get<vector<int>>(columns[i].column_data).resize(row_n);
				}
				else if (std::holds_alternative<vector<double>>(columns[i].column_data))
				{
					for (int j = k; j < row_n; j++)
					{
						std::get<vector<double>>(columns[i].column_data)[j] = std::get<vector<double>>(columns[i].column_data)[j + 1];
					}
					std::get<vector<double>>(columns[i].column_data).resize(row_n);
				}
				else if (std::holds_alternative<vector<bool>>(columns[i].column_data))
				{
					for (int j = k; j < row_n; j++)
					{
						std::get<vector<bool>>(columns[i].column_data)[j] = std::get<vector<bool>>(columns[i].column_data)[j + 1];
					}
					std::get<vector<bool>>(columns[i].column_data).resize(row_n);
				}
				else if (std::holds_alternative<vector<string>>(columns[i].column_data))
				{
					for (int j = k; j < row_n; j++)
					{
						std::get<vector<string>>(columns[i].column_data)[j] = std::get<vector<string>>(columns[i].column_data)[j + 1];
					}
					std::get<vector<string>>(columns[i].column_data).resize(row_n);
				}
			}
			if(row_names){
				for (int i = k; i < row_n; i++)
				{	
					ind.index_names[i] = ind.index_names[i + 1];
				}

				std::cout << "I am iron"<< std::endl;
				ind.index_names.resize(row_n);
			}
				
		}
		else
		{
			throw std::out_of_range("row index out of range");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void DataFrame::drop_row(string j)
{
	try
	{
		if (row_names)
		{
			int i = ind.get_index_position(j);
			if (i != -1)
				drop_row(i);
			else
				throw std::out_of_range("row names dint exist");
		}
		else
		{
			throw std::out_of_range("row names dont exist");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void DataFrame::set_rownames(vector<string> row_namus)
{
	try
	{
		if (row_namus.size() == row_n)
		{
			ind = Index(row_namus);
			row_names = true;
		}
		else
		{
			throw std::invalid_argument("No of Rows don't match");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void DataFrame::replace_rowname(string old_name, string new_name)
{
	try
	{
		if (row_names)
		{
			int i = ind.get_index_position(old_name);
			if (i != -1)
				ind.index_names[i] = new_name;
			else
				throw std::invalid_argument("row name doesn't exist");
		}
		else
		{
			throw std::runtime_error("DataFrame doesnt have row names");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void DataFrame::set_colnames(vector<string> col_namus)
{
	try
	{
		if (col_namus.size() == col_n)
		{
			column_names = col_namus;
			col_names = true;
			for (int i = 0; i < col_n; i++)
			{
				columns[i].column_name = col_namus[i];
			}
		}
		else
		{
			throw std::invalid_argument("Sizes dont match");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void DataFrame::replace_colname(string old_name, string new_name)
{
	try
	{
		if (col_names && if_colname_exists(old_name))
		{
			int i = find_column_position(old_name);
			if (i < col_n)
			{
				column_names[i] = new_name;
				columns[i].column_name = new_name;
			}
			else
				throw std::runtime_error("What is error");
		}
		else
		{
			throw std::invalid_argument("this operation cant be performed on this dataframe");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void DataFrame::mean()
{
	try
	{
		for (int i = 0; i < col_n; i++)
		{
			mean(column_names[i]);
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

/*template <typename T>
void DataFrame::countFrequency(Column<T>vec ,T& mode , int& maxF )
{
	int spl_count = 0;
	for(int i = 0 ; i < vec.size() ; i++)
	{
		spl_count = vec[i].
	}
}*/

template <typename T>
double calculate_mean(const vector<T> vec)
{
	try
	{
		if (std::is_same_v<T, int>)
		{
			double sum = 0;
			int n = vec.size();
			for (int i = 0; i < n; i++)
			{
				sum += (double)(vec[i]);
			}
			sum = sum / n;
			return sum;
		}
		else
		{
			throw std::invalid_argument("column is not Numeric type");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

template <>
double calculate_mean(vector<double> vec)
{
	int n = vec.size();
	int no_of_values = n;
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (std::isnan(vec[i]))
		{
			no_of_values--;
			continue;
		}
		sum += (vec[i]);
	}
	sum = sum / no_of_values;
	return sum;
}

void DataFrame::mean(string col_name)
{
	try
	{
		int i = find_column_position(col_name); // To do =  check if column exists or not
		if (std::holds_alternative<vector<int>>(columns[i].column_data))
		{
			double mean_value = calculate_mean(std::get<vector<int>>(columns[i].column_data));
			cout << "mean of column " << col_name << " = " << mean_value << endl;
		}
		else if (std::holds_alternative<vector<double>>(columns[i].column_data))
		{
			double mean_value = calculate_mean(std::get<vector<double>>(columns[i].column_data));
			cout << "mean of column " << col_name << " = " << mean_value << endl;
		}
		else
		{
			throw std::invalid_argument("col " + col_name +" is not Numeric" );
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

int DataFrame::count(int col_ind, string val)
{
	try
	{
		if (col_ind < col_n)
		{
			if (std::holds_alternative<vector<string>>(get_column_data(col_ind)))
			{
				vector<string> temp(std::get<vector<string>>(get_column_data(col_ind)));
				return count_string(temp, std::string(val));
			}
			else
			{
				throw std::invalid_argument("column type and value type dont match");
			}
		}
		else
		{
			throw std::invalid_argument("index out of range");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	return -1;
}

col_type DataFrame::get_column_data(int i)
{
	return columns[i].get_column();
}

void DataFrame::mode()
{
	for(int i = 0 ; i < col_n ; i++){
		mode(i);
	}
}

void DataFrame::mode(string col_name)
{
	try
	{
		if (if_colname_exists(col_name))
		{
			return mode(find_column_position(col_name));
		}
		else
		{
			throw std::invalid_argument("column name doesnt exist");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void DataFrame::mode(int col_pos)
{
	try
	{	
		if (col_pos < col_n && col_pos >= 0)
		{
			int max = 0;
			if (std::holds_alternative<vector<string>>(get_column_data(col_pos)))
			{
				vector<string> temp(std::get<vector<string>>(get_column_data(col_pos)));
				int max = INT_MIN;
				string mode_v;
				for (int i = 0; i < row_n; i++)
				{
					int coun = count(col_pos, temp[i]);
					if (coun > max)
					{
						max = coun;
						mode_v = temp[i];
					}
				}
				if (col_names)
					cout << "mode of column " << column_names[col_pos] << " : " << mode_v << endl;
				else
					cout << "mode of column " << col_pos << " : " << mode_v << endl;
			}
			else if (std::holds_alternative<vector<int>>(get_column_data(col_pos)))
			{
				vector<int> temp(std::get<vector<int>>(get_column_data(col_pos)));
				int max = INT_MIN;
				int mode_v;
				for (int i = 0; i < row_n; i++)
				{
					int coun = count(col_pos, temp[i]);
					if (coun > max)
					{
						max = coun;
						mode_v = temp[i];
					}
				}
				if (col_names)
					cout << "mode of column " << column_names[col_pos] << " : " << mode_v << endl;
				else
					cout << "mode of column " << col_pos << " : " << mode_v << endl;
			}
			else if (std::holds_alternative<vector<double>>(get_column_data(col_pos)))
			{

				vector<double> temp(std::get<vector<double>>(get_column_data(col_pos)));
				int max = INT_MIN;
				double mode_v;
				for (int i = 0; i < row_n; i++)
				{
					int coun = count(col_pos, temp[i]);
					if (coun > max)
					{
						max = coun;
						mode_v = temp[i];
					}
				}
				if (col_names)
					cout << "mode of column " << column_names[col_pos] << " : " << mode_v << endl;
				else
					cout << "mode of column " << col_pos << " : " << mode_v << endl;
			}
			else if (std::holds_alternative<vector<bool>>(get_column_data(col_pos)))
			{

				vector<bool> temp(std::get<vector<bool>>(get_column_data(col_pos)));
				int max = INT_MIN;
				bool mode_v;
				for (int i = 0; i < row_n; i++)
				{
					int coun = count(col_pos, temp[i]);
					if (coun > max)
					{
						max = coun;
						mode_v = temp[i];
					}
				}
				if (col_names)
					cout << std::boolalpha << "mode of column " << column_names[col_pos] << " : " << mode_v << endl;
				else
					cout << std::boolalpha << "mode of column " << col_pos << " : " << mode_v << endl;
			}
		}
		else
		{
			throw std::invalid_argument("column index out of range from mode function");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	
}
