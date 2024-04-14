#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "dataframe.h"
#include "Column.h"

using std::vector;
using std::istringstream;
using std::string;
using std::ifstream;

vector<string> DataFrame::read_and_write_column_names(ifstream& file){
	string line;
	std::getline(file,line);
	std::istringstream names(line);
	string cell ;
    std::getline(names,cell,',') ; 
	while(std::getline(names,cell,',')){
		if((std::find(column_names.begin(),column_names.end(),cell) == column_names.end()))
        	column_names.push_back(cell);
		else throw
			std::runtime_error("Duplicate column name found!!");
	}
	return column_names;
}

template<typename T>
void DataFrame::initialise_column(const string& col_name){
	Column a(vector<T>(),col_name);
    columns.push_back(a);
}

void DataFrame::initialise_index(const string& type_name){
	if(type_name == "int")
		ind = Index(vector<int>());
	else if (type_name == "string"){
		ind = Index(vector<string>());
	}
	else {
        throw std::runtime_error("Wrong index type: "+ type_name +" in:\n");
    }
}



void DataFrame::initialise_column(const string& type,const string& col_name){
	if (type == "double")
        initialise_column<double>(col_name);
    else if (type == "int")
        initialise_column<int>(col_name);
    else if (type == "string")
        initialise_column<string>(col_name);
    else if (type == "bool")
        initialise_column<bool>(col_name);
    else {
        throw std::runtime_error("Wrong column type: " + type + " for: " + col_name +" in:\n");
    }
}

string DataFrame::initialise_column(ifstream& file,vector<string> col_names){
	string line;
	std::getline(file,line);
	std::istringstream type_names(line);
    string index_type;
	getline(type_names,index_type,','); // init index
	initialise_index(index_type);
	string cell;
	int i =0;
	while(std::getline(type_names,cell,','))
	{	
		initialise_column(cell,col_names[i++]);
	}
	return index_type;
}

void DataFrame::insert_data(std::ifstream& file, const vector<string>& cols,
                            const std::string& index_type) {
    string line, value;
    while (std::getline(file, line)) {
        istringstream row(line);
        std::getline(row, value, ',');
        if (index_type == "int")
            std::get<vector<int>>(ind.index_names).push_back(stoi(value));
        else
            std::get<vector<string>>(ind.index_names).push_back(value);
        for (const string& col : cols) {
            std::getline(row, value, ',');
            columns[find_column_position(col)].convert_and_push_back(value);
        }
		if(row.str().empty())
			std::runtime_error("Column/Row Overflow");
		//have to check if row becomes empty or not else we have to throw error as data is more than the no of columns

    }
}

DataFrame::DataFrame(string filename){
    ifstream infile(filename);
	
	try{
		//std::cout << "I have initialized column names 1"<<std::endl;
    	vector<string> col_names = read_and_write_column_names(infile);
		//std::cout << "I have initialized column names 2"<<std::endl;
		string index_type = initialise_column(infile,col_names);
		//std::cout << "I have initialized column names 3"<<std::endl;
		insert_data(infile,col_names,index_type);
		//std::cout << "I have initialized column names 4"<<std::endl;
		

	} catch (const std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
	
	
}

