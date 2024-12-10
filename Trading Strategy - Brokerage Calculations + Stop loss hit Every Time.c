#include <stdio.h>
#include <stdlib.h> // For malloc and free

// Structure to store trade details
typedef struct {
    double stockBuyPrice;     // Stock Buy Price
    double stockSellPrice;    // Stock Sell Price
    int quantity;             // Quantity to trade
    double turnover;          // Total turnover (buy + sell prices)
    double brokerage;         // Brokerage charges
    double stt;               // Securities Transaction Tax
    double transactionCharges; // Exchange transaction charges
    double gst;               // GST on transaction charges
    double sebiFees;          // SEBI charges
    double stampDuty;         // Stamp duty
    double totalCharges;      // Total charges
    double profitOrLoss;      // Profit or Loss for this trade
    double remainingCapital;  // Remaining capital after this trade
} Trade;

int main() 
{
    Trade *trades; // Pointer for dynamic allocation
    int tradeCount = 500; // Fixed number of trades
    double totalCapital; // Starting capital
    double brokerage; // Fixed brokerage per trade

    double stockBuyPrice; // Common stock buy price
    double stockSellPrice; // Common stock sell price
    int quantity; // Quantity to trade

    // Input trade configuration
    printf("Enter total capital: ");
    scanf("%lf", &totalCapital);

    // Dynamically allocate memory for trades
    trades = (Trade *)malloc(tradeCount * sizeof(Trade));
    if (trades == NULL) {
        printf("Error: Unable to allocate memory for trades.\n");
        return 1;
    }

    printf("Enter brokerage amount per trade: ");
    scanf("%lf", &brokerage);

    // Input fixed stock prices and quantity directly
    printf("Enter stock buy price: ");
    scanf("%lf", &stockBuyPrice);

    printf("Enter stock sell price: ");
    scanf("%lf", &stockSellPrice);

    printf("Enter quantity of shares to trade directly: ");
    scanf("%d", &quantity);

    double remainingCapital = totalCapital; // Capital available for trading

    int i; // Declare the loop variable outside of the loop
    for (i = 0; i < tradeCount; i++) 
    {
        Trade *trade = &trades[i];

        // Assign fixed values for this trade
        trade->stockBuyPrice = stockBuyPrice;
        trade->stockSellPrice = stockSellPrice;
        trade->quantity = quantity;

        // Calculate turnover
        trade->turnover = (trade->stockBuyPrice + trade->stockSellPrice) * trade->quantity;

        // Charges calculation
        trade->brokerage = brokerage;
        trade->stt = 0.0005 * (trade->stockSellPrice * trade->quantity);
        trade->transactionCharges = 0.0003503 * trade->turnover;
        trade->gst = 0.18 * trade->transactionCharges;
        trade->sebiFees = 0.000001 * trade->turnover;
        trade->stampDuty = 0.00; // Fixed stamp duty example

        // Total charges
        trade->totalCharges = trade->brokerage + trade->stt + trade->transactionCharges + trade->gst + trade->sebiFees + trade->stampDuty;

        // Profit or Loss calculation
        trade->profitOrLoss = (trade->stockSellPrice - trade->stockBuyPrice) * trade->quantity - trade->totalCharges;

        // Adjust remaining capital based on profit or loss
        remainingCapital += trade->profitOrLoss;
        trade->remainingCapital = remainingCapital;

        if (remainingCapital <= 0) 
        {
            trade->remainingCapital = 0; // Ensure it displays 0 in the table
            printf("Insufficient funds to continue trading. Stopping at trade %d.\n", i + 1);
            break;
        }
    }

    // Print the table header
    printf("\n--- Trade Summary ---\n");
    printf("+------+-------------+-------------+----------+------------+------------+------------+-------------+----------------+\n");
    printf("| Trade| Buy Price   | Sell Price  | Quantity | Turnover   | Charges    | P/L        | Remaining   |\n");
    printf("| No.  | (per unit)  | (per unit)  |          |            | (Total)    | (Total)    | Capital     |\n");
    printf("+------+-------------+-------------+----------+------------+------------+------------+-------------+----------------+\n");

    // Print the table rows
    int j; // Declare the variable outside the loop to avoid the error
    for (j = 0; j <= i; j++) 
    {
        Trade *trade = &trades[j];
        printf("| %-4d | %-11.2f | %-11.2f | %-8d | %-10.2f | %-10.2f | %-10.2f | %-13.2f |\n",
               j + 1,
               trade->stockBuyPrice,
               trade->stockSellPrice,
               trade->quantity,
               trade->turnover,
               trade->totalCharges,
               trade->profitOrLoss,
               trade->remainingCapital);
    }

    // Print the table footer
    printf("+------+-------------+-------------+----------+------------+------------+------------+-------------+----------------+\n");

    printf("\nFinal Remaining Capital: %.2f\n", remainingCapital);

    // Notes section
    printf("\n--- Notes ---\n");
    printf("STT (Securities Transaction Tax): 0.05%% of the sell price * quantity\n");
    printf("Transaction Cost: 0.03503%% of the turnover (buy + sell price * quantity)\n");
    printf("GST (Goods and Services Tax): 18%% of the transaction charges\n");
    printf("Brokerage Charge: Fixed per trade (%.2f per trade in this example)\n", brokerage);
    printf("Total Charges per Trade: Sum of Brokerage, STT, Transaction Cost, GST, SEBI Fees, and Stamp Duty\n");

    // Free the dynamically allocated memory
    free(trades);

    return 0;
}
