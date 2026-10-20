#include "random.h"

#include <stdlib.h>

double random_double(void) {
    // RAND_MAX is inclusive, so the denominator must be one larger to keep 1.0 out.
    return (double)rand() / ((double)RAND_MAX + 1.0);
}

double random_double_range(double min, double max) {
    return min + (max - min) * random_double();
}
