#include <iostream>

#include "Vector.h"

int main()
{
    my::Vector<int> test{ 4 , 8 , 4 , 5 };

    for( auto x : test ) {
        std::cout << x << std::endl;
    }

    std::cout << std::endl;

    my::Vector<int>::iterator iter = test.begin();

    for( iter ; iter != test.end() ; iter ++ ) {
        std::cout << *iter << std::endl;
    }
}
