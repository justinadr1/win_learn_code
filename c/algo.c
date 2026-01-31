
#include <stdio.h>
#include <windows.h>
int main()
{
    int nums[] = { 800, 400, 300, 900, 700, 500, 100, 600, 200 };

    size_t size = sizeof(nums) / sizeof(nums[0]);
    
    for (int i = 0; i < size; i++)
    {
        printf("%u ", nums[i]);
    }

    printf("\n");

    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (nums[i] > nums[j])
            {
                printf("swap: nums[%u] = %i and nums[%u] = %i\n", i, nums[i], j, nums[j]);
                int n = nums[i];
                nums[i] = nums[j];
                nums[j] = n;
                Sleep(1000);
            }
        }
        printf("%i: [", i);
        for (int i = 0; i < size; i++)
        {
            if (i == size - 1)
            {
                printf("%u", nums[i]);
                break;
            }
            printf("%u ", nums[i]);
        }   
        printf("]\n");
        getchar();
    }

    for (int i = 0; i < size; i++)
    {
        printf("%u ", nums[i]);
    }

}