#ifndef  include_concat_h
#define  include_concat_h


#include <iostream>
#include "dataframe.h"
#include "concepts.h"
#include <type_traits>

// template<typename T , typename U>
//  requires is_DataFrame<T> && is_eligible_Vector<U> || is_DataFrame<U> && is_eligible_Vector<T>
// DataFrame operator+(T lhs , U rhs){
//     if(is_DataFrame<T>);
//     return DataFrame();
// }

// template <class T, class U>
// requires (is_DataFrame<T>) && (is_eligible_Vector<U>) || (is_DataFrame<U>) && (is_eligible_Vector<T>)
// DataFrame operator+(T lhs, U rhs) {
//     if constexpr (is_DataFrame<T> && is_eligible_Vector<U>) {
//         // Add a vector to a DataFrame
//         return lhs.append_column({"new_column"}, rhs);
//     } else if constexpr (is_DataFrame<U> && is_eligible_Vector<T>) {
//         // Add a vector to a DataFrame
//         return rhs.append_column({"new_column"}, lhs);
//     } else {
//         // Handle other cases if needed
//         throw std::runtime_error("Invalid operands for operator+");
//     }
// }

#endif // ! 
