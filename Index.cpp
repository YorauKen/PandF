#include "dataframe.h"
#include "Index.h"


int Index::get_index_position(string s){
    for (int i = 0; i < index_names.size(); i++){
        if (s == index_names[i])
            return i;
    }
    return -1;
}