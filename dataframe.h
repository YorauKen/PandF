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
		void append_column(const string col_name ,int pos, vector<T> column);
	
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



#endif 