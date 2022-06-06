
#include <iostream>
#include "Vector/vector.hpp"

#include <vector>
#include <iterator>

int main()
{

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////           VECTOR                 /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// ------ CONSTRUCTORS ------
    {
        ft::vector<int> vec;
        vec.push_back(2);
        vec.push_back(4);
        vec.push_back(6);
        std::cout << "The contents of the vector are:";
		for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

    }


}