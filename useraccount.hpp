#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utility.hpp"

class UserAccount {

// WRITE YOUR CODE HERE
  // Suggestions:
 private:
  std::string n;

 public:
  std::map<std::string,int> Portfolio{};
  std::vector<Order> openorders{};
  std::vector<Order> filledorders{};
  UserAccount(std::string name);
  void Deposit(std::string asset, int amount);
  bool Withdrawal(std::string assert, int amount);
  bool AddOrder(Order order);
  void PerformBuy(Order buy_order, Trade trade);
  void PerformSell(Order sell_order, Trade trade);
  std::map<std::string, int> GetPortfolio();
  std::vector<Order> GetOpenOrders();
  void PrintOrders(std::ostream &os);
  std::string GetName();
  void adjustPort(std::string,int);
  void fillopen(Order order);
  void fillfilled(Order order);
  void removeorder(Order order);
  void adjustorder(Order order,Order neworder);
};