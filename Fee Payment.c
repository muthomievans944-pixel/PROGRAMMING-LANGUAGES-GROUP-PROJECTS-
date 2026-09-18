#include <stdio.h>
#include <string.h>

#define REQUIRED_FEE 50000
#define REGISTRATION_CHARGE 2000

typedef struct {
    int id;
    char name[30];
    double balance;
    double totalPayments;
    double totalWaivers;
    double totalReversals;
} StudentAccount;

typedef struct {
    int transId;
    int studentId;
    char type[15];   // "payment", "waiver", "reversal"
    double amount;
} Transaction;

// Check for duplicate transaction IDs
int isDuplicate(Transaction transactions[], int count, int transId) {
    for (int i = 0; i < count; i++) {
        if (transactions[i].transId == transId) return 1;
    }
    return 0;
}

// Apply payment
void applyPayment(StudentAccount *acc, double amount) {
    if (amount < 0) {
        printf("Rejected negative payment!\n");
        return;
    }
    acc->totalPayments += amount;
    acc->balance -= amount;
}

// Apply waiver
void applyWaiver(StudentAccount *acc, double amount) {
    acc->totalWaivers += amount;
    acc->balance -= amount;
}

// Apply reversal
void applyReversal(StudentAccount *acc, double amount) {
    acc->totalReversals += amount;
    acc->balance += amount;
}

// Reconciliation report
void reconciliationReport(StudentAccount students[], int count) {
    printf("\n--- Reconciliation Report ---\n");
    for (int i = 0; i < count; i++) {
        printf("Student %d (%s): Balance %.2f | Payments %.2f | Waivers %.2f | Reversals %.2f\n",
               students[i].id, students[i].name,
               students[i].balance, students[i].totalPayments,
               students[i].totalWaivers, students[i].totalReversals);

        if (students[i].balance <= 0)
            printf(" -> CLEARED\n");
        else
            printf(" -> UNCLEARED\n");
    }
}

int main() {
    // Initialize 5 students
    StudentAccount students[5] = {
        {1, "Alice", REQUIRED_FEE + REGISTRATION_CHARGE, 0, 0, 0},
        {2, "Bob", REQUIRED_FEE + REGISTRATION_CHARGE, 0, 0, 0},
        {3, "Charlie", REQUIRED_FEE + REGISTRATION_CHARGE, 0, 0, 0},
        {4, "Diana", REQUIRED_FEE + REGISTRATION_CHARGE, 0, 0, 0},
        {5, "Ethan", REQUIRED_FEE + REGISTRATION_CHARGE, 0, 0, 0}
    };

    // 12 transactions
    Transaction transactions[12] = {
        {101, 1, "payment", 20000},
        {102, 1, "payment", 30000},
        {103, 2, "waiver", 10000},
        {104, 2, "payment", 20000},
        {105, 3, "payment", 50000},
        {106, 3, "reversal", 5000},
        {107, 4, "payment", 25000},
        {108, 4, "payment", 25000},
        {109, 5, "payment", -1000},   // Invalid negative
        {110, 5, "payment", 20000},
        {111, 5, "payment", 30000},
        {111, 5, "payment", 5000}     // Duplicate ID
    };

    int transCount = 0;
    for (int i = 0; i < 12; i++) {
        if (isDuplicate(transactions, transCount, transactions[i].transId)) {
            printf("Duplicate transaction %d rejected!\n", transactions[i].transId);
            continue;
        }
        transactions[transCount++] = transactions[i];

        StudentAccount *acc = &students[transactions[i].studentId - 1];
        if (strcmp(transactions[i].type, "payment") == 0)
            applyPayment(acc, transactions[i].amount);
        else if (strcmp(transactions[i].type, "waiver") == 0)
            applyWaiver(acc, transactions[i].amount);
        else if (strcmp(transactions[i].type, "reversal") == 0)
            applyReversal(acc, transactions[i].amount);
    }

    reconciliationReport(students, 5);
    return 0;
}
