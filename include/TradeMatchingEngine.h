#ifndef TRADEMATCHINGENGINE_H
#define TRAFEMATCHINGENGINE_H

#include "OrdersBook.h"

/*
Class implements SINGLETON pattern to have only one instance of the class.
*/

class TradeMatchingEngine
{
public:
	static TradeMatchingEngine* instance();

	/* entry function which run engine */
	void start();

	/* processes given orders */
	void processOrder(Order*);

	/*
	set debug level from the outside
	if used the buy and sell resting orders tables are dumped after each order request
	*/
	void setDebugLevel(bool);

private:
	/*
	Function read the orders from the standard input.
	Each line represent the following structure:

	<Trader Identifier> <Side> <Quantity> <Price>

	Where
	<Trader Identifier> is an alpha-numeric string
	<Side> is a single char: 'B' if this is a buy request, and 'S' if this is a sell request
	<Quantity> is an integer size of a request
	<Price> is an integer price of request
	*/
	Order* getOrder();

	/* used private for SINGLETON pattern implementation */
	TradeMatchingEngine() : m_orderBook(new OrdersBook()) {};
	TradeMatchingEngine(const TradeMatchingEngine&) {};
	~TradeMatchingEngine() { delete m_orderBook; };


	/* Members */
private:
	static TradeMatchingEngine* engine;
	/* stores the orders information */
	OrdersBook* m_orderBook;

	bool m_debug_enabled;
};


#endif // !TRADEMATCHINGENGINE_H
