
#define __DEBUG__DYN__BITSETS 2
#define __LOG__DYN__BITSETS 3
#include <DynamicBitset.h>
#include <string>

template<typename T>
T getType(T a)
{
	std::cout<<__PRETTY_FUNCTION__<<std::endl;
	return a;
}

void test()
{
	std::cout<<"hi it test ssss hi"<<std::endl;
	DynamicBitset<> bitset{1};
	bitset.insert(8,1);
	bitset.insert(7,1);
	{
		DynamicBitset<> bits1{3};
		DynamicBitset<> bits2{4};
		bits2.set(3,1);
		bits2.print();
	}
	bitset.print();
	int a;
}