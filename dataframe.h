#ifndef  dataframe_header_guard
#define dataframe_header_guard

#include <fstream>
#include <memory>
#include <utility>
#include <string>
#include <numeric>

// STL To implement
#include <map>
#include <deque>
#include <vector>

#include "column.h"
#include "index.h"


class DataFrame {

	public:
		// Default Constructor
		DataFrame();	
		
		// reading from a file-stream object
		explicit DataFrame(std::ifstream&);
		
		// dataframe with column names and vector column of different types 
		template <typename T1 , typename... T>
		DataFrame(
			const std::vector<std::string>& , 
			const std::vector<T1>&,
			const std::vector<T>&...
		) ;

	private:
		// Dataframe attributes
		std::vector<std::shared_ptr<Column>> columns;
		std::map<std::string,int> column_names;

		//Methods
		void duplicate_rows(std::deque<std::pair<int,int>> & correspondence);

		void duplicate_rows(int);
		void copy_row(int);
		
	
		template<typename T1 , typename... T>
		void append_column(const  std::string&,int pos,
						   const std::vector<T1>& ,
						   	const std::vector<T>&...); 
		
		template <typename T1>
    	void append_column(const std::vector<std::string>&, int,
                       		const std::vector<T1>&);


		void append_column(const std::string&, const SharedCol&);
		/**
		 * @brief Initilizes the map `column_names` from the first line of the csv
		 * file
		 */
		std::vector<std::string> create_column_names(std::ifstream&);

		/**
		 * @brief Helper function to create the column names
		 */
    	void create_column_names(const std::string&, const char*);

		/**
		 * @brief Initilizes the Columns with the datatypes mentiond in the second
		 * line of the csv file
		 */
		 std::string initialize_column(
			std::ifstream&,
            const std::vector<std::string>& );

		/**
		 * @brief fills the previously intilaized columns and creates the index
		 */
		template <typename T>
		void initialize_column(const std::string&);

		 /**
		 * @brief helper function.
		 */
		void initialize_column(const std::string&, const std::string&);
		void insert_data(
			std::ifstream&, 
			const std::vector<std::string>&,
			const std::string&);

		template <typename T1, typename... T>
		void equal_length(
			size_t len_idx, 
			const char* fun, 
			const std::vector<T1>& v1,
			const std::vector<T>&... v
		) {
			if (!(len_idx == v1.size())) {
				std::string s(
					"The index lenght is: " + 
					std::to_string(len_idx) + 
					" but the input vector has length " + 
					std::to_string(v1.size()) + "in:\n"
			);
				throw std::invalid_argument(s + fun);
			}
			
			if constexpr (sizeof...(T) > 0) equal_length<T...>(len_idx, fun, v...);
		}

		void equal_width(size_t num_names, size_t, const char*);

		template <typename T1, typename... T>
		DataFrame::DataFrame(
			const std::vector<std::string>& names,
			const std::vector<T1>& v1, 
			const std::vector<T>&... cols
		) {
			equal_width(names.size(), sizeof...(T) + 1, __PRETTY_FUNCTION__);
			std::vector<int> idx(v1.size());
			std::iota(idx.begin(), idx.end(), 0);
			index = Index(idx);
			append_column(names[0], std::make_shared<Column>(v1));
			if constexpr (sizeof...(T) > 0) append_column<T...>(names, 1, cols...);
		}

		template <typename T1>
		void DataFrame::append_column(
			const std::vector<std::string>& names, int pos,
            const std::vector<T1>& v1
		) {
    		append_column(names[pos], std::make_shared<Column>(v1));
		}

		template <typename T1, typename... T>
		void DataFrame::append_column(
			const std::vector<std::string>& names, int pos,
            const std::vector<T1>& v1,
            const std::vector<T>&... v2
		) {
   		append_column(names[pos], std::make_shared<Column>(v1));
    	append_column<T...>(names, pos + 1, v2...);
		}

}
#endif 