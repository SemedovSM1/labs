#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void
test_negative(){
    double min = 0;
    double max = 0;
    find_minmax({ -23, -76, -101 }, min, max);
    assert(min == -101);
    assert(max == -23);
}

void test_same_numbers()
{
    double min;
    double max;
    find_minmax({ 8,8,8}, min, max);
    assert(min == 8);
    assert(max == 8);
}

void test_one_number()
{
    double min;
    double max;
    find_minmax({44}, min, max);
    assert(min == 44);
    assert(max == 44);
}


void test_empty_vector()
{
    double min = 1;
    double max = 3;
    find_minmax({}, min, max);
    assert(min == 1);
    assert(max == 3);
}


int
main() {
    test_positive();
    test_negative();
    test_same_numbers();
    test_one_number();
    test_empty_vector();
}
