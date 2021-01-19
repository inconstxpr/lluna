#include <Engine/Container/Public/DynamicArray.h>

#include <stdlib.h>
#include <string.h>

static void ScaleUp(struct lluna_Container_DynamicArray* Handle)
{
        Handle->AllocatedSize *= lluna_Container_DynamicArray_ResizeFactor;
        // TODO This could leak memory. Waiting on validation/custom allocators to fix.
        Handle->Data = realloc(Handle->Data, Handle->AllocatedSize);
}

struct lluna_Container_DynamicArray* lluna_Container_DynamicArray_Create(uint64 InitialSize, uint32 ElementSize)
{
        struct lluna_Container_DynamicArray* Handle = malloc(sizeof(struct lluna_Container_DynamicArray));
        Handle->Data = malloc(InitialSize * ElementSize);
        Handle->AllocatedSize = InitialSize * ElementSize;
        Handle->Offset = 0;
        Handle->ElementSize = ElementSize;

        return Handle;
}

struct lluna_Container_DynamicArray* lluna_Container_DynamicArray_CreateFromData(byte* Data, uint64 Size, uint32 ElementSize)
{
        struct lluna_Container_DynamicArray* Handle = malloc(sizeof(struct lluna_Container_DynamicArray));
        Handle->Data = malloc(Size);
        Handle->AllocatedSize = Size;
        Handle->Offset = Size;
        Handle->ElementSize = ElementSize;

        memcpy(Handle->Data, Data, Size);

        return Handle;
}

void lluna_Container_DynamicArray_Destroy(struct lluna_Container_DynamicArray* Handle)
{
        free(Handle->Data);
        free(Handle);
}

boolean lluna_Container_DynamicArray_Empty(struct lluna_Container_DynamicArray* Handle)
{
        return Handle->Offset == 0;
}

uint64 lluna_Container_DynamicArray_Count(struct lluna_Container_DynamicArray* Handle)
{
        return Handle->Offset / Handle->ElementSize;
}

uint64 lluna_Container_DynamicArray_Capacity(struct lluna_Container_DynamicArray* Handle)
{
        return Handle->AllocatedSize / Handle->ElementSize;
}

void lluna_Container_DynamicArray_Resize(struct lluna_Container_DynamicArray* Handle, uint64 Size)
{
        // TODO This could leak memory. Waiting on validation/custom allocators to fix.
        Handle->Data = realloc(Handle->Data, Size * Handle->ElementSize);
        Handle->AllocatedSize = Size * Handle->ElementSize;
}

void lluna_Container_DynamicArray_Shrink(struct lluna_Container_DynamicArray* Handle)
{
        // TODO This could leak memory. Waiting on validation/custom allocators to fix.
        Handle->Data = realloc(Handle->Data, Handle->Offset);
        Handle->AllocatedSize = Handle->Offset;
}

byte* lluna_Container_DynamicArray_First(struct lluna_Container_DynamicArray* Handle)
{
        return Handle->Data;
}

byte* lluna_Container_DynamicArray_Last(struct lluna_Container_DynamicArray* Handle)
{
        return Handle->Data + Handle->Offset - Handle->ElementSize;
}


byte* lluna_Container_DynamicArray_Get(struct lluna_Container_DynamicArray* Handle, uint64 Index)
{
        return Handle->Data + Handle->ElementSize * Index;
}

void lluna_Container_DynamicArray_Append(struct lluna_Container_DynamicArray* Handle, byte* Data)
{
        if (Handle->Offset + Handle->ElementSize > Handle->AllocatedSize)
        {
                ScaleUp(Handle);
        }

        memcpy(Handle->Data + Handle->Offset, Data, Handle->ElementSize);
        Handle->Offset += Handle->ElementSize;
}

void lluna_Container_DynamicArray_Prepend(struct lluna_Container_DynamicArray* Handle, byte* Data)
{
        if (Handle->Offset + Handle->ElementSize > Handle->AllocatedSize)
        {
                ScaleUp(Handle);
        }

        memcpy(Handle->Data + Handle->ElementSize, Handle->Data, Handle->Offset);
        memcpy(Handle->Data, Data, Handle->ElementSize);
        Handle->Offset += Handle->ElementSize;
}

void lluna_Container_DynamicArray_Insert(struct lluna_Container_DynamicArray* Handle, byte* Data, uint64 Index)
{
        if (Handle->Offset + Handle->ElementSize > Handle->AllocatedSize)
        {
                ScaleUp(Handle);
        }

        uint64 InsertOffset = Index * Handle->ElementSize;
        memcpy(Handle->Data + InsertOffset + Handle->ElementSize, Handle->Data + InsertOffset, Handle->Offset - InsertOffset);
        memcpy(Handle->Data + InsertOffset, Data, Handle->ElementSize);
        Handle->Offset += Handle->ElementSize;
}

void lluna_Container_DynamicArray_Remove(struct lluna_Container_DynamicArray* Handle, uint64 Index)
{
        uint64 VictimOffset = Index * Handle->ElementSize;
        memcpy(Handle->Data + VictimOffset, Handle->Data + Handle->Offset - Handle->ElementSize, Handle->ElementSize);
        Handle->Offset -= Handle->ElementSize;
}

void lluna_Container_DynamicArray_RemoveStable(struct lluna_Container_DynamicArray* Handle, uint64 Index)
{
        uint64 VictimOffset = Index * Handle->ElementSize;
        memcpy(Handle->Data + VictimOffset, Handle->Data + VictimOffset + Handle->ElementSize, Handle->Offset - (VictimOffset + Handle->ElementSize));
        Handle->Offset -= Handle->ElementSize;
}

void lluna_Container_DynamicArray_RemoveFirst(struct lluna_Container_DynamicArray* Handle)
{
        memcpy(Handle->Data, Handle->Data + Handle->ElementSize, Handle->Offset - Handle->ElementSize);
        Handle->Offset -= Handle->ElementSize;
}

void lluna_Container_DynamicArray_RemoveLast(struct lluna_Container_DynamicArray* Handle)
{
        Handle->Offset -= Handle->ElementSize;
}

void lluna_Container_DynamicArray_Clear(struct lluna_Container_DynamicArray* Handle)
{
        Handle->Offset = 0;
}
