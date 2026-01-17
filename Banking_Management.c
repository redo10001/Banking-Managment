
// Simple Banking Management System

#include <stdio.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    char pass[20];
    float balance;
};

struct Account accounts[100];
int totalAccounts = 0;
int loggedindex = -1; 


void addAccount() {
    struct Account a; 
    int exists = 0;

    printf("\nEnter Account Number: ");
    scanf("%d", &a.accNo);

    // Check if account number already exists
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accNo == a.accNo) {
            exists = 1;
            break;
        }
    }

    if (exists) {
        printf("Account number already exists!\n");
    } else {
        printf("Enter Name: ");
        getchar(); // Clear newline from buffer
        scanf("%[^\n]", a.name);

        printf("Enter Password: ");
        scanf("%s", a.pass);

        printf("Enter Initial Balance: ");
        scanf("%f", &a.balance);

        // Store the temporary struct in the array
        accounts[totalAccounts] = a;
        totalAccounts++;

        printf("Account created successfully!\n");
    }
}

// Function to display balance
void showBalance() {
    printf("\nYour current balance: %.2f\n", accounts[loggedindex].balance);
}

// Function to deposit money
void depositMoney() {
    float amount;
    printf("\nEnter amount to deposit: ");
    scanf("%f", &amount);

    if (amount > 0) {
        accounts[loggedindex].balance += amount;
        printf("%.2f deposited successfully!\n", amount);
    } else {
        printf("Invalid amount!\n");
    }
}

// Function to withdraw money
void withdrawMoney() {
    float amount;
    printf("\nEnter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
    } else if (amount > accounts[loggedindex].balance) {
        printf("Insufficient balance!\n");
    } else {
        accounts[loggedindex].balance -= amount;
        printf("%.2f withdrawn successfully!\n", amount);
    }
}

// Function to transfer money
void transferMoney() {
    int targetAcc;
    float amount;

    printf("\nEnter target account number: ");
    scanf("%d", &targetAcc);

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    int found = -1;
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accNo == targetAcc) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Target account not found!\n");
        return;
    }

    if (amount > accounts[loggedindex].balance) {
        printf("Insufficient balance!\n");
    } else {
        accounts[loggedindex].balance -= amount;
        accounts[found].balance += amount;
        printf("Money transferred successfully!\n");
    }
}

// Function for login
int loginAccount() {
    int accNo;
    char pass[20];
 
    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);
    printf("Enter Password: ");
    scanf("%s", pass);

    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accNo == accNo && strcmp(accounts[i].pass, pass) == 0) {
            loggedindex = i; // updated variable name
            printf("Login successful!\n");
            return 1;
        }
    }

    printf("Invalid account number or password!\n");
    return 0;
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Create New Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addAccount();
        } else if (choice == 2) {
            if (loginAccount()) {
                int subChoice = 0;
                while (subChoice != 5) {
                    printf("\n--- Account Menu ---\n");
                    printf("1. Check Balance\n");
                    printf("2. Deposit\n");
                    printf("3. Withdraw\n");
                    printf("4. Transfer\n");
                    printf("5. Logout\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);

                    switch (subChoice) {
                        case 1: showBalance(); break;
                        case 2: depositMoney(); break;
                        case 3: withdrawMoney(); break;
                        case 4: transferMoney(); break;
                        case 5: printf("Logging out...\n"); break;
                        default: printf("Invalid choice!\n");
                    }
                }
                loggedindex = -1; // reset after logout
            }
        } else if (choice == 3) {
            printf("Thank you for using our banking system!\n");
            break;
        } else {
            printf("Invalid choice!\n"
            );
        }
    }

    return 0;
}

