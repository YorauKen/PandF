#include <limits>
#include <variant>
#include <vector>
#include <iostream>
#include <string>

#include "dataframe.h"
#include "column.h"

using std::string;
using std::vector;
using std::holds_alternative;




bool Column::check_possible_na(string s){
  return (s.empty()) || (s == "None") || (s == "NaN") || (s == "null");
}

size_t Column::size(){
    return static_cast<const Column&>(*this).size();
}
size_t Column::size() const {
    if(holds_alternative<vector<double>>(column_data))
        return std::get<vector<double>>(column_data).size();
    else if (holds_alternative<vector<string>>(column_data))
        return std::get<vector<string>>(column_data).size();
    else if (holds_alternative<vector<bool>>(column_data))
        return std::get<vector<bool>>(column_data).size();
    else if(holds_alternative<vector<int>>(column_data))
        return std::get<vector<int>>(column_data).size();
    return 0;
}

void Column::push_nan(){
    typedef std::numeric_limits<double> nan;

    if (std::holds_alternative<vector<double>>(column_data))
       push_back(nan::quiet_NaN());
    else if (std::holds_alternative<vector<string>>(column_data))
       push_back(string("nan"));
    else  {
        string msg = "Attemting to push_back NA for a bool/int type causes failure";
        throw std::runtime_error(msg);
    }
}

template <typename T>
void Column::push_back(const T t){
    if(std::holds_alternative<std::vector<T>>(column_data))
        std::get<std::vector<T>>(column_data).push_back(t);
    else{
        //error
    }
}


void Column::convert_and_push_back(string value){
  if(check_possible_na(value)){
    push_nan();
    return;
  }
  try{
    if(std::get_if<vector<double>>(&column_data)){
        push_back(std::stod(value));
    } else if(std::get_if<vector<int>>(&column_data)){
        push_back(std::stoi(value));
    } else if(std::get_if<vector<string>>(&column_data)){
        push_back(value);
    } else if(std::get_if<vector<bool>>(&column_data)){
        if(value == "true") 
            push_back(true);
        else if(value == "false")
           push_back(false);
        else {
            throw std::runtime_error("invalid value to boolean column");
        }
      } 
 } catch(const std::runtime_error& e){
    std::cerr << "Error: " << e.what() << std::endl;
  }
  
}



