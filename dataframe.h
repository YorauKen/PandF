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
		    
		DataFrame():row_n(0),col_n(0){};

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
		
		template<typename T>
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

		vector<string> get_col_names();

		auto get_column(int& i);

		DataFrame operator+(DataFrame& rhs);

		bool if_colname_exists(string);

		void append_column(Column , string);
				
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

template<typename T>
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
		if (col_names.size() == pos+1){
			append_column(col_names[pos] , column);
			return ;
		}
		// std::cout << pos << std::endl;
		append_column(col_names[pos] , column);
		append_columns(col_names , pos +1 ,Next_Columns...);
	} catch( const std::exception& e) {
		std::cerr << "Exception caught: "<< e.what() << std::endl;
	}
	
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


bool DataFrame::if_colname_exists(string colu_name ){
	for(int i = 0 ; i < col_n ; i++){
		if(colu_name == column_names[i])
			return true;
	}
	return false;
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



#endif 