#ifndef AKARIN_MATH
#define AKARIN_MATH

#include <stdlib.h>

namespace AkarinMath
{
/*
Returns a number from (-range, range)
*/
int rand_with_negative(int range);
int rand_with_negative(void);
int rand_with_negative_2(const int range);
int rand_with_negative_3(const int range);
//int random_number_generator_from_discord(int min, int max);
} // namespace AkarinMath

#endif