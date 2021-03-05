#include <TestHelper.h>

#include <Engine/Container/Public/DynamicArray.h>

#include <string.h>

struct lluna_TestHelper_Session SessionState;

static void Create();
static void CreateFromData();
static void Destroy();
static void Empty();
static void Count();
static void Capacity();
static void Resize();
static void Shrink();
static void First();
static void Last();
static void Get();
static void Append();
static void Prepend();
static void Insert();
static void Remove();
static void RemoveStable();
static void RemoveFirst();
static void RemoveLast();
static void Clear();
static void ForEach();
static void ReversedForEach();

int main(int argc, const char* argv[])
{
        lluna_TestHelper_StartSession(&SessionState, "lluna_Container_DynamicArray");

        lluna_TestHelper_RunTest(&SessionState, Create);
        lluna_TestHelper_RunTest(&SessionState, CreateFromData);
        lluna_TestHelper_RunTest(&SessionState, Destroy);
        lluna_TestHelper_RunTest(&SessionState, Empty);
        lluna_TestHelper_RunTest(&SessionState, Count);
        lluna_TestHelper_RunTest(&SessionState, Capacity);
        lluna_TestHelper_RunTest(&SessionState, Resize);
        lluna_TestHelper_RunTest(&SessionState, Shrink);
        lluna_TestHelper_RunTest(&SessionState, First);
        lluna_TestHelper_RunTest(&SessionState, Last);
        lluna_TestHelper_RunTest(&SessionState, Get);
        lluna_TestHelper_RunTest(&SessionState, Append);
        lluna_TestHelper_RunTest(&SessionState, Prepend);
        lluna_TestHelper_RunTest(&SessionState, Insert);
        lluna_TestHelper_RunTest(&SessionState, Remove);
        lluna_TestHelper_RunTest(&SessionState, RemoveStable);
        lluna_TestHelper_RunTest(&SessionState, RemoveFirst);
        lluna_TestHelper_RunTest(&SessionState, RemoveLast);
        lluna_TestHelper_RunTest(&SessionState, Clear);
        lluna_TestHelper_RunTest(&SessionState, ForEach);
        lluna_TestHelper_RunTest(&SessionState, ReversedForEach);

        lluna_TestHelper_FinishSession(&SessionState);
}

static void Create()
{
        uint64 InitialSize = 2;
        uint32 ElementSize = sizeof(uint32);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_Create(InitialSize, ElementSize);

        lluna_TestHelper_CheckNotEqual(DynamicArray, NULL, &SessionState, "Create returned NULL.");
        lluna_TestHelper_CheckNotEqual(DynamicArray->Data, NULL, &SessionState, "Create set Data to NULL.");
        lluna_TestHelper_CheckEqual(DynamicArray->AllocatedSize, InitialSize * ElementSize, &SessionState, "Create did not properly set AllocatedSize.");
        lluna_TestHelper_CheckEqual(DynamicArray->Offset, 0, &SessionState, "Create did not set Offset to 0.");
        lluna_TestHelper_CheckEqual(DynamicArray->ElementSize, ElementSize, &SessionState, "Create did not properly set ElementSize.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void CreateFromData()
{
        uint32 Data[] = { 3, 14, 15, 92 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        lluna_TestHelper_CheckNotEqual(DynamicArray, NULL, &SessionState, "Create returned NULL.");
        lluna_TestHelper_CheckNotEqual(DynamicArray->Data, NULL, &SessionState, "Create set Data to NULL.");
        lluna_TestHelper_CheckEqual(DynamicArray->AllocatedSize, sizeof(Data), &SessionState, "CreateFromData did not properly set AllocatedSize.");
        lluna_TestHelper_CheckEqual(DynamicArray->Offset, sizeof(Data), &SessionState, "CreateFromData did not properly set Offset.");
        lluna_TestHelper_CheckEqual(DynamicArray->ElementSize, ElementSize, &SessionState, "CreateFromData did not properly set ElementSize.");
        lluna_TestHelper_CheckEqual(memcmp(Data, DynamicArray->Data, sizeof(Data)), 0, &SessionState, "CreateFromData did not properly copy given data.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Destroy()
{
        uint64 InitialSize = 2;
        uint32 ElementSize = sizeof(uint32);
         
        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_Create(InitialSize, ElementSize);

        lluna_Container_DynamicArray_Destroy(DynamicArray);

        // TODO Check if the memory was properly freed. Waiting on custom allocators.
}

static void Empty()
{
        uint64 InitialSize = 2;
        uint32 ElementSize = sizeof(uint32);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_Create(InitialSize, ElementSize);

        boolean IsEmpty = lluna_Container_DynamicArray_Empty(DynamicArray);
        lluna_TestHelper_CheckTrue(IsEmpty, &SessionState, "Empty did not return true for empty array.");

        uint32 Element = 42;
        lluna_Container_DynamicArray_Append(DynamicArray, &Element);

        IsEmpty = lluna_Container_DynamicArray_Empty(DynamicArray);
        lluna_TestHelper_CheckFalse(IsEmpty, &SessionState, "Empty did not return false for non-empty array.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Count()
{
        uint32 Data[] = { 3, 14, 15, 92 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        lluna_TestHelper_CheckEqual(lluna_Container_DynamicArray_Count(DynamicArray), sizeof(Data) / ElementSize, &SessionState, "Count did not return the correct number of elements.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Capacity()
{
        uint64 InitialSize = 2;
        uint32 ElementSize = sizeof(uint32);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_Create(InitialSize, ElementSize);

        lluna_TestHelper_CheckEqual(lluna_Container_DynamicArray_Capacity(DynamicArray), InitialSize, &SessionState, "Capacity did not return the proper value.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Resize()
{
        uint64 InitialSize = 2;
        uint32 ElementSize = sizeof(uint32);
        uint64 NewSize = 4;

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_Create(InitialSize, ElementSize);

        lluna_Container_DynamicArray_Resize(DynamicArray, NewSize);

        lluna_TestHelper_CheckEqual(DynamicArray->AllocatedSize, NewSize * ElementSize, &SessionState, "Resize did not properly set AllocatedSize.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Shrink()
{
        uint64 InitialSize = 4;
        uint32 Data[] = { 42, 3 };
        uint32 ElementSize = Data[0];

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_Create(InitialSize, ElementSize);
        for (int i = 0; i < lluna_Container_DynamicArray_Count(DynamicArray); ++i)
        {
                lluna_Container_DynamicArray_Append(DynamicArray, &Data[i]);
        }

        lluna_Container_DynamicArray_Shrink(DynamicArray);

        lluna_TestHelper_CheckEqual(DynamicArray->AllocatedSize, sizeof(Data) / ElementSize, &SessionState, "Shrink did not properly resize to the number of elements.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void First()
{
        uint32 Data[] = { 42, 3, 14 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        uint32* ReturnedPointer = (uint32*)lluna_Container_DynamicArray_First(DynamicArray);

        lluna_TestHelper_CheckEqual(*ReturnedPointer, Data[0], &SessionState, "First did not return the first element of the array");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Last()
{
        uint32 Data[] = { 42, 3, 14 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        uint32* ReturnedPointer = (uint32*)lluna_Container_DynamicArray_Last(DynamicArray);

        lluna_TestHelper_CheckEqual(*ReturnedPointer, Data[sizeof(Data) / ElementSize - 1], &SessionState, "Last did not return the last element of the array");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Get()
{
        uint32 Data[] = { 42, 3, 14 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        for (int i = 0; i < lluna_Container_DynamicArray_Count(DynamicArray); ++i)
        {
                uint32* ReturnedPointer = (uint32*)lluna_Container_DynamicArray_Get(DynamicArray, i);
                lluna_TestHelper_CheckEqual(*ReturnedPointer, Data[i], &SessionState, "Get did not return the correct pointer.");
        }

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Append()
{
        uint64 InitialSize = 2;
        uint32 Data[] = { 42, 3, 14, 15 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_Create(InitialSize, ElementSize);

        for (int i = 0; i < sizeof(Data) / ElementSize; ++i)
        {
                lluna_Container_DynamicArray_Append(DynamicArray, &Data[i]);

                uint32* ReturnedPointer = (uint32*)lluna_Container_DynamicArray_Last(DynamicArray);
                lluna_TestHelper_CheckEqual(*ReturnedPointer, Data[i], &SessionState, "Appended value was not found at the end of the array");
        }
        lluna_TestHelper_CheckEqual(DynamicArray->Offset, sizeof(Data), &SessionState, "Appends did not properly change the offset.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Prepend()
{
        uint64 InitialSize = 2;
        uint32 Data[] = { 42, 3, 14, 15 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_Create(InitialSize, ElementSize);

        for (int i = 0; i < sizeof(Data) / ElementSize; ++i)
        {
                lluna_Container_DynamicArray_Prepend(DynamicArray, &Data[i]);

                uint32* ReturnedPointer = (uint32*)lluna_Container_DynamicArray_First(DynamicArray);
                lluna_TestHelper_CheckEqual(*ReturnedPointer, Data[i], &SessionState, "Prepended value was not found at the start of the array");
        }
        lluna_TestHelper_CheckEqual(DynamicArray->Offset, sizeof(Data), &SessionState, "Appends did not properly change the offset.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Insert()
{
        uint32 Data[] = { 42, 3, 15 };
        uint32 ExpectedData[] = { 14, 42, 3, 14, 15, 14 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        uint32 Element = 14;
        lluna_Container_DynamicArray_Insert(DynamicArray, &Element, 3);
        lluna_Container_DynamicArray_Insert(DynamicArray, &Element, 2);
        lluna_Container_DynamicArray_Insert(DynamicArray, &Element, 0);

        lluna_TestHelper_CheckEqual(DynamicArray->Offset, sizeof(ExpectedData), &SessionState, "Multiple inserts did not properly change the offset.");
        lluna_TestHelper_CheckEqual(memcmp(DynamicArray->Data, ExpectedData, sizeof(ExpectedData)), 0, &SessionState, "Insert did not place new elements at correct indices.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Remove()
{
        uint32 Data[] = { 42, 3, 14, 15, 92 };
        uint32 ExpectedData[] = { 42, 3, 92, 15 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        lluna_Container_DynamicArray_Remove(DynamicArray, 2);

        lluna_TestHelper_CheckEqual(DynamicArray->Offset, sizeof(ExpectedData), &SessionState, "Offset was not correctly updated after remove.");
        lluna_TestHelper_CheckEqual(memcmp(ExpectedData, DynamicArray->Data, sizeof(ExpectedData)), 0, &SessionState, "Array data did not match expected data after remove.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void RemoveStable()
{
        uint32 Data[] = { 42, 3, 14, 15, 16 };
        uint32 ExpectedData[] = { 42, 3, 15, 16 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        lluna_Container_DynamicArray_RemoveStable(DynamicArray, 2);

        lluna_TestHelper_CheckEqual(DynamicArray->Offset, sizeof(ExpectedData), &SessionState, "Offset was not correctly updated after remove stable.");
        lluna_TestHelper_CheckEqual(memcmp(ExpectedData, DynamicArray->Data, sizeof(ExpectedData)), 0, &SessionState, "Array data did not match expected data after remove.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void RemoveFirst()
{
        uint32 Data[] = { 42, 3, 14, 15, 16 };
        uint32 ExpectedData[] = { 3, 14, 15, 16 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        lluna_Container_DynamicArray_RemoveFirst(DynamicArray);

        lluna_TestHelper_CheckEqual(DynamicArray->Offset, sizeof(ExpectedData), &SessionState, "Offset was not correctly updated after remove.");
        lluna_TestHelper_CheckEqual(memcmp(ExpectedData, DynamicArray->Data, sizeof(ExpectedData)), 0, &SessionState, "Array data did not match expected data after remove.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void RemoveLast()
{
        uint32 Data[] = { 42, 3, 14, 15, 16 };
        uint32 ExpectedData[] = { 42, 3, 14, 15 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        lluna_Container_DynamicArray_RemoveLast(DynamicArray);

        lluna_TestHelper_CheckEqual(DynamicArray->Offset, sizeof(ExpectedData), &SessionState, "Offset was not correctly updated after remove.");
        lluna_TestHelper_CheckEqual(memcmp(ExpectedData, DynamicArray->Data, sizeof(ExpectedData)), 0, &SessionState, "Array data did not match expected data after remove.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void Clear()
{
        uint32 Data[] = { 42, 3, 14, 15, 16 };
        uint32 ElementSize = sizeof(Data[0]);

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        lluna_Container_DynamicArray_Clear(DynamicArray);

        lluna_TestHelper_CheckEqual(DynamicArray->Offset, 0, &SessionState, "Offset was not set to 0 after clear.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void ForEach()
{
        uint32 Data[] = { 42, 3, 14, 15, 16 };
        uint32 ElementSize = sizeof(Data[0]);
        uint32 ElementCount = sizeof(Data) / ElementSize;

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        uint32* Iterator;
        uint64 Index = 0;
        lluna_Container_DynamicArray_ForEach(DynamicArray, Iterator)
        {
                lluna_TestHelper_CheckEqual(*Iterator, Data[Index], &SessionState, "ForEach did not retrieve the correct pointer.");
                ++Index;
        }

        lluna_TestHelper_CheckEqual(Index, ElementCount, &SessionState, "ForEach did not go through all elements.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}

static void ReversedForEach()
{
        uint32 Data[] = { 42, 3, 14, 15, 16 };
        uint32 ElementSize = sizeof(Data[0]);
        uint32 ElementCount = sizeof(Data) / ElementSize;

        struct lluna_Container_DynamicArray* DynamicArray = lluna_Container_DynamicArray_CreateFromData(Data, sizeof(Data), ElementSize);

        uint32* Iterator;
        uint64 Index = ElementCount - 1;
        lluna_Container_DynamicArray_ReversedForEach(DynamicArray, Iterator)
        {
                lluna_TestHelper_CheckEqual(*Iterator, Data[Index], &SessionState, "ReversedForEach did not retrieve the correct pointer.");
                --Index;
        }

        lluna_TestHelper_CheckEqual(Index, -1, &SessionState, "ReversedForEach did not go through all elements.");

        lluna_Container_DynamicArray_Destroy(DynamicArray);
}
