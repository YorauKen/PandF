#include<fstream>
#include<iostream>
#include<vector>
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
	for(int i = 0 ; i < col_n ; i++){
		if(colu_name == column_names[i])
			return true;
	}
	return false;
}



vector<string> DataFrame::get_col_names(){
	return column_names;
}


auto DataFrame::get_column(int& i) {
	
	// auto get_column_lambda = [=]<typename T>(){
	//   	if(get_column_lambda<int>())
	// 		return std::get<vector<int>>(columns[i].column_data);   
	// 	else if(get_column_lambda<double>())
	// 		return std::get<vector<double>>(columns[i].column_data); 
	// 	else if(get_column_lambda<string>())
	// 		return std::get<vector<string>>(columns[i].column_data); 
	// 	else if(get_column_lambda<bool>())
	// 		return std::get<vector<bool>>(columns[i].column_data);
	// };
	
	// if(get_column_lambda<int>())
	// 	return std::get<vector<int>>(columns[i].column_data);   
	// else if(get_column_lambda<double>())
	// 	return std::get<vector<double>>(columns[i].column_data); 
	// else if(get_column_lambda<string>())
	// 	return std::get<vector<string>>(columns[i].column_data); 
	// else if(get_column_lambda<bool>())
	// 	return std::get<vector<bool>>(columns[i].column_data); 
	// else {
	// 	std::cout << "I am lazy u please debug " << std::endl;
	// 	throw std::runtime_error("invalid col type");
	// }


	
}





DataFrame DataFrame::operator+(DataFrame &rhs){
	
	try
	{
		// if((this->row_n == rhs.row_n)  && (this->col_names && rhs.row_names))
		// {	
		// 	vector<string> colu_namus = rhs.get_col_names();
		// 	for(int i = 0 ; i < rhs.col_n ; i++){
		// 		if(this->if_colname_exists(colu_namus[i])){
		// 			this->append_column(colu_namus[i] , rhs.get_column(i));
		// 		}
		// 	}
		// } else if ((this->row_n == rhs.row_n) && (!this->col_names && !rhs.row_names))
		// {
		// 	for(int i = 0 ; i < rhs.col_n ; i++){
		// 		this->append_columns(rhs.get_column(i));
		// 	}
		// }
		// else {
		// 	throw std::runtime_error("dataframe size doesnt match or column headers are absent in either of the dataframe ");
		// }
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
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