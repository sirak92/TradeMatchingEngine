#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>



/*
Class represents sigle order request.
*/
struct Order {
	std::string m_traderId;
	bool m_isBuy;
	size_t	m_quantity;
	size_t	m_price;

	// init with default values
	Order() :m_traderId(""), m_isBuy(false), m_quantity(0), m_price(0)
	{}
	/*Order(const std::string tId, const int price, const int qnty, bool buy):
		m_traderId(tId), m_price(price), m_quantity(qnty), m_isBuy(buy)
	{}*/

	/* Overloaded operators*/
	/*
	Orders are equal when the trader identifier, trade type and price is equal.
	*/
	bool operator == (const Order&);
	bool operator != (const Order&);
	/*
	Order sum is calulated based on order's qyantity field.
	*/
	Order operator + (const Order&);
	Order& operator += (const Order&);

	/*
	Function print the order info with the following format:
	<Trader Identifier><Sign><Quantity>@<Price>
 
	where
	<Trader Identifier> is a trader identifier from the input stream.
	<Sign> is "+" for a buy and "-" for a sell.
	*/
	friend std::ostream& operator << (std::ostream &out, const Order &order);
	friend std::istream& operator >> (std::istream &in, Order &order);
};

#endif // !ORDER_H


