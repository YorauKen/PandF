#ifndef include_dataframe_h
#define include_dataframe_h

#include "Column.h"
#include "Index.h"

#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>



using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::ifstream;

class Column;
class Index;
class DataFrame{

	public:
		    
		DataFrame();
		
		DataFrame(string );

		typedef std::variant<vector<string>, vector<int>, vector<double>, vector<bool>> col_type;

		template<typename T , typename... T1>
		DataFrame(const vector<string> row_names, const vector<string> col_headers , const vector<T>,const vector<T1>...);
		
		int find_column_position(const std::string& col_name);

		void print_dataframe();
		
		template<typename T>
		void append_column(const string col_name ,  vector<T> column );

		template<typename T>
		void append_columns(const vector<string> col_name ,int pos, vector<T> column);
	
		template <typename T , typename... T1>
		void append_columns(const vector<string> col_names ,int pos, vector<T> column , vector<T1>...);

	
	private:
		Index ind;
		vector<string> column_names; 
		vector<Column> columns;

		vector<string> read_and_write_column_names(ifstream& file);

		string initialise_column(ifstream& file, vector<string> col_names);

		template <typename T>
		void initialise_column(const string& );

		void initialise_column(const string& col_type , const string& col_name);
		

		void initialise_index(const string&);

		void insert_data(ifstream& file ,const vector<string>&col , const string&);	

		template <typename T , typename ...T1>
		bool check_Index_Length(int , vector<T> , vector<T1>...);

		
 
};

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

template<typename T , typename... T1>
bool DataFrame::check_Index_Length(int size , vector<T> col , vector<T1>... Next_Column ){
	return ((col.size() == size) && ... && (Next_Column.size() == size));
}


template<typename T>
void DataFrame::append_column(const string col_name ,  vector<T> column ){
	columns.push_back(Column(column , col_name));
}

template<typename T>
void DataFrame::append_columns(const vector<string> col_names ,int pos, vector<T> column){
	append_column(col_names[pos] , column);
}

template <typename T , typename... T1>
void DataFrame::append_columns(const vector<string> col_names ,int pos, vector<T> column , vector<T1>... Next_Columns){
	// std::cout << pos << std::endl ;
	if (col_names.size() == pos+1){
		append_column(col_names[pos] , column);
		return ;
	}
	// std::cout << pos << std::endl;
	append_column(col_names[pos] , column);
	append_columns(col_names , pos +1 ,Next_Columns...);
}


#endif 