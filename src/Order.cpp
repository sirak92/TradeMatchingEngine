#include "Order.h"

bool Order::operator == (const Order &o)
{
	if (this->m_traderId == o.m_traderId &&
		this->m_isBuy == o.m_isBuy &&
		this->m_price == o.m_price)
		return true;
	else
		return false;
}

bool Order::operator != (const Order &o)
{
	return !(*this == o);
}

Order Order::operator + (const Order &o)
{
	Order sum(*this);
	sum += o;

	return sum;
}
Order& Order::operator += (const Order &o)
{
	this->m_quantity += o.m_quantity;

	return *this;
}


std::ostream& operator << (std::ostream &out, const Order &order)
{
	out << order.m_traderId << (order.m_isBuy ? '+' : '-') << order.m_quantity << "@" << order.m_price << " ";
	
	return out;
}

std::istream& operator >> (std::istream &in, Order &order)
{
	char side;
	in >> order.m_traderId >> side >> order.m_quantity >> order.m_price;
	if (toupper(side) == 'B')
		order.m_isBuy = true;

	return in;
}
