#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node *child;
struct Node {
    int Value;
    child Left;
    child Right;
};
typedef child leaf;

leaf Build_Tree(int Num);
void Element_Create(int *Element, int Num);
int Byte_Count(int Num);
void Out_Put(int *Element, int Num, int Count);
void Quick_Sort(int *Element, int Num);
int Sort_Order(const void *left, const void *right);
int *Number_Insert(leaf Root, int *Element);
void Levelorder_Traversal(leaf Root, int Num);
void Memory_Clear(leaf Root);

int main(void)
{
    int Num, Count;
    int *Element;
    leaf Root;

    printf("Enter the number of nodes (positive) in the binary_search_tree: ");
    scanf("%d", &Num);
    Element = (int *)malloc(Num * sizeof(int));
    Root = Build_Tree(Num);
    printf("The binary_search_tree has been built.\n");
    printf("And the shape of the tree can not be changed.\n");
    Element_Create(Element, Num);
    Count = Byte_Count(Num);
    printf("The elements should be inserted into the tree are as follows.\n");
    Out_Put(Element, Num, Count + 2);

    Quick_Sort(Element, Num);
    Element = Number_Insert(Root, Element) - Num;
    printf("The random_created binary_search_tree is as follows.\n");
    Levelorder_Traversal(Root, Num);

    printf("Press ENTER to quit.\n");
    free(Element);
    Memory_Clear(Root);
    getchar();
    getchar();

    return 0;
}

leaf Build_Tree(int Num)
{
    int count, pos, temp, left = 0, right = 0;
    int *node;
    leaf head = NULL;
    leaf *tail;

    node = (int *)malloc(2 * Num * sizeof(int));
    for (count = 0; count < 2 * Num; count++)
        *(node + count) = count;
    tail = (leaf *)malloc(Num * sizeof(leaf));
    srand((int)time(NULL));
    for (count = 0; count < Num; count++) {
        *(tail + count) = (struct Node *)malloc(sizeof(struct Node));
        (*(tail + count))->Left = NULL;
        (*(tail + count))->Right = NULL;
        if (head == NULL)
            head = *(tail + count);
        else {
            pos = rand() % (right - left) + left;
            temp = *(node + pos);
            if (temp % 2)
                (*(tail + temp / 2))->Right = *(tail + count);
            else
                (*(tail + temp / 2))->Left = *(tail + count);
            *(node + pos) = *(node + left);
            *(node + left++) = temp;
        }
        right += 2;
    }
    free(node);

    return head;
}

void Element_Create(int *Element, int Num)
{
    int *node;
    int pos, right, temp;

    node = (int *)malloc(10 * Num * sizeof(int));
    for (pos = 0; pos < 10 * Num; pos++)
        *(node + pos) = pos + 1;
    srand((int)time(NULL));
    for (pos = 0; pos < Num; pos++) {
        right = rand() % (10 * Num - pos) + pos;
        temp = *(node + right);
        *(node + right) = *(node + pos);
        *(node + pos) = *(Element + pos) = temp;
    }
    free(node);
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

void Out_Put(int *Element, int Num, int Count)
{
    int pos;

    for (pos = 0; pos < Num; pos++)
        printf("%-*d", Count, *(Element + pos));
    putchar('\n');
}

void Quick_Sort(int *Element, int Num)
{
    qsort(Element, Num, sizeof(Element[0]), Sort_Order);
}

int Sort_Order(const void *left, const void *right)
{
    return (*(int *)left - *(int *)right);
}

int *Number_Insert(leaf Root, int *Element)
{
    if (Root) {
        Element = Number_Insert(Root->Left, Element);
        Root->Value = *(Element++);
        Element = Number_Insert(Root->Right, Element);
    }

    return Element;
}

void Levelorder_Traversal(leaf Root, int Num)
{
    int front = 0, rear = 0;
    leaf temp = Root;
    leaf *queue;

    queue = (leaf *)malloc(Num * sizeof(leaf));
    *(queue + rear++) = temp;
    while (front < rear) {
        printf("%-10d", temp->Value);
        if (temp->Left) {
            printf("%10d->%-10d", temp->Value, temp->Left->Value);
            *(queue + rear++) = temp->Left;
        }
        else
            printf("%10d->NULL      ", temp->Value);
        if (temp->Right) {
            printf("%10d->%d", temp->Value, temp->Right->Value);
            *(queue + rear++) = temp->Right;
        }
        else
            printf("%10d->NULL", temp->Value);
        putchar('\n');
        front++;
        temp = *(queue + front);
    }
    free(queue);
}

void Memory_Clear(leaf Root)
{
    if (Root) {
        Memory_Clear(Root->Left);
        Memory_Clear(Root->Right);
        free(Root);
    }
}
