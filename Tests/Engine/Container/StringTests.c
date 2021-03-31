#include <TestHelper.h>

#include <Engine/Container/Public/String.h>
#include <Engine/Core/Public/Macros.h>

#include <string.h>

struct lluna_TestHelper_Session SessionState;

static void Create();
static void CreateFromText();
static void CreateFormatted();
static void Destroy();
static void Empty();
static void Length();
static void Capacity();
static void Resize();
static void Shrink();
static void Equals();
static void EqualsText();
static void Compare();
static void CompareText();
static void First();
static void Last();
static void Get();
static void Append();
static void AppendText();
static void Assign();
static void AssignText();
static void Format();
static void Clear();
static void ForEach();
static void ReversedForEach();


int main(int argc, const char* argv[])
{
        lluna_TestHelper_StartSession(&SessionState, "lluna_Container_String");

        lluna_TestHelper_RunTest(&SessionState, Create);
        lluna_TestHelper_RunTest(&SessionState, CreateFromText);
        lluna_TestHelper_RunTest(&SessionState, CreateFormatted);
        lluna_TestHelper_RunTest(&SessionState, Destroy);
        lluna_TestHelper_RunTest(&SessionState, Empty);
        lluna_TestHelper_RunTest(&SessionState, Length);
        lluna_TestHelper_RunTest(&SessionState, Capacity);
        lluna_TestHelper_RunTest(&SessionState, Resize);
        lluna_TestHelper_RunTest(&SessionState, Shrink);
        lluna_TestHelper_RunTest(&SessionState, Equals);
        lluna_TestHelper_RunTest(&SessionState, EqualsText);
        lluna_TestHelper_RunTest(&SessionState, Compare);
        lluna_TestHelper_RunTest(&SessionState, CompareText);
        lluna_TestHelper_RunTest(&SessionState, First);
        lluna_TestHelper_RunTest(&SessionState, Last);
        lluna_TestHelper_RunTest(&SessionState, Get);
        lluna_TestHelper_RunTest(&SessionState, Append);
        lluna_TestHelper_RunTest(&SessionState, AppendText);
        lluna_TestHelper_RunTest(&SessionState, Assign);
        lluna_TestHelper_RunTest(&SessionState, AssignText);
        lluna_TestHelper_RunTest(&SessionState, Format);
        lluna_TestHelper_RunTest(&SessionState, Clear);
        lluna_TestHelper_RunTest(&SessionState, ForEach);
        lluna_TestHelper_RunTest(&SessionState, ReversedForEach);

        lluna_TestHelper_FinishSession(&SessionState);
}

static void Create()
{
        uint64 InitialSize = 64;

        struct lluna_Container_String* String = lluna_Container_String_Create(InitialSize);

        lluna_TestHelper_CheckNotEqual(String, NULL, &SessionState, "Create returned NULL.");
        lluna_TestHelper_CheckNotEqual(String->Data, NULL, &SessionState, "Create set Data to NULL.");
        lluna_TestHelper_CheckEqual(String->AllocatedSize, InitialSize + 1, &SessionState, "Create did not properly set AllocatedSize.");
       
        lluna_Container_String_Destroy(String);
}

static void CreateFromText()
{
#define Text "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(Text);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        lluna_TestHelper_CheckNotEqual(String, NULL, &SessionState, "CreateFromText returned NULL.");
        lluna_TestHelper_CheckNotEqual(String->Data, NULL, &SessionState, "CreateFromText set Data to NULL.");
        lluna_TestHelper_CheckEqual(String->AllocatedSize, Size, &SessionState, "CreateFromText did not properly set AllocatedSize.");
        lluna_TestHelper_CheckEqual(String->Offset, Size - 1, &SessionState, "CreateFromText did not properly set Offset.");
        lluna_TestHelper_CheckEqual(String->Data[String->Offset], '\0', &SessionState, "Create did not proplerly NULL terminate the string.");
        lluna_TestHelper_CheckEqual(strcmp(String->Data, Text), 0, &SessionState, "CreateFromText did not copy the correct string to Data.");

        lluna_Container_String_Destroy(String);

#undef Text
}

static void CreateFormatted()
{
#define Result "{key: 3}"

        const char* FormatString = "{%s: %d}";
        uint64 TextSize = sizeof(Result);

        struct lluna_Container_String* String = lluna_Container_String_CreateFormatted(lluna_Macros_Text(FormatString), "key", 3);

        lluna_TestHelper_CheckEqual(strcmp(String->Data, Result), 0, &SessionState, "CreateFormatted did not set Data to correct string.");
        lluna_TestHelper_CheckNotEqual(String, NULL, &SessionState, "CreateFormatted returned NULL");
        lluna_TestHelper_CheckNotEqual(String->Data, NULL, &SessionState, "CreateFormatted set Data to NULL");
        lluna_TestHelper_CheckEqual(String->AllocatedSize, TextSize, &SessionState, "CreateFormatted did not properly set AllocatedSize.");
        lluna_TestHelper_CheckEqual(String->Offset, TextSize - 1, &SessionState, "CreateFormatted did not properly set Offset.");
        lluna_TestHelper_CheckEqual(String->Data[String->Offset], '\0', &SessionState, "CreateFormatted did not proplerly NULL terminate the string.");

        lluna_Container_String_Destroy(String);

#undef Result
}

static void Destroy()
{
        uint64 InitialSize = 64;

        struct lluna_Container_String* String = lluna_Container_String_Create(InitialSize);

        lluna_Container_String_Destroy(String);

        // TODO Check if the memory was properly freed. Waiting on custom allocators.
}

static void Empty()
{
        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(""));
        struct lluna_Container_String* OtherString = lluna_Container_String_CreateFromText(lluna_Macros_Text("OtherString"));

        lluna_TestHelper_CheckTrue(lluna_Container_String_Empty(String), &SessionState, "Empty did not return true for empty string.");
        lluna_TestHelper_CheckFalse(lluna_Container_String_Empty(OtherString), &SessionState, "Empty did not return false for non-empty string.");

        lluna_Container_String_Destroy(String);
        lluna_Container_String_Destroy(OtherString);
}

static void Length()
{

#define Text "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(Text);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        lluna_TestHelper_CheckEqual(lluna_Container_String_Length(String), Size - 1, &SessionState, "Length did not return the correct number of characters.")

        lluna_Container_String_Destroy(String);

#undef Text
}

static void Capacity()
{
        uint64 InitialSize = 64;

        struct lluna_Container_String* String = lluna_Container_String_Create(InitialSize);

        lluna_TestHelper_CheckEqual(lluna_Container_String_Capacity(String), InitialSize, &SessionState, "Capacity did not return the proper value.");

        lluna_Container_String_Destroy(String);
}

static void Resize()
{
        uint64 InitialSize = 32;
        uint64 NewSize = 64;

        struct lluna_Container_String* String = lluna_Container_String_Create(InitialSize);

        lluna_Container_String_Resize(String, NewSize);

        lluna_TestHelper_CheckEqual(String->AllocatedSize, NewSize + 1, &SessionState, "Resize did not properly set AllocatedSize.");

        lluna_Container_String_Destroy(String);
}

static void Shrink()
{
#define Text "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(Text);
        uint64 InitialSize = Size * 2;

        struct lluna_Container_String* String = lluna_Container_String_Create(InitialSize);

        lluna_Container_String_AssignText(String, lluna_Macros_Text(Text));
        lluna_Container_String_Shrink(String);

        lluna_TestHelper_CheckEqual(String->AllocatedSize, Size, &SessionState, "Shrink did not properly set AllocatedSize.");

        lluna_Container_String_Destroy(String);

#undef Text
}

static void Equals()
{
#define Text "Sphinx of black quartz judge my vow."
#define Other "The quick brown fox jumps over the lazy dog."

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));
        struct lluna_Container_String* OtherString = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));
        struct lluna_Container_String* AnotherString = lluna_Container_String_CreateFromText(lluna_Macros_Text(Other));

        lluna_TestHelper_CheckTrue(lluna_Container_String_Equals(String, OtherString), &SessionState, "Equals did not return true for equal strings.");
        lluna_TestHelper_CheckFalse(lluna_Container_String_Equals(String, AnotherString), &SessionState, "Equals did not return false for different strings.");

        lluna_Container_String_Destroy(String);
        lluna_Container_String_Destroy(OtherString);
        lluna_Container_String_Destroy(AnotherString);

#undef Text
#undef Other
}

static void EqualsText()
{
#define Text "Sphinx of black quartz judge my vow."
#define Other "The quick brown fox jumps over the lazy dog."

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        lluna_TestHelper_CheckTrue(lluna_Container_String_EqualsText(String, lluna_Macros_Text(Text)), &SessionState, "Equals did not return true for equal strings.");
        lluna_TestHelper_CheckFalse(lluna_Container_String_EqualsText(String, lluna_Macros_Text(Other)), &SessionState, "Equals did not return false for different strings.");

        lluna_Container_String_Destroy(String);

#undef Text
#undef Other
}

static void Compare()
{
#define Text "Sphinx of black quartz judge my vow."
#define Other "The quick brown fox jumps over the lazy dog."

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));
        struct lluna_Container_String* OtherString = lluna_Container_String_CreateFromText(lluna_Macros_Text(Other));

        lluna_TestHelper_CheckEqual(lluna_Container_String_Compare(String, OtherString), strcmp(String->Data, OtherString->Data), &SessionState, "Compare did not return the same value as strcmp.");

        lluna_Container_String_Destroy(String);
        lluna_Container_String_Destroy(OtherString);

#undef Text
#undef Other
}

static void CompareText()
{
#define Text "Sphinx of black quartz judge my vow."
#define Other "The quick brown fox jumps over the lazy dog."

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        lluna_TestHelper_CheckEqual(lluna_Container_String_CompareText(String, lluna_Macros_Text(Other)), strcmp(String->Data, Other), &SessionState, "Compare did not return the same value as strcmp.");

        lluna_Container_String_Destroy(String);

#undef Text
#undef Other
}

static void First()
{
#define Text "Sphinx of black quartz judge my vow."

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        char* ReturnedPointer = lluna_Container_String_First(String);

        lluna_TestHelper_CheckEqual(*ReturnedPointer, Text[0], &SessionState, "First did not return the first character of the string.");

        lluna_Container_String_Destroy(String);

#undef Text
}

static void Last()
{
#define Text "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(Text);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        char* ReturnedPointer = lluna_Container_String_Last(String);

        lluna_TestHelper_CheckEqual(*ReturnedPointer, Text[Size - 2], &SessionState, "Last did not return the last character of the string.");

        lluna_Container_String_Destroy(String);

#undef Text
}

static void Get()
{
#define Text "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(Text);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        for (uint64 i = 0; i < Size - 1; ++i)
        {
                char* ReturnedPointer = lluna_Container_String_Get(String, i);
                lluna_TestHelper_CheckEqual(*ReturnedPointer, Text[i], &SessionState, "Get did not return the correct pointer.");
        }

        lluna_Container_String_Destroy(String);

#undef Text
}

static void Append()
{
#define Text "Sphinx of black quartz"
#define Other " judge my vow."
#define Result "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(Result);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));
        struct lluna_Container_String* OtherString = lluna_Container_String_CreateFromText(lluna_Macros_Text(Other));

        lluna_Container_String_Append(String, OtherString);

        lluna_TestHelper_CheckTrue(lluna_Container_String_EqualsText(String, lluna_Macros_Text(Result)), &SessionState, "AppendText did not set Data to correct string.");
        lluna_TestHelper_CheckTrue(String->AllocatedSize >= Size, &SessionState, "AppendText did not allocate enough space.");
        lluna_TestHelper_CheckEqual(String->Offset, Size - 1, &SessionState, "AppendText did not properly set Offset.");
        lluna_TestHelper_CheckEqual(String->Data[String->Offset], '\0', &SessionState, "AppendText did not proplerly NULL terminate the string.");

        lluna_Container_String_Destroy(String);
        lluna_Container_String_Destroy(OtherString);

#undef Text
#undef Other
#undef Result
}

static void AppendText()
{
#define Text "Sphinx of black quartz"
#define Other " judge my vow."
#define Result "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(Result);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        lluna_Container_String_AppendText(String, lluna_Macros_Text(Other));

        lluna_TestHelper_CheckTrue(lluna_Container_String_EqualsText(String, lluna_Macros_Text(Result)), &SessionState, "Append did not set Data to correct string.");
        lluna_TestHelper_CheckTrue(String->AllocatedSize >= Size, &SessionState, "Append did not allocate enough space.");
        lluna_TestHelper_CheckEqual(String->Offset, Size - 1, &SessionState, "Append did not properly set Offset.");
        lluna_TestHelper_CheckEqual(String->Data[String->Offset], '\0', &SessionState, "Allocate did not proplerly NULL terminate the string.");

        lluna_Container_String_Destroy(String);

#undef Text
#undef Other
#undef Result
}

static void Assign()
{
#define Text "The quick brown fox jumps over the lazy dog."
#define OtherText "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(OtherText);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));
        struct lluna_Container_String* OtherString = lluna_Container_String_CreateFromText(lluna_Macros_Text(OtherText));

        lluna_Container_String_Assign(String, OtherString);

        lluna_TestHelper_CheckTrue(lluna_Container_String_EqualsText(String, lluna_Macros_Text(OtherText)), &SessionState, "Assign did not set Data to correct string.");
        lluna_TestHelper_CheckTrue(String->AllocatedSize >= Size, &SessionState, "Assign did not allocate enough space.");
        lluna_TestHelper_CheckEqual(String->Offset, Size - 1, &SessionState, "Assign did not properly set Offset.");
        lluna_TestHelper_CheckEqual(String->Data[String->Offset], '\0', &SessionState, "Assign did not proplerly NULL terminate the string.");

        lluna_Container_String_Destroy(String);
        lluna_Container_String_Destroy(OtherString);

#undef Text
#undef OtherText
}

static void AssignText()
{
#define Text "The quick brown fox jumps over the lazy dog."
#define OtherText "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(OtherText);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        lluna_Container_String_AssignText(String, lluna_Macros_Text(OtherText));

        lluna_TestHelper_CheckTrue(lluna_Container_String_EqualsText(String, lluna_Macros_Text(OtherText)), &SessionState, "Assign did not set Data to correct string.");
        lluna_TestHelper_CheckTrue(String->AllocatedSize >= Size, &SessionState, "Assign did not allocate enough space.");
        lluna_TestHelper_CheckEqual(String->Offset, Size - 1, &SessionState, "Assign did not properly set Offset.");
        lluna_TestHelper_CheckEqual(String->Data[String->Offset], '\0', &SessionState, "Assign did not proplerly NULL terminate the string.");

        lluna_Container_String_Destroy(String);

#undef Text
#undef OtherText
}

static void Format()
{
#define Result "{key: 3}"

        const char* FormatString = "{%s: %d}";
        uint64 Size = sizeof(Result);

        struct lluna_Container_String* String = lluna_Container_String_Create(0);

        lluna_Container_String_Format(String, lluna_Macros_Text(FormatString), "key", 3);

        lluna_TestHelper_CheckEqual(strcmp(String->Data, Result), 0, &SessionState, "Format did not set Data to correct string.");
        lluna_TestHelper_CheckNotEqual(String, NULL, &SessionState, "Format returned NULL");
        lluna_TestHelper_CheckNotEqual(String->Data, NULL, &SessionState, "Format set Data to NULL");
        lluna_TestHelper_CheckEqual(String->AllocatedSize, Size, &SessionState, "Format did not properly set AllocatedSize.");
        lluna_TestHelper_CheckEqual(String->Offset, Size - 1, &SessionState, "Format did not properly set Offset.");
        lluna_TestHelper_CheckEqual(String->Data[String->Offset], '\0', &SessionState, "Format did not proplerly NULL terminate the string.");

        lluna_Container_String_Destroy(String);

#undef Result
}

static void Clear()
{
#define Text "Sphinx of black quartz judge my vow."

        uint64 TextSize = sizeof(Text);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        lluna_Container_String_Clear(String);

        lluna_TestHelper_CheckEqual(String->Offset, 0, &SessionState, "Clear did not set Offset to 0.");
        lluna_TestHelper_CheckEqual(String->Data[String->Offset], '\0', &SessionState, "Clear did not proplerly NULL terminate the string.");

        lluna_Container_String_Destroy(String);

#undef Text
}

static void ForEach()
{
#define Text "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(Text);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        char* Iterator;
        uint64 Index = 0;
        lluna_Container_String_ForEach(String, Iterator)
        {
                lluna_TestHelper_CheckEqual(*Iterator, Text[Index], &SessionState, "ForEach did not retrieve the correct pointer.");
                ++Index;
        }

        lluna_TestHelper_CheckEqual(Index, Size - 1, &SessionState, "ForEach did not go through all elements.");

        lluna_Container_String_Destroy(String);

#undef Text
}

static void ReversedForEach()
{
#define Text "Sphinx of black quartz judge my vow."

        uint64 Size = sizeof(Text);

        struct lluna_Container_String* String = lluna_Container_String_CreateFromText(lluna_Macros_Text(Text));

        char* Iterator;
        uint64 Index = Size - 2;
        lluna_Container_String_ReversedForEach(String, Iterator)
        {
                lluna_TestHelper_CheckEqual(*Iterator, Text[Index], &SessionState, "ForEach did not retrieve the correct pointer.");
                --Index;
        }

        lluna_TestHelper_CheckEqual(Index, -1, &SessionState, "ForEach did not go through all elements.");

        lluna_Container_String_Destroy(String);

#undef Text
}
