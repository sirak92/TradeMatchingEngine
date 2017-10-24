#include <algorithm>
#include "OrdersBook.h"


void OrdersBook::makeOrder(Order *order)
{
	// starts from empty logs for each order
	m_tradeLogs.clear();

	// store the original quantity of item
	int origQnty = order->m_quantity;

	if (order->m_isBuy) {
		handleRequest<OrdersAskTable>(m_asks, order, origQnty);
	}
	else {
		handleRequest<OrdersBidTable>(m_bids, order, origQnty);
	}

	// requested quantity isn't satisfied then store the request as a resting order
	if (origQnty != 0) {
		// update quantity with the remain count
		order->m_quantity = origQnty;
		addOrder(order);
	}
	else {
		// release memory
		delete order;
	}

	// dump trade logs
	dumpTradeLogs();
}

template<typename T>
void OrdersBook::handleRequest(T &table, Order *order, int &origQnty)
{
	int currQnty, performedQnty;
	Order usedOrder;
	
	//get the range of satisfied key prices from the table.
	auto lowIt = table.lower_bound(order->m_price);
	// include in the range the equal element
	if (table.find(order->m_price) != table.end())
		lowIt++;

	// use while loops to have a change to remove some elements
	auto tableIt = table.begin();
	while (tableIt != lowIt) {
		auto ordIt = (tableIt->second).begin();
		// check the list of orders with the same price
		while (ordIt != (tableIt->second).end() && origQnty != 0) {
			currQnty = (*ordIt)->m_quantity;
			performedQnty = std::min(currQnty, origQnty);
			// the current quantity is more than the requested one
			if (currQnty > performedQnty) {
				// update the current order quantity
				(*ordIt)->m_quantity = currQnty - performedQnty;
				usedOrder = *(*ordIt);
			}
			else {
				// stored order before removing
				usedOrder = *(*ordIt);
				// current order's quantity is used, so remove it
				ordIt = (tableIt->second).erase(ordIt);
			}

			// add trade log info
			addTradeInfo(order, usedOrder, performedQnty);
			// decrease the number of aggresor order quantity
			origQnty -= performedQnty;
		}

		// remove the key from table when the list gets empty
		if (tableIt->second.empty())
			tableIt = table.erase(tableIt);
		else
			tableIt++;
	}
}


void OrdersBook::addTradeInfo(Order *origOrder, Order curOrder, int performedQnty)
{
	// store the first log
	curOrder.m_quantity = performedQnty;
	logOrder(curOrder);

	// update the quantity and price of original order and store it
	Order order = *origOrder;
	order.m_quantity = performedQnty;
	order.m_price = curOrder.m_price;
	logOrder(order);
}


void OrdersBook::addOrder(Order *o)
{
	if (o->m_isBuy)
		m_bids[o->m_price].push_back(o);
	else
		m_asks[o->m_price].push_back(o);
}


void OrdersBook::logOrder(Order order)
{
	std::pair<OrdersLog::iterator, OrdersLog::iterator> range = m_tradeLogs.equal_range(order.m_traderId);

	for (auto iter = range.first; iter != range.second; iter++)
		if (iter->second == order) {
			iter->second += order;
			return;
		}
			
	m_tradeLogs.insert(std::pair < std::string, Order>(order.m_traderId, order));
}

void OrdersBook::dumpTradeLogs()
{
	if (m_tradeLogs.empty())
		return;

	std::cout << "\n-----------------------------------------\n";
	for (auto iter = m_tradeLogs.begin(); iter != m_tradeLogs.end(); iter++) {
		std::cout << iter->second;
	}
	std::cout << "\n-----------------------------------------\n";
}


template<class T>
void OrdersBook::dumpHelper(const T &table)
{
	for (auto it = table.begin(); it != table.end(); it++) {
		std::cout << it->first << " => ";
		for (auto order : it->second) {
			std::cout << "( traderId=" << order->m_traderId
				<< ", isBuy=" << order->m_isBuy
				<< ", quantity=" << order->m_quantity
				<< ", price=" << order->m_price << " )";
		}
		std::cout << std::endl;
	}
}


void OrdersBook::dumpAsks()
{
	std::cout << "Asks table dump:\n";
	dumpHelper<OrdersAskTable>(m_asks);
	std::cout << "\n--------------------------------------\n";
}


void OrdersBook::dumpBids()
{
	std::cout << "Bids table dump:\n";
	dumpHelper<OrdersBidTable>(m_bids);
	std::cout << "\n--------------------------------------\n";
}

