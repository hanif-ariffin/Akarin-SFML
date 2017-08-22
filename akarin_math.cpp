#include <stdlib.h>

int rand_with_negative(int range)
{
	unsigned int rand_value = 2 * (rand() % range);
	int value;

	if ((rand_value) & (1 << 31)) {
		value = -(rand_value / 2);
	} else {
		value = (rand_value / 2);
	}
	return value;
}

int rand_with_negative(void)
{
	return rand_with_negative(1);
}

int rand_with_negative_2(const int range)
{
	int abs_range = abs(range);
	return 2 * (rand() % abs_range) - abs_range;
}