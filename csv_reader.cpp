#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "dataframe.hpp"
#include "column.hpp"

using std::vector;
using std::istringstream;
using std::string;
using std::ifstream;

vector<string> DataFrame::read_and_write_column_names(ifstream& file,bool row_names){
	string line;
	std::getline(file,line);
	std::istringstream names(line);
	string cell ;
	if(row_names)
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
	ind = Index(vector<string>());
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



void DataFrame::initialise_column(string col_type)
{
	if (col_type == "double")
        initialise_column<double>();
    else if (col_type == "int")
        initialise_column<int>();
    else if (col_type == "string")
        initialise_column<string>();
    else if (col_type == "bool")
        initialise_column<bool>();
    else {
        throw std::runtime_error("Wrong column type: " +col_type + " for: "+" in:\n");
    }
}

void DataFrame::initialise_column(ifstream& file , bool row_nam){
	string line;
	std::getline(file,line);
	std::istringstream type_names(line);
	if(row_nam){
		string index_type;
		getline(type_names,index_type,','); // init index
		if(index_type != "string"){
			throw std::runtime_error("index type not equal to string");
		}
		initialise_index(index_type);
	}
	string cell;
	int i =0;
	while(std::getline(type_names,cell,','))
	{	
		initialise_column(cell);
	}
	
}


void DataFrame::initialise_column(ifstream& file,vector<string> col_names,bool row_nam ){
	string line;
	std::getline(file,line);
	std::istringstream type_names(line);
	if(row_nam){
		string index_type;
		getline(type_names,index_type,','); // init index
		if(index_type != "string"){
			throw std::runtime_error("index type not equal to string");
		}
		initialise_index(index_type);
	}
   
	string cell;
	int i =0;
	while(std::getline(type_names,cell,','))
	{	
		initialise_column(cell,col_names[i++]);
	}
}



void DataFrame::insert_data(std::ifstream& file,bool row_nam ) {
    string line, value;
    while (std::getline(file, line)) {
        istringstream row(line);
		if(row_nam){
        	std::getline(row, value, ',');
      		ind.index_names.push_back(value);
		}
        
		int n = columns.size();
		for (int i = 0 ; i < n ; i++) {
            std::getline(row, value, ',');
            columns[i].convert_and_push_back(value);
        }
		if(row.str().empty())
			std::runtime_error("Column/Row Overflow");
		//have to check if row becomes empty or not else we have to throw error as data is more than the no of columns

    }
}

DataFrame::DataFrame(string filename , bool row_nam = false ,bool col_nam = false){
    ifstream infile(filename);
	 // boolean
	try{
		if(col_nam && row_nam){
	    	vector<string> colu_names = read_and_write_column_names(infile,row_nam);
			col_n = colu_names.size();
			initialise_column(infile,colu_names,row_nam);
			insert_data(infile,row_nam);
			row_n = ind.index_names.size();
		}
		else if(col_nam && !row_nam){
			vector<string> colu_names = read_and_write_column_names(infile,row_nam);
			col_n = colu_names.size();
			initialise_column(infile,colu_names,row_nam);
			insert_data(infile,row_nam);
			row_n = columns[0].size();

		}
		else if (!col_nam && row_nam){
			initialise_column(infile,row_nam);
			insert_data(infile,row_nam);
			row_n = columns[0].size();
			col_n = columns.size();
		} 
		else {
			initialise_column(infile,row_nam);
			insert_data(infile,row_nam);							
			row_n = columns[0].size();
			col_n = columns.size();
		}
		col_names = col_nam; // boolean
		row_names = row_nam;
		
		
	
	} catch (const std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
}

