#include "dataframe.h"
#include "Index.h"
#include "Column.h"


#include <iostream>

int main(int argc, const char** argv) {

    DataFrame df("ex.csv");
	df.print_dataframe();
	return 0;
}