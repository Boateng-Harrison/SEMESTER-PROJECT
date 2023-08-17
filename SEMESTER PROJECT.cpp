#include <iostream>
#include <vector>
#include <algorithm> // Include this for std::remove()

using namespace std;

class Stock {
private:
    string symbol;
    string name;
    double currentPrice;

public:
    Stock(string s, string n, double price)
        : symbol(s), name(n), currentPrice(price) {}

    string GetSymbol() { return symbol; }
    string GetName() { return name; }
    double GetCurrentPrice() { return currentPrice; }
};

class StockQuantityPair {
public:
    Stock stock;
    int quantity;

    StockQuantityPair(Stock _stock, int _quantity)
        : stock(_stock), quantity(_quantity) {}
};

class Portfolio {
private:
    vector<StockQuantityPair> stocksOwned;

public:
    void BuyStock(Stock stock, int quantity) {
        stocksOwned.push_back(StockQuantityPair(stock, quantity));
        cout << quantity << " shares of " << stock.GetName() << " bought." << endl;
    }

    void SellStock(Stock stock, int quantity) {
        bool sold = false;
        for (size_t i = 0; i < stocksOwned.size(); ++i) {
            if (stocksOwned[i].stock.GetSymbol() == stock.GetSymbol() && stocksOwned[i].quantity >= quantity) {
                stocksOwned[i].quantity -= quantity;
                sold = true;
                cout << quantity << " shares of " << stock.GetName() << " sold." << endl;
                if (stocksOwned[i].quantity == 0) {
                    stocksOwned.erase(stocksOwned.begin() + i);
                    cout << "No more " << stock.GetName() << " shares left in portfolio." << endl;
                }
                break; // Exit the loop after finding and processing the sale
            }
        }
        if (!sold) {
            cout << "Not enough shares of " << stock.GetName() << " to sell." << endl;
        }
    }

    void DisplayTransactions() {
        cout << "Transaction history:" << endl;
        for (size_t i = 0; i < stocksOwned.size(); ++i) {
            cout << "Stock: " << stocksOwned[i].stock.GetName() << ", Quantity: " << stocksOwned[i].quantity << endl;
        }
    }
};

class Account {
private:
    string accountNumber;
    string accountHolder;
    double balance;

public:
    Account(string number = "Harrison", string holder = "123456789", double initialBalance = 500.0)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    string GetAccountNumber() { return accountNumber; }
    string GetAccountHolder() { return accountHolder; }
    double GetBalance() { return balance; }

    void Deposit(double amount) {
        balance += amount;
        cout << "Deposit successful! New balance: $" << balance << endl;
    }
};

int main() {
    Account userAccount("B0ATENG HARRISON", "UEB3239522", 5000.0);
    Portfolio userPortfolio;

    int choice;
    do {
        cout << "********************" << endl;
        cout << "Trading Application" << endl;
        cout << "********************" << endl;
        cout << "1. Get Account Information" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Buy Stocks" << endl;
        cout << "4. Sell Stocks" << endl;
        cout << "5. Check Transactions" << endl;
        cout << "6. Exit" << endl;

        cout << "Please select an option (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Display account information
                cout << "Account Number: " << userAccount.GetAccountNumber() << endl;
                cout << "Account Holder: " << userAccount.GetAccountHolder() << endl;
                cout << "Balance: $" << userAccount.GetBalance() << endl;
                break;
            case 2:
                // Deposit money
                double depositAmount;
                cout << "Enter the amount to deposit: $";
                cin >> depositAmount;
                userAccount.Deposit(depositAmount);
                break;
            case 3:
                // Buy stocks
                {
                    int stockQuantity;
                    string stockSymbol;
                    cout << "Enter the stock symbol to buy: ";
                    cin >> stockSymbol;
                    cout << "Enter the quantity to buy: ";
                    cin >> stockQuantity;
                    Stock stockToBuy(stockSymbol, "Apple Inc.", 150.0); // Replace with actual stock details
                    userPortfolio.BuyStock(stockToBuy, stockQuantity);
                }
                break;
            case 4:
                // Sell stocks
                {
                    int stockQuantitySell;
                    string stockSymbolSell;
                    cout << "Enter the stock symbol to sell: ";
                    cin >> stockSymbolSell;
                    cout << "Enter the quantity to sell: ";
                    cin >> stockQuantitySell;
                    Stock stockToSell(stockSymbolSell, "Apple Inc.", 150.0); // Replace with actual stock details
                    userPortfolio.SellStock(stockToSell, stockQuantitySell);
                }
                break;
            case 5:
                // Display transaction history
                userPortfolio.DisplayTransactions();
                break;
            case 6:
                cout << "Exiting the application. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please select a valid option (1-6)." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}

