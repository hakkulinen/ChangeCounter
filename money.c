#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int *allocateArray(int length)
{
    int *array = (int *)malloc(length * sizeof(int));
    if (array == NULL)
    {
        printf("\nMemory allocation error, restart the program and try again.");
        exit(101);
    }
    return array;
}

void makeChange(int amount, int coins[], int numCoins)
{
    for (int i = 0; i < numCoins; i++)
    {
        int numCoins = amount / coins[i];
        if (numCoins > 0)
        {
            printf("\n%d %d-ruble coins", numCoins, coins[i]);
            amount -= coins[i] * numCoins;
        }
    }
    if (amount > 0)
    {
        printf("\nCouldn't split properly into change with the given denominations, amount left over: %d", amount);
    }
}

int mmin()
{
    int i = 1;
    while (i * 2 >= i)
        i = i * 2;
    i = i * 2;
    return i;
}

int getValidIntegerLimited()
{
    int n = 0, d, nmax, nmin;
    char c;
    int flag = 0, znak = 0;
    nmin = mmin();
    nmax = nmin - 1;
    while ((c = getch()) != '\r' || flag == 0 || (flag == 1 && n == 0 && znak == 1))
    {
        if ((c >= '0' && c <= '9') || flag == 1 && n == 0 && znak == 0 && c != '\b')
        {
            if ((c == '0' && flag == 1 && n == 0) || (flag == 1 && n == 0 && znak == 0))
                continue;
            d = c - '0';
            if ((znak == 0 && n > (nmax - d) / 10) || (znak == 1 && n < (nmin + d) / 10))
                continue;
            if (znak == 0)
                n = n * 10 + d;
            else
                n = n * 10 - d;
            printf("%c", c);
            flag = 1;
        }
        if (c == '-' && nmin < 0)
            if (flag == 0)
            {
                znak = 1;
                flag = 1;
                printf("%c", c);
            }
        if (c == '\b')
        {
            if (flag == 0)
                continue;
            if (znak == 1 && n == 0)
            {
                znak = 0;
                flag = 0;
                printf("\b \b");
                continue;
            }
            n = n / 10;
            printf("\b \b");
            if (n == 0 && znak == 0)
                flag = 0;
        }
    }
    return n;
}

void sortDescending(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    printf("Enter the number of coin denominations: ");

    int numCoins = getValidIntegerLimited();
    int *coins = allocateArray(numCoins);

    for (int i = 0; i < numCoins; i++)
    {
        printf("\nEnter the denomination of coin %d: ", i + 1);
        coins[i] = getValidIntegerLimited();
    }
    sortDescending(coins, numCoins);
    int amount;
    while (1)
    {
        printf("\nEnter the amount to make change for or enter 0 to end the program: ");
        amount = getValidIntegerLimited();
        if (amount == 0)
        {
            break;
        }
        makeChange(amount, coins, numCoins);
    }
    free(coins);
    return 0;
}
