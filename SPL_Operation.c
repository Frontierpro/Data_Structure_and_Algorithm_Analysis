#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *child;
typedef struct Node *parent;
struct Node {
    int Value;
    child Left;
    child Right;
    parent Top;
};
typedef struct Node *leaf;

leaf Element_Insert(leaf Root, int Num);
leaf Element_Delete(leaf Root, int Num);
leaf Find_Min(leaf Root);
leaf Splay_Rotation(leaf temp);
leaf Left_Rotation(leaf Root);
leaf Right_Rotation(leaf Root);
leaf Left_Left(leaf Root);
leaf Left_Right(leaf Root);
leaf Right_Right(leaf Root);
leaf Right_Left(leaf Root);
void Levelorder_Traversal(leaf Root);
void Memory_Clear(leaf Root);

int main(void)
{
    leaf Root = NULL;
    int Num;
    char *Command;

    Command = (char *)malloc(10 * sizeof(char));
    printf("Enter \"insert\", \"delete\", \"query\" or \"quit\" command!\n");
    printf("Enter command: ");
    scanf("%s", Command);
    while (strcmp(Command, "quit")) {
        if (strcmp(Command, "insert") == 0) {
            scanf("%d", &Num);
            Root = Element_Insert(Root, Num);
        }
        else if (strcmp(Command, "delete") == 0) {
            scanf("%d", &Num);
            Root = Element_Delete(Root, Num);
        }
        else if (strcmp(Command, "query") == 0) {
            if (Root) {
                printf("The binary_search_tree is as follows.\n");
                Levelorder_Traversal(Root);
            }
            else
                printf("The binary_search_tree is empty!\n");
        }
        else
            printf("Enter \"insert\", \"delete\", \"query\" or \"quit\" command!\n");
        printf("Enter command: ");
        scanf("%s", Command);
    }
    free(Command);
    Memory_Clear(Root);

    return 0;
}

leaf Element_Insert(leaf Root, int Num)
{
    leaf temp = Root, top = NULL;

    while (temp) {
        top = temp;
        if (Num < top->Value)
            temp = top->Left;
        else if (Num > top->Value)
            temp = top->Right;
        else {
            printf("This element has been in the binary_search_tree!\n");
            return Root;
        }
    }
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->Value = Num;
    temp->Left = NULL;
    temp->Right = NULL;
    temp->Top = top;
    if (top) {
        if (top->Value > temp->Value)
            top->Left = temp;
        else
            top->Right = temp;
    }
    Root = Splay_Rotation(temp);

    return Root;
}

leaf Element_Delete(leaf Root, int Num)
{
    leaf temp = Root, min;
    int flag = 1;

    while (temp) {
        if (Num < temp->Value)
            temp = temp->Left;
        else if (Num > temp->Value)
            temp = temp->Right;
        else {
            if (flag) {
                Root = Splay_Rotation(temp);
                temp = Root;
                flag = 0;
            }
            if (temp->Left && temp->Right) {
                min = Find_Min(temp->Right);
                temp->Value = min->Value;
                Num = temp->Value;
                temp = min;
                continue;
            }
            else if (temp->Left) {
                temp->Left->Top = temp->Top;
                if (temp->Top) {
                    if (temp->Top->Left == temp)
                        temp->Top->Left = temp->Left;
                    else
                        temp->Top->Right = temp->Left;
                }
                else
                    Root = temp->Left;
                free(temp);
            }
            else if (temp->Right) {
                temp->Right->Top = temp->Top;
                if (temp->Top) {
                    if (temp->Top->Left == temp)
                        temp->Top->Left = temp->Right;
                    else
                        temp->Top->Right = temp->Right;
                }
                else
                    Root = temp->Right;
                free(temp);
            }
            else {
                if (temp == Root)
                    Root = NULL;
                else if (temp->Top->Left == temp)
                    temp->Top->Left = NULL;
                else
                    temp->Top->Right = NULL;
                free(temp);
            }
            return Root;
        }
    }
    printf("There is no such element in the binary_search_tree!\n");

    return Root;
}

leaf Find_Min(leaf Root)
{
    while (Root->Left)
        Root = Root->Left;

    return Root;
}

leaf Splay_Rotation(leaf temp)
{
    leaf top;

    while (temp->Top) {
        if (temp->Top->Top == NULL) {
            if (temp->Top->Value > temp->Value)
                temp = Left_Rotation(temp->Top);
            else
                temp = Right_Rotation(temp->Top);
            temp->Top = NULL;
        }
        else {
            top = temp->Top->Top->Top;
            if (temp->Top->Top->Value > temp->Top->Value && temp->Top->Value > temp->Value)
                temp = Left_Left(temp->Top->Top);
            else if (temp->Top->Top->Value > temp->Top->Value && temp->Top->Value < temp->Value)
                temp = Left_Right(temp->Top->Top);
            else if (temp->Top->Top->Value < temp->Top->Value && temp->Top->Value < temp->Value)
                temp = Right_Right(temp->Top->Top);
            else
                temp = Right_Left(temp->Top->Top);
            temp->Top = top;
            if (top) {
                if (top->Value > temp->Value)
                    top->Left = temp;
                else
                    top->Right = temp;
            }
        }
    }

    return temp;
}

leaf Left_Rotation(leaf Root)
{
    leaf temp = Root->Left;

    Root->Left = temp->Right;
    if (temp->Right)
        temp->Right->Top = Root;
    temp->Right = Root;
    Root->Top = temp;

    return temp;
}

leaf Right_Rotation(leaf Root)
{
    leaf temp = Root->Right;

    Root->Right = temp->Left;
    if (temp->Left)
        temp->Left->Top = Root;
    temp->Left = Root;
    Root->Top = temp;

    return temp;
}

leaf Left_Left(leaf Root)
{
    Root = Left_Rotation(Root);

    return Left_Rotation(Root);
}

leaf Right_Right(leaf Root)
{
    Root = Right_Rotation(Root);

    return Right_Rotation(Root);
}

leaf Left_Right(leaf Root)
{
    Root->Left = Right_Rotation(Root->Left);
    Root->Left->Top = Root;

    return Left_Rotation(Root);
}

leaf Right_Left(leaf Root)
{
    Root->Right = Left_Rotation(Root->Right);
    Root->Right->Top = Root;

    return Right_Rotation(Root);
}

void Levelorder_Traversal(leaf Root)
{
    int front = 0, rear = 0;
    leaf temp = Root;
    leaf *queue;

    queue = (leaf *)malloc(100 * sizeof(leaf));
    if (temp)
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
            printf("%10d->%-10d", temp->Value, temp->Right->Value);
            *(queue + rear++) = temp->Right;
        }
        else
            printf("%10d->NULL      ", temp->Value);
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
