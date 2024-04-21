#include "dataframe.hpp"
#include "Index.hpp"
#include "column.hpp"
// #include "concepts.hpp"

#include <iostream>

int main(int argc, const char** argv) {

	//Data{Frame df("ex.csv",false,false);
	try
	{		vector<int> a = {1,2,3};
			DataFrame df(vector<string>{string("first row"),string("second row"),string("third row")},vector<string>{string("first row"),string("second row"),string("3rd row"),string("4th Column")},vector<int>{1,3,3},vector<double>{1,4,3},vector<string>{string("first row"),string("second row"),string("third row")},vector<bool>{true,false,true});
			// df.print_dataframe();
			
			// df = operator+(df,a) ;

			
			// DataFrame df(a,vector<int>{1,2,3},a,vector<int>{1,2,3});
			// df.print_dataframe();
			// df = df + a;
			// df.print_dataframe();
			// DataFrame df2(a,vector<int>{1,2,3},a);
			// df.drop_row(2);
			//df = df + df2;
			std::cout << df.count(4,string("first row")) << endl;
			//df.print_dataframe();		

			df.mean();  // MEAN OF possible column names
			// df.mean("row_name");

			// df.count(0,0);

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
	return 0;
}