# DataFrame Library PandF

## Overview
The DataFrame library is a powerful tool for working with tabular data in C++. It provides a comprehensive set of functionalities for creating, manipulating, and analyzing datasets. Whether you need to perform basic data operations or complex analyses, this library offers a robust solution.

## Features
- **Efficient Data Handling:** The library is designed to handle large datasets efficiently, ensuring optimal performance even with significant amounts of data.
- **Tabular Data Operations:** Users can perform a wide range of operations on tabular data, including filtering, sorting, aggregation, and more.
- **Integration with Standard C++ Libraries:** The library seamlessly integrates with standard C++ libraries, making it easy to incorporate into existing projects.
- **Flexibility:** Users have the flexibility to customize various aspects of data manipulation and analysis according to their specific requirements.

## Usage
To use the DataFrame library, include the necessary header files in your C++ project and instantiate the DataFrame class. Here's a basic example of how to get started:

```cpp
#include "dataframe.hpp"
#include "Index.hpp"
#include "column.hpp"
// Create a DataFrame object

int main(){
	try{
		DataFrame df("ex.csv",true,true);
		cout << "Dataframe initilization" << endl;
		cout << "Dataframe df  : " << endl;
		df.print_dataframe();
	} catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
```

## Template Features Used

### 1. Variadic Templates
> This variadic template constructor initializes a DataFrame object with multiple columns provided as vectors of different types, ensuring all columns have the same length.

```cpp
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
		} /* rest of the code */
	} /* rest of the code */
}
```
### 2.  Template specialization
>This is the specialization for calculating the mean specifically for double columns, taking into account the presence of NaN values.
```cpp
template <>
double calculate_mean(vector<double> vec)
{
	int n = vec.size();
	int no_of_values = n;
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (std::isnan(vec[i]))
		{
			no_of_values--;
			continue;
		}
		sum += (vec[i]);
	}
	sum = sum / no_of_values;
	return sum;
}
```

### 3.  Lambda Templates 
>  the lambda function comp is used to define the comparison operation for sorting the column names in ascending order
```cpp
void DataFrame::sort_by_column_names()
{
    /* Lambda template function for comparison operation */
    auto comp = []<typename T>(T a, T b)
    {
        return a > b;
    };

    int pos;
    for (int i = 0; i < col_n; i++)
    {
        pos = i;
        for (int j = i; j < col_n; j++)
        {
            if (comp(column_names[pos], column_names[j]))
                pos = j;
        }
		/* rest of the code */
	}
}
```

### 4.  Concepts and type traits
>concept `is_eligible_Vector`, which ensures that only certain vector types can be used as columns in the DataFrame. This helps maintain type safety and prevents unintended usage of incompatible data types. and type traits `is_same_v` is used to verify the vector type 

```cpp
template <typename T>
concept is_eligible_Vector = std::is_same_v<vector<int>,vector<T>> || std::is_same_v<vector<double>,vector<T>> ||
std::is_same_v<vector<string>,vector<T>> ||std::is_same_v<vector<bool>,vector<T>>;
```

### 5. Fold expression 
> Fold expressions are used to ensure that all provided vectors have the same length in the `check_Index_Length` function by iterating over the parameter pack of vectors and combining the size comparisons using the logical AND operator
```cpp
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
		} else { /* rest of code*/ }
	}	/* rest of code */
```

### 6. Template Friendship
> Friend function template for overloading the addition operator (+) to append a vector to a DataFrame, checking size compatibility and column name absence.
```cpp
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
```
