#ifndef include_dataframe_h
#define include_dataframe_h

#include<fstream>
#include<iostream>
#include<vector>

#include<algorithm>
#include<map>
#include <concepts>
#include <type_traits>

#include "Column.h"
#include "Index.h"
#include "concepts.h"


using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::ifstream;

// class DataFrame;
// template <typename T>
// concept is_eligible_Vector = std::is_same_v<vector<int>,vector<T>> || std::is_same_v<vector<double>,vector<T>> ||std::is_same_v<vector<string>,vector<T>> ||std::is_same_v<vector<bool>,vector<T>>;

// template <typename T>
// concept is_DataFrame = std::is_same_v<DataFrame , T> ;

class Column;
class Index;
class DataFrame{

	public:
		    
		DataFrame():row_n(0),col_n(0),columns(vector<Column>{}){};

		DataFrame(string , bool  , bool );

		typedef std::variant<vector<string>, vector<int>, vector<double>, vector<bool>> col_type;

		template<typename T , typename... T1>
		DataFrame(const vector<string> row_namus, const vector<string> col_headers , const vector<T>,const vector<T1>...);
		
		template<typename T , typename... T1>
		DataFrame(const vector<T> , const vector<T1>...) ;

		template<typename T>
		DataFrame(const vector<T>);

		int find_column_position(const std::string& col_name);

		void print_dataframe();
		
		template<is_eligible_Vector T>
		void append_column(const string col_name ,  vector<T> column );

		template<typename T>
		void append_columns(const vector<string> col_name ,int pos, vector<T> column);
	
		template <typename T , typename... T1>
		void append_columns(const vector<string> col_names ,int pos, vector<T> column , vector<T1>...);
		
		template<typename T>
		void append_columns(vector<T>);
		
		template<typename T, typename... T1>
		void append_columns(vector<T>col , vector<T1>... cols  );

		DataFrame operator[](vector<string>);

		DataFrame operator[](string);

		vector<string> get_col_names();

		Column get_column(int i);

		DataFrame operator+(DataFrame& rhs);

		bool if_colname_exists(string);

		void append_column(Column , string);

		void sort_by_column_names();

		void drop_row(int);

		void drop_row(string);

		void drop_column(int );

		void drop_column(string );

		void set_rownames(vector<string>);

		void replace_rowname(string , string);

		void set_colnames(vector<string>);

		void replace_colname(string ,string);
				
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
	// std::cout << pos << std::endl ;
	try{
		
		// std::cout << pos << std::endl;
		append_column(col_names[pos] , column);
		append_columns(col_names , pos +1 ,Next_Columns...);
	} catch( const std::exception& e) {
		std::cerr << "Exception caught: "<< e.what() << std::endl;
	}
	
}







#endif 