// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
	TBitField a(this->BitField);
	return a;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.GetMaxPower();
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet a(BitField | s.BitField);
	return a;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < MaxPower)
	{
		TSet a(BitField);
		a.InsElem(Elem);
		return a;
	}
	else
		throw std::logic_error("bad large");
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem < MaxPower)
	{
		TSet a(BitField);
		a.DelElem(Elem);
		return a;
	}
	else 
		throw std::logic_error("bad large");
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet a(BitField & s.BitField);
	return a;
}

TSet TSet::operator~(void) // дополнение
{
	TSet a(~BitField);
	return a;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int tmp;
	char ch;
	do {
		istr >> ch;
	} while (ch != ' {');
	do {
		istr >> tmp;
		s.InsElem(tmp);
		do {
			istr >> ch;
		} while (ch != ',' && ch != '}');
	} while (ch != '}');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i, n; char ch = ' ';
	n = s.GetMaxPower();
	ostr << "{ ";
	for (i = 0; i < n; i++)
	{
		if (s.IsMember(i))

		{
			ostr << ch << i << ' ';
		}
	}
	ostr << "}";
	return ostr;
}
