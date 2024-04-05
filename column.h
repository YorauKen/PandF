#ifndef column_header_guard
#define column_header_guard

#include <algorithm>
#include <string>
#include <variant>

// STL TO IMPLEMENT
#include <vector>
#include <deque>


class DataFrame;
class Column {
	public:
		
		Column() : col() {};
		//Copy constructor --brief idea
		Column(const Column& , const std::deque<int>&);

		// construct from existing one
		template<typename T>
		explicit Column(const std::vector<T>&t):col(t) {}

		/**
		 * @brief converting the string type to respective datatype as,we read the data as string from a file ,we infer datatype here
		 */
		void typecast_push_back(const std::string&);

		// Our push_back to column vector
		template<typename T>
		void push_back(const T);

		/***
		 * @brief length of the column
		*/
		size_t size() const; 
		/**
		 * @brief Returns the type of the stored data as a string
		 */
		std::string type_name();

		template <typename T>
		T& get_value(int i);


		private:
			template<typename T>
			T& Column::get_value(int t){
				if(std::holds_alternative<std::vector<T>>(col))
					 return std::get<std::vector<T>>(col)[i];
				else {
					std::string s = "incompatible template type in :\n";
					throw std::invalid_argument(s + __PRETTY_FUNCTION__);
				}
			}

			template<typename T>
			void Column::push_back(const T t) {
				if (std::holds_alternative<std::vector<T>>(col))
					std::get<std::vector<T>>(col).push_back(t);
				else {
					std::string s = "cannot push type into column, in\n: ";
					throw std::invalid_argument(s + __PRETTY_FUNCTION__);
				}
			}
		
}


#endif

