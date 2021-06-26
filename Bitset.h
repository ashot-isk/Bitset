#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <size_t sizeOfStr>
class Bitset
{
private:
	int bitscount;
	long forBits = 0;
	vector<long> table;
	int tableIndex;

public:
	Bitset<sizeOfStr>();
	Bitset<sizeOfStr>(int k);
	Bitset<sizeOfStr> &set(int size, bool tf = true);
	Bitset<sizeOfStr> &set();
	Bitset<sizeOfStr> &reset();
	Bitset<sizeOfStr>(Bitset<sizeOfStr> &&srq);
	Bitset<sizeOfStr>(Bitset<sizeOfStr> &srq);
	Bitset<sizeOfStr> &operator=(const Bitset<sizeOfStr> &lhs);
	/*Bitset<sizeOfStr> operator<<(std::size_t pos) const;
	Bitset<sizeOfStr> operator>>(std::size_t pos) const;
	Bitset<sizeOfStr> operator<<=(std::size_t pos);
	Bitset<sizeOfStr> operator>>=(std::size_t pos);*/
	friend Bitset<sizeOfStr> operator&(const Bitset<sizeOfStr> &lhs, const Bitset<sizeOfStr> &rhs)
	{

		Bitset<sizeOfStr> tmp;
		if (sizeOfStr <= 32)
		{
			tmp.table[0] = lhs.table[0] & rhs.table[0];
			return tmp;
		}
		else
		{

			for (int j = lhs.tableIndex; j >= 0; --j)
			{
				tmp.table[j] = rhs.table[j] & lhs.table[j];
			}
			return tmp;
		}
		return tmp;
	}
	friend Bitset<sizeOfStr> operator|(const Bitset<sizeOfStr> &lhs, const Bitset<sizeOfStr> &rhs)
	{

		Bitset<sizeOfStr> tmp;
		if (sizeOfStr <= 32)
		{
			tmp.table[0] = lhs.table[0] | rhs.table[0];
			return tmp;
		}
		else
		{

			for (int j = lhs.tableIndex; j >= 0; --j)
			{
				tmp.table[j] = rhs.table[j] | lhs.table[j];
			}
			return tmp;
		}
		return tmp;
	}
	friend Bitset<sizeOfStr> operator^(const Bitset<sizeOfStr> &lhs, const Bitset<sizeOfStr> &rhs)
	{

		Bitset<sizeOfStr> tmp;
		if (sizeOfStr <= 32)
		{
			tmp.table[0] = lhs.table[0] ^ rhs.table[0];
			return tmp;
		}
		else
		{

			for (int j = lhs.tableIndex; j >= 0; --j)
			{
				tmp.table[j] = rhs.table[j] ^ lhs.table[j];
			}
			return tmp;
		}
		return tmp;
	}

	Bitset<sizeOfStr> operator~() const
	{
		Bitset<sizeOfStr> tmp;
		if (sizeOfStr <= 32)
		{
			tmp.table[0]= ~this->table[0];
			return tmp;
		}
		else
		{

			for (int j = this->tableIndex; j >= 0; --j)
			{
				tmp.table[j] = ~this->table[j];
			}
			return tmp;
		}

		return tmp;
	}

	friend ostream &operator<<(ostream &ostr, const Bitset<sizeOfStr> &srq)
	{

		int k = sizeOfStr;
		if (k <= 32)
		{
			for (int i = k - 1; i >= 0; --i)
			{
				if (srq.table[0] & (1 << i))
				{
					ostr << true;
				}
				else
				{
					ostr << false;
				}
			}
		}
		else
		{
			int shiftcount = k % 32;
			if (shiftcount == 0)
			{
				for (int j = srq.tableIndex; j >= 0; --j)
				{
					for (int i = 31; i >= 0; --i)
					{
						if (srq.table[j] & (1 << i))
						{
							ostr << true;
						}
						else
						{
							ostr << false;
						}
					}
				}
			}
			else
			{
				for (int i = shiftcount - 1; i >= 0; --i)
				{
					if (srq.table[srq.tableIndex] & (1 << i))
					{
						ostr << true;
					}
					else
					{
						ostr << false;
					}
				}

				for (int j = srq.tableIndex - 1; j >= 0; --j)
				{
					for (int i = 31; i >= 0; --i)
					{
						if (srq.table[j] & (1 << i))
						{
							ostr << true;
						}
						else
						{
							ostr << false;
						}
					}
				}
			}
		}

		return ostr;
	}
};
template <size_t sizeOfStr>
Bitset<sizeOfStr>::Bitset(int k) : bitscount{sizeOfStr}, forBits{k}
{
	int xz = 0;
	table.push_back(forBits);
	size_t c = sizeOfStr;
	while (c > 32)
	{
		++xz;
		c -= 32;
		table.push_back(0);
	}
	tableIndex = xz;
}
template <size_t sizeOfStr>
Bitset<sizeOfStr>::Bitset() : bitscount{sizeOfStr}
{
	int xz = 0;
	table.push_back(0);
	size_t k = sizeOfStr;
	while (k > 32)
	{
		++xz;
		k -= 32;
		table.push_back(0);
	}
	tableIndex = xz;
}

template <size_t sizeOfStr>
Bitset<sizeOfStr> &Bitset<sizeOfStr>::set(int size, bool tf)
{
	if (size <= 32)
	{

		if (tf)
		{
			this->table[0] |= (1 << size - 1);
			return *this;
		}
		else
		{
			if (this->table[0] & (1 << size - 1))
				this->table[0] ^= (1 << size - 1);

			return *this;
		}
	}
	else
	{
		int shiftSize = size % 32;
		int index = size / 32;
		if (shiftSize == 0)
		{
			if (tf)
			{
				this->table[index] |= (1 << 31);
				return *this;
			}
			else
			{
				if (this->table[index] & (1 << 31))
					this->table[index] ^= (1 << 31);

				return *this;
			}
		}
		else
		{
			if (tf)
			{
				this->table[index] |= (1 << shiftSize - 1);
				return *this;
			}
			else
			{
				if (this->table[index] & (1 << shiftSize - 1))
					this->table[index] ^= (1 << shiftSize - 1);

				return *this;
			}
		}
	}

	return *this;
}

template <size_t sizeOfStr>
Bitset<sizeOfStr> &Bitset<sizeOfStr>::set()
{
	for (int i = tableIndex; i >= 0; --i)
	{
		this->table[i] = 0;
		this->table[i] = ~this->table[i];
	}
	return *this;
}

template <size_t sizeOfStr>
Bitset<sizeOfStr> &Bitset<sizeOfStr>::reset()
{
	for (int i = tableIndex; i >= 0; --i)
	{
		this->table[i] = 0;
	}
	return *this;
}

template <size_t sizeOfStr>
Bitset<sizeOfStr>::Bitset(Bitset<sizeOfStr> &src)
{
	this->bitscount = src.bitscount;
	this->forBits = src.forBits;
	this->tableIndex = src.tableIndex;
	for (int i = 0; i <= this->tableIndex; ++i)
	{
		this->table.push_back(src.table[i]);
	}
}

template <size_t sizeOfStr>
Bitset<sizeOfStr>::Bitset(Bitset<sizeOfStr> &&src)
{
	this->bitscount = src.bitscount;
	this->forBits = src.forBits;
	this->tableIndex = src.tableIndex;
	this->table = src.table;
}

template <size_t sizeOfStr>
Bitset<sizeOfStr> &Bitset<sizeOfStr>::operator=(const Bitset<sizeOfStr> &rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	this->bitscount = rhs.bitscount;
	this->forBits = rhs.forBits;
	this->tableIndex = rhs.tableIndex;
	for (int i = 0; i <= this->tableIndex; ++i)
	{
		this->table[i] = rhs.table[i];
	}

	return *this;
}
