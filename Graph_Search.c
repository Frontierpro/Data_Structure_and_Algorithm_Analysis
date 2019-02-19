#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **Map_Create(int Num);
int Num_Count(int Num);
void Read_Map(int **Map, int Num, int Count);
int *Depth_First(int **Map, int Num);
void Find_Path(int **Map, int *stack, int *label, int Num, int top, int count);
int *Breadth_First(int **Map, int Num);
void Extend_Path(int **Map, int *queue, int *label, int Num, int count);
void Out_Put(int **Map, int *Array, int Num, int Count);
void Memory_Clear(int **Map, int Num);

int main(void)
{
    int Num, Count;
    int **Map;
    int *Stack, *Queue;

    printf("Enter the number (positive) of nodes in the graph: ");
    scanf("%d", &Num);
    Map = Map_Create(Num);
    Count = Num_Count(Num);
    printf("The random_created map is as follows.\n");
    Read_Map(Map, Num, Count);

    Stack = Depth_First(Map, Num);
    printf("The solution searched by depth_first method is as follows.\n");
    Out_Put(Map, Stack, Num, Count);
    Queue = Breadth_First(Map, Num);
    printf("The solution searched by breadth_first method is as follows.\n");
    Out_Put(Map, Queue, Num, Count);

    printf("Press ENTER to quit.\n");
    Memory_Clear(Map, Num);
    free(Stack);
    free(Queue);
    getchar();
    getchar();

    return 0;
}

int **Map_Create(int Num)
{
    int row, col;
    int **map;

    map = (int **)malloc(Num * sizeof(int *));
    for (row = 0; row < Num; row++)
        *(map + row) = (int *)malloc(Num * sizeof(int));
    srand((int)time(NULL));
    for (row = 0; row < Num; row++)
        for (col = 0; col < Num; col++) {
            if (row == col)
                *(*(map + row) + col) = 0;
            else {
                *(*(map + row) + col) = rand() % Num;
                if (*(*(map + row) + col))
                    *(*(map + row) + col) = 0;
                else
                    *(*(map + row) + col) = rand() % 99 + 1;
                *(*(map + col) + row) = *(*(map + row) + col);
            }
        }

    return map;
}

int Num_Count(int Num)
{
    int count = 0;

    while (Num) {
        count++;
        Num /= 10;
    }

    return count;
}

void Read_Map(int **Map, int Num, int Count)
{
    int row, col;

    for (row = 0; row < Num; row++)
        for (col = row + 1; col < Num; col++)
            if (*(*(Map + row) + col))
                printf("%*d<->%-*d:%2d; ", Count, row, Count, col, *(*(Map + row) + col));
    putchar('\n');
}

int *Depth_First(int **Map, int Num)
{
    int *stack, *label;
    int pos, count = 0;

    stack = (int *)malloc(Num * sizeof(int));
    label = (int *)malloc(Num * sizeof(int));
    for (pos = 0; pos < Num; pos++)
        *(label + pos) = 0;
    while (true) {
        for (pos = 0; pos < Num; pos++)
            *(stack + pos) = -1;
        for (pos = 0; pos < Num; pos++)
            if (*(label + pos) == 0)
                break;
        if (pos == Num)
            break;
        count++;
        *stack = pos;
        *(label + pos) = count;
        Find_Path(Map, stack, label, Num, 1, count);
    }
    free(stack);

    return label;
}

void Find_Path(int **Map, int *stack, int *label, int Num, int top, int count)
{
    int row = *(stack + top - 1), col = *(stack + top) + 1;

    while (col < Num) {
        if (*(*(Map + row) + col) && *(label + col) == 0)
            break;
        col++;
    }
    if (col == Num) {
        *(stack + top--) = -1;
        if (top == 0)
            return;
    }
    else {
        *(stack + top++) = col;
        *(label + col) = count;
    }
    Find_Path(Map, stack, label, Num, top, count);
}

int *Breadth_First(int **Map, int Num)
{
    int *queue, *label;
    int pos, count = 0;

    queue = (int *)malloc(Num * sizeof(int));
    label = (int *)malloc(Num * sizeof(int));
    for (pos = 0; pos < Num; pos++)
        *(label + pos) = 0;
    while (true) {
        for (pos = 0; pos < Num; pos++)
            if (*(label + pos) == 0)
                break;
        if (pos == Num)
            break;
        count++;
        *queue = pos;
        *(label + pos) = count;
        Extend_Path(Map, queue, label, Num, count);
    }
    free(queue);

    return label;
}

void Extend_Path(int **Map, int *queue, int *label, int Num, int count)
{
    int front = 0, rear = 1, row, col;

    while (front != rear) {
        row = *(queue + front);
        for (col = 0; col < Num; col++)
            if (*(*(Map + row) + col) && *(label + col) == 0) {
                *(queue + rear++) = col;
                *(label + col) = count;
            }
        front++;
    }
}

void Out_Put(int **Map, int *Array, int Num, int Count)
{
    int pos, count = 1, max = 0;

    for (pos = 0; pos < Num; pos++)
        if (*(Array + pos) > max)
            max = *(Array + pos);
    while (count <= max) {
        for (pos = 0; pos < Num; pos++)
            if (*(Array + pos) == count) {
                printf("{%*d", Count, pos);
                break;
            }
        pos++;
        while (pos < Num) {
            if (*(Array + pos) == count)
                printf(",%*d", Count, pos);
            pos++;
        }
        printf(" }\n");
        count++;
    }
}

void Memory_Clear(int **Map, int Num)
{
    int row;

    for (row = 0; row < Num; row++)
        free(*(Map + row));
    free(Map);
}
