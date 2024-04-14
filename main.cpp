#include "dataframe.h"
#include "Index.h"
#include "Column.h"


#include <iostream>

int main(int argc, const char** argv) {

    // DataFrame df("ex.csv");
	DataFrame df(vector<string>{"first row","second row"},vector<string>{"first row","second row"},vector<int>{1,2},vector<int>{1,2});
	df.print_dataframe();
	return 0;
}