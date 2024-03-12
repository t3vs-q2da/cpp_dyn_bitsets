#pragma once
#if __DEBUG__DYN__BITSETS
#include <iostream>
#endif

template<typename Size_t = unsigned int>
requires std::is_integral<Size_t>::value
class DynamicBitset{
	unsigned char* bits;
	Size_t size;
public:
	DynamicBitset(Size_t size = 4):bits{new unsigned char[size]{}},size{size}
	{
		#if __DEBUG__DYN__BITSETS
		std::cout<<"created DynamicBitset with\n   size:"<<size<<std::endl;
		#endif
	}

	void resize(Size_t n_size)
	{
		if(!n_size)
		{
			throw std::underflow_error("resize with 0");
		}
		unsigned char* n_bits=new unsigned char[n_size]{};
		if(size>n_size)
		{
			size=n_size;
		}
		for(unsigned int i = 0;i<size;++i)
		{
			n_bits[i]=bits[i];
		}
		delete[] bits;
		bits=n_bits;
		size=n_size;
	}

	//std::range_error
	void set(Size_t pos,bool a)
	{
		if(pos>=size*8)
		{
			throw std::range_error("DynamicBitset::set size:"+std::to_string(size*8)+" pos:"+std::to_string(pos));
		}
		if(a)
		{
			bits[pos/8]|=1<<pos%8;
			return;
		}
		bits[pos/8]&=~(1<<pos%8);
	}
	//std::range_error
	bool get(Size_t pos)
	{
		if(pos>=size*8)
		{
			throw std::range_error("DynamicBitset::get size:"+std::to_string(size*8)+" pos:"+std::to_string(pos));
		}
		return bits[pos/8]&1<<pos%8;
	}

	const unsigned char* getAll() const
	{
		return bits;
	}

	Size_t getSize() const
	{
		return size;
	}

	~DynamicBitset()
	{
		delete[] bits;
		#if __DEBUG__DYN__BITSETS
		std::cout<<"destroy DynamicBitset"<<std::endl;
		#endif
	}
};