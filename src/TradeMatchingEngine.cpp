#include <iostream>

#include "TradeMatchingEngine.h"


// TODO to be removed
void dumpOrder(Order* order)
{
	std::cout << "\nOrder:"
		<< "\nTradeId = " << order->m_traderId
		<< "\nisBuy = " << order->m_isBuy
		<< "\nQuantity = " << order->m_quantity
		<< "\nPrice = " << order->m_price << std::endl;
}

// initialize static member
TradeMatchingEngine* TradeMatchingEngine::engine = 0;

TradeMatchingEngine* TradeMatchingEngine::instance()
{
	if (!engine)
		engine = new TradeMatchingEngine();

	return engine;
}

void TradeMatchingEngine::start()
{
	std::cout << "Trade Matching Engine started....\n";

	Order *order = getOrder();

	while (order) {
		processOrder(order);

		// get next order
		order = getOrder();
	}
}


Order* TradeMatchingEngine::getOrder()
{
	Order *ord = new Order();

	std::cout << "\nInput request <Trader Identifier> <Side> <Quantity> <Price>: \n";
	std::cin >> *ord;
	
	return ord;
}


void TradeMatchingEngine::setDebugLevel(bool enable)
{
	m_debug_enabled = enable;
}

void TradeMatchingEngine::processOrder(Order* o)
{
	m_orderBook->makeOrder(o);

	// for testing purposes only
	if (m_debug_enabled) {
		m_orderBook->dumpAsks();
		m_orderBook->dumpBids();
	}

	
}