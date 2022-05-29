#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <chrono>
#include <stdlib.h>

#include "position.hpp"
#include "optimized_astar.hpp"

//#define TEST_ASTAR



#ifdef TEST_ASTAR
    // override the above search iterations if testing
    // the astar algorithm
    #define SEARCH_ITERATIONS 1
#else // !defined(TEST_ASTAR)
    #define MAP_WIDTH 500
    #define MAP_HEIGHT 500
    #define SEARCH_ITERATIONS 100
    #define MAX_MAP_HEIGHT 2
#endif // TEST_ASTAR


#endif