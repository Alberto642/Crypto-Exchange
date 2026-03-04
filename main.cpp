#include <iostream>
#include "exchange.hpp"
#include "utility.hpp"
#include <sstream>

int main() {
  Exchange e;
  std::ostringstream oss;
  e.MakeDeposit("Nahum", "BTC", 1000);
  e.MakeDeposit("Dolson", "USD", 555555);
  std::cout<<(e.AddOrder({"Nahum", "Sell", "BTC", 5, 100}));
  e.PrintUserPortfolios(std::cout);
  oss.str("");
  e.PrintUserPortfolios(oss);
  std::cout<<(oss.str() == "User Portfolios (in alphabetical order):\nDolson's Portfolio: 555555 USD, \nNahum's Portfolio: 995 BTC, \n");
  e.PrintUsersOrders(std::cout);
  oss.str("");
  e.PrintUsersOrders(oss);
  std::cout<<(oss.str() == "Users Orders (in alphabetical order):\nDolson's Open Orders (in chronological order):\nDolson's Filled Orders (in chronological order):\nNahum's Open Orders (in chronological order):\nSell 5 BTC at 100 USD by Nahum\nNahum's Filled Orders (in chronological order):\n");
  std::cout << std::endl << std::endl;
  std::cout<<(e.AddOrder({"Dolson", "Buy", "BTC", 70, 150}));
  e.PrintUserPortfolios(std::cout);
  oss.str("");
  e.PrintUserPortfolios(oss);
  std::cout<<(oss.str() == "User Portfolios (in alphabetical order):\nDolson's Portfolio: 5 BTC, 545055 USD, \nNahum's Portfolio: 995 BTC, 750 USD, \n");
  e.PrintUsersOrders(std::cout);
  oss.str("");
  e.PrintUsersOrders(oss);
  std::cout<<(oss.str() == "Users Orders (in alphabetical order):\nDolson's Open Orders (in chronological order):\nBuy 65 BTC at 150 USD by Dolson\nDolson's Filled Orders (in chronological order):\nBuy 5 BTC at 150 USD by Dolson\nNahum's Open Orders (in chronological order):\nNahum's Filled Orders (in chronological order):\nSell 5 BTC at 150 USD by Nahum\n");
  std::cout << std::endl << std::endl;
  std::cout<<(e.AddOrder({"Nahum", "Sell", "BTC", 30, 125}));
  e.PrintUserPortfolios(std::cout);
  oss.str("");
  e.PrintUserPortfolios(oss);
  std::cout<<(oss.str() == "User Portfolios (in alphabetical order):\nDolson's Portfolio: 35 BTC, 545055 USD, \nNahum's Portfolio: 965 BTC, 4500 USD, \n");
  e.PrintUsersOrders(std::cout);
  oss.str("");
  e.PrintUsersOrders(oss);
  std::cout<<(oss.str() == "Users Orders (in alphabetical order):\nDolson's Open Orders (in chronological order):\nBuy 35 BTC at 150 USD by Dolson\nDolson's Filled Orders (in chronological order):\nBuy 5 BTC at 150 USD by Dolson\nBuy 30 BTC at 125 USD by Dolson\nNahum's Open Orders (in chronological order):\nNahum's Filled Orders (in chronological order):\nSell 5 BTC at 150 USD by Nahum\nSell 30 BTC at 125 USD by Nahum\n");
  std::cout << std::endl << std::endl;
  std::cout<<(e.AddOrder({"Nahum", "Sell", "BTC", 40, 120}));
  e.PrintTradeHistory(std::cout);
  oss.str("");
  e.PrintTradeHistory(oss);
  std::cout<<(oss.str() == "Trade History (in chronological order):\nDolson Bought 5 of BTC From Nahum for 150 USD\nDolson Bought 30 of BTC From Nahum for 125 USD\nDolson Bought 35 of BTC From Nahum for 120 USD\n");




  /*Exchange msu_base;
  msu_base.MakeDeposit("Nahum", "USD", 1000);
  msu_base.MakeDeposit("Nahum", "ETH", 400);
  msu_base.MakeDeposit("Dolson", "BTC", 100);
  msu_base.MakeDeposit("Dolson", "USD", 7000);
  msu_base.MakeDeposit("Enbody", "USD", 7000);
  msu_base.MakeDeposit("Ofria", "BCH", 9);
  msu_base.MakeWithdrawal("Dolson", "BTC", 100);
  msu_base.PrintUserPortfolios(std::cout);
  std::cout << std::endl;
  Order o_n{"Nahum", "Buy", "BTC", 2, 22};
  Order o_d{"Dolson", "Sell", "BTC", 3, 17};
  std::cout << "Before 1st add order" << std::endl;

  msu_base.AddOrder(o_n);
  std::cout << "After 1st add order" << std::endl;
  msu_base.PrintUsersOrders(std::cout);

  std::cout << std::endl;

  std::cout << "Before 2nd add order" << std::endl;

  msu_base.AddOrder(o_d);

  std::cout << "After 2nd add order" << std::endl;

  msu_base.PrintTradeHistory(std::cout);
  std::cout << std::endl;
  msu_base.PrintUserPortfolios(std::cout);
  std::cout << std::endl;
  msu_base.PrintUsersOrders(std::cout);
  std::cout << std::endl;
  msu_base.AddOrder({"Dolson", "Buy", "ETH", 10, 200});
  msu_base.AddOrder({"Enbody", "Buy", "ETH", 15, 300});
  msu_base.AddOrder({"Nahum", "Sell", "ETH", 20, 100});

  msu_base.PrintTradeHistory(std::cout);
  msu_base.PrintUsersOrders(std::cout);
  msu_base.AddOrder({"Nahum", "Sell", "ETH", 20, 1000});
  msu_base.AddOrder({"Dolson", "Sell", "ETH", 2, 250});
  msu_base.AddOrder({"Enbody", "Buy", "BTC", 1, 10});
  msu_base.PrintTradeHistory(std::cout);
  msu_base.PrintUserPortfolios(std::cout);
  std::cout << std::endl << std::endl;
  msu_base.PrintUsersOrders(std::cout);
  msu_base.AddOrder({"Enbody", "Buy", "LTC", 1, 10});
  msu_base.AddOrder({"Ofria", "Sell", "BCH", 2, 55});
  msu_base.PrintBidAskSpread(std::cout);

  return 0; */
}