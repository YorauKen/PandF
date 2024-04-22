#include "dataframe.hpp"
#include "Index.hpp"
#include "column.hpp"

#include <iostream>

int  main(int argc, const char** argv) {
	// create dataframe from vectors (row_names , col_names , cols)
	try {
		
		DataFrame df (
				vector<string>{string("first row"),string("second row"),string("third row")},
				vector<string>{string("first col"),string("second col"),string("third col"),string("fourth Column")},
				vector<int>{1,3,3},
				vector<double>{1,1,3},
				vector<string>{string("first row"),string("second row"),string("second row")},
				vector<bool>{true,false,true}
			);
		cout << "Dataframe initilization" << endl;
		cout << "Dataframe df  : " << endl;
		df.print_dataframe();

		DataFrame df2 (
				vector<string>{string("first row"),string("second row"),string("third row")},
				vector<string>{string("fifth col"),string("sixth col")},
				vector<int>{3,6,9},
				vector<double>{10.5,1.55,3.63}
		);
		cout << "Dataframe df2  : " << endl;
		df2.print_dataframe();

		cout << "Concatenation of dataframes : "<< endl;

		df + df2;

		df.print_dataframe();

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}