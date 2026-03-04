#include "exchange.hpp"
// WRITE YOUR CODE HERE
void Exchange:: MakeDeposit(std::string username, std::string asset,
    int amount)
    {
        if (N_L.find(username)==N_L.end())
        {
            UserAccount user(username);
            users.push_back(user);
             N_L[username] = users.size()-1;
        }
        users.at(N_L[username]).Deposit(asset,amount);
    }
  void Exchange:: PrintUserPortfolios(std::ostream &os)
  {
    std::vector<std::string> allusers{};
    for(std::pair p : N_L)
    {
        allusers.push_back(p.first);
    }
    std::sort(allusers.begin(),allusers.end());
    os<<"User Portfolios (in alphabetical order):";
    os<<"\n";
    for(std::string name : allusers)
    {
        os<<name<<"'s Portfolio: ";
        std::map<std::string,int> Portfolio = users.at(N_L[name]).GetPortfolio();
        for (std::pair pair: Portfolio)
        {
            if (pair.second==0)
            {
                continue;
            }
            os<<pair.second<<" "<<pair.first<<", ";
        }
        os<<"\n";
    }
    

  }
  bool Exchange:: MakeWithdrawal(std::string username, std::string asset,
    int amount)
    {
        if (N_L.find(username)==N_L.end())
        {
            return false;
        }
        return users.at(N_L[username]).Withdrawal(asset,amount);

    }
  bool Exchange:: AddOrder(Order order,bool locked)
  {
    std::string username = order.username;
    UserAccount* taker = &users.at(N_L[username]);
    bool placed = true;
    if (!locked)
    {placed = users.at(N_L[username]).AddOrder(order);}
    int size = order.amount;
    int price = order.price;
    std::string side = order.side;
    if (!placed)
    {
        return false;
    }

    if (side == "Sell")
    {
        std::pair <Order*,int> pair = FindBuy(order.asset,price);
        if (pair.first != nullptr)
        {
            UserAccount* maker = &users.at(N_L[pair.first->username]);
            int newsize = size - pair.first->amount;
            int amount = findamt(order.amount,pair.first->amount);
            filltrades(pair.first->username,amount,order.asset,username,price);
            if (newsize==0)
            {
                //both filled code later
                taker->fillfilled(order);
                maker->removeorder(*pair.first);
                maker->fillfilled(*pair.first);
                //
                taker->adjustPort("USD",size*price);
                maker->adjustPort(order.asset,size);
                OpenOrders.erase(OpenOrders.begin()+pair.second);
            }
            else if(newsize<0)
            {
                Order new_order{pair.first->username,"Buy", order.asset,pair.first->amount-size, pair.first->price};
                Order Partial{pair.first->username,"Buy", order.asset,pair.first->amount-(newsize*(-1)), price};
                //taker filled maker new order
                taker->fillfilled(order);
                maker->adjustorder(*pair.first,new_order);
                maker->fillfilled(Partial);
                //
                taker->adjustPort("USD",size*price);
                maker->adjustPort(order.asset,size);
                OpenOrders.at(pair.second) =new_order;
            }
            else if(newsize>0)
            {
                Order new_order{order.username,"Sell", order.asset,newsize, price};
                Order Partial{order.username,"Sell", order.asset,pair.first->amount, price};
                //taker new order maker filled
                maker->removeorder(*pair.first);
                pair.first->price = price;
                maker->fillfilled(*pair.first);
                taker->fillfilled(Partial);
                //
                taker->adjustPort("USD",pair.first->amount*price);
                maker->adjustPort(order.asset,pair.first->amount);
                OpenOrders.erase(OpenOrders.begin()+pair.second);
                AddOrder(new_order,true);
            }
        }
        else{
            OpenOrders.push_back(order);
            taker->fillopen(order);
        }
    }

    else if(side == "Buy")
    {
        std::pair <Order*,int> pair = FindSell(order.asset,price);
        if (pair.first != nullptr)
        {
            UserAccount* maker = &users.at(N_L[pair.first->username]);
            int newsize = size - pair.first->amount;
            int amount = findamt(order.amount,pair.first->amount);
            filltrades(username,amount,order.asset,pair.first->username,price);
            if (newsize==0)
            {
                //both filled code later
                taker->fillfilled(order);
                maker->removeorder(*pair.first);
                maker->fillfilled(*pair.first);
                //
                taker->adjustPort(order.asset,size);
                maker->adjustPort("USD",size*price);
                OpenOrders.erase(OpenOrders.begin()+pair.second);
            }
            else if(newsize<0)
            {
                Order Partial{pair.first->username,"Sell", order.asset,pair.first->amount-(newsize*(-1)), price};
                Order new_order{pair.first->username,"Sell", order.asset,(newsize*(-1)), pair.first->price};
                //taker filled maker adjust order
                taker->fillfilled(order);
                maker->adjustorder(*pair.first,new_order);
                maker->fillfilled(Partial);
                //
                taker->adjustPort(order.asset,size);
                maker->adjustPort("USD",size*price);
                OpenOrders.at(pair.second) = new_order;
            }
            else if(newsize>0)
            {
                Order new_order{order.username,"Buy", order.asset,newsize, price};
                Order Partial{order.username,"Buy", order.asset,pair.first->amount, price};
                //taker new order maker filled
                maker->removeorder(*pair.first);
                pair.first->price = price;
                maker->fillfilled(*pair.first);
                taker->fillfilled(Partial);
                //
                taker->adjustPort(order.asset,pair.first->amount);
                maker->adjustPort("USD",pair.first->amount*price);
                OpenOrders.erase(OpenOrders.begin()+pair.second);
                AddOrder(new_order,true);
            }
        }
        else{
            OpenOrders.push_back(order);
            taker->fillopen(order);
        }
    }
    return true;
  }


  std::pair <Order*,int> Exchange:: FindSell(std::string currency,int p)
  {
    int price = 1000000;
    Order*  temp = nullptr;
    int ind = 0;
    int count = 0;
    for(Order &order:OpenOrders)
    {
        if(order.asset == currency && order.side=="Sell" && p>=order.price && order.price<price)
        {
            price = order.price;
            temp = &order; 
            ind = count;
        }
        ++count;
    }
    return {temp,ind};
  }

  std::pair <Order*,int> Exchange:: FindBuy(std::string currency,int p)
  {
    int price = 0;
    Order*  temp = nullptr;
    int ind = 0;
    int count = 0;
    for(Order &order:OpenOrders)
    {
        if(order.asset == currency && order.side=="Buy" && p<=order.price && order.price>price)
        {
            price = order.price;
            temp = &order; 
            ind = count;
        }
        ++count;
    }
    return {temp,ind};
  }

  void Exchange:: PrintUsersOrders(std::ostream &os)
  {
    std::vector<std::string> allusers{};
    for(std::pair p : N_L)
    {
        allusers.push_back(p.first);
    }
    std::sort(allusers.begin(),allusers.end());
    os<<"Users Orders (in alphabetical order):\n";
    for (std::string name:allusers)
    {
        users.at(N_L[name]).PrintOrders(os);
    }

  }
  void Exchange:: filltrades(std::string buyer,int amt,std::string asset,std::string seller,int price)
    {
        std::string amt1 = std::to_string(amt);
        std::string price1 = std::to_string(price);
        std::string line{};
        line+=buyer+" Bought "; 
        line+= amt1;
        line += " of "+asset+" From "+seller+" for ";
        line += price1;
        line += " USD";
        Trades.push_back(line);

        
    }
    int Exchange:: findamt(int taker,int maker)
    {
        int amt{};
        if (taker>maker)
        {
            amt = maker;
        }
        else
        {
            amt = taker;
        }
        return amt;
    }
  void Exchange:: PrintTradeHistory(std::ostream &os)
  {
    os<<"Trade History (in chronological order):\n";
    for (std::string line:Trades)
    {
        os<<line<<"\n";
    }

  }
  void Exchange:: PrintBidAskSpread(std::ostream &os)
  {
    std::vector<std::string>assets{};
    std::map <std::string,std::vector<int>> map;// asset->lowest buy highest sell
    for (Order order:OpenOrders)
    {
        auto find = std::find(assets.begin(),assets.end(),order.asset);
        if(find == assets.end())
        {
            assets.push_back(order.asset);
        }
    }
    std::sort(assets.begin(),assets.end());
    for (std::string asset:assets)
    {
        int buy = 0;
        int sell = 9999999;
        for (Order order:OpenOrders)
        {
            if (order.asset == asset)
            {
                if(order.side == "Buy"&&order.price>buy)
                {
                    buy = order.price;
                }
                else if(order.side == "Sell"&&order.price<sell)
                {
                    sell = order.price;
                }
            }
        }
        map[asset] = {buy,sell};
    }
    //Actual printing
    os<<"Asset Bid Ask Spread (in alphabetical order):\n";
    for(std::pair pair:map)
    {
        std::string name = pair.first;
        int buy = pair.second.at(0);
        int sell = pair.second.at(1);
        bool check = false;
        bool check2 = false;
        if (buy==0)
        {
            check = true;
        }
        if(sell==9999999)
        {
            check2 = true;
        }
        if(check&&check2)
        {
            std::string buy1 = "NA";
            os<<name<<": Highest Open Buy = "<<buy1<<" USD and Lowest Open Sell = "<<buy1<<" USD\n";
        }
        else if(check&&!check2)
        {
            std::string buy1 = "NA";
            os<<name<<": Highest Open Buy = "<<buy1<<" USD and Lowest Open Sell = "<<sell<<" USD\n";
        }
        else if(!check&&check2)
        {
            std::string buy1 = "NA";
            os<<name<<": Highest Open Buy = "<<buy<<" USD and Lowest Open Sell = "<<buy1<<" USD\n";
        }
        else{
            os<<name<<": Highest Open Buy = "<<buy<<" USD and Lowest Open Sell = "<<sell<<" USD\n";
        }
    }
  }