#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

int main(int, char* [])
{
    my_class test_object("qwerty");

    return test_object.is_valid() ? EXIT_SUCCESS : EXIT_FAILURE;
}