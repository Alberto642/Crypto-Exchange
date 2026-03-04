#include <iostream>
#include "exchange.hpp"
#include "utility.hpp"
#include <sstream>

int main() {
  Exchange e;
  std::ostringstream oss;
  e.MakeDeposit("Nahum", "BTC", 1000);
  e.MakeDeposit("Dolson", "USD", 555555);
  e.AddOrder({"Nahum", "Sell", "BTC", 5, 100});
  e.PrintUserPortfolios(std::cout);
  oss.str("");
  e.PrintUserPortfolios(oss);
  e.PrintUsersOrders(std::cout);
  oss.str("");
  e.PrintUsersOrders(oss);
  std::cout << std::endl << std::endl;
  e.AddOrder({"Dolson", "Buy", "BTC", 70, 150});
  e.PrintUserPortfolios(std::cout);
  oss.str("");
  e.PrintUserPortfolios(oss);
  e.PrintUsersOrders(std::cout);
  oss.str("");
  e.PrintUsersOrders(oss);
  std::cout << std::endl << std::endl;
  e.AddOrder({"Nahum", "Sell", "BTC", 30, 125});
  e.PrintUserPortfolios(std::cout);
  oss.str("");
  e.PrintUserPortfolios(oss);
  e.PrintUsersOrders(std::cout);
  oss.str("");
  e.PrintUsersOrders(oss);
  std::cout << std::endl << std::endl;
  e.AddOrder({"Nahum", "Sell", "BTC", 40, 120});
  e.PrintTradeHistory(std::cout);
  oss.str("");
  e.PrintTradeHistory(oss);

}