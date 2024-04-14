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
        typedef std::variant<vector<string>,vector<int>> idx ;
		friend class DataFrame;
		
		template<typename T>
		Index(vector<T> ind) : index_names(ind) {}

		Index() = default;

    private:
		idx index_names;
};


#endif