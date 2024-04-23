#include "dataframe.hpp"
#include "Index.hpp"
#include "column.hpp"

#include <iostream>

int  main(int argc, const char** argv) {
	// create dataframe from vectors (row_names , col_names , cols)
	try {
		
		DataFrame df2 (
				vector<string>{string("first row"),string("second row"),string("third row")},
				vector<string>{string("z"),string("g"),string("a")},
				vector<int>{3,6,9},
				vector<double>{10.5,1.55,3.63},
				vector<int>{90,99,100}
		);
		cout << "Dataframe df2  before sorting by column names : " << endl;
		df2.print_dataframe();

		df2.sort_by_column_names();

		cout << "After sorting the dataframe by column name " << endl;

		df2.print_dataframe();


	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}