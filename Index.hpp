#ifndef include_index_h
#define include_index_h

#include <variant>
#include <vector>
#include <string>
#include "dataframe.hpp"

using std::string;
using std::vector;

class Index {

	public:
        
		friend class DataFrame;
		
		/**
		 * @brief Construct a new Index object given index column
		 * 
		 * @tparam T 
		 * @param ind 
		 */
		template<typename T>
		Index(vector<T> ind) : index_names(ind) {}
		/**
		 * @brief Construct a new Index object
		 * 
		 */
		Index() = default;

		/**
		 * @brief Get the index position object, takes in string and returns the position of the index value
		 *  used in row related fuctions
		 * @return int 
		 */
		int get_index_position(string);

    private:
		vector<string> index_names; 
};


#endif