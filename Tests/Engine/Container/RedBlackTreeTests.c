#include <TestHelper.h>

#include <Engine/Container/Public/RedBlackTree.h>

struct lluna_TestHelper_Session SessionState;

static void Create();
static void InitializeNode();
static void Destroy();
static void Empty();
static void Count();
static void First();
static void Last();
static void Next();
static void Previous();
static void Insert();
static void Remove();
static void ForEach();
static void ReversedForEach();

int main(int argc, const char* argv[])
{
        lluna_TestHelper_StartSession(&SessionState, "lluna_Container_RedBlackTree");

        lluna_TestHelper_RunTest(&SessionState, Create);
        lluna_TestHelper_RunTest(&SessionState, InitializeNode);
        lluna_TestHelper_RunTest(&SessionState, Destroy);
        lluna_TestHelper_RunTest(&SessionState, Empty);
        lluna_TestHelper_RunTest(&SessionState, Count);
        lluna_TestHelper_RunTest(&SessionState, First);
        lluna_TestHelper_RunTest(&SessionState, Last);
        lluna_TestHelper_RunTest(&SessionState, Next);
        lluna_TestHelper_RunTest(&SessionState, Previous);
        lluna_TestHelper_RunTest(&SessionState, Insert);
        lluna_TestHelper_RunTest(&SessionState, Remove);
        lluna_TestHelper_RunTest(&SessionState, ForEach);
        lluna_TestHelper_RunTest(&SessionState, ReversedForEach);

        lluna_TestHelper_FinishSession(&SessionState);
}

struct Holder
{
        uint32 Data;

        struct lluna_Container_RedBlackTree_Node RedBlackTree;
};

static void InsertHolder(struct lluna_Container_RedBlackTree* Handle, struct Holder* Node)
{
        lluna_Container_RedBlackTree_InitializeNode(&Node->RedBlackTree);

        if (!Handle->Root)
        {
                Node->RedBlackTree.Color = lluna_Container_RedBlackTree_Black;
                Handle->Root = &Node->RedBlackTree;
                return;
        }

        struct lluna_Container_RedBlackTree_Node** Link = &Handle->Root;
        struct lluna_Container_RedBlackTree_Node* Parent = NULL;
        while (*Link)
        {
                Parent = *Link;
                if (Node->Data < lluna_Macros_ContainerOf(*Link, struct Holder, RedBlackTree)->Data)
                {
                        Link = &((*Link)->Left);
                }
                else
                {
                        Link = &((*Link)->Right);
                }
        }

        lluna_Container_RedBlackTree_Link(&Node->RedBlackTree, Parent, Link);
        lluna_Container_RedBlackTree_InsertFixup(Handle, &Node->RedBlackTree);
}

static uint32 BlackHeight(struct lluna_Container_RedBlackTree_Node* Node)
{
        if (!Node)
        {
                return 1;
        }

        return BlackHeight(Node->Left) + (Node->Color == lluna_Container_RedBlackTree_Black ? 1 : 0);
}

static void Create()
{
        struct lluna_Container_RedBlackTree* RedBlackTree = lluna_Container_RedBlackTree_Create();

        lluna_TestHelper_CheckNotEqual(RedBlackTree, NULL, &SessionState, "Create returned NULL.");
        lluna_TestHelper_CheckEqual(RedBlackTree->Root, NULL, &SessionState, "Create did not set Root to NULL.");

        lluna_Container_RedBlackTree_Destroy(RedBlackTree);
}

static void InitializeNode()
{
        struct lluna_Container_RedBlackTree_Node Node;

        lluna_Container_RedBlackTree_InitializeNode(&Node);

        lluna_TestHelper_CheckEqual(Node.Color, lluna_Container_RedBlackTree_Red, &SessionState, "InitializeNode did not set Color to red.");
        lluna_TestHelper_CheckEqual(Node.Parent, NULL, &SessionState, "InitializeNode did not set Parent to NULL.");
        lluna_TestHelper_CheckEqual(Node.Left, NULL, &SessionState, "InitializeNode did not set Left to NULL.");
        lluna_TestHelper_CheckEqual(Node.Right, NULL, &SessionState, "InitializeNode did not set Right to NULL.");
}

static void Destroy()
{
        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        lluna_Container_RedBlackTree_Destroy(Handle);

        // TODO Check if the memory was properly freed. Waiting on custom allocators.
}

static void Empty()
{
        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        lluna_TestHelper_CheckTrue(lluna_Container_RedBlackTree_Empty(Handle), &SessionState, "Empty did not return true for empty tree.");

        struct Holder* CurrentHolder = malloc(sizeof(struct Holder));
        CurrentHolder->Data = 3;

        InsertHolder(Handle, CurrentHolder);

        lluna_TestHelper_CheckFalse(lluna_Container_RedBlackTree_Empty(Handle), &SessionState, "Empty did not return false for non-empty tree.");

        free(CurrentHolder);
        lluna_Container_RedBlackTree_Destroy(Handle);
}

static void Count()
{
        uint32 Data[] = { 50, 15, 68, 5, 75, 6, 1, 2, 8, 10 };
        uint32 First = 1;
        uint64 ElementCount = sizeof(Data) / sizeof(Data[0]);
        struct Holder** Holders = malloc(ElementCount * sizeof(struct Holder*));

        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        lluna_TestHelper_CheckEqual(lluna_Container_RedBlackTree_Count(Handle), 0, &SessionState, "Count did not return zero for empty tree.");

        for (uint64 i = 0; i < ElementCount; ++i)
        {
                struct Holder* CurrentHolder = malloc(sizeof(struct Holder));
                CurrentHolder->Data = Data[i];

                Holders[i] = CurrentHolder;

                InsertHolder(Handle, CurrentHolder);

                lluna_TestHelper_CheckEqual(lluna_Container_RedBlackTree_Count(Handle), i + 1, &SessionState, "Count did not return the correct number of nodes.");
        }


        lluna_Container_RedBlackTree_Destroy(Handle);
        for (uint64 i = 0; i < ElementCount; ++i)
        {
                free(Holders[i]);
        }
        free(Holders);
}

static void First()
{
        uint32 Data[] = { 50, 15, 68, 5, 75, 6, 1, 2, 8, 10 };
        uint32 First = 1;
        uint64 ElementCount = sizeof(Data) / sizeof(Data[0]);
        struct Holder** Holders = malloc(ElementCount * sizeof(struct Holder*));

        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        for (uint64 i = 0; i < ElementCount; ++i)
        {
                struct Holder* CurrentHolder = malloc(sizeof(struct Holder));
                CurrentHolder->Data = Data[i];

                Holders[i] = CurrentHolder;

                InsertHolder(Handle, CurrentHolder);
        }

        lluna_TestHelper_CheckEqual(lluna_Macros_ContainerOf(lluna_Container_RedBlackTree_First(Handle), struct Holder, RedBlackTree)->Data, First, &SessionState, "First did not return the proper node.")

        lluna_Container_RedBlackTree_Destroy(Handle);
        for (uint64 i = 0; i < ElementCount; ++i)
        {
                free(Holders[i]);
        }
        free(Holders);
}

static void Last()
{
        uint32 Data[] = { 50, 15, 68, 5, 75, 6, 1, 2, 8, 10 };
        uint32 Last = 75;
        uint64 ElementCount = sizeof(Data) / sizeof(Data[0]);
        struct Holder** Holders = malloc(ElementCount * sizeof(struct Holder*));

        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        for (uint64 i = 0; i < ElementCount; ++i)
        {
                struct Holder* CurrentHolder = malloc(sizeof(struct Holder));
                CurrentHolder->Data = Data[i];

                Holders[i] = CurrentHolder;

                InsertHolder(Handle, CurrentHolder);
        }

        lluna_TestHelper_CheckEqual(lluna_Macros_ContainerOf(lluna_Container_RedBlackTree_Last(Handle), struct Holder, RedBlackTree)->Data, Last, &SessionState, "Last did not return the proper node.")

        lluna_Container_RedBlackTree_Destroy(Handle);
        for (uint64 i = 0; i < ElementCount; ++i)
        {
                free(Holders[i]);
        }
        free(Holders);
}

static void Next()
{
        uint32 Data[] = { 50, 15, 68, 5, 75, 6, 1, 2, 8, 10 };
        uint32 OrderedData[] = { 1, 2, 5, 6, 8, 10, 15, 50, 68, 75 };
        uint64 ElementCount = sizeof(Data) / sizeof(Data[0]);
        struct Holder** Holders = malloc(ElementCount * sizeof(struct Holder*));

        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        for (uint64 i = 0; i < ElementCount; ++i)
        {
                struct Holder* CurrentHolder = malloc(sizeof(struct Holder));
                CurrentHolder->Data = Data[i];

                Holders[i] = CurrentHolder;

                InsertHolder(Handle, CurrentHolder);
        }

        struct lluna_Container_RedBlackTree_Node* Node = lluna_Container_RedBlackTree_First(Handle);
        for (uint64 i = 0; i < ElementCount; ++i)
        {
                lluna_TestHelper_CheckEqual(lluna_Macros_ContainerOf(Node, struct Holder, RedBlackTree)->Data, OrderedData[i], &SessionState, "Next did not return the correct value.");
                Node = lluna_Container_RedBlackTree_Next(Node);
        }

        lluna_Container_RedBlackTree_Destroy(Handle);
        for (uint64 i = 0; i < ElementCount; ++i)
        {
                free(Holders[i]);
        }
        free(Holders);
}

static void Previous()
{
        uint32 Data[] = { 50, 15, 68, 5, 75, 6, 1, 2, 8, 10 };
        uint32 OrderedData[] = { 1, 2, 5, 6, 8, 10, 15, 50, 68, 75 };
        uint64 ElementCount = sizeof(Data) / sizeof(Data[0]);
        struct Holder** Holders = malloc(ElementCount * sizeof(struct Holder*));

        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        for (uint64 i = 0; i < ElementCount; ++i)
        {
                struct Holder* CurrentHolder = malloc(sizeof(struct Holder));
                CurrentHolder->Data = Data[i];

                Holders[i] = CurrentHolder;

                InsertHolder(Handle, CurrentHolder);
        }

        struct lluna_Container_RedBlackTree_Node* Node = lluna_Container_RedBlackTree_Last(Handle);
        for (int64 i = ElementCount - 1; i >= 0; --i)
        {
                lluna_TestHelper_CheckEqual(lluna_Macros_ContainerOf(Node, struct Holder, RedBlackTree)->Data, OrderedData[i], &SessionState, "Previous did not return the correct value.");
                Node = lluna_Container_RedBlackTree_Previous(Node);
        }

        lluna_Container_RedBlackTree_Destroy(Handle);
        for (uint64 i = 0; i < ElementCount; ++i)
        {
                free(Holders[i]);
        }
        free(Holders);
}

static void Insert()
{
        uint32 Data[] = { 640, 1, 2, 3, 6, 7, 8, 9, 10, 11, 14, 15, 270, 17, 19, 20, 21, 22, 280, 25, 26, 28, 30, 31, 32, 34, 35, 930, 38, 39, 40, 170, 43, 44, 46, 48, 49, 50, 51, 53, 54, 55, 58, 59, 60, 64, 65, 66, 450, 69, 71, 72, 75, 79, 80, 81, 82, 84, 85, 86, 470, 89, 92, 93, 94, 95, 96, 97, 99, 230, 620 };
        uint64 ElementCount = sizeof(Data) / sizeof(Data[0]);
        struct Holder** Holders = malloc(ElementCount * sizeof(struct Holder*));

        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        for (uint64 i = 0; i < ElementCount; ++i)
        {
                struct Holder* CurrentHolder = malloc(sizeof(struct Holder));
                CurrentHolder->Data = Data[i];

                Holders[i] = CurrentHolder;

                uint32 OldBlackHeight = BlackHeight(Handle->Root);
                InsertHolder(Handle, CurrentHolder);
                uint32 NewBlackHeight = BlackHeight(Handle->Root);

                lluna_TestHelper_CheckEqual(lluna_Container_RedBlackTree_Count(Handle), i + 1, &SessionState, "The tree did not have the correct number of nodes after insert.");

                int32 Delta = NewBlackHeight - OldBlackHeight;
                lluna_TestHelper_CheckTrue(Delta == 0 || Delta == 1, &SessionState, "Insertion changed black height by something other than 1.");

                lluna_TestHelper_CheckEqual(Handle->Root->Color, lluna_Container_RedBlackTree_Black, &SessionState, "The root of the tree was not black.");

                struct lluna_Container_RedBlackTree_Node* Iterator;
                lluna_Container_RedBlackTree_ForEach(Handle, Iterator)
                {
                        lluna_TestHelper_CheckTrue(Iterator->Color == lluna_Container_RedBlackTree_Black || Iterator->Color == lluna_Container_RedBlackTree_Red, &SessionState, "A node was not black or red.");

                        if (Iterator->Color == lluna_Container_RedBlackTree_Red)
                        {
                                lluna_TestHelper_CheckTrue(!Iterator->Left || Iterator->Left->Color == lluna_Container_RedBlackTree_Black, &SessionState, "A red node had red children.");
                                lluna_TestHelper_CheckTrue(!Iterator->Right || Iterator->Right->Color == lluna_Container_RedBlackTree_Black, &SessionState, "A red node had red children.");
                        }
                }
        }

        lluna_Container_RedBlackTree_Destroy(Handle);
        for (uint64 i = 0; i < ElementCount; ++i)
        {
                free(Holders[i]);
        }
        free(Holders);
}

static void Remove()
{
        uint32 Data[] = { 640, 1, 2, 3, 6, 7, 8, 9, 10, 11, 14, 15, 270, 17, 19, 20, 21, 22, 280, 25, 26, 28, 30, 31, 32, 34, 35, 930, 38, 39, 40, 170, 43, 44, 46, 48, 49, 50, 51, 53, 54, 55, 58, 59, 60, 64, 65, 66, 450, 69, 71, 72, 75, 79, 80, 81, 82, 84, 85, 86, 470, 89, 92, 93, 94, 95, 96, 97, 99, 230, 620 };
        uint32 DeletionIndices[] = { 46, 64, 49, 0, 41, 8, 1, 7, 13, 60, 29, 65, 59, 32, 31, 52, 14, 5, 12, 68, 37, 4, 47, 33, 48, 69, 3, 16, 50, 35, 66, 40, 62, 44, 36, 10, 57, 27, 56, 9, 20, 58, 22, 2, 6, 26, 25, 17, 70, 45, 21, 43, 38, 63, 55, 28, 23, 39, 53, 42, 34, 18, 54, 24, 30, 61, 11, 51, 15, 67, 19 };
        uint64 ElementCount = sizeof(Data) / sizeof(Data[0]);
        struct Holder** Holders = malloc(ElementCount * sizeof(struct Holder*));

        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        for (uint64 i = 0; i < ElementCount; ++i)
        {
                struct Holder* CurrentHolder = malloc(sizeof(struct Holder));
                CurrentHolder->Data = Data[i];

                Holders[i] = CurrentHolder;

                InsertHolder(Handle, CurrentHolder);
        }

        for (uint64 i = 0; i < ElementCount; ++i)
        {
                uint32 OldBlackHeight = BlackHeight(Handle->Root);
                lluna_Container_RedBlackTree_Remove(Handle, &Holders[DeletionIndices[i]]->RedBlackTree);
                uint32 NewBlackHeight = BlackHeight(Handle->Root);

                lluna_TestHelper_CheckEqual(lluna_Container_RedBlackTree_Count(Handle), ElementCount - 1 - i, &SessionState, "The tree did not have the correct number of nodes after remove.");

                int32 Delta = NewBlackHeight - OldBlackHeight;
                lluna_TestHelper_CheckTrue(Delta == 0 || Delta == -1, &SessionState, "Insertion changed black height by something other than -1.");

                lluna_TestHelper_CheckTrue(!Handle->Root || Handle->Root->Color == lluna_Container_RedBlackTree_Black, &SessionState, "The root of the tree was not black.");

                struct lluna_Container_RedBlackTree_Node* Iterator;
                lluna_Container_RedBlackTree_ForEach(Handle, Iterator)
                {
                        lluna_TestHelper_CheckTrue(Iterator->Color == lluna_Container_RedBlackTree_Black || Iterator->Color == lluna_Container_RedBlackTree_Red, &SessionState, "A node was not black or red.");

                        if (Iterator->Color == lluna_Container_RedBlackTree_Red)
                        {
                                lluna_TestHelper_CheckTrue(!Iterator->Left || Iterator->Left->Color == lluna_Container_RedBlackTree_Black, &SessionState, "A red node had red children.");
                                lluna_TestHelper_CheckTrue(!Iterator->Right || Iterator->Right->Color == lluna_Container_RedBlackTree_Black, &SessionState, "A red node had red children.");
                        }
                }
        }

        lluna_Container_RedBlackTree_Destroy(Handle);
        for (uint64 i = 0; i < ElementCount; ++i)
        {
                free(Holders[i]);
        }
        free(Holders);
}

static void ForEach()
{
        uint32 Data[] = { 50, 15, 68, 5, 75, 6, 1, 2, 8, 10 };
        uint32 OrderedData[] = { 1, 2, 5, 6, 8, 10, 15, 50, 68, 75 };
        uint64 ElementCount = sizeof(Data) / sizeof(Data[0]);
        struct Holder** Holders = malloc(ElementCount * sizeof(struct Holder*));

        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        for (uint64 i = 0; i < ElementCount; ++i)
        {
                struct Holder* CurrentHolder = malloc(sizeof(struct Holder));
                CurrentHolder->Data = Data[i];

                Holders[i] = CurrentHolder;

                InsertHolder(Handle, CurrentHolder);
        }

        struct lluna_Container_RedBlackTree_Node* Iterator;
        uint64 i = 0;
        lluna_Container_RedBlackTree_ForEach(Handle, Iterator)
        {
                lluna_TestHelper_CheckEqual(lluna_Macros_ContainerOf(Iterator, struct Holder, RedBlackTree)->Data, OrderedData[i], &SessionState, "ForEach did not retrieve the correct pointer.");
                ++i;
        }

        lluna_Container_RedBlackTree_Destroy(Handle);
        for (uint64 i = 0; i < ElementCount; ++i)
        {
                free(Holders[i]);
        }
        free(Holders);
}

static void ReversedForEach()
{
        uint32 Data[] = { 50, 15, 68, 5, 75, 6, 1, 2, 8, 10 };
        uint32 OrderedData[] = { 1, 2, 5, 6, 8, 10, 15, 50, 68, 75 };
        uint64 ElementCount = sizeof(Data) / sizeof(Data[0]);
        struct Holder** Holders = malloc(ElementCount * sizeof(struct Holder*));

        struct lluna_Container_RedBlackTree* Handle = lluna_Container_RedBlackTree_Create();

        for (uint64 i = 0; i < ElementCount; ++i)
        {
                struct Holder* CurrentHolder = malloc(sizeof(struct Holder));
                CurrentHolder->Data = Data[i];

                Holders[i] = CurrentHolder;

                InsertHolder(Handle, CurrentHolder);
        }

        struct lluna_Container_RedBlackTree_Node* Iterator;
        uint64 i = ElementCount - 1;
        lluna_Container_RedBlackTree_ReversedForEach(Handle, Iterator)
        {
                lluna_TestHelper_CheckEqual(lluna_Macros_ContainerOf(Iterator, struct Holder, RedBlackTree)->Data, OrderedData[i], &SessionState, "ReversedForEach did not retrieve the correct pointer.");
                --i;
        }

        lluna_Container_RedBlackTree_Destroy(Handle);
        for (uint64 i = 0; i < ElementCount; ++i)
        {
                free(Holders[i]);
        }
        free(Holders);
}
