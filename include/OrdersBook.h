#ifndef ORDERSBOOK_H
#define ORDERSBOOK_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <functional>
#include <set>

#include "Order.h"

/*
Class records all the comming orders and giva a output about the trade information.
*/

class OrdersBook
{
	typedef std::map<int, std::list<Order*>> OrdersAskTable;
	typedef std::map<int, std::list<Order*>, std::greater<int>> OrdersBidTable;
	typedef std::multimap<std::string, Order> OrdersLog;
public:
	/* entry point of the class, which treat the given order */
	void makeOrder(Order*);

	/* Helper functions */
private:
	/* generic function used for both types of orders */
	template<typename T>
	void handleRequest(T&, Order*, int&);

	/* function updates the trade info for the given order items*/
	void addTradeInfo(Order *origOrder, Order curOrder, int performed);

	/* add order to one of the container depends on order type */
	void addOrder(Order*);

	/* add order to m_tradeLogs */
	void logOrder(Order);

	/* Functions intended only for testing purposes */
public:
	void dumpBids();
	void dumpAsks();
private:
	template<typename T>
	void dumpHelper(const T&);
	void dumpTradeLogs();


	/* Members */
private:
	/* 
	Stores the resting bids and asks with the following structure:
	price->list of orders with the same price
	*/
	OrdersAskTable m_asks;
	/* store in decreasing order */
	OrdersBidTable m_bids;
	/* stores the logs about the one trade */
	OrdersLog m_tradeLogs;
};


#endif // ORDERSBOOK_H