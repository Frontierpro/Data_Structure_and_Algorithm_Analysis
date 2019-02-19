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

void Build_Tree(int *Preorder, int *Inorder, int Num);
int Num_Count(int Num);
leaf Postfix_Order(int *Preorder, int *Inorder, int Num);
void Postorder_Traversal(leaf Root, int Count);
void Out_Put(int *Tree, int Num, int Count);
void Memory_Clear(leaf Root);

int main(void)
{
    int Num, Count;
    int *Preorder, *Inorder;
    leaf Root;

    printf("Enter the number of nodes (positive) in the binary tree: ");
    scanf("%d", &Num);
    Preorder = (int *)malloc(Num * sizeof(int));
    Inorder = (int *)malloc(Num * sizeof(int));
    Build_Tree(Preorder, Inorder, Num);
    Count = Num_Count(Num);

    printf("The preorder of the random_created binary tree is as follows.\n");
    Out_Put(Preorder, Num, Count + 1);
    printf("The inorder of the random_created binary tree is as follows.\n");
    Out_Put(Inorder, Num, Count + 1);
    Root = Postfix_Order(Preorder, Inorder, Num);
    printf("The postorder obtained from preorder and inorder is as follows.\n");
    Postorder_Traversal(Root, Count + 1);
    putchar('\n');

    printf("Press ENTER to quit.\n");
    free(Preorder);
    free(Inorder);
    Memory_Clear(Root);
    getchar();
    getchar();

    return 0;
}

void Build_Tree(int *Preorder, int *Inorder, int Num)
{
    int *stack;
    int top = 0, front = 0, rear = 0, pos = 0;

    stack = (int *)malloc(Num * sizeof(int));
    for (rear = 0; rear < Num; rear++)
        *(Preorder + rear) = rear + 1;
    *(stack + top++) = *(Preorder + front++);
    srand((int)time(NULL));
    while (top != 0 || front < rear) {
        if (top == 0)
            *(stack + top++) = *(Preorder + front++);
        else {
            if (front < rear && rand() % 2)
                *(stack + top++) = *(Preorder + front++);
            else {
                top--;
                *(Inorder + pos++) = *(stack + top);
            }
        }
    }
    free(stack);
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

leaf Postfix_Order(int *Preorder, int *Inorder, int Num)
{
    int pos;
    leaf temp;

    if (Num == 0)
        return NULL;
    for (pos = 0; pos < Num; pos++)
        if (*(Inorder + pos) == *Preorder)
            break;
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->Left = Postfix_Order(Preorder + 1, Inorder, pos);
    temp->Right = Postfix_Order(Preorder + pos + 1, Inorder + pos + 1, Num - pos - 1);
    temp->Value = *(Inorder + pos);

    return temp;
}

void Postorder_Traversal(leaf Root, int Count)
{
    if (Root) {
        Postorder_Traversal(Root->Left, Count);
        Postorder_Traversal(Root->Right, Count);
        printf("%-*d", Count, Root->Value);
    }
}

void Out_Put(int *Tree, int Num, int Count)
{
    int pos;

    for (pos = 0; pos < Num; pos++)
        printf("%-*d", Count, *(Tree + pos));
    putchar('\n');
}

void Memory_Clear(leaf Root)
{
    if (Root) {
        Memory_Clear(Root->Left);
        Memory_Clear(Root->Right);
        free(Root);
    }
}
