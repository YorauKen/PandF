#ifndef include_concepts_h
#define include_concepts_h


#include <concepts>
#include <variant>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <vector>
#include <string>
#include "dataframe.hpp"
using std::vector;
using std::string;

class DataFrame;
/**
 * @brief this concept is used to check if the column type is required column or not in append column
 * 
 * @tparam T 
 */
template <typename T>
concept is_eligible_Vector = std::is_same_v<vector<int>,vector<T>> || std::is_same_v<vector<double>,vector<T>> ||std::is_same_v<vector<string>,vector<T>> ||std::is_same_v<vector<bool>,vector<T>>;


#endif