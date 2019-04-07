#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *child;
struct Node {
    int Value;
    int Height;
    child Left;
    child Right;
};
typedef struct Node *leaf;

leaf Element_Insert(leaf Root, int Num);
leaf Element_Delete(leaf Root, int Num);
leaf Left_Rotation(leaf Root);
leaf Right_Rotation(leaf Root);
leaf Left_Right(leaf Root);
leaf Right_Left(leaf Root);
int Max_Obtain(int Left, int Right);
int Height_Obtain(leaf Root);
leaf Find_Min(leaf Root);
leaf Find_Max(leaf Root);
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
    if (Root == NULL) {
        Root = (struct Node *)malloc(sizeof(struct Node));
        Root->Value = Num;
        Root->Left = NULL;
        Root->Right = NULL;
    }
    else {
        if (Num < Root->Value) {
            Root->Left = Element_Insert(Root->Left, Num);
            if (Height_Obtain(Root->Left) - Height_Obtain(Root->Right) == 2) {
                if (Num < Root->Left->Value)
                    Root = Left_Rotation(Root);
                else
                    Root = Left_Right(Root);
            }
        }
        else if (Num > Root->Value) {
            Root->Right = Element_Insert(Root->Right, Num);
            if (Height_Obtain(Root->Right) - Height_Obtain(Root->Left) == 2) {
                if (Num > Root->Right->Value)
                    Root = Right_Rotation(Root);
                else
                    Root = Right_Left(Root);
            }
        }
        else
            printf("This element has been in the binary_search_tree!\n");
    }
    Root->Height = Max_Obtain(Height_Obtain(Root->Left), Height_Obtain(Root->Right)) + 1;

    return Root;
}

leaf Element_Delete(leaf Root, int Num)
{
    leaf temp;

    if (Root == NULL)
        printf("There is no such element in the binary_search_tree!\n");
    else if (Num < Root->Value)
        Root->Left = Element_Delete(Root->Left, Num);
    else if (Num > Root->Value)
        Root->Right = Element_Delete(Root->Right, Num);
    else {
        if (Root->Left && Root->Right) {
            if (Height_Obtain(Root->Left) > Height_Obtain(Root->Right)) {
                temp = Find_Max(Root->Left);
                Root->Value = temp->Value;
                Root->Left = Element_Delete(Root->Left, Root->Value);
            }
            else {
                temp = Find_Min(Root->Right);
                Root->Value = temp->Value;
                Root->Right = Element_Delete(Root->Right, Root->Value);
            }
        }
        else {
            temp = Root;
            if (Root->Left == NULL)
                Root = Root->Right;
            else
                Root = Root->Left;
            free(temp);
        }
    }
    if (Root) {
        if (Height_Obtain(Root->Right) - Height_Obtain(Root->Left) == 2) {
            if (Height_Obtain(Root->Right->Right) >= Height_Obtain(Root->Right->Left))
                Root = Right_Rotation(Root);
            else
                Root = Right_Left(Root);
        }
        else if (Height_Obtain(Root->Left) - Height_Obtain(Root->Right) == 2) {
            if (Height_Obtain(Root->Left->Left) >= Height_Obtain(Root->Left->Right))
                Root = Left_Rotation(Root);
            else
                Root = Left_Right(Root);
        }
        Root->Height = Max_Obtain(Height_Obtain(Root->Left), Height_Obtain(Root->Right)) + 1;
    }

    return Root;
}

leaf Left_Rotation(leaf Root)
{
    leaf temp = Root->Left;

    Root->Left = temp->Right;
    temp->Right = Root;
    Root->Height = Max_Obtain(Height_Obtain(Root->Left), Height_Obtain(Root->Right)) + 1;
    temp->Height = Max_Obtain(Height_Obtain(temp->Left), Root->Height) + 1;

    return temp;
}

leaf Right_Rotation(leaf Root)
{
    leaf temp = Root->Right;

    Root->Right = temp->Left;
    temp->Left = Root;
    Root->Height = Max_Obtain(Height_Obtain(Root->Left), Height_Obtain(Root->Right)) + 1;
    temp->Height = Max_Obtain(Height_Obtain(temp->Right), Root->Height) + 1;

    return temp;
}

leaf Left_Right(leaf Root)
{
    Root->Left = Right_Rotation(Root->Left);
    return Left_Rotation(Root);
}

leaf Right_Left(leaf Root)
{
    Root->Right = Left_Rotation(Root->Right);
    return Right_Rotation(Root);
}

int Max_Obtain(int left, int right)
{
    if (left > right)
        return left;
    return right;
}

int Height_Obtain(leaf Root)
{
    if (Root)
        return Root->Height;
    return -1;
}

leaf Find_Min(leaf Root)
{
    while (Root->Left)
        Root = Root->Left;
    
    return Root;
}

leaf Find_Max(leaf Root)
{
    while (Root->Right)
        Root = Root->Right;
    
    return Root;
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
