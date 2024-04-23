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
    /**
     * @brief this is a column type vector where in we take only four data types
     * 
     */
    typedef std::variant<vector<string>, vector<int>, vector<double>, vector<bool>> col_type;
    friend class DataFrame;
    /**
     * @brief Construct a new Column object default constructor
     * 
     */
    Column() = default;

    /**
     * @brief Construct a new Column object takes in vector data and column name , this is also called in append_column
     * function
     * @tparam T 
     * @param data 
     * @param name 
     */
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
    /**
     * @brief Construct a new Column object with just column vector
     * 
     * @tparam T 
     * @param data 
     */
    template <typename T>
    Column(vector<T> data) : column_data(data) { }

    /**
     * @brief returns the size of the column
     * 
     * @return size_t 
     */
    size_t size();
     /**
     * @brief returns the size of the const column  
     * 
     * @return size_t 
     */
    size_t size() const;
    /**
     * @brief our own implementation of pushback for variant vector,takes in any datatype
     * 
     * @tparam T 
     */
    template <typename T>
    void push_back(const T);
    /**
     * @brief Get the column object
     * 
     * @return col_type 
     */
    col_type get_column(){
      return column_data;
    }

  private:
    string column_name;
    col_type column_data;
    // bool 
    

    /**
     * @brief this is checked in csv_reader file, where in if our csv has blank values or none or nan
     * it returns true or false
     * @return true 
     * @return false 
     */
    bool check_possible_na(string);
    /**
     * @brief this function checks the current column type and then converts the data to that type and pushes the value
     * 
     */
    void convert_and_push_back(string );
    /**
     * @brief if there is a possible nan value we append nan 
     * 
     */
    void push_nan();
};


#endif