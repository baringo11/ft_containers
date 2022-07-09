
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
// ------ OPERATOR = ------
	{
		std::cout << "\n------------- FT Vector (operator=)-------------" << std::endl;
		NS::vector<int> foo(3, 100);
		NS::vector<int> bar(5, 200);
		bar = foo;
		foo = NS::vector<int>();
		std::cout << "Size of foo: " << int(foo.size()) << std::endl;
		std::cout << "Size of bar: " << int(bar.size()) << std::endl;
		std::cout << "The contents of bar vector are:";
		for (NS::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}
// ------ DIFERENT ITERATORS ------
	{
		std::cout << "\n---- FT Vector (iterator walk & comparison diferent iterators) ----" << std::endl;
		NS::vector<int> myvector;
		for (int i = 1; i <= 5; i++)
			myvector.push_back(i);
		std::cout << "myvector contains:";
		NS::vector<int>::iterator it = myvector.begin();
		NS::vector<int>::const_iterator cit = myvector.end();
		for (; it != cit; ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		std::cout << "\n------------- FT Vector (reverse iterator walk)-------------" << std::endl;
		std::cout << "myvector contains:";
		for (NS::vector<int>::reverse_iterator it1 = myvector.rbegin(); it1 != myvector.rend(); ++it1)
			std::cout << ' ' << *it1;
		std::cout << std::endl;
	}

// CAPACITY:
	{
	// ------ SIZE ------
		{
			std::cout << "\n------------- FT Vector (size)-------------" << std::endl;
			NS::vector<int> myvector;
			std::cout << "size (should be 0):  " << myvector.size() << std::endl;
			for (int i = 0; i < 10; i++)
				myvector.push_back(i);
			std::cout << "size (should be 10): " << myvector.size() << std::endl;
			myvector.insert(myvector.end(), 10, 100);
			std::cout << "size (should be 20): " << myvector.size() << std::endl;
			myvector.pop_back();
			std::cout << "size (should be 19): " << myvector.size() << std::endl;

			std::cout << "\n------------- FT Vector (max_size)-------------" << std::endl;
			std::cout << "max_size: " << myvector.max_size() << std::endl;

			std::cout << "\n------------- FT Vector (resize)-------------" << std::endl;
			NS::vector<int> myvector1;
			for (int i = 0; i < 10; i++)
				myvector1.push_back(i);
			std::cout << "myvector contains 10 elements:                           ";
			for (size_t i = 0; i < myvector1.size(); i++)
				std::cout << ' ' << myvector1[i];
			std::cout << std::endl;

			myvector1.resize(5);
			std::cout << "myvector contains 5 elements:                            ";
			for (size_t i = 0; i < myvector1.size(); i++)
				std::cout << ' ' << myvector1[i];
			std::cout << std::endl;

			myvector1.resize(8);
			std::cout << "myvector contains 8 elements, filled up with value 0:    ";
			for (size_t i = 0; i < myvector1.size(); i++)
				std::cout << ' ' << myvector1[i];
			std::cout << std::endl;

			myvector1.resize(11, 100);
			std::cout << "myvector contains 11 elements, filled up with value 100: ";
			for (size_t i = 0; i < myvector1.size(); i++)
				std::cout << ' ' << myvector1[i];
			std::cout << std::endl;
		}
	// ------ CAPACITY ------
		{
			std::cout << "\n------------- FT Vector (capacity)-------------" << std::endl;
			NS::vector<int> myvector;
			std::cout << "capacity: " << myvector.capacity() << std::endl;
			std::cout << "size: " << myvector.size() << std::endl;
			std::cout << std::endl;

			myvector.push_back(1);
			std::cout << "myvector contains: ";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << std::endl;
			std::cout << "capacity: " << myvector.capacity() << std::endl;
			std::cout << "size: " << myvector.size() << std::endl;
			std::cout << std::endl;

			myvector.push_back(2);
			std::cout << "myvector contains: ";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << std::endl;
			std::cout << "capacity: " << myvector.capacity() << std::endl;
			std::cout << "size: " << myvector.size() << std::endl;
			std::cout << std::endl;

			myvector.push_back(3);
			std::cout << "myvector contains: ";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << std::endl;
			std::cout << "capacity: " << myvector.capacity() << std::endl;
			std::cout << "size: " << myvector.size() << std::endl;
			std::cout << std::endl;

			myvector.push_back(4);
			std::cout << "myvector contains: ";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << std::endl;
			std::cout << "capacity: " << myvector.capacity() << std::endl;
			std::cout << "size: " << myvector.size() << std::endl;
			std::cout << std::endl;

			myvector.push_back(5);
			std::cout << "myvector contains: ";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << std::endl;
			std::cout << "capacity: " << myvector.capacity() << std::endl;
			std::cout << "size: " << myvector.size() << std::endl;
			std::cout << std::endl;

			myvector.push_back(6);
			std::cout << "myvector contains: ";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << std::endl;
			std::cout << "capacity: " << myvector.capacity() << std::endl;
			std::cout << "size: " << myvector.size() << std::endl;
			std::cout << std::endl;

			myvector.push_back(7);
			std::cout << "myvector contains: ";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << std::endl;
			std::cout << "capacity: " << myvector.capacity() << std::endl;
			std::cout << "size: " << myvector.size() << std::endl;
			std::cout << std::endl;

			myvector.push_back(8);
			std::cout << "myvector contains: ";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << std::endl;
			std::cout << "capacity: " << myvector.capacity() << std::endl;
			std::cout << "size: " << myvector.size() << std::endl;
			std::cout << std::endl;

			myvector.push_back(9);
			std::cout << "myvector contains: ";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << std::endl;
			std::cout << "capacity: " << myvector.capacity() << std::endl;
			std::cout << "size: " << myvector.size() << std::endl;
		}
	// ------ EMPTY ------
		{
			std::cout << "\n------------- FT Vector (empty)-------------" << std::endl;
			NS::vector<int> myvector;
			std::cout << "Is my vector empty?: " << myvector.empty() << std::endl;
			for (int i = 1; i < 10; i++)
				myvector.push_back(i);
			std::cout << "size after pushing values 1 to 9 included: " << myvector.size() << std::endl;
			std::cout << "Is my vector empty?: " << myvector.empty() << std::endl;
			while (!myvector.empty())
				myvector.pop_back();
			std::cout << "size after pop back until empty:           " << myvector.size() << std::endl;
			std::cout << "Is my vector empty?: " << myvector.empty() << std::endl;
		}
	// ------ RESERVE ------
		{
		std::cout << "\n--------- FT Vector (reserve) ---------" << std::endl;
		NS::vector<int> myvector;
		for (int i = 1; i < 10; i++)
			myvector.push_back(i);
		std::cout << "Initial capacity: " << myvector.capacity() << std::endl;

		myvector.reserve(5);
		std::cout << "Capacity should be the same: " << myvector.capacity() << std::endl;

		myvector.reserve(20);
		std::cout << "Capacity should be 20: " << myvector.capacity() << std::endl;
	}
	}

// ELEMENT ACCESS:
	{
		// ------ OPERATOR [] ------
		{
			std::cout << "\n------------- FT Vector (operator[])-------------" << std::endl;
			NS::vector<int> myvector1(10);
			for (unsigned i = 0; i < myvector1.size(); i++)
				myvector1[i] = i;
			std::cout << "myvector contains:";
			for (unsigned i = 0; i < myvector1.size(); i++)
				std::cout << ' ' << myvector1[i];
			std::cout << std::endl;
		}
		// ------ AT ------
		{
			std::cout << "\n------------- FT Vector (at)-------------" << std::endl;
			NS::vector<int> myvector1(10);
			for (unsigned i = 0; i < myvector1.size(); i++)
				myvector1.at(i) = i;
			std::cout << "myvector contains:";
			for (unsigned i = 0; i < myvector1.size(); i++)
				std::cout << ' ' << myvector1.at(i);

			myvector1.at(5) = 28;

			std::cout << "\nmyvector contains:";
			for (unsigned i = 0; i < myvector1.size(); i++)
				std::cout << ' ' << myvector1.at(i);

			try
			{
				std::cout << myvector1.at(45);
			}
			catch(const std::exception& e)
			{
				std::cout << "\nlooking out of bounds";
			}
			std::cout << std::endl;
		}
		// ------ FRONT / BACK ------
		{
			std::cout << "\n------------- FT Vector (front/back)-------------" << std::endl;
			NS::vector<int> myvector1;
			myvector1.push_back(78);
			myvector1.push_back(42);
			myvector1.push_back(16);

			std::cout << "myvector.front() (should be 78):   " << myvector1.front() << std::endl;
			std::cout << "myvector.back()  (should be 16):   " << myvector1.back() << std::endl;

			myvector1.front() -= myvector1.back();
			std::cout << "myvector.front() (should be 62):   " << myvector1.front() << std::endl;
		}
	}
}