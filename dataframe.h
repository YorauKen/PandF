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

#include "Column.h"
#include "Index.h"
#include "concepts.h"


using std::vector;
using std::cout;
using std::endl;
using std::ifstream;


template<typename T>
int calculate_count(vector<T> , T val);

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
		 * @brief Construct a new Data Frame object without column names
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

		void drop_row(string);

		void drop_column(int );

		void drop_column(string );

		void set_rownames(vector<string>);

		void replace_rowname(string , string);

		void set_colnames(vector<string>);

		void replace_colname(string ,string);

		void mean();

		void mean(string col_name);


		void mode();

		void mode(string col_name);
				
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
		
		vector<string> read_and_write_column_names(ifstream& file , bool);

		void initialise_column(ifstream& file, vector<string> col_names , bool row_nam);

		template <typename T>
		void initialise_column(const string& );

		void initialise_column(const string& col_type , const string& col_name);
		
		void initialise_index(const string&);

		void insert_data(ifstream& file ,bool row_nam);	

		void initialise_column(ifstream& file , bool row_nam);

		void initialise_column(string col_type);

		template<typename T>
		void initialise_column(); // without column name

		template <typename T , typename ...T1>
		bool check_Index_Length(int , vector<T> , vector<T1>...);
		
 
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
		throw std::runtime_error("unequal column size");	
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




#endif 