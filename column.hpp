#ifndef include_column_h
#define include_column_h
#include <limits>
#include <variant>
#include <vector>
#include <iostream>
#include <string>
#include "dataframe.hpp"

using std::string;
using std::vector;
using std::holds_alternative;


class Column {


  public:
    
    typedef std::variant<vector<string>, vector<int>, vector<double>, vector<bool>> col_type;
    friend class DataFrame;

    Column() = default;
    template <typename T>
    Column(vector<T> data,const string& name)  {
      try
      {
        column_data=data;
        column_name=name;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      
    }
    template <typename T>
    Column(vector<T> data) : column_data(data) { }
    size_t size();
    size_t size() const;
    template <typename T>
    void push_back(const T);
   
    col_type get_column(){
      return column_data;
    }

  private:
    string column_name;
    col_type column_data;
    // bool 
    

    
    bool check_possible_na(string);
    void convert_and_push_back(string );
    
    void push_nan();
};


#endif