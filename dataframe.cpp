#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

#include "Column.h"
#include "dataframe.h"

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

template<typename T , typename... T1>
DataFrame::DataFrame(const vector<string> row_names , const vector<string> col_headers , const vector<T> Column,const vector<T1>...Next_Columns){
	
	if(check_Index_Length(row_names.size() ,Column , Next_Columns... )){
		 
		if(sizeof...(T1)+1 == col_headers.size()){
			ind = Index(row_names);
			column_names = col_headers ;
			append_columns(col_headers , 0 , Column , Next_Columns... );
		}
		else{
			throw std::runtime_error("No of columns doesnt match column headers");	
		}
	}
	else{
		throw std::runtime_error("unequal column size");	
	}
}

void DataFrame::print_dataframe(){
	// cout << "I am before print stmt" << endl;
	for (int i = 0; i < columns.size(); i++){
		// cout << "I am in for loop print stmt" << endl;
		col_type temp = columns[i].column_data;
		if(std::holds_alternative<vector<int>>(temp))
		{
			for (int j = 0; j < std::get<vector<int>>(temp).size(); j++){
				cout << std::get<vector<int>>(temp)[j] << ' ' ;
			}
			cout << endl;
		} else if(std::holds_alternative<vector<double>>(temp)){
			
			for (int j = 0; j < std::get<vector<double>>(temp).size(); j++){
				cout << (int)std::get<vector<double>>(temp)[j] << ' ' ;
			}
			cout << endl;
		} else if(std::holds_alternative<vector<string>>(temp)){
			
			for (int j = 0; j < std::get<vector<string>>(temp).size(); j++){
				cout << std::get<vector<string>>(temp)[j] << ' ' ;
			}
			cout << endl;
		} else if(std::holds_alternative<vector<bool>>(temp)){
			std::cout << std::boolalpha;
			for (int j = 0; j < std::get<vector<bool>>(temp).size(); j++){
				cout << std::get<vector<bool>>(temp)[j] << ' ' ;
			}
			cout << endl;
		} else {
			// error
	
		}
	}
}


template<typename T , typename... T1>
bool DataFrame::check_Index_Length(int size , vector<T> col , vector<T1>... Next_Column ){
	return ((col.size() == size) && ... && (Next_Column.size() == size));
}

template<typename T>
void DataFrame::append_column(const string col_name ,  vector<T> column ){
	columns.push_back(Column(column , col_name));
}

template<typename T>
void append_column(const string col_name ,int pos, vector<T> column){
	
}

template <typename T , typename... T1>
void DataFrame::append_columns(const vector<string> col_names ,int pos, vector<T> column , vector<T1>... Next_Columns){
	append_column(col_names[pos] , column);
	append_columns(col_names , pos +1 ,Next_Columns...);
}
