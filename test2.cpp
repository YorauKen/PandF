#include "dataframe.hpp"
#include "Index.hpp"
#include "column.hpp"

#include <iostream>

int  main(int argc, const char** argv) {
	// create dataframe from csv file
	try {
		/**
		 * @brief Dataframe intilization from csv file
		 * filename followed by boolean for row no's and column no's
		 */
		DataFrame df("ex.csv",true,true);
		cout << "before changing the id column header to jobID " << endl;
		df.print_dataframe();
		cout << "after changing the id column header to jobID " << endl;
		df.replace_colname("id","jobID");
		df.print_dataframe();
		cout << "before dropping row 1" << endl;
		df.drop_row("1");
		df.print_dataframe();
		cout << "after dropping row 1 and before removing column salary" << endl;
		df.drop_column("salary");
		df.print_dataframe();
		cout << "after removing salary column" << endl << "\n";

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}