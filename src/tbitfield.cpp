// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{

    BitLen = len;
    if (BitLen > 0) {

	    MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;

	    pMem = new TELEM[MemLen];
	    if (pMem != NULL)
			for (int i = 0; i < MemLen; ++i) {
				pMem[i] = 0;
			}

				
}
	else
		throw std::logic_error("bad Length");
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; ++i) {
			pMem[i] = bf.pMem[i];
		}
}



TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0)
	{
		return n / (sizeof(TELEM) * 8);
	}
	else 
		throw 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n - GetMemIndex(n) * sizeof(TELEM) * 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	else
		throw std::logic_error("bad position");
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
	else
		throw std::logic_error("bad position");
}


int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
	{
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	}
	else
		throw std::logic_error("bad position");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (MemLen != bf.MemLen)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
	}
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		int f = 1;
		for (int i = 0; i<MemLen - 1; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				f = 0;
				break;
			}
		}
		for (int i = (MemLen - 1) * 8 * sizeof(TELEM); i<BitLen; i++)
		{
			if (GetBit(i) != bf.GetBit(i))
			{
				f = 0;
				break;
			}
		}
		return f;
	}
	else
	{
		return 0;
	}
}


int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		int res = 0;
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				res = 1;
				break;
			}
		}
		return res;
	}
	else
	{
		return 1;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i;
	int	len = BitLen;
	if (bf.BitLen>len)
	{ 
		len = bf.BitLen;
	}
	TBitField a(len);
	for (i = 0; i < MemLen; i++)
	{
		a.pMem[i] = pMem[i];
	}
 
	for (i = 0; i < bf.MemLen; i++)
	{
		a.pMem[i] |= bf.pMem[i];
	}
	return a;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i;
	int	len = BitLen;
	if (bf.BitLen > len)
	{
		len = bf.BitLen;
	}
	TBitField a(len);
	for (i = 0; i < MemLen; i++)
	{
		a.pMem[i] = pMem[i];
	}
	for (i = 0; i < bf.MemLen; i++)
	{
		a.pMem[i] &= bf.pMem[i];
	}
	return a;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField a(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i))
		{
			a.ClrBit(i);
		}
		else
			a.SetBit(i);
	}
	return a;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	
		int i = 0;
		char ch;
		do
			istr >> ch;
		while (ch != ' ');
		while (1)
		{
			istr >> ch;
			if (ch == '0')
				bf.ClrBit(i++);
			else if (ch == '1')
				bf.SetBit(i++);
			else
				break;
		}
		return istr;
	
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	/*int len = bf.GetLength();
	int i = 0;
	char ch = ' ';
	ostr << "{ ";
	for (; i < len; ++i)
	{
		if (bf.GetBit(i))
		{
			ostr << ch << i << ' ';
		}
		}
	ostr << "} ";
	return ostr;*/// вывод чисел как в tset
	int len = bf.GetLength();
	for (int i = 0; i < len; ++i)
	{
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	}
	return ostr;
}
