#include <Engine/Container/Public/RedBlackTree.h>

#include <Engine/Core/Public/Macros.h>

#include <stdlib.h>
#include <string.h>

static void ReplaceSubtree(struct lluna_Container_RedBlackTree* Handle, struct lluna_Container_RedBlackTree_Node* Subtree, struct lluna_Container_RedBlackTree_Node* NewSubtree, struct lluna_Container_RedBlackTree_Node* Parent)
{
        if (!Parent)
        {
                Handle->Root = NewSubtree;
        }
        else if (Parent->Left == Subtree)
        {
                Parent->Left = NewSubtree;
        }
        else
        {
                Parent->Right = NewSubtree;
        }
}

static void RotateLeft(struct lluna_Container_RedBlackTree* Handle, struct lluna_Container_RedBlackTree_Node* Node)
{
        struct lluna_Container_RedBlackTree_Node* Pivot = Node->Right;

        Node->Right = Pivot->Left;
        if (Pivot->Left)
        {
                Pivot->Left->Parent = Node;
        }

        ReplaceSubtree(Handle, Node, Pivot, Node->Parent);

        Pivot->Parent = Node->Parent;
        Pivot->Left = Node;

        Node->Parent = Pivot;
}

static void RotateRight(struct lluna_Container_RedBlackTree* Handle, struct lluna_Container_RedBlackTree_Node* Node)
{
        struct lluna_Container_RedBlackTree_Node* Pivot = Node->Left;

        Node->Left = Pivot->Right;
        if (Pivot->Right)
        {
                Pivot->Right->Parent = Node;
        }

        ReplaceSubtree(Handle, Node, Pivot, Node->Parent);

        Pivot->Parent = Node->Parent;
        Pivot->Right= Node;

        Node->Parent = Pivot;
}

static boolean IsBlack(struct lluna_Container_RedBlackTree_Node* Node)
{
        return !Node || Node->Color == lluna_Container_RedBlackTree_Black;
}

static struct lluna_Container_RedBlackTree_Node* Minimum(struct lluna_Container_RedBlackTree_Node* Node)
{
        if (!Node)
        {
                return NULL;
        }

        struct lluna_Container_RedBlackTree_Node* CurrentNode = Node;
        while (CurrentNode->Left)
        {
                CurrentNode = CurrentNode->Left;
        }

        return CurrentNode;
}

static struct lluna_Container_RedBlackTree_Node* Maximum(struct lluna_Container_RedBlackTree_Node* Node)
{
        if (!Node)
        {
                return NULL;
        }

        struct lluna_Container_RedBlackTree_Node* CurrentNode = Node;
        while (CurrentNode->Right)
        {
                CurrentNode = CurrentNode->Right;
        }

        return CurrentNode;
}

static struct lluna_Container_RedBlackTree_Node* Erase(struct lluna_Container_RedBlackTree* Handle, struct lluna_Container_RedBlackTree_Node* Node)
{
        struct lluna_Container_RedBlackTree_Node* Parent = Node->Parent;
        struct lluna_Container_RedBlackTree_Node* FixupTarget = NULL;

        if (!Node->Left)
        {
                ReplaceSubtree(Handle, Node, Node->Right, Parent);
                if (Node->Right)
                {
                        Node->Right->Parent = Parent;
                        Node->Right->Color = Node->Color;
                }
                else if (IsBlack(Node))
                {
                        FixupTarget = Parent;
                }
        }
        else if (!Node->Right)
        {
                ReplaceSubtree(Handle, Node, Node->Left, Parent);
                Node->Left->Parent = Parent;
                Node->Left->Color = Node->Color;
        }
        else
        {
                struct lluna_Container_RedBlackTree_Node* Successor = Minimum(Node->Right);
                struct lluna_Container_RedBlackTree_Node* SuccessorChild = NULL;

                if (Successor == Node->Right)
                {
                        Parent = Successor;
                        SuccessorChild = Successor->Right;
                }
                else
                {
                        Parent = Successor->Parent;
                        SuccessorChild = Successor->Right;

                        Parent->Left = SuccessorChild;
                        Successor->Right = Node->Right;

                        Node->Right->Parent = Successor;
                }

                Successor->Left = Node->Left;
                Node->Left->Parent = Successor;

                ReplaceSubtree(Handle, Node, Successor, Node->Parent);

                if (SuccessorChild)
                {
                        SuccessorChild->Parent = Parent;
                        SuccessorChild->Color = lluna_Container_RedBlackTree_Black;

                        FixupTarget = NULL;
                }
                else if (IsBlack(Successor))
                {
                        FixupTarget = Parent;
                }

                Successor->Parent = Node->Parent;
                Successor->Color = Node->Color;
        }

        return FixupTarget;
}

static void EraseFixup(struct lluna_Container_RedBlackTree* Handle, struct lluna_Container_RedBlackTree_Node* FixupTarget)
{
        struct lluna_Container_RedBlackTree_Node* Node = NULL;
        struct lluna_Container_RedBlackTree_Node* Sibling;
        struct lluna_Container_RedBlackTree_Node* Tmp1;
        struct lluna_Container_RedBlackTree_Node* Tmp2;

        while (true)
        {
                Sibling = FixupTarget->Right;
                if (Node != Sibling)
                {
                        if (!IsBlack(Sibling))
                        {
                                Tmp1 = Sibling->Left;

                                RotateLeft(Handle, FixupTarget);

                                Tmp1->Color = lluna_Container_RedBlackTree_Black;
                                Sibling->Color = FixupTarget->Color;
                                FixupTarget->Color = lluna_Container_RedBlackTree_Red;

                                Sibling = Tmp1;
                        }

                        Tmp1 = Sibling->Right;
                        if (IsBlack(Tmp1))
                        {
                                Tmp2 = Sibling->Left;
                                if (IsBlack(Tmp2))
                                {
                                        Sibling->Parent = FixupTarget;
                                        Sibling->Color = lluna_Container_RedBlackTree_Red;

                                        if (!IsBlack(FixupTarget))
                                        {
                                                FixupTarget->Color = lluna_Container_RedBlackTree_Black;
                                        }
                                        else
                                        {
                                                Node = FixupTarget;
                                                FixupTarget = Node->Parent;
                                                if (FixupTarget)
                                                {
                                                        continue;
                                                }
                                        }
                                        break;
                                }

                                Tmp1 = Tmp2->Right;

                                RotateRight(Handle, Sibling);
                                if (Tmp1)
                                {
                                        Tmp1->Color = lluna_Container_RedBlackTree_Black;
                                }

                                Tmp1 = Sibling;
                                Sibling = Tmp2;
                        }

                        RotateLeft(Handle, FixupTarget);

                        Tmp1->Color = lluna_Container_RedBlackTree_Black;
                        Sibling->Color = FixupTarget->Color;
                        FixupTarget->Color = lluna_Container_RedBlackTree_Black;

                        break;
                }
                else
                {
                        Sibling = FixupTarget->Left;
                        if (!IsBlack(Sibling))
                        {
                                Tmp1 = Sibling->Right;
                                RotateRight(Handle, FixupTarget);


                                Tmp1->Color = lluna_Container_RedBlackTree_Black;
                                Sibling->Color = FixupTarget->Color;
                                FixupTarget->Color = lluna_Container_RedBlackTree_Red;

                                Sibling = Tmp1;
                        }

                        Tmp1 = Sibling->Left;
                        if (IsBlack(Tmp1))
                        {
                                Tmp2 = Sibling->Right;
                                if (IsBlack(Tmp2))
                                {
                                        Sibling->Parent = FixupTarget;
                                        Sibling->Color = lluna_Container_RedBlackTree_Red;

                                        if (!IsBlack(FixupTarget))
                                        {
                                                FixupTarget->Color = lluna_Container_RedBlackTree_Black;
                                        }
                                        else
                                        {
                                                Node = FixupTarget;
                                                FixupTarget = Node->Parent;
                                                if (FixupTarget)
                                                {
                                                        continue;
                                                }
                                        }
                                        break;
                                }

                                Tmp1 = Tmp2->Left;

                                RotateLeft(Handle, Sibling);
                                if (Tmp1)
                                {
                                        Tmp1->Color = lluna_Container_RedBlackTree_Black;
                                }

                                Tmp1 = Sibling;
                                Sibling = Tmp2;
                        }

                        RotateRight(Handle, FixupTarget);

                        Tmp1->Color = lluna_Container_RedBlackTree_Black;
                        Sibling->Color = FixupTarget->Color;
                        FixupTarget->Color = lluna_Container_RedBlackTree_Black;

                        break;
                }
        }
}

static uint64 CountSubtree(struct lluna_Container_RedBlackTree_Node* Node)
{
        if (!Node)
        {
                return 0;
        }

        return CountSubtree(Node->Left) + CountSubtree(Node->Right) + 1;
}

struct lluna_Container_RedBlackTree* lluna_Container_RedBlackTree_Create()
{
        struct lluna_Container_RedBlackTree* Handle = malloc(sizeof(struct lluna_Container_RedBlackTree));
        Handle->Root = NULL;
}

void lluna_Container_RedBlackTree_InitializeNode(struct lluna_Container_RedBlackTree_Node* Node)
{
        Node->Color = lluna_Container_RedBlackTree_Red;

        Node->Parent = NULL;
        Node->Left = NULL;
        Node->Right = NULL;
}

void lluna_Container_RedBlackTree_Destroy(struct lluna_Container_RedBlackTree* Handle)
{
        free(Handle);
}

boolean lluna_Container_RedBlackTree_Empty(struct lluna_Container_RedBlackTree* Handle)
{
        return Handle->Root == NULL;
}

uint64 lluna_Container_RedBlackTree_Count(struct lluna_Container_RedBlackTree* Handle)
{
        return CountSubtree(Handle->Root);
}

struct lluna_Container_RedBlackTree_Node* lluna_Container_RedBlackTree_First(struct lluna_Container_RedBlackTree* Handle)
{
        return Minimum(Handle->Root);
}

struct lluna_Container_RedBlackTree_Node* lluna_Container_RedBlackTree_Last(struct lluna_Container_RedBlackTree* RedBlackTree)
{
        return Maximum(RedBlackTree->Root);
}

struct lluna_Container_RedBlackTree_Node* lluna_Container_RedBlackTree_Next(struct lluna_Container_RedBlackTree_Node* Node)
{
        struct lluna_Container_RedBlackTree_Node* CurrentNode;
        if (Node->Right)
        {
                return Minimum(Node->Right);
        }
        else
        {
                CurrentNode = Node;
                while (CurrentNode->Parent && CurrentNode->Parent->Right == CurrentNode)
                {
                        CurrentNode = CurrentNode->Parent;
                }

                return CurrentNode->Parent;
        }
}

struct lluna_Container_RedBlackTree_Node* lluna_Container_RedBlackTree_Previous(struct lluna_Container_RedBlackTree_Node* Node)
{
        struct lluna_Container_RedBlackTree_Node* CurrentNode;
        if (Node->Left)
        {
                return Maximum(Node->Left);
        }
        else
        {
                CurrentNode = Node;
                while (CurrentNode->Parent && CurrentNode->Parent->Left == CurrentNode)
                {
                        CurrentNode = CurrentNode->Parent;
                }

                return CurrentNode->Parent;
        }
}

void lluna_Container_RedBlackTree_Link(struct lluna_Container_RedBlackTree_Node* Node, struct lluna_Container_RedBlackTree_Node* Parent, struct lluna_Container_RedBlackTree_Node** Link)
{
        Node->Parent = Parent;
        *Link = Node;
}

void lluna_Container_RedBlackTree_InsertFixup(struct lluna_Container_RedBlackTree* Handle, struct lluna_Container_RedBlackTree_Node* FixupTarget)
{
        while (!IsBlack(FixupTarget->Parent))
        {
                if (FixupTarget->Parent == FixupTarget->Parent->Parent->Left)
                {
                        struct lluna_Container_RedBlackTree_Node* Uncle = FixupTarget->Parent->Parent->Right;
                        if (!IsBlack(Uncle))
                        {
                                FixupTarget->Parent->Color = lluna_Container_RedBlackTree_Black;
                                Uncle->Color = lluna_Container_RedBlackTree_Black;
                                FixupTarget->Parent->Parent->Color = lluna_Container_RedBlackTree_Red;

                                FixupTarget = FixupTarget->Parent->Parent;
                                continue;
                        }

                        if (FixupTarget == FixupTarget->Parent->Right)
                        {
                                FixupTarget = FixupTarget->Parent;
                                RotateLeft(Handle, FixupTarget);
                        }

                        FixupTarget->Parent->Color = lluna_Container_RedBlackTree_Black;
                        FixupTarget->Parent->Parent->Color = lluna_Container_RedBlackTree_Red;
                        RotateRight(Handle, FixupTarget->Parent->Parent);
                        break;
                }
                else
                {
                        struct lluna_Container_RedBlackTree_Node* Uncle = FixupTarget->Parent->Parent->Left;
                        if (!IsBlack(Uncle))
                        {
                                FixupTarget->Parent->Color = lluna_Container_RedBlackTree_Black;
                                Uncle->Color = lluna_Container_RedBlackTree_Black;
                                FixupTarget->Parent->Parent->Color = lluna_Container_RedBlackTree_Red;

                                FixupTarget = FixupTarget->Parent->Parent;
                                continue;
                        }

                        if (FixupTarget == FixupTarget->Parent->Left)
                        {
                                FixupTarget = FixupTarget->Parent;
                                RotateRight(Handle, FixupTarget);
                        }

                        FixupTarget->Parent->Color = lluna_Container_RedBlackTree_Black;
                        FixupTarget->Parent->Parent->Color = lluna_Container_RedBlackTree_Red;
                        RotateLeft(Handle, FixupTarget->Parent->Parent);
                        break;
                }
        }

        Handle->Root->Color = lluna_Container_RedBlackTree_Black;
}

void lluna_Container_RedBlackTree_Remove(struct lluna_Container_RedBlackTree* Handle, struct lluna_Container_RedBlackTree_Node* Node)
{
        struct lluna_Container_RedBlackTree_Node* FixupTarget;
        FixupTarget = Erase(Handle, Node);

        if (FixupTarget)
        {
                EraseFixup(Handle, FixupTarget);
        }
}
