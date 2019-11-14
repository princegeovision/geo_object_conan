#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
//#include <iostream>
#include "geo_object.h"

TEST_CASE( "get library version", "[basic]" ) {

    char* result = geo_object_version();
    REQUIRE( std::string(result) == std::string("geo_object_version = v1.1.0") );
}
// int main() {
//     char* result = geo_object_version();
    
//     printf("result=%s", result); 
// }
