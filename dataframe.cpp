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



