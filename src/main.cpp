#include "TradeMatchingEngine.h"
#include <string>

int main()
{
	// set debug level to true to see the  buy and sell resting order's table
	TradeMatchingEngine::instance()->setDebugLevel(false);

	TradeMatchingEngine::instance()->start();

	return 0;
}