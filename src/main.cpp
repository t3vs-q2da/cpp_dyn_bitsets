#include <iostream>
#define __DEBUG__DYN__BITSETS 1
#include <DynamicBitset.h>
#include <string>

void printBinary(const unsigned char * pointer,size_t size)
{
	unsigned char c;
	for(int i = 0;i<size;++i)
	{
		c=pointer[i];
		for(int i = 128;i!=0;i>>=1)
		{
			std::cout<<bool(i&c);
			// std::cout<<i<<' ';
		}
		std::cout<<' ';
	}
	std::cout<<std::endl;
}

void test()
{
	std::cout<<"hi it test"<<std::endl;
	DynamicBitset<> bitset{};
	printBinary(bitset.getAll(),bitset.getSize());
	bitset.set(0,1);
	bitset.set(24,1);
	bitset.set(31,1);
	// std::cout<<bitset.get(0)<<std::endl;
	printBinary(bitset.getAll(),bitset.getSize());
	bitset.resize(8);
	bitset.set(31,0);
	bitset.set(32,1);
	printBinary(bitset.getAll(),bitset.getSize());
	bitset.resize(4);
	printBinary(bitset.getAll(),bitset.getSize());
	bitset.resize(32);
	bitset.set(255,1);
	printBinary(bitset.getAll(),bitset.getSize());
	bitset.set(255,0);
	printBinary(bitset.getAll(),bitset.getSize());
	int a;
}