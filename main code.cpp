#include <iostream>
#include <fstream>


class BankAccount {
private:
    std::string account_number;
    double balance;

public:
    BankAccount() = default;  

    BankAccount(const std::string& account_number, double balance = 0)
        : account_number(account_number), balance(balance) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited $" << amount << ". New balance: " << balance <<" INR"<< std::endl;
        } else {
            std::cout << "Invalid deposit amount." << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrew " << amount <<" INR" << ". New balance: " << balance <<" INR"<< std::endl;
        } else {
            std::cout << "Invalid withdrawal amount or insufficient funds." << std::endl;
        }
    }

    void inquiry() {
        std::cout << "Account Number: " << account_number << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }
    void saveToFile(std::ofstream& file)  {
        file << account_number << " " << balance << std::endl;
    }

    void loadFromFile(std::ifstream& file) {
        file >> account_number >> balance;
    }
};


int displayMenu() {
    int choice;
    std::cout << "1. Deposit\n2. Withdraw\n3. Balance Inquiry\n4. Quit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}

int main() {
    
    const int numAccounts = 10;
    BankAccount accounts[numAccounts];

    
    std::ifstream inFile("accounts.txt");
    for (int i = 0; i < numAccounts; ++i) {
        accounts[i].loadFromFile(inFile);
    }
    inFile.close();

    
    int choice;
    do {
        
        choice = displayMenu();

        switch (choice) {
            case 1: {
                int accountId;
                std::cout << "Enter account ID: ";
                std::cin >> accountId;
                if (accountId >= 0 && accountId < numAccounts) {
                    double amount;
                    std::cout << "Enter deposit amount: $";
                    std::cin >> amount;
                    accounts[accountId].deposit(amount);
                } else {
                    std::cout << "Invalid account ID." << std::endl;
                }
                break;
            }
            case 2: {
                int accountId;
                std::cout << "Enter account ID: ";
                std::cin >> accountId;
                if (accountId >= 0 && accountId < numAccounts) {
                    double amount;
                    std::cout << "Enter withdrawal amount: $";
                    std::cin >> amount;
                    accounts[accountId].withdraw(amount);
                } else {
                    std::cout << "Invalid account ID." << std::endl;
                }
                break;
            }
            case 3: {
                int accountId;
                std::cout << "Enter account ID: ";
                std::cin >> accountId;
                if (accountId >= 0 && accountId < numAccounts) {
                    accounts[accountId].inquiry();
                } else {
                    std::cout << "Invalid account ID." << std::endl;
                }
                break;
            }
            case 4:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
        }
    } while (choice != 4);

    std::ofstream outFile("accounts.txt");
    for (int i = 0; i < numAccounts; ++i) {
        accounts[i].saveToFile(outFile);
    }
    outFile.close();

    return 1;
}
