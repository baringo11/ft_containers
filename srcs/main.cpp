
#include <iostream>
#include "Vector/vector.hpp"
#include "Stack/stack.hpp"

#include <vector>
#include <stack>
#include <iterator>

#ifndef NS
# define NS ft
#endif

#define STR(X) #X
#define ASSTR(X) STR(X)

int main()
{
	std::cout << "------------------- Testing " << ASSTR(NS) << " containers -------------------" << std::endl;

	std::cout << "\n\n\n*************************************************************************" << std::endl;
	std::cout << "**************************   VECTOR   ***********************************" << std::endl;
	std::cout << "*************************************************************************" << std::endl;
// ------ CONSTRUCTORS ------
	{
		std::cout << "\n---------- FT Vector (Constructors and iterator) ----------" << std::endl;
		
		NS::vector<int> empty_vec;
		std::cout << "Empty vector:";
		for (NS::vector<int>::iterator it = empty_vec.begin(); it != empty_vec.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		NS::vector<int> fill_vec(5, 10);
		std::cout << "Fill vector:";
		for (NS::vector<int>::iterator it = fill_vec.begin(); it != fill_vec.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		empty_vec.push_back(2);
		empty_vec.push_back(4);
		empty_vec.push_back(6);
		NS::vector<int> range_vec(empty_vec.begin(), empty_vec.end());
		std::cout << "Range vector:";
		for (NS::vector<int>::iterator it = range_vec.begin(); it != range_vec.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		NS::vector<int> copy_vec(fill_vec);
		std::cout << "Copy vector:";
		for (NS::vector<int>::iterator it = copy_vec.begin(); it != copy_vec.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
		copy_vec.push_back(33);
		copy_vec.push_back(66);
		copy_vec.push_back(99);

		NS::vector<int> deep_copy_vec(copy_vec);
		copy_vec.clear();
		std::cout << "Deep copy vector:";
		for (NS::vector<int>::iterator it = deep_copy_vec.begin(); it != deep_copy_vec.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		int myints[] = {16, 2, 77, 29};
		NS::vector<int> extra(myints, myints + sizeof(myints) / sizeof(int));
		std::cout << "Extra vector:";
		for (NS::vector<int>::iterator it = extra.begin(); it != extra.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}


}