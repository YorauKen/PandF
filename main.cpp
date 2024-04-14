#include "dataframe.h"
#include "Index.h"
#include "Column.h"


#include <iostream>

int main(int argc, const char** argv) {

	DataFrame df("ex.csv");
	// DataFrame df(vector<string>{string("first row"),string("second row"),string("third row")},vector<string>{string("first row"),string("second row"),string("3rd row")},vector<int>{1,2,3},vector<double>{1,2,3},vector<bool>{true,false,true});
	df.print_dataframe();
	return 0;
}