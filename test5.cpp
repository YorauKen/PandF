#include "dataframe.hpp"
#include "Index.hpp"
#include "column.hpp"

#include <iostream>

int  main(int argc, const char** argv) {
	// create dataframe from csv file
	try {
		
		DataFrame df (
				vector<int>{1,3,3},
				vector<double>{1,1,3},
				vector<string>{string("first row"),string("second row"),string("second row")},
				vector<bool>{true,false,true}
			);
		cout << "Dataframe initilization" << endl;
		cout << "Dataframe df  : " << endl;
		df.print_dataframe();

		cout << "After appending a column "<< endl;
		vector<int> a = {1,2,3};
		df = df + a;

		

		df.print_dataframe();
		

		

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}