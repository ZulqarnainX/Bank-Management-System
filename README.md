# Bank Management System

## Overview
This is a simple **Bank Management System** written in C. It allows users to create bank accounts, deposit and withdraw money, and view account details. Account information is stored in a text file (`accounts.txt`), and the system supports multiple accounts with unique IDs.

## Features
- **Create Account:** Users can create a new bank account by providing their name, a unique ID, and an initial balance.
- **Deposit Money:** Allows users to add money to an existing account using the account ID.
- **Withdraw Money:** Users can withdraw money from an existing account, ensuring the withdrawal amount is not greater than the account balance.
- **View Account:** Displays account details (name, ID, and balance) based on the provided account ID.
- **Persistent Storage:** All account information is stored in `accounts.txt` and is updated in real-time.

## Project Structure
- `main.c` - The core C file that contains all the functionality of the bank management system.
- `accounts.txt` - The file where account data (account holder's name, ID, and balance) is stored.

## How to Use
### 1. Clone the Repository
To get a local copy of the project up and running, use the following command:
```bash
git clone https://github.com/ZulqarnainX/bank-management-system.git
