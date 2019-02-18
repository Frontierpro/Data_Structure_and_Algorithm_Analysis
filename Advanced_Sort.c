#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Random_Initial(int *List, int Num);
int Byte_Count(int Num);
void Array_Copy(int *List, int *Sort, int Num);
void Heap_Sort(int *Sort, int Num);
void Percolate_Down(int *Sort, int pos, int Num);
void Quick_Sort(int *Sort, int Left, int Right);
int Find_Pivot(int *Sort, int Left, int Right);
void Divide_Conquer(int *List, int *Sort, int Left, int Right);
void Merge_Back(int *List, int *Sort, int left_head, int left_tail, int right_head, int right_tail);
void Out_Put(int *Array, int Num, int Count);

int main(void)
{
    int Num, Count;
    int *List;
    int *Sort;

    printf("Enter the length (positive) of the sorting list: ");
    scanf("%d", &Num);
    List = (int *)malloc(Num * sizeof(int));
    Sort = (int *)malloc(Num * sizeof(int));
    printf("The random_initial list is as follows.\n");
    Random_Initial(List, Num);
    Count = Byte_Count(Num);
    Out_Put(List, Num, Count + 1);

    Array_Copy(List, Sort, Num);
    Heap_Sort(Sort, Num);
    printf("The sorting result solved by heap_sort is as follows.\n");
    Out_Put(Sort, Num, Count + 1);
    Array_Copy(List, Sort, Num);
    Quick_Sort(Sort, 0, Num - 1);
    printf("The sorting result solved by quick_sort is as follows.\n");
    Out_Put(Sort, Num, Count + 1);
    Array_Copy(List, Sort, Num);
    Divide_Conquer(List, Sort, 0, Num - 1);
    printf("The sorting result solved by divide_merge is as follows.\n");
    Out_Put(Sort, Num, Count + 1);

    printf("Press ENTER to quit.\n");
    free(List);
    free(Sort);
    getchar();
    getchar();

    return 0;
}

void Random_Initial(int *List, int Num)
{
    int pos, left, right, temp;

    for (pos = 0; pos < Num; pos++)
        *(List + pos) = pos;
    srand((int)time(NULL));
    for (left = 0; left < Num; left++) {
        right = rand() % (Num - left) + left;
        temp = *(List + left);
        *(List + left) = *(List + right);
        *(List + right) = temp;
    }
}

int Byte_Count(int Num)
{
    int count = 0;

    while (Num) {
        count++;
        Num /= 10;
    }

    return count;
}

void Array_Copy(int *List, int *Sort, int Num)
{
    int pos;

    for (pos = 0; pos < Num; pos++)
        *(Sort + pos) = *(List + pos);
}

void Heap_Sort(int *Sort, int Num)
{
    int temp, pos = Num / 2 - 1;

    while (pos >= 0) {
        Percolate_Down(Sort, pos, Num);
        pos--;
    }
    pos = Num - 1;
    while (pos > 0) {
        temp = *Sort;
        *Sort = *(Sort + pos);
        *(Sort + pos) = temp;
        Percolate_Down(Sort, 0, pos);
        pos--;
    }
}

void Percolate_Down(int *Sort, int pos, int Num)
{
    int max, temp = *(Sort + pos);

    while (2 * pos + 1 < Num) {
        max = 2 * pos + 1;
        if (2 * (pos + 1) < Num && *(Sort + 2 * pos + 1) < *(Sort + 2 * (pos + 1)))
            max++;
        if (*(Sort + max) > temp) {
            *(Sort + pos) = *(Sort + max);
            pos = max;
        }
        else
            break;
    }
    *(Sort + pos) = temp;
}

void Quick_Sort(int *Sort, int Left, int Right)
{
    int pivot, temp, head, tail;

    if (Right - Left + 1 > 20) {
        pivot = Find_Pivot(Sort, Left, Right);
        head = Left + 1;
        tail = Right - 2;
        while (head < tail) {
            while (*(Sort + head) < pivot)
                head++;
            while (*(Sort + tail) > pivot)
                tail--;
            if (head < tail) {
                temp = *(Sort + head);
                *(Sort + head) = *(Sort + tail);
                *(Sort + tail) = temp;
            }
        }
        *(Sort + Right - 1) = *(Sort + head);
        *(Sort + head) = pivot;
        Quick_Sort(Sort, Left, head - 1);
        Quick_Sort(Sort, head + 1, Right);
    }
    else
        for (tail = Left + 1; tail <= Right; tail++) {
            head = tail - 1;
            temp = *(Sort + tail);
            while (head >= Left && *(Sort + head) > temp) {
                *(Sort + head + 1) = *(Sort + head);
                head--;
            }
            *(Sort + head + 1) = temp;
        }
}

int Find_Pivot(int *Sort, int Left, int Right)
{
    int mid = (Left + Right) / 2;
    int temp;

    if (*(Sort + mid) < *(Sort + Left)) {
        temp = *(Sort + Left);
        *(Sort + Left) = *(Sort + mid);
        *(Sort + mid) = temp;
    }
    if (*(Sort + Right) < *(Sort + Left)) {
        temp = *(Sort + Left);
        *(Sort + Left) = *(Sort + Right);
        *(Sort + Right) = temp;
    }
    if (*(Sort + Right) < *(Sort + mid)) {
        temp = *(Sort + mid);
        *(Sort + mid) = *(Sort + Right);
        *(Sort + Right) = temp;
    }
    temp = *(Sort + mid);
    *(Sort + mid) = *(Sort + Right - 1);
    *(Sort + Right - 1) = temp;

    return temp;
}

void Divide_Conquer(int *List, int *Sort, int Left, int Right)
{
    int mid = (Left + Right) / 2;

    if (Left == Right)
        return;
    Divide_Conquer(List, Sort, Left, mid);
    Divide_Conquer(List, Sort, mid + 1, Right);
    Merge_Back(List, Sort, Left, mid, mid + 1, Right);
}

void Merge_Back(int *List, int *Sort, int left_head, int left_tail, int right_head, int right_tail)
{
    int pos = left_head, left = left_head, right = right_head;

    while (left <= left_tail && right <= right_tail) {
        if (*(List + left) < *(List + right))
            *(Sort + pos++) = *(List + left++);
        else
            *(Sort + pos++) = *(List + right++);
    }
    while (left <= left_tail)
        *(Sort + pos++) = *(List + left++);
    while (right <= right_tail)
        *(Sort + pos++) = *(List + right++);
    for (pos = left_head; pos <= right_tail; pos++)
        *(List + pos) = *(Sort + pos);
}

void Out_Put(int *Array, int Num, int Count)
{
    int pos;

    for (pos = 0; pos < Num; pos++)
        printf("%-*d", Count, *(Array + pos));
    putchar('\n');
}
