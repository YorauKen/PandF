#include "dataframe.hpp"
#include "Index.hpp"
#include "column.hpp"

#include <iostream>

int  main(int argc, const char** argv) {
	// create dataframe from csv file
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

		cout << "retrieving single column" << endl;
		DataFrame df2 = df["first col"];
		df2.print_dataframe();

		cout << "retrieving two columns "<< endl;
		vector<string> cols = {"first col","second col"};
		DataFrame df3 = df[cols];
		df3.print_dataframe();

		df.mean();

		df.mode();

		cout << df.count(0,3) << endl;

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}