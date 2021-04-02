#include <Engine/Container/Public/String.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void NullTerminate(struct lluna_Container_String* Handle)
{
        Handle->Data[Handle->Offset] = '\0';
}

struct lluna_Container_String* lluna_Container_String_Create(uint64 InitialSize)
{
        uint64 Size = (InitialSize + 1) * sizeof(char);

        struct lluna_Container_String* Handle = malloc(sizeof(struct lluna_Container_String));
        Handle->Data = malloc(Size);
        Handle->AllocatedSize = Size;
        Handle->Offset = 0;

        NullTerminate(Handle);

        return Handle;
}

struct lluna_Container_String* lluna_Container_String_CreateFromText(struct lluna_Core_Types_Text Text)
{
        struct lluna_Container_String* Handle = malloc(sizeof(struct lluna_Container_String));
        Handle->Data = malloc(Text.Size);
        Handle->AllocatedSize = Text.Size;
        Handle->Offset = Text.Size - 1;

        memcpy(Handle->Data, Text.Data, Text.Size);

        return Handle;
}

struct lluna_Container_String* lluna_Container_String_CreateFormatted(struct lluna_Core_Types_Text Format, ...)
{
        struct lluna_Container_String* Handle = malloc(sizeof(struct lluna_Container_String));

        int32 Size;
        va_list Args;

        va_start(Args, Format);

        Size = vsnprintf(NULL, 0, Format.Data, Args);
        ++Size;

        Handle->Data = malloc(Size);
        Handle->AllocatedSize = Size;

        vsnprintf(Handle->Data, Size, Format.Data, Args);
        Handle->Offset = Size - 1;

        va_end(Args);

        NullTerminate(Handle);

        return Handle;
}

void lluna_Container_String_Destroy(struct lluna_Container_String* Handle)
{
        free(Handle->Data);
        free(Handle);
}

boolean lluna_Container_String_Empty(struct lluna_Container_String* Handle)
{
        return Handle->Offset == 0;
}

uint64 lluna_Container_String_Length(struct lluna_Container_String* Handle)
{
        return Handle->Offset / sizeof(char);
}

uint64 lluna_Container_String_Capacity(struct lluna_Container_String* Handle)
{
        return Handle->AllocatedSize - 1;
}

void lluna_Container_String_Resize(struct lluna_Container_String* Handle, uint64 Size)
{
        uint64 NewSize = (Size + 1) * sizeof(char);

        Handle->Data = realloc(Handle->Data, NewSize);
        Handle->AllocatedSize = NewSize;
        Handle->Offset = Handle->Offset > Handle->AllocatedSize - 1 ? Handle->AllocatedSize - 1 : Handle->Offset;
}

void lluna_Container_String_Shrink(struct lluna_Container_String* Handle)
{
        uint64 NewSize = Handle->Offset + 1 * sizeof(char);

        Handle->Data = realloc(Handle->Data, NewSize);
        Handle->AllocatedSize = NewSize;
}

boolean lluna_Container_String_Equals(struct lluna_Container_String* Handle, struct lluna_Container_String* Other)
{
        return lluna_Container_String_Compare(Handle, Other) == 0;
}

boolean lluna_Container_String_EqualsText(struct lluna_Container_String* Handle, struct lluna_Core_Types_Text Text)
{
        return lluna_Container_String_CompareText(Handle, Text) == 0;
}


int32 lluna_Container_String_Compare(struct lluna_Container_String* Handle, struct lluna_Container_String* Other)
{
        return strcmp(Handle->Data, Other->Data);
}

int32 lluna_Container_String_CompareText(struct lluna_Container_String* Handle, struct lluna_Core_Types_Text Text)
{
        return strcmp(Handle->Data, Text.Data);
}

char* lluna_Container_String_First(struct lluna_Container_String* Handle)
{
        return Handle->Data;
}

char* lluna_Container_String_Last(struct lluna_Container_String* Handle)
{
        return Handle->Data + Handle->Offset - 1;
}

char* lluna_Container_String_Get(struct lluna_Container_String* Handle, uint64 Index)
{
        return Handle->Data + Index;
}

void lluna_Container_String_Append(struct lluna_Container_String* Handle, struct lluna_Container_String* Other)
{
        uint64 CombinedSize = Handle->Offset + Other->Offset;

        if (CombinedSize > Handle->AllocatedSize)
        {
                lluna_Container_String_Resize(Handle, CombinedSize);
        }

        memcpy((byte*)Handle->Data + Handle->Offset, Other->Data, Other->Offset);
        Handle->Offset += Other->Offset;

        NullTerminate(Handle);
}

void lluna_Container_String_AppendText(struct lluna_Container_String* Handle, struct lluna_Core_Types_Text Text)
{
        uint64 CombinedSize = Handle->Offset + Text.Size - 1;

        if (CombinedSize > Handle->AllocatedSize)
        {
                lluna_Container_String_Resize(Handle, CombinedSize);
        }

        memcpy((byte*)Handle->Data + Handle->Offset, Text.Data, Text.Size);
        Handle->Offset += Text.Size - 1;
}

void lluna_Container_String_Assign(struct lluna_Container_String* Handle, struct lluna_Container_String* Other)
{
        if (Other->Offset + 1 > Handle->AllocatedSize) {
                lluna_Container_String_Resize(Handle, Other->Offset);
        }

        memcpy(Handle->Data, Other->Data, Other->Offset + 1);
        Handle->Offset = Other->Offset;
}

void lluna_Container_String_AssignText(struct lluna_Container_String* Handle, struct lluna_Core_Types_Text Text)
{
        if (Text.Size > Handle->AllocatedSize) {
                lluna_Container_String_Resize(Handle, Text.Size - 1);
        }

        memcpy(Handle->Data, Text.Data, Text.Size);
        Handle->Offset = Text.Size - 1;
}

void lluna_Container_String_Clear(struct lluna_Container_String* Handle)
{
        Handle->Offset = 0;
        NullTerminate(Handle);
}

void lluna_Container_String_Format(struct lluna_Container_String* Handle, struct lluna_Core_Types_Text Format, ...)
{
        int32 Size;
        va_list Args;

        va_start(Args, Format);

        Size = vsnprintf(NULL, 0, Format.Data, Args);
        ++Size;

        if (Size > Handle->AllocatedSize)
        {
                lluna_Container_String_Resize(Handle, Size - 1);
        }


        vsnprintf(Handle->Data, Size, Format.Data, Args);
        Handle->Offset = Size - 1;

        va_end(Args);

        NullTerminate(Handle);
}
