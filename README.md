# Trade Matching Engine
The following project intends to solve the task described below:

## Description of task
 
Your task is to implement an engine that matches client orders and reports trades.
A trader places an order to buy or sell some quantity at a specific (or better) price. An order that enters the market is called Aggressor. Orders that exist in the market are called resting orders. The aggressor matches against resting orders of the opposite side with a best price first. If there are many resting orders at the best price then resting orders are taken from oldest to newest. Price of a matched trade is a price of a resting order. Aggressor matches against resting orders until all aggressor’s quantity is matched or the requested price no longer matches opposite orders. If there are no opposite orders with overlapping prices in the market then the aggressor rests until execution.
 
Your program should be a console application that reads input from stdin and writes results to stdout.
 
Input is a sequence of requests to buy or sell, one request per line. The request is a series of fields separated by spaces.
 
A request looks like this:
```
<Trader Identifier> <Side> <Quantity> <Price>
```
Where
<Trader Identifier> is an alpha-numeric string
<Side> is a single char: 'B' if this is a buy request, and 'S' if this is a sell request
<Quantity> is an integer size of a request
<Price> is an integer price of request
 
Here is an input example:
````
T1 B 5 30
T2 S 5 70
T3 B 1 40
T4 S 2 60
T5 S 3 70
T6 S 20 80
T7 S 1 50
T2 S 5 70
T1 B 1 50
T1 B 3 60
T7 S 2 50
T8 B 10 90
````
Output is a sequence of resulting trades. One line represents all trades created on one aggressor order execution separated by space.
 
One trade looks like this:
```
<Trader Identifier><Sign><Quantity>@<Price>
```
where
<Trader Identifier> is a trader identifier from the input stream.
<Sign> is "+" for a buy and "-" for a sell.
 
Several trades of one trader with the same side and price, created on one aggressor execution, should be reported as one trade with cumulative size.
 
Here is an output example:
```
T1+1@50 T7-1@50
T1+2@60 T4-2@60
T1+1@60 T7-1@60
T2-6@70 T5-3@70 T7-1@50 T8+1@50 T8+9@70
```
Trades of one line are sorted by trader, sign and price.

## Usage
To run project, use the following commands:
```
make
./bin/TradeMatchingEngine
```
