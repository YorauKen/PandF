#include<fstream>
#include<iostream>
#include<vector>
#include <variant>
#include<algorithm>
#include<map>


#include "Column.h"
// #include "dataframe.h"

using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::ifstream;


int DataFrame::find_column_position(const std::string& col_name){

	auto it = std::find(DataFrame::column_names.begin(), DataFrame::column_names.end(), col_name);
    if (it != DataFrame::column_names.end()) {
        return std::distance(DataFrame::column_names.begin(), it); // Calculate the index
    } else {
        throw std::runtime_error("The given column" + col_name + "doesn't exist in the dataframe"); // Value not found
		return -1;
    }
}



void DataFrame::print_dataframe(){
	// cout << "I am before print stmt" << endl;
	try
	{
	cout << "row size :" << row_n << " col size :"<< col_n << endl;
	for (int i = 0; i < col_n; i++){
		// cout << "I am in for loop print stmt" << endl;
		col_type temp = columns[i].column_data;
		if(std::holds_alternative<vector<int>>(temp))
		{	
			for (int j = 0; j < row_n; j++){
				cout << std::get<vector<int>>(temp)[j] << ' ' ;
				
			}
			cout << endl;
		} else if(std::holds_alternative<vector<double>>(temp)){
			
			for (int j = 0; j < row_n; j++){
				cout << (int)std::get<vector<double>>(temp)[j] << ' ' ;
			}
			cout << endl;
		} else if(std::holds_alternative<vector<string>>(temp)){
			
			for (int j = 0; j < row_n; j++){
				cout << std::get<vector<string>>(temp)[j] << ' ' ;
			}
			cout << endl;
		} else if(std::holds_alternative<vector<bool>>(temp)){
			std::cout << std::boolalpha;
			for (int j = 0; j < row_n; j++){
				cout << std::get<vector<bool>>(temp)[j] << ' ' ;
			}
			cout << endl;
		} else {
			// error
	
		}
	}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
}


DataFrame DataFrame::operator[](vector<string> list){
	DataFrame df = DataFrame();
	int k=0 ;
	for (int i = 0; i < list.size(); i++){
		
		if(if_colname_exists(list[i])){
			df.append_column(columns[find_column_position(list[i])],list[i]);
		}
		
	}
	df.row_n = this->row_n;
	return df;
	
}

void DataFrame::append_column(Column c,string name){
	columns.push_back(c);
	column_names.push_back(name);
	col_n += 1 ;
}

bool DataFrame::if_colname_exists(string colu_name ){
	if (col_names){
		for(int i = 0 ; i < col_n ; i++){
			if(colu_name == column_names[i])
				return true;
		}
	}
	
	return false;
}



vector<string> DataFrame::get_col_names(){
	return column_names;
}


Column DataFrame::get_column(int i) {
	return columns[i];
}





DataFrame DataFrame::operator+(DataFrame &rhs){
	
	try
	{
		if((this->row_n == rhs.row_n)  && (this->col_names && rhs.row_names))
		{	
			vector<string> colu_namus = rhs.get_col_names();
			for(int i = 0 ; i < rhs.col_n ; i++){
				if(this->if_colname_exists(colu_namus[i])){
					this->append_column(rhs.get_column(i) ,colu_namus[i] );
				}
			}

		} else if ((this->row_n == rhs.row_n) && (!this->col_names && !rhs.row_names))
		{
			for(int i = 0 ; i < rhs.col_n ; i++){
				this->columns.push_back(rhs.get_column(i));
				this->col_n += 1;
			}

		}
		else {
			throw std::runtime_error("dataframe size doesnt match or column headers are absent in either of the dataframe ");
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return *this;
	
}

DataFrame DataFrame::operator[](string c){
	DataFrame df = DataFrame();
	
	if (if_colname_exists(c)){
		df.append_column(columns[find_column_position(c)],c);
		df.row_n = this->row_n ;
	}
	return df;
}

void DataFrame::sort_by_column_names(){
	
	auto comp = []<typename T>(T a , T b){
		return a > b ;
	};

	int pos;
	for(int i = 0 ; i < col_n ;i++){
		pos = i ; 
		for (int j = i; j < col_n; j++){
			if(comp(column_names[pos],column_names[j]))
				pos = j;
		}

		if(pos != i){
			string temp = column_names[i];
			Column Temp = columns[i];

			columns[i] = columns[pos];
			column_names[i] = column_names[pos];

			columns[pos] = Temp ;
			column_names[pos] = temp ;

		}
		
	}
}

void DataFrame::drop_column(int j){
	try{

		if(j < col_n){
			for (int i = j; i < col_n - 1; i++){
				column_names[i] = column_names[i+1];
				columns[i] = columns[i+1];
			}
			
			col_n -= 1;
			column_names.resize(col_n);
			columns.resize(col_n);
		}else{
			throw std::out_of_range("column index out of range");
		}


	}catch(const std::exception& e){
		std::cerr << e.what() << '\n';
	}
	
}

		
void DataFrame::drop_column(string c){
	try{
		if (if_colname_exists(c)){
			int i = find_column_position(c);
			drop_column(i);
		}else{
			throw std::out_of_range("Column name doesnt exist");
		}
		
	}
	catch(const std::exception& e){
		std::cerr << e.what() << '\n';
	}
	
}



void DataFrame::drop_row(int k){
	try{

		if(k < row_n){
			row_n -= 1;
			for (int i = 0; i < col_n; i++){

				
				if(std::holds_alternative<vector<int>>(columns[i].column_data)){
					
					for (int j = k; j < row_n; j++){
						std::get<vector<int>>(columns[i].column_data)[j] = std::get<vector<int>>(columns[i].column_data)[j+1];
					}
					std::get<vector<int>>(columns[i].column_data).resize(row_n);
				}
				else if (std::holds_alternative<vector<double>>(columns[i].column_data)){
					for (int j = k; j < row_n; j++){
						std::get<vector<double>>(columns[i].column_data)[j] = std::get<vector<double>>(columns[i].column_data)[j+1];
					}
					std::get<vector<double>>(columns[i].column_data).resize(row_n);
				}
				else if (std::holds_alternative<vector<bool>>(columns[i].column_data)){
					for (int j = k; j < row_n; j++){
						std::get<vector<bool>>(columns[i].column_data)[j] = std::get<vector<bool>>(columns[i].column_data)[j+1];
					}
					std::get<vector<bool>>(columns[i].column_data).resize(row_n);
				}
				else if (std::holds_alternative<vector<string>>(columns[i].column_data)){
					for (int j = k; j < row_n ; j++){
						std::get<vector<string>>(columns[i].column_data)[j] = std::get<vector<string>>(columns[i].column_data)[j+1];
					}
					std::get<vector<string>>(columns[i].column_data).resize(row_n);
				}
				
			}

			for (int i = k; i < row_n; i++){
				ind.index_names[i] = ind.index_names[i+1];
			}
			
			ind.index_names.resize(row_n);
			
		}else{
			throw std::out_of_range("row index out of range");
		}


	}catch(const std::exception& e){
		std::cerr << e.what() << '\n';
	}
}

void DataFrame::drop_row(string j){
	try{
		if(row_names ){
			int i = ind.get_index_position(j);
			if(i != -1)
				drop_row(i);
			else
				throw std::out_of_range("row names dint exist");
		}else{
			throw std::out_of_range("row names dont exist");
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}

void DataFrame::set_rownames(vector<string> row_namus){
	try{
		if (row_namus.size() == row_n){
			ind = Index(row_namus);
			row_names = true ;
		}
		else{
			throw std::invalid_argument("No of Rows don't match");
		}
		
	}
	catch(const std::exception& e){
		std::cerr << e.what() << '\n';
	}
		
}


void DataFrame::replace_rowname(string old_name, string new_name){
	try{
		if (row_names ){
			int i = ind.get_index_position(old_name);
			if(i != -1)
				ind.index_names[i] = new_name;
			else
				throw std::invalid_argument("row name doesn't exist");
		}
		else{
			throw std::runtime_error("DataFrame doesnt have row names");
		}
	}
	catch(const std::exception& e){
		std::cerr << e.what() << '\n';
	}
	
}


void DataFrame::set_colnames(vector<string> col_namus){
	try{
		if (col_namus.size() == col_n){
			column_names = col_namus;
			col_names = true;
			for (int i = 0; i < col_n; i++){
				columns[i].column_name = col_namus[i] ;
			}
		}
		else{
			throw std::invalid_argument("Sizes dont match");
		}
		
	}
	catch(const std::exception& e){
		std::cerr << e.what() << '\n';
	}
	
}

void DataFrame::replace_colname(string old_name,string new_name){
	try{
		if (col_names && if_colname_exists(old_name) ){
			int i = find_column_position(old_name);
			if(i < col_n){
				column_names[i] = new_name;
				columns[i].column_name = new_name ;
			}
			else throw std::runtime_error("What is error");
		}
		else{
			throw std::invalid_argument("this operation cant be performed on this dataframe");
		}
	}
	catch(const std::exception& e){
		std::cerr << e.what() << '\n';
	}
		
}


// void DataFrame::mean(){
// 	// check for the columns with the type int or double
// 	for (const Column& col : columns) {
//         std::visit([this](const auto& vec) {
//             using T = typename std::decay_t<decltype(vec)>::value_type;
//             if (std::is_same_v<T, int>) {
//                 double sum = 0.0;
//                 size_t count = 0;
//                 for (const auto& value : vec) {
//                     sum += value;
//                     count++;
//                 }
//                 double mean = sum / count;
//                 std::cout <<"Column"<<col.colum_name<<" mean (int): " << mean << std::endl;
//             } else if (std::is_same_v<T, double>) {
//                 double sum = 0.0;
//                 size_t count = 0;
//                 for (const auto& value : vec) {
//                     sum += value;
//                     count++;
//                 }
//                 double mean = sum / count;
//                 std::cout << "Column mean (double): " << mean << std::endl;
//             } else {
//                 std::cout << "Column data type is not numeric." << std::endl;
//             }
//         }, col.column_data);
//     }
// }

void DataFrame::mean(string col_name){

}
