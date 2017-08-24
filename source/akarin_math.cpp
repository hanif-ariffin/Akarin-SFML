#include <stdlib.h>
#include <iostream>


namespace AkarinMath
{
int rand_with_negative(int range)
{
	if (range >= RAND_MAX)
	{
		std::cout << "AkarinMath::rand_with_negative -- requesting a range larger than RAND_MAX" << std::endl;
		return rand_with_negative(RAND_MAX - 1);
	}
	else
	{
		int value = ((rand() % range) * 2) - range;
		std::cout << value << std::endl;
		return value;
	}
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

int rand_with_negative_3(const int range)
{
	int abs_range = abs(range);
	return 1 * (rand() % abs_range);

}

} // namespace AkarinMath