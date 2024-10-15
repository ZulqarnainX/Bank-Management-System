#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSACTIONS 100
#define FILE_NAME "accounts.txt"

struct Account {
    int accountNumber;
    char name[100];            // Changed to allow multiple-word names
    float balance;             // This can handle both int and float values
    char transactionHistory[MAX_TRANSACTIONS][100];
    int transactionCount;
};

// Function prototypes
void createAccount();
void depositMoney();
void withdrawMoney();
void viewAccount();
void saveAccount(struct Account *account);
int loadAccount(int accountNumber, struct Account *account);

int main() {
    int choice;

    while (1) {
        printf("\n=== Bank Management System ===\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. View Account\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear the newline character left by scanf

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                withdrawMoney();
                break;
            case 4:
                viewAccount();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// Create a new account
void createAccount() {
    struct Account newAccount;
    FILE *file = fopen(FILE_NAME, "ab");

    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &newAccount.accountNumber);
    getchar();  // Clear the newline character after account number

    printf("Enter name: ");
    fgets(newAccount.name, sizeof(newAccount.name), stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = 0;  // Remove newline character

    printf("Enter initial deposit (you can enter both integer and float values): ");
    scanf("%f", &newAccount.balance);

    // Initialize transaction history
    newAccount.transactionCount = 0;
    sprintf(newAccount.transactionHistory[newAccount.transactionCount], "Initial deposit: %.2f", newAccount.balance);
    newAccount.transactionCount++;

    // Save the account to the file
    fwrite(&newAccount, sizeof(struct Account), 1, file);
    fclose(file);

    printf("Account created successfully!\n");
}

// Deposit money into an account
void depositMoney() {
    int accountNumber;
    float depositAmount;
    struct Account account;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (!loadAccount(accountNumber, &account)) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter deposit amount (you can enter both integer and float values): ");
    scanf("%f", &depositAmount);

    account.balance += depositAmount;
    sprintf(account.transactionHistory[account.transactionCount], "Deposit: %.2f", depositAmount);
    account.transactionCount++;

    saveAccount(&account);
    printf("Deposit successful! New balance: %.2f\n", account.balance);
}

// Withdraw money from an account
void withdrawMoney() {
    int accountNumber;
    float withdrawalAmount;
    struct Account account;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (!loadAccount(accountNumber, &account)) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter withdrawal amount (you can enter both integer and float values): ");
    scanf("%f", &withdrawalAmount);

    if (withdrawalAmount > account.balance) {
        printf("Insufficient balance.\n");
        return;
    }

    account.balance -= withdrawalAmount;
    sprintf(account.transactionHistory[account.transactionCount], "Withdrawal: %.2f", withdrawalAmount);
    account.transactionCount++;

    saveAccount(&account);
    printf("Withdrawal successful! New balance: %.2f\n", account.balance);
}

// View account details and transaction history
void viewAccount() {
    int accountNumber;
    struct Account account;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (!loadAccount(accountNumber, &account)) {
        printf("Account not found.\n");
        return;
    }

    printf("\nAccount Number: %d\n", account.accountNumber);
    printf("Name: %s\n", account.name);
    printf("Balance: %.2f\n", account.balance);
    printf("Transaction History:\n");
    for (int i = 0; i < account.transactionCount; i++) {
        printf("%d. %s\n", i + 1, account.transactionHistory[i]);
    }
}

// Save account details back to the file (overwrite old account)
void saveAccount(struct Account *account) {
    FILE *file = fopen(FILE_NAME, "rb+");
    struct Account temp;

    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&temp, sizeof(struct Account), 1, file)) {
        if (temp.accountNumber == account->accountNumber) {
            fseek(file, -sizeof(struct Account), SEEK_CUR);
            fwrite(account, sizeof(struct Account), 1, file);
            fclose(file);
            return;
        }
    }
    fclose(file);
}

// Load account details from the file
int loadAccount(int accountNumber, struct Account *account) {
    FILE *file = fopen(FILE_NAME, "rb");

    if (!file) {
        return 0;
    }

    while (fread(account, sizeof(struct Account), 1, file)) {
        if (account->accountNumber == accountNumber) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
