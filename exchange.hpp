#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "useraccount.hpp"
#include "utility.hpp"

class Exchange {
  
 public:
  std::map <std::string,int> N_L{};
  std::vector<UserAccount> users{};
  std::vector<Order> OpenOrders{};
  std::vector<std::string> Trades{};
  void MakeDeposit(std::string username, std::string asset,
                   int amount);
  void PrintUserPortfolios(std::ostream &os);
  bool MakeWithdrawal(std::string username, std::string asset,
                      int amount);
  bool AddOrder(Order order,bool locked = false);
  void PrintUsersOrders(std::ostream &os);
  void PrintTradeHistory(std::ostream &os);
  void PrintBidAskSpread(std::ostream &os);
  std::pair <Order*,int> FindBuy(std::string,int);
  std::pair <Order*,int> FindSell(std::string,int);
  void filltrades(std::string,int,std::string,std::string,int);
  int findamt(int taker, int maker);
};