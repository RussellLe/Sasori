#include "stdafx.h"



long long int fastPower(long long int base, long long int power, long long int mod = LONG_MAX)
{
	long long int output = 1;
	while (power > 0)
	{
		if (power % 2 != 0)
		{
			output = output * base % mod;
		}
		power = power / 2;
		base = (base * base) % mod;
	}
	return output;
}