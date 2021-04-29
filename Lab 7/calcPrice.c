#include <stdio.h>

/*
 * Name: Michael Anderson
 * Student Email: manderson113@student.gsu.edu
 */
 
int main(void)
{
  int itemNumber, quantity, day, month, year;
  float unitPrice;
  char date[10];
  printf("Enter item number:");
  scanf("%d", &itemNumber);
  printf("Enter unit price:");
  scanf("%f", &unitPrice);
  printf("Enter quantity:");
  scanf("%d", &quantity);
  printf("Enter purchase date (mm/dd/yyyy):");
  scanf("%d/%d/%d", &month, &day, &year);
  sprintf(date, "%d/%d/%d", month, day, year);
  printf("%-4s  %10s  %-3s  %-13s  %12s\n",
    "Item", "Unit Price", "QTY", "Purchase Date", "Total Amount");
  printf("%-4d  $%9.2f  %-3d  %-13s  $%11.2f\n",
    itemNumber, unitPrice, quantity, date, unitPrice*quantity);
}