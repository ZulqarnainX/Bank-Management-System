
// Bank Management System By Rizzler Zulqarnain

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "accounts.txt"

struct Bank
{
    int id;         // Integer field
    char name[100]; // String field
    int balance;    // Integer field (for account balance)
};

int main()
{
    int amount;        // Declare 'amount' once here
    int choice;
    int searchID, found = 0;

    // Declare a variable of type 'struct Bank'
    struct Bank MCB1;

    while (1)
    {
        // Printing The Index
        printf("\n=== Bank Management System ===\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. View Account\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character left by scanf

        FILE *file, *tempFile; // Adding a temporary file pointer

        switch (choice)
        {
        case 1:
            // Creating a new account
            printf("Please Enter Your Name : ");
            scanf("%s", MCB1.name);

            printf("Please Enter ID Number : ");
            scanf("%d", &MCB1.id);

            printf("Please Enter Initial Balance : ");
            scanf("%d", &MCB1.balance);

            file = fopen(FILE_NAME, "a");

            if (file == NULL)
            {
                printf("Error opening file!\n");
                return 1;
            }

            fprintf(file, "Account Holder Name : %s\n", MCB1.name);
            fprintf(file, "Bank ID : %d\n", MCB1.id);
            fprintf(file, "Balance : %d\n", MCB1.balance);

            // Closing the file
            fclose(file);

            printf("Account Created Successfully.\n");
            break;

        case 2:
            // Depositing money
            printf("Please Enter Your Bank ID: ");
            scanf("%d", &searchID);

            printf("Please Enter The Amount to Add: ");
            scanf("%d", &amount);

            // Open the original file for reading
            file = fopen(FILE_NAME, "r");
            if (file == NULL)
            {
                printf("Error opening file!\n");
                return 1;
            }

            // Open a temporary file for writing
            tempFile = fopen("temp.txt", "w");
            if (tempFile == NULL)
            {
                printf("Error opening temp file!\n");
                fclose(file);
                return 1;
            }

            // Read each account and update the balance for the matching ID
            found = 0;
            while (fscanf(file, "Account Holder Name : %99[^\n]\n", MCB1.name) != EOF)
            {
                fscanf(file, "Bank ID : %d\n", &MCB1.id);
                fscanf(file, "Balance : %d\n", &MCB1.balance);

                // If the ID matches, update the balance
                if (MCB1.id == searchID)
                {
                    MCB1.balance += amount;
                    printf("New Balance: %d\n", MCB1.balance);
                    found = 1;
                }

                // Write the account info to the temporary file
                fprintf(tempFile, "Account Holder Name : %s\n", MCB1.name);
                fprintf(tempFile, "Bank ID : %d\n", MCB1.id);
                fprintf(tempFile, "Balance : %d\n", MCB1.balance);
            }

            fclose(file);
            fclose(tempFile);

            // Replace the original file with the updated temp file
            remove(FILE_NAME);
            rename("temp.txt", FILE_NAME);

            if (!found)
            {
                printf("Account with ID %d not found!\n", searchID);
            }
            else
            {
                printf("Balance updated successfully!\n");
            }

            break;

        case 3:
            // Withdraw money (similar to deposit)
            printf("Please Enter Your Bank ID: ");
            scanf("%d", &searchID);

            printf("Please Enter The Amount to Withdraw: ");
            scanf("%d", &amount);

            // Open the original file for reading
            file = fopen(FILE_NAME, "r");
            if (file == NULL)
            {
                printf("Error opening file!\n");
                return 1;
            }

            // Open a temporary file for writing
            tempFile = fopen("temp.txt", "w");
            if (tempFile == NULL)
            {
                printf("Error opening temp file!\n");
                fclose(file);
                return 1;
            }

            // Read each account and update the balance for the matching ID
            found = 0;
            while (fscanf(file, "Account Holder Name : %99[^\n]\n", MCB1.name) != EOF)
            {
                fscanf(file, "Bank ID : %d\n", &MCB1.id);
                fscanf(file, "Balance : %d\n", &MCB1.balance);

                if (MCB1.id == searchID)
                {
                    if (amount <= MCB1.balance)
                    {
                        MCB1.balance -= amount;
                        printf("New Balance: %d\n", MCB1.balance);
                        found = 1;
                    }
                    else
                    {
                        printf("Insufficient balance!\n");
                        found = 1;
                    }
                }

                // Write the account info to the temporary file
                fprintf(tempFile, "Account Holder Name : %s\n", MCB1.name);
                fprintf(tempFile, "Bank ID : %d\n", MCB1.id);
                fprintf(tempFile, "Balance : %d\n", MCB1.balance);
            }

            fclose(file);
            fclose(tempFile);

            // Replace the original file with the updated temp file
            remove(FILE_NAME);
            rename("temp.txt", FILE_NAME);

            if (!found)
            {
                printf("Account with ID %d not found!\n", searchID);
            }

            break;

        case 4:
            // View account details
            printf("Please Enter Your Bank ID: ");
            scanf("%d", &searchID);
            found = 0;  // Reset 'found' to 0 for each search

            // Open the file for reading
            file = fopen(FILE_NAME, "r");
            if (file == NULL)
            {
                printf("Error opening file!\n");
                return 1;
            }

            // Loop through the file to find the account with the matching ID
            while (fscanf(file, "Account Holder Name : %99[^\n]\n", MCB1.name) != EOF)
            {
                fscanf(file, "Bank ID : %d\n", &MCB1.id);
                fscanf(file, "Balance : %d\n", &MCB1.balance);

                if (MCB1.id == searchID)
                {
                    // Display account details
                    printf("\n=== Account Details ===\n");
                    printf("Account Holder Name : %s\n", MCB1.name);
                    printf("Bank ID : %d\n", MCB1.id);
                    printf("Balance : %d\n", MCB1.balance);
                    found = 1;
                    break;
                }
            }

            fclose(file);

            if (!found)
            {
                printf("Account with ID %d not found!\n", searchID);
            }

            break;

        case 5:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
