#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <map>
using namespace std;

// Utility Template Class for Logging
template <typename T>
class Logger {
public:
    static void log(const T& data) {
        ofstream out("transaction_log.txt", ios::app);
        if (out.is_open()) {
            out << data << endl;
            out.close();
        }
    }
};

// Abstract Class for Transaction Handling
class TransactionInterface {
public:
    virtual void deposit(double) = 0;
    virtual void withdraw(double) = 0;
    virtual void displayBalance() const = 0;
    virtual void showTransactionHistory() const = 0;
    virtual ~TransactionInterface() {}
};

// Person Base Class
class Person {
protected:
    string name;
    int age;
public:
    Person(string n = "", int a = 0) : name(n), age(a) {}
    virtual void displayInfo() const {
        cout << "Name: " << name << "\nAge: " << age << endl;
    }
};

// BankEntity
class BankEntity : virtual public Person {
protected:
    static int accountCounter;
    int accountNumber;
    string username;
    string password;
    double balance;
public:
    BankEntity(string n = "", int a = 0, double b = 0.0, string user = "", string pass = "") : Person(n, a), balance(b), username(user), password(pass) {
        accountNumber = ++accountCounter;
    }
    int getAccountNumber() const { return accountNumber; }
    string getUsername() const { return username; }
    bool authenticate(string pass) const { return password == pass; }
    virtual ~BankEntity() {}
    double getBalance() const {
    return balance;
}
    
};

int BankEntity::accountCounter = 1000;

// Customer Class
class Customer : virtual public BankEntity, public TransactionInterface {
    vector<string> transactionHistory;
public:
    Customer(string n = "", int a = 0, double b = 0.0, string u = "", string p = "") : BankEntity(n, a, b, u, p) {}

    void deposit(double amount) override {
        if (amount <= 0) throw invalid_argument("Deposit amount must be positive.");
        balance += amount;
        string log = "Deposited: $" + to_string(amount);
        transactionHistory.push_back(log);
        Logger<string>::log("[" + username + "] " + log);
    }

    void withdraw(double amount) override {
        if (amount > balance) throw runtime_error("Insufficient funds.");
        balance -= amount;
        string log = "Withdrawn: $" + to_string(amount);
        transactionHistory.push_back(log);
        Logger<string>::log("[" + username + "] " + log);
    }

    void transfer(Customer& to, double amount) {
        if (amount > balance) throw runtime_error("Insufficient funds for transfer.");
        this->balance -= amount;
        to.balance += amount;
        string logFrom = "Transferred $" + to_string(amount) + " to " + to.username;
        string logTo = "Received $" + to_string(amount) + " from " + this->username;
        this->transactionHistory.push_back(logFrom);
        to.transactionHistory.push_back(logTo);
        Logger<string>::log("[" + username + "] " + logFrom);
        Logger<string>::log("[" + to.username + "] " + logTo);
    }

    void displayBalance() const override {
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void showTransactionHistory() const override {
        cout << "\nTransaction History for " << username << ":\n";
        for (const auto& record : transactionHistory) cout << record << endl;
    }

    friend ostream& operator<<(ostream& out, const Customer& c) {
        out << "Account #" << c.accountNumber << " | User: " << c.username << " | Name: " << c.name << " | Balance: $" << fixed << setprecision(2) << c.balance;
        return out;
    }
};

// Admin Class
class Admin : virtual public BankEntity {
public:
    Admin(string n = "", int a = 0, string u = "", string p = "") : BankEntity(n, a, 0.0, u, p) {}

    void resetCustomerBalance(Customer& c) {
        c.deposit(-c.getBalance());
        Logger<string>::log("[Admin] Reset balance for " + c.getUsername());
    }

    void deleteCustomer(map<string, Customer>& customers, const string& username) {
        if (customers.erase(username)) {
            Logger<string>::log("[Admin] Deleted account: " + username);
        }
    }

    void listAllCustomers(const map<string, Customer>& customers) {
        cout << "\n-- All Customers --\n";
        for (const auto& pair : customers) {
            cout << pair.second << endl;
        }
    }
};

// ATM Class
class ATM {
    string location;
public:
    ATM(string loc = "Main Branch") : location(loc) {}

    void accessAccount(Customer& c, map<string, Customer>& customers) {
        int choice;
        double amount;
        string targetUser;
        cout << "\nWelcome to ATM - " << location << endl;
        do {
            cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Transfer\n5. View Transactions\n6. Exit\nChoice: ";
            cin >> choice;
            try {
                switch (choice) {
                    case 1:
                        cout << "Amount: "; cin >> amount;
                        c.deposit(amount);
                        break;
                    case 2:
                        cout << "Amount: "; cin >> amount;
                        c.withdraw(amount);
                        break;
                    case 3:
                        c.displayBalance();
                        break;
                    case 4:
                        cout << "Transfer to username: "; cin >> targetUser;
                        if (customers.count(targetUser)) {
                            cout << "Amount: "; cin >> amount;
                            c.transfer(customers[targetUser], amount);
                        } else cout << "User not found." << endl;
                        break;
                    case 5:
                        c.showTransactionHistory();
                        break;
                    case 6:
                        cout << "Thank you for using ATM.\n";
                        break;
                    default:
                        cout << "Invalid choice.\n";
                }
            } catch (exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        } while (choice != 6);
    }
};

// Main Function
int main() {
    map<string, Customer> customers;
    customers["john"] = Customer("John Doe", 30, 1000.0, "john", "1234");
    customers["alice"] = Customer("Alice Smith", 25, 1500.0, "alice", "4321");

    Admin admin("Admin", 40, "admin", "adminpass");
    ATM atm("Downtown Branch");

    string username, password;
    cout << "Login (type 'admin' for admin access)\nUsername: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == "admin" && admin.authenticate(password)) {
        int choice;
        do {
            cout << "\n--- Admin Menu ---\n1. View All Customers\n2. Delete Customer\n3. Exit\nChoice: ";
            cin >> choice;
            if (choice == 1) admin.listAllCustomers(customers);
            else if (choice == 2) {
                string userToDelete;
                cout << "Username to delete: "; cin >> userToDelete;
                admin.deleteCustomer(customers, userToDelete);
            }
        } while (choice != 3);
    } else if (customers.count(username) && customers[username].authenticate(password)) {
        atm.accessAccount(customers[username], customers);
    } else {
        cout << "Login failed." << endl;
    }

    return 0;
}