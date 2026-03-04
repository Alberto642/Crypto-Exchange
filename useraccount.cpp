#include "useraccount.hpp"

  UserAccount:: UserAccount (std::string name):n(name){}

  void UserAccount:: Deposit(std::string asset, int amount)
  {
    Portfolio[asset] += amount;
  }
  bool UserAccount::Withdrawal(std::string asset, int amount)
  {
    bool success = true;
    if (Portfolio[asset]<amount)
    {
        success=false;
    }
    else
    {
        Portfolio[asset]-=amount;
    }
     return success;
  }
  bool UserAccount::AddOrder(Order order)
  {
    bool success = true;
    if (order.side=="Sell")
    {
        if (Portfolio[order.asset]<order.amount)
        {
            success = false;;
        }
        else
        {
            success = true;
            Portfolio[order.asset]-=order.amount;
        }
    }
    else if(order.side=="Buy")
    {
        if (Portfolio["USD"]<(order.amount*order.price))
        {
            success = false;
        }
        else
        {
            success = true;
            Portfolio["USD"]-=order.amount*order.price;
        }
    }
    return success;
  }
  void UserAccount::PerformBuy(Order buy_order, Trade trade)
  {

  }
  void UserAccount::PerformSell(Order sell_order, Trade trade)
  {

  }
  std::map<std::string, int> UserAccount:: GetPortfolio()
  {
    return Portfolio;
  }
  std::vector<Order> UserAccount:: GetOpenOrders()
  {
    return openorders;
  }
  void UserAccount:: PrintOrders(std::ostream &os)
  {
    os<<n<<"'s Open Orders (in chronological order):\n";
    for (Order order:openorders)
    {
        os<<order<<"\n";
    }
    os<<n<<"'s Filled Orders (in chronological order):\n";
    for (Order order:filledorders)
    {
        os<<order<<"\n";
    }
  }
  std::string UserAccount:: GetName()
  {
    return n;
  }
void UserAccount:: adjustPort(std::string asset,int amt)
{
    Portfolio[asset] += amt;
}
void UserAccount:: fillopen(Order order)
{
    openorders.push_back(order);
}
void UserAccount:: fillfilled(Order order)
{
    filledorders.push_back(order);
}
void UserAccount:: removeorder(Order filled)
{
    int ind=500;
    int count{};
    for (Order order:openorders)
    {
        if (filled == order)
        {
            ind = count;
        }
        ++count;
    }
    if (ind<500)
    {
        openorders.erase(openorders.begin()+ind);
    }
}

void UserAccount:: adjustorder(Order order,Order neworder)
{
    int ind = -1;
    int count = 0;
    for (Order &o:openorders)
    {
        if(o==order)
        {
            ind = count;
            break;
        }
        count+=1;
    }
    if (ind!=-1)
    {openorders.at(ind) = neworder;}
}