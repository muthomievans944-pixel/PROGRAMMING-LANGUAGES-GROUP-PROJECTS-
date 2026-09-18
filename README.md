# PROGRAMMING-LANGUAGES-GROUP-PROJECTS-

GROUP MEMBERS.
1. Evans Muthomi C026-01-2768/2025
2. Paul Ogutu    C026-01-0983/2025
3. Schyler Chartely C026-01-0979/2025


PROJECT 1:M-Pesa Transaction Verification and Recovery

Description

This Lua program demonstrates how coroutines can be used to manage M-Pesa transactions.

Each transaction runs as an independent coroutine and goes through different stages. The transaction is paused using "coroutine.yield()" and continued using "coroutine.resume()".

The program also checks whether the customer has sufficient funds before completing the transaction.

Features

- Creates independent transaction coroutines.
- Pauses transactions after each stage using "yield()".
- Checks for insufficient funds.
- Uses a scheduler to manage transactions.
- Preserves transaction state between yields.

Transaction Stages

1. Received
2. Customer details checked
3. Balance verified
4. Transaction authorized
5. Receipt generated

If the balance is insufficient, the transaction fails.



Key Concepts

- "coroutine.create()" — creates a coroutine.
- "coroutine.yield()" — pauses execution.
- "coroutine.resume()" — continues execution.
- "coroutine.status()" — checks the coroutine state


2: Project 2:Student Fee Payment System

Description

This C program manages student fee accounts and processes different transactions.

Features

- Processes student payments.
- Applies fee waivers.
- Processes payment reversals.
- Rejects negative payments.
- Detects duplicate transactions.
- Calculates the remaining balance.
- Shows whether a student is CLEARED or UNCLEARED.

Starting Fee

Each student starts with a balance of 52,000:

- Required fee: 50,000
- Registration charge: 2,000

Main Functions

- "isDuplicate()" – Checks duplicate transaction IDs.
- "applyPayment()" – Processes payments.
- "applyWaiver()" – Applies waivers.
- "applyReversal()" – Processes reversals.
- "reconciliationReport()" – Displays the final report.