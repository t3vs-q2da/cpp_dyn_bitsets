#pragma once
#if __LOG__DYN__BITSETS
#include <iostream>
#endif

template<typename size_byte_t = size_t,typename size_bit_t = unsigned int>
requires std::is_integral<size_byte_t>::value&&std::is_integral<size_bit_t>::value
class DynamicBitset{
private:
	unsigned char* bits;
	size_byte_t size;
	#if __DEBUG__DYN__BITSETS>=2
	unsigned int uuid = 0;
	static unsigned int uuid_n;
	#endif

	inline void setBit(size_bit_t pos, bool a)
	{
		if(a)
		{
			bits[pos/8]|=1<<pos%8;
			return;
		}
		bits[pos/8]&=~(1<<pos%8);
	}

public:
	DynamicBitset(size_byte_t size = 4):bits{new unsigned char[size]{}},size{size}
	#if __DEBUG__DYN__BITSETS>=2
		,uuid{uuid_n++}
	#endif
	{
		#if __LOG__DYN__BITSETS
		std::cout<<"created DynamicBitset with\n  size:"<<size
		#if __DEBUG__DYN__BITSETS>=2
		<<"\n  uuid:"<<uuid
		#endif
		<<std::endl;
		#endif
	}

	void resize(size_byte_t n_size)
	{
		if(!n_size)
		{
			throw std::underflow_error("resize with 0");
		}
		unsigned char* n_bits=new unsigned char[n_size]{};
		#if __LOG__DYN__BITSETS>=2
		std::cout<<"resize DynamicBitset from:"<<size<<" to:"<<n_size<<std::endl;
		#endif
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

	void insert(size_bit_t pos,bool a)
	{
		if(pos>=size*8)
		{
			resize(pos/8+1);
		}
		setBit(pos,a);
		#if __LOG__DYN__BITSETS>=3
		std::cout<<"insert DynamicBitset pos:"<<pos<<" to:"<<a<<std::endl;
		#endif
	}

	//std::range_error
	void set(size_bit_t pos,bool a)
	{
		if(pos>=size*8)
		{
			throw std::range_error("DynamicBitset::set size:"+std::to_string(size*8)+" pos:"+std::to_string(pos));
		}
		setBit(pos,a);
		#if __LOG__DYN__BITSETS>=3
		std::cout<<"set DynamicBitset pos:"<<pos<<" to:"<<a<<std::endl;
		#endif
	}
	//std::range_error
	bool get(size_bit_t pos)
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

	size_byte_t getSize() const
	{
		return size;
	}

	~DynamicBitset()
	{
		delete[] bits;
		#if __LOG__DYN__BITSETS
		std::cout<<"destroy DynamicBitset"
		#if __DEBUG__DYN__BITSETS>=2
		<<"with:\n  uuid:"<<uuid
		#endif
		<<std::endl;
		#endif
	}
	#if __DEBUG__DYN__BITSETS
	void print()
	{
		unsigned char c;
		for(int i = 0;i<size;++i)
		{
			c=bits[i];
			for(int i = 128;i!=0;i>>=1)
			{
				std::cout<<bool(i&c);
			}
			std::cout<<' ';
		}
		std::cout<<std::endl;
	}
	#endif
};

#if __DEBUG__DYN__BITSETS>=2
template<typename size_byte_t,typename size_bit_t>
requires std::is_integral<size_byte_t>::value&&std::is_integral<size_bit_t>::value
unsigned int DynamicBitset<size_byte_t,size_bit_t>::uuid_n=0;
#endif