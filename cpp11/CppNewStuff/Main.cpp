/*
 * Main.cpp
 *
 * Just maing a change on GitHub to check I can retrieve that change in eClipse.
 *
 *  Created on: 6 Dec 2023
 *      Author: paulhackett
 */

#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <Logging/Logging.h>


namespace
{

void Cpp03VersusCpp11 (void)
{
	LOG_DEBUG("--> Cpp03VersusCpp11");

	{
		//
		// The auto keyword
		//
		std::vector< int >	lIV;

		// the C++03 way
		for (std::vector<int>::const_iterator ci = lIV.begin(); ci != lIV.end(); ++ci);

		// the C++11 way
		for (auto ci = lIV.cbegin(); ci != lIV.cend(); ++ci);
	}

	{
		//
		// Range-based for()
		//
		std::vector< int >	lIV;

		// the C++03 way
		for (std::vector<int>::iterator i = lIV.begin(); i != lIV.end(); ++i);

		// the C++11 way
		for (int &item: lIV);
		// item will become, in order, all the things stored in v
		// notice how we're referencing the item, that allows us to change it

		for (const int &item: lIV); // can't change item, we reference it for speed
		for (int item: lIV); // can't change item, we're passing it by value
	}

	{
		//
		// Initializer lists
		//
		// C arrays
		char   array1[] = {'A', 'B'};
		double array2[] = {32.0, 6.003, -0.1};

		// C++03 vectors
		std::vector<char> cpp03vector1;
		cpp03vector1.push_back('A');
		cpp03vector1.push_back('B');

		std::vector<double> cpp03vector2(3);
		cpp03vector2[0] = 32.0;
		cpp03vector2[1] = 6.003;
		cpp03vector2[2] = -0.1;

		// C++11 vectors
		std::vector<char>   cpp11vector1 = {'A', 'B'};
		std::vector<double> cpp11vector2 = {32.0, 6.003, -0.1};
		// or...
		std::vector<char>   cpp11vector3{'A', 'B'};
		std::vector<double> cpp11vector4{32.0, 6.003, -0.1};
		// notice that this works for all other containers as well, not just std::vector

		//
		// more complex examples
		//
		std::map< std::string, std::vector< std::pair< std::string, int>>> name_languages_year
		{
		    {"Dennis Ritchie",    {{"B",      1969}, {"C",        1973}}},
		    {"Niklaus Wirth",     {{"Pascal", 1970}, {"Modula-2", 1973}, {"Oberon", 1986}}},
		    {"Bjarne Stroustrup", {{"C++",    1983}}},
		    {"Walter Bright",     {{"D",      1999}}}
		};
		// notice how the lists are nested to match the templates' parameters

		LOG_DEBUG (name_languages_year["Niklaus Wirth"].at(0).first); // prints `Pascal'
		// cout << name_languages_year["Niklaus Wirth"].at(0).first << endl; // prints `Pascal'

		// adds a new entry to the map
		name_languages_year["John McCarthy"] =
		{
		    {"Lisp", 1958}
		};
		// notice the lack of explicit types
	}

	{
		//
		// C++ arrays
		//
		// C arrays
		char  carray1[] = "Abc"; // caution, an unseen '\0' is added to the end
		float carray2[] = {0.2f, 33.33f};

		// C++ arrays
		std::array<char, 3>  cpparray1{{'A', 'b', 'c'}};
		std::array<float, 2> cpparray2{{0.2f, 33.33f}};
		// observation 1: the size must be deducible at compile time
		// observation 2: the array cannot be resized
		// observation 3: the inner braces are due to the nature of initializer lists,
		//  think of it as one list per template parameter

		// array test drive: the old versus the new

		std::cout << sizeof carray1 - 1 << std::endl; // -1 because of the extra '\0'
		std::cout << sizeof carray2 / sizeof (float) << std::endl; // because number of elements != number of bytes
		std::cout << cpparray1.size() << std::endl;
		std::cout << cpparray2.size() << std::endl;

		//
		// The following is to demonstrate the difference in C/CPP arrays
		// and out-of-bound accesses
		//
		carray2[-5] = 0.1f; // do the moonwalk! *** SURELY THIS IS A BAD ACCESS

		try
		{
			cpparray2.at(-5) = 0.1f; // throws std::out_of_range exception
		}
		catch (const std::exception& lE)
		{
			LOG_DEBUG("Caught exception: " << lE.what());
		}


		// of course there are more reasons why C++ arrays are better than C arrays
		// but this example code section is already too big...
	}

	{
		//
		// Lambda
		//
		// Really good article at https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
		//
		LOG_DEBUG("Lambda");

		char s[]="Hello World!";

		   int Uppercase = 0; //modified by the lambda

		   std::for_each (s, s+sizeof(s),
				   	   	   [&Uppercase] (char c)
						   {
			   	   	   	   		if (isupper(c))
			   	   	   	   		{
			   	   	   	   			Uppercase++;
			   	   	   	   		}
						   }
		   	   	   	     );

		 LOG_DEBUG (Uppercase << " uppercase letters in: "<< s);
	}

	{
		//
		// Uniform Initialization Syntax
		//
		std::string s("hello");
		int m=int(); //default initialization

		// You can also use the = notation for the same purpose in certain cases:
		std::string sx="hello";
		int x=5;

		// For POD aggregates, you use braces:
		int arr[4]={0,1,2,3};
		struct tm today={0};

		class C
		{
			int a;
			int b;
			int c=7; // C++11 supports in-class initialization of data members:

		public:

			 C(int i, int j)
			 :	a(i), b(j)
			 {
			 }
		};

		C c {0,0}; //C++11 only. Equivalent to: C c(0,0);

		int* a = new int[3] { 1, 2, 0 }; //C++11 only

		class X
		{
		  int a[4];

		public:
		  X() : a{1,2,3,4} {} //C++11, member array initializer
		};
	}

	{
		//
		// Deleted and Defaulted Functions
		//
		struct A
		{
			A()=default; //C++11

			virtual ~A()=default; //C++11
		};

		struct NoCopy
		{
			NoCopy()=default; //C++11

			NoCopy & operator =( const NoCopy & ) = delete;
			NoCopy ( const NoCopy & ) = delete;
		};

		NoCopy a;

		// NoCopy b(a); //compilation error, copy ctor is deleted
	}

	{
		//
		// nullptr
		// At last, C++ has a keyword that designates a null pointer constant.
		// nullptr replaces the bug-prone NULL macro and the literal 0 that
		// have been used as null pointer substitutes for many years. nullptr
		// is strongly-typed:
		//
	}

	{
		//
		// Delegating Constructors
		//
		class M //C++11 delegating constructors
		{
			int x, y;
			char *p;

		public:
			M(int v) : x(v), y(0), p(new char [99]) {} //#1 target

			M(): M(0) {std::cout << "delegating ctor" << std::endl;} //#2 delegating

		};
	}

	{
		//
		// Rvalue References
		// Reference types in C++03 can only bind to lvalues.
		// C++11 introduces a new category of reference types called rvalue references.
		// Rvalue references can bind to rvalues, e.g. temporary objects and literals.
		// The primary reason for adding rvalue references is move semantics. Unlike
		// traditional copying, moving means that a target object pilfers the resources of
		// the source object, leaving the source in an "empty" state. In certain cases
		// where making a copy of an object is both expensive and unnecessary, a move
		// operation can be used instead. To appreciate the performance gains of move
		// semantics, consider string swapping. A naive implementation would look like this:
		//
		//	void naiveswap(string &a, string & b)
		//	{
		//		string temp = a;
		//
		//		a=b;
		//		b=temp;
		//	}
		//
		// This is expensive. Copying a string entails the allocation of raw memory and copying
		// the characters from the source to the target. In contrast, moving strings merely swaps
		// two data members, without allocating memory, copying char arrays and deleting memory:
		//
		//	void moveswapstr(string& empty, string & filled)
		//	{
		//		//pseudo code, but you get the idea
		//		size_t sz=empty.size();
		//		const char *p= empty.data();
		//
		//		//move filled's resources to empty
		//		empty.setsize(filled.size());
		//		empty.setdata(filled.data());
		//
		//		//filled becomes empty
		//		filled.setsize(sz);
		//		filled.setdata(p);
		//	}
		//
		// If you're implementing a class that supports moving, you can declare a move constructor
		// and a move assignment operator like this:
		//
		//	class Movable
		//	{
		//		Movable (Movable&&); //move constructor
		//
		//		Movable&& operator=(Movable&&); //move assignment operator
		//	};
	}

	{
		//
		// C++11 Standard Library
		//
		// C++ underwent a major facelift in 2003 in the form of the Library Technical
		// Report 1 (TR1). TR1 included new container classes (unordered_set, unordered_map,
		// unordered_multiset, and unordered_multimap) and several new libraries for
		// regular expressions, tuples, function object wrapper and more. With the approval
		// of C++11, TR1 is officially incorporated into standard C++ standard, along with
		// new libraries that have been added since TR1. Here are some of the C++11
		// Standard Library features:
		//

		//
		// Threading Library
		//

		//
		// New Smart Pointer Classes
		//

		//
		// New C++ Algorithms
		// The C++11 Standard Library defines new algorithms that mimic the set theory
		// operations
		//
		//		all_of()
		//		any_of()
		//		none_of().
		//
		// The following listing applies the predicate ispositive() to the range [first, first+n) and
		// uses all_of(), any_of() and none_of() to examine the range's properties:
		//
		//	#include <algorithm>
		//	//C++11 code
		//
		//	//are all of the elements positive?
		//	all_of(first, first+n, ispositive()); //false
		//
		//	//is there at least one positive element?
		//	any_of(first, first+n, ispositive());//true
		//
		//	// are none of the elements positive?
		//	none_of(first, first+n, ispositive()); //false
		//
		//
		// Also -
		//		copy_n(source,5,target);
		//		iota(a, a+5, 10);
	}

	{
		//
		// Other
		//

		// shared_ptr
		// Strongly-typed enums
		// static assert
		// Variadic template
		// override identifier
		// Unordered containers
	}
}


void Cpp11VersusCpp14 (void)
{
	//
	// See https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1319r0.html
	//
}


void Cpp14VersusCpp17 (void)
{
	//
	// See https://isocpp.org/files/papers/p0636r0.html
	//
}


void Cpp17VersusCpp20 (void)
{
	//
	// See https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2131r0.html
	//
}

}	// Anonymous namespace


int main (int aArgc, char **appArgv)
{
	int lRet(0);

	LOG_DEBUG("==>Begin the test");

	Cpp03VersusCpp11 ();
	Cpp11VersusCpp14 ();
	Cpp14VersusCpp17 ();
	Cpp17VersusCpp20 ();

	return (lRet);
}
