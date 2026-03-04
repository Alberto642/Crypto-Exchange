# Crypto Exchange Simulator

A C++ cryptocurrency exchange simulator built for learning and portfolio purposes.  
Developed in WSL/Ubuntu with modular class design to manage users, trades, and account balances.

---

## Features

- Multi-user account management  
- Simulated buying and selling of cryptocurrency  
- Tracks account balances and transaction history  
- Modular architecture separating exchange logic, user accounts, and utility functions  
- Fully implemented in C++ using object-oriented programming principles

---

## Getting Started

### Requirements

- Ubuntu / WSL (Windows Subsystem for Linux) or any Linux environment  
- g++ compiler (C++11 or newer)

### Build & Run

Open terminal in the project folder:

```bash
g++ main.cpp exchange.cpp useraccount.cpp utility.cpp -Wall
./a.out
```
- In main.cpp place user inputs through making deposits, withdrawls, adding orders to marketplace, checking trade history etc.
