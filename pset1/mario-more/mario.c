#include<stdio.h>
int main()
{
    int num, row, s, x;

    // get num of hashes from user
    do
    {
        printf("Height : ");
        scanf("%d", &num);
    }
    while (num < 1 || num > 8);

    // spaces + hashes = total hight 8 => spaces = total hight - hashes

    // for loop
    for (row = 1; row <= num; row++)
    {

        for (s = 1; s <= num - row; s++)
        {
            printf(" ");
        }
        for (x = 1; x <= row; x++)
        {
            printf("#");
        }
        printf("  ");
        for (x = 1; x <= row; x++)
        {
            printf("#");
        }
        printf("\n");
    }
}