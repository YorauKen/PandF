#ifndef include_dataframe_h
#define include_dataframe_h

#include<fstream>
#include<iostream>
#include<vector>

#include<algorithm>
#include <cfloat>
#include <cmath>
#include <concepts>
#include <type_traits>

#include "column.hpp"
#include "Index.hpp"
#include "concepts.hpp"


using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::is_same_v;

// template<typename T>
// int calculate_count(vector<T> , T val);

template<typename T>
int count_string(vector<string> temp,T a){
	return std::count(temp.begin(),temp.end(),a);
}

class Column;
class Index;
class DataFrame{

	public:
		/**
		 * @brief initialize dataframe with zero rows and columns
		 * 
		 */
		DataFrame():row_n(0),col_n(0),columns(vector<Column>{}){};

		/**
		 * @brief Construct a new Data Frame from csv file 
		 * 
		 */
		DataFrame(string , bool  , bool );

		/**
		 * @brief A column type of int ,double , string and boolean
		 * 
		 */
		typedef std::variant<vector<string>, vector<int>, vector<double>, vector<bool>> col_type;

		/**
		 * @brief Construct a new Data Frame object with index and column names provided followed by the individual columns
		 * 	variadic template to take in n columns
		 * @tparam T  
		 * @tparam T1 
		 * @param row_namus 
		 * @param col_headers 
		 */
		template<typename T , typename... T1>
		DataFrame(const vector<string> row_namus, const vector<string> col_headers , const vector<T>,const vector<T1>...);
		
		/**
		 * @brief Construct a new Data Frame object without the index and column names , takes multiple columns 
		 * variadic template to take in n columns
		 * @tparam T
		 * @tparam T1 
		 */
		template<typename T , typename... T1>
		DataFrame(const vector<T> , const vector<T1>...) ;

		/**
		 * @brief Construct a new Data Frame object with single column
		 * 
		 * @tparam T 
		 */
		template<typename T>
		DataFrame(const vector<T>);

		/**
		 * @brief This function returns the column position in the dataframe, used as helper function in other functions
		 * 
		 * @param col_name 
		 * @return int 
		 */
		int find_column_position(const std::string& col_name);

		void print_dataframe();
		
		/**
		 * @brief returns a respective columns by taking column names and returns as dataframe object
		 * 
		 * @return DataFrame 
		 */
		DataFrame operator[](vector<string>);
		/**
		 * @brief Takes a single column name and returns the columns
		 * 
		 * @return DataFrame 
		 */
		DataFrame operator[](string);

		/**
		 * @brief Get the col names object used as helper object
		 * 
		 * @return vector<string> 
		 */
		vector<string> get_col_names();

		/**
		 * @brief Get the column object by position
		 * 
		 * @param i 
		 * @return Column 
		 * 
		 */
		Column get_column(int i);

		/**
		 * @brief concatenates the dataframe , merges the dataframe if only the rows are equal
		 * 
		 * @param rhs 
		 * @return DataFrame 
		 */
		DataFrame operator+(DataFrame& rhs);

		/**
		 * @brief checks if column exists by column name
		 * 
		 * @return true 
		 * @return false 
		 */
		bool if_colname_exists(string);

		/**
		 * @brief appends the column object to dataframe
		 * 
		 */
		void append_column(Column , string);

		/**
		 * @brief sorts the dataframe by column names
		 * 
		 */
		void sort_by_column_names();
		/**
		 * @brief drop the row by index
		 * 
		 */
		void drop_row(int);
		/**
		 * @brief drop the row by their column name
		 * 
		 */
		void drop_row(string);
		/**
		 * @brief drop the column by column index
		 * 
		 */
		void drop_column(int );
		/**
		 * @brief column by string name
		 * 
		 */
		void drop_column(string );
		/**
		 * @brief Set the rownames of the dataframe by vector strings
		 * 
		 */
		void set_rownames(vector<string>);
		/**
		 * @brief replace row name , takes in row name and replaces another row name
		 * 
		 */
		void replace_rowname(string , string);
		/**
		 * @brief Set the colnames for a dataframe object
		 * 
		 */
		void set_colnames(vector<string>);
		/**
		 * @brief  replace col name , takes in column name and replaces another column name
		 * 
		 */
		void replace_colname(string ,string);

		/**
		 * @brief provides the mean for all the column objects
		 * 
		 */
		void mean();
		/**
		 * @brief mean of the column name
		 * 
		 * @param col_name 
		 */
		void mean(string col_name);
		/**
		 * @brief returns the count of a certain value , takes in column name and val type
		 * 
		 * @tparam T 
		 * @param col_ind 
		 * @param val 
		 * @return int 
		 */
		template<typename T>
		int count(string col_ind ,T val );

		/**
		 * @brief returns the count of a certain value , takes in column index and val type 
		 * 
		 * @tparam T 
		 * @param col_ind 
		 * @param val 
		 * @return int 
		 */
		template<typename T >
		int count(int col_ind ,T val );

		/**
		 * @brief returns the count of a certain value , takes in column index and val type
		 * 
		 * @param col_ind 
		 * @param val 
		 * @return int 
		 */
		int count(int col_ind , string val);
		/**
		 * @brief returns the mode of all columns
		 * 
		 */
		void mode();
		/**
		 * @brief returns the mode for particular column name
		 * 
		 * @param col_name 
		 */
		void mode(string col_name);
		/**
		 * @brief returns the mode for particular column index
		 * 
		 * @param col_pos 
		 */
		void mode(int col_pos);
		/**
		 * @brief concatenation of dataframe with column vector
		 * 
		 * @param dataframe lhs 
		 * @param vector rhs 
		 * @return DataFrame object
		 */
		template <typename T>
		friend DataFrame operator+(DataFrame lhs, vector<T> rhs){
    		try{
				if(!lhs.col_names && rhs.size() == lhs.row_n ){
					lhs.append_columns(rhs);
					return lhs ;
				}
				else{
					throw std::runtime_error("Invalid no of rows matching/Dataframe doesnt have column name");
				}
			} catch( const std::exception& e) {
				std::cerr << "Exception caught: "<< e.what() << std::endl;
			}
			return DataFrame();
		}	
		
	private:
		Index ind;
		vector<string> column_names; 
		vector<Column> columns;
		size_t row_n;
		size_t col_n;
		bool row_names;
		bool col_names;
		
		/**
		 * @brief helper function to read csv file to read and write column names to dataframe object
		 * 
		 * @param file  fileobject 
		 * @param rownames bool
		 * @return vector<string> 
		 */
		vector<string> read_and_write_column_names(ifstream& file , bool);

		/**
		 * @brief helper function  to initilize the column names
		 * 
		 * @param fileobject file 
		 * @param  vector<string> col_names 
		 * @param bool - row_names exists or not 
		 */
		void initialise_column(ifstream& file, vector<string> col_names , bool row_nam);

		/**
		 * @brief initialize the column with column name
		 * 
		 * @tparam T  - datatype
		 */
		template <typename T>
		void initialise_column(const string& );
		/**
		 * @brief initializes the column with column type and column name
		 * 
		 * @param col_type 
		 * @param col_name 
		 */
		void initialise_column(const string& col_type , const string& col_name);
		/**
		 * @brief Initialize index object of dataframe with string
		 * 
		 */
		void initialise_index(const string&);
		/**
		 * @brief takes in filestream object and appends the data to the columns , 
		 * 
		 * @param filestream object file
		 * @param bool row_name if row_names exist
		 */
		void insert_data(ifstream& file ,bool row_nam);	
		/**
		 * @brief initialise the columns with defined datatype 
		 * 
		 * @param file 
		 * @param row_nam  - if row_names exist
		 */
		void initialise_column(ifstream& file , bool row_nam);
		/**
		 * @brief helper function to initialize the column type with given type
		 * 
		 * @param col_type 
		 */
		void initialise_column(string col_type);
		/**
		 * @brief function to create column without column name
		 * 
		 * @tparam T 
		 */
		template<typename T>
		void initialise_column(); // without column name

		/**
		 * @brief This function appends the column with column name and column vector
		 * 
		 * @tparam T 
		 * @param col_name column name 
		 * @param column  column vector
		 */
		template<is_eligible_Vector T>
		void append_column(const string col_name ,  vector<T> column );

		/**
		 * @brief This function appends the column with certain position , column name and column vector , used as intermediate 
		 *  or base function in append columns variadic template condition
		 * 
		 * @tparam T 
		 * @param col_name column name 
		 * @param pos 	   position
		 * @param column column vector
		 */
		template<typename T>
		void append_columns(const vector<string> col_name ,int pos, vector<T> column);
		/**
		 * @brief This function appends the columns with their column names recursively incrementing the position , variadic approach is followed here
		 * 
		 * @tparam  
		 * @tparam T1 
		 * @param col_names 
		 * @param pos 
		 * @param column 
		 */
		template <typename T , typename... T1>
		void append_columns(const vector<string> col_names ,int pos, vector<T> column , vector<T1>...);
		/**
		 * @brief This function acts as base function for appending columns for dataframe without the column headers
		 * 
		 * @tparam T 
		 */
		template<typename T>
		void append_columns(vector<T>);
		/**
		 * @brief This function is used for appending columns for dataframe without the column headers, variadic method is used 
		 * to append columns here
		 * 
		 * @tparam T 
		 * @tparam T1 
		 * @param cols 
		 */
		template<typename T, typename... T1>
		void append_columns(vector<T>col , vector<T1>... cols  );
		/**
		 * @brief This function is used to check if the columnsthat are getting appended are of same size
		 * 
		 * @tparam  
		 * @tparam T1 
		 * @return true 
		 * @return false 
		 */
		template <typename T , typename ...T1>
		bool check_Index_Length(int , vector<T> , vector<T1>...);
		
		/**
		 * @brief fetches the column data value ,
		 * 
		 * @param i 
		 * @return col_type 
		 */
		col_type get_column_data(int i);

		
};



template<typename T>
void DataFrame::append_columns(vector<T>col ){
 	columns.push_back(Column(col));
	col_n += 1 ;
}

		
template<typename T, typename... T1>
void DataFrame::append_columns(vector<T>col , vector<T1>... cols  ){
	append_columns(col);
	
	append_columns(cols...);
}


template<typename T>
DataFrame::DataFrame(const vector<T>col){
	col_names = false;
	row_names = false;
	row_n = col.size();
	col_n = 1 ;
	columns.push_back(Column(col));
}


template<typename T , typename... T1>
DataFrame::DataFrame(const vector<T>col , const vector<T1>... cols ){
	try
	{
		if(check_Index_Length(col.size() ,col ,cols... )){
			
			col_names = false;
			row_names = false;
			row_n = col.size();
			col_n = 0 ;
			append_columns(col ,cols...);
	} else{
		throw std::runtime_error("column sizes doesn't match here");
	}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
}



template<typename T , typename... T1>
DataFrame::DataFrame(const vector<string> row_namus , const vector<string> col_headers , const vector<T> Column,const vector<T1>...Next_Columns){
	
	if(check_Index_Length(row_namus.size() ,Column , Next_Columns... )){
		 
		if(sizeof...(T1)+1 == col_headers.size()){
			ind = Index(row_namus);
			row_names = true ;
			col_names = true ;
			col_n = col_headers.size();
			row_n = row_namus.size();
			column_names = col_headers ;
			append_columns(col_headers , 0 , Column , Next_Columns... );
		}
		else{
			throw std::runtime_error("No of columns doesnt match column headers");	
		}
	}
	else{
		throw std::runtime_error("unequal row size");	
	}
}

template<typename T , typename... T1>
bool DataFrame::check_Index_Length(int size , vector<T> col , vector<T1>... Next_Column ){
	return ((col.size() == size) && ... && (Next_Column.size() == size));
}

template<typename T>
void DataFrame::initialise_column(){
	Column a(vector<T>{});
    columns.push_back(a);
}

template<is_eligible_Vector T>
void DataFrame::append_column(const string col_name ,  vector<T> column ){
	
	try {
		if(is_eligible_Vector<T>){
			columns.push_back(Column(column , col_name)); 
		}
		else 
			throw std::runtime_error("Invalid column type");
	} catch( const std::exception& e) {
		std::cerr << "Exception caught: "<< e.what() << std::endl;
	}
	
}

template<typename T>
void DataFrame::append_columns(const vector<string> col_names ,int pos, vector<T> column){
	try
	{
		append_column(col_names[pos] , column);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

template <typename T , typename... T1>
void DataFrame::append_columns(const vector<string> col_names ,int pos, vector<T> column , vector<T1>... Next_Columns){
	
	try{		
		append_column(col_names[pos] , column);
		append_columns(col_names , pos +1 ,Next_Columns...);
	} catch( const std::exception& e) {
		std::cerr << "Exception caught: "<< e.what() << std::endl;
	}
	
}

template<typename T>
int DataFrame::count(string col_ind ,T val ){
	try{
			if (if_colname_exists(col_ind)){
 				return count(find_column_position(col_ind),val);
 			}
 			else{
 				throw std::invalid_argument("column name doesnt exist");
 			}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return -1;
}





template<typename T >
int DataFrame::count(int col_ind ,T val ){
	try{
			if (col_ind < col_n)
			{	
				if(std::holds_alternative<vector<int>>(columns[col_ind].column_data) ){
				vector<int> temp(std::get<vector<int>>(columns[col_ind].column_data));
				return std::count(temp.begin(),temp.end(),val);
				}
				else if(std::holds_alternative<vector<double>>(columns[col_ind].column_data)){
					vector<double> temp(std::get<vector<double>>(columns[col_ind].column_data));
					
					return std::count(temp.begin(),temp.end(),val);
				}
				else if(std::holds_alternative<vector<bool>>(columns[col_ind].column_data)){
					vector<bool> temp(std::get<vector<bool>>(columns[col_ind].column_data));
					return std::count(temp.begin(),temp.end(),val);
				}
				else{
					throw std::invalid_argument("column type and value type dont match");
				}
			}
			else{
				throw std::invalid_argument("index out of range");
			}
			
	}
	catch(const std::exception& e){
		std::cerr << e.what() << '\n';
	}
	return -1;
}




#endif 