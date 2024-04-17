#ifndef include_index_h
#define include_index_h

#include <variant>
#include <vector>
#include <string>
#include "dataframe.h"

using std::string;
using std::vector;

class Index {

	public:
        
		friend class DataFrame;
		
		template<typename T>
		Index(vector<T> ind) : index_names(ind) {}
		
		Index() = default;

		int get_index_position(string);

    private:
		vector<string> index_names; 
};


#endif