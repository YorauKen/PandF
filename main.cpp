#include "dataframe.h"
#include "Index.h"
#include "Column.h"
// #include "concepts.h"

#include <iostream>

int main(int argc, const char** argv) {

	//Data{Frame df("ex.csv",false,false);
	try
	{		vector<int> a = {1,2,3};
			DataFrame df(vector<string>{string("first row"),string("second row"),string("third row")},vector<string>{string("first row"),string("second row"),string("3rd row")},vector<int>{1,2,3},vector<int>{1,2,3},vector<int>{1,2,3});
			// df.print_dataframe();
			
			// df = operator+(df,a) ;

			
			// DataFrame df(a,vector<int>{1,2,3},a,vector<int>{1,2,3});
			// df.print_dataframe();
			// df = df + a;
			// df.print_dataframe();
			// DataFrame df2(a,vector<int>{1,2,3},a);
			df = df[vector<string>{string("first row"),string("second row")}];
			//df = df + df2;
			df.print_dataframe();		

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
	return 0;
}