#include <climits>
#include <cstring>
#include <iostream>
#include <random>
using namespace std;

int encode(float a) {
	int ret;
	int *tmp = (int *)(&a);
	if (a > 0) {
		ret = *tmp;
		ret |= 0x80000000;
	} else {
		ret = ~(*tmp);
	}
	ret = ((ret & 0xff) << 24) | (((ret >> 8) & 0xff) << 16) |
		  (((ret >> 16) & 0xff) << 8) | ((ret >> 24) & 0xff);
	return ret;
}

int encode(int a) {
	unsigned int tmp = a - INT_MIN;
	int ret = 0;
	ret = ((tmp & 0xff) << 24) | (((tmp >> 8) & 0xff) << 16) |
		  (((tmp >> 16) & 0xff) << 8) | ((tmp >> 24) & 0xff);
	return ret;
}

bool test(float a, float b) {
	unsigned int ta = encode(a);
	unsigned int tb = encode(b);
	if (a == b)
		return memcmp((unsigned char *)&ta, (unsigned char *)&tb, 4) == 0;
	else if (a < b)
		return memcmp((unsigned char *)&ta, (unsigned char *)&tb, 4) < 0;
	else
		return memcmp((unsigned char *)&ta, (unsigned char *)&tb, 4) > 0;
}

int main() {
	// float a = -1.0;
	// float b = 1.3;
	// for(int i = INT_MIN; i < INT_MAX; ++i)
	//     if(!test(i, rand()))
	//         cout << "failed" << endl;

	for (int i = 0; i < 10000; ++i) {
	}
	if (!test((float)(i), float(rand()))) cout << "failed" << endl;
}