#pragma once

/**
 * @file String.h
 * @brief Managed string.
 *
 * lluna_Container_String is a managed, null terminated string with cached length.
 */

#include <Engine/Core/Public/Types.h>

/**
 * @brief Describes a managed, null terminated string.
 */
struct lluna_Container_String
{
        char* Data; /**< Handle to the string data. */

        uint64 AllocatedSize; /**< Size of the currently allocated memory. */
        uint64 Offset; /**< Offset to the first empty position. */
};

/**
 * @brief Creates a string and returns a handle to it.
 *
 * Created strings have to be manually destroyed.
 *
 * @param InitialSize Size of the initial memory allocation.
 * @return Handle to the created string.
 *
 * @see lluna_Container_String_Destroy
 */
struct lluna_Container_String* lluna_Container_String_Create(uint64 InitialSize);
/**
 * @brief Creates a string from the given text and returns a handle to it.
 *
 * @param Text The text from which to create the string.
 * @return Handle to the created string.
 *
 * @see lluna_Container_String_Destroy
 * @see lluna_Macros_Text
 */
struct lluna_Container_String* lluna_Container_String_CreateFromText(struct lluna_Core_Types_Text Text);
/**
 * @brief Creates a formatted string and returns a handle to it.
 *
 * @param Format Format string.
 * @param Args List of format arguments.
 * @return Handle to the created string.
 *
 * @see lluna_Container_String_Destroy
 * @see lluna_Macros_Text
 */
struct lluna_Container_String* lluna_Container_String_CreateFormatted(struct lluna_Core_Types_Text Format, ...);
/**
 * @brief Destroys the given string.
 *
 * @param Handle String to destroy.
 */
void lluna_Container_String_Destroy(struct lluna_Container_String* Handle);

/**
 * @brief Returns true if the string is empty.
 *
 * @param Handle String to check.
 * @return Whether or not the string is empty.
 */
boolean lluna_Container_String_Empty(struct lluna_Container_String* Handle);
/**
 * @brief Returns the length of the given string.
 *
 * @param Handle String to get the length of.
 * @return Length of the string.
 */
uint64 lluna_Container_String_Length(struct lluna_Container_String* Handle);
/**
 * @brief Returns the maximum number of characters that will fit in the currently allocated space.
 *
 * @param Handle String to get the capacity.
 * @return Current capacity of the string.
 */
uint64 lluna_Container_String_Capacity(struct lluna_Container_String* Handle);
/**
 * @brief Resises the string to the given length.
 *
 * If `Size` is smaller than the current lenght, only `Size` characters will be kept.
 *
 * @param Handle String to resize.
 * @param Size New size.
 */
void lluna_Container_String_Resize(struct lluna_Container_String* Handle, uint64 Size);
/**
 * @brief Shrinks the string to fit the current length.
 *
 * @param Handle String to shrink.
 */
void lluna_Container_String_Shrink(struct lluna_Container_String* Handle);

/**
 * @brief Returns true if the contents of the two given strings is equal.
 *
 * @param Handle First string.
 * @param Other Second string.
 * @return Whether or not the string contents are equal.
 */
boolean lluna_Container_String_Equals(struct lluna_Container_String* Handle, struct lluna_Container_String* Other);
/**
 * @brief Returns true if the contents of the given string is equal to the given text.
 *
 * @param Handle First string.
 * @param Text Other text.
 * @return Whether or not the string and text are equal.
 * 
 * @see lluna_Macros_Text
 */
boolean lluna_Container_String_EqualsText(struct lluna_Container_String* Handle, struct lluna_Core_Types_Text Text);
/**
 * @brief Returns the difference between the two given strings.
 *
 * @param Handle First string.
 * @param Other Second string.
 * @return Difference between given strings.
 */
int32 lluna_Container_String_Compare(struct lluna_Container_String* Handle, struct lluna_Container_String* Other);
/**
 * @brief Returns the difference between the given string and the given text.
 *
 * @param Handle First string.
 * @param Text Other text.
 * @return Difference between given string and text.
 *
 *@see lluna_Macros_Text
 */
int32 lluna_Container_String_CompareText(struct lluna_Container_String* Handle, struct lluna_Core_Types_Text Text);
/**
 * @brief Gets the first character.
 *
 * @param Handle String from which to get the first character.
 * @return First character.
 */
char* lluna_Container_String_First(struct lluna_Container_String* Handle);
/**
 * @brief Gets the last character.
 *
 * @param Handle String from which to get the last character.
 * @return Last character.
 */
char* lluna_Container_String_Last(struct lluna_Container_String* Handle);
/**
 * @brief Gets the character at the given index.
 *
 * @param Handle String from which to get the character from.
 * @param Index Index of the caracter to get.
 * @return Character.
 */
char* lluna_Container_String_Get(struct lluna_Container_String* Handle, uint64 Index);

/**
 * @brief Appends a string to the end.
 *
 * @param Handle String to append to.
 * @param Other String to append.
 */
void lluna_Container_String_Append(struct lluna_Container_String* Handle, struct lluna_Container_String* Other);
/**
 * @brief Appends text to the end.
 *
 * @param Handle String to append to.
 * @param Text Text to append.
 *
 * @see lluna_Macros_Text
 */
void lluna_Container_String_AppendText(struct lluna_Container_String* Handle, struct lluna_Core_Types_Text Text);
/**
 * @brief Replaces the content of the string by the contents of the given string.
 *
 * @param Handle String to be replaced.
 * @param Other New string.
 */
void lluna_Container_String_Assign(struct lluna_Container_String* Handle, struct lluna_Container_String* Other);
/**
 * @brief Replaces the content of the string by the given text.
 *
 * @param Handle String to be replaced.
 * @param Text New text.
 *
 * @see lluna_Macros_Text
 */
void lluna_Container_String_AssignText(struct lluna_Container_String* Handle, struct lluna_Core_Types_Text Text);
/**
 * @brief Replaces the content of the given string by a formatted string.
 *
 * @param Handle String to replace.
 * @param Format Format string.
 * @param Args List of format arguments.
 *
 * @see lluna_Macros_Text
 */
void lluna_Container_String_Format(struct lluna_Container_String* Handle, struct lluna_Core_Types_Text Format, ...);
/**
 * @brief Clears the given string.
 *
 * Not the same as destroy. The memory will still be allocated.
 *
 * @param Handle String to clear.
 */
void lluna_Container_String_Clear(struct lluna_Container_String* Handle);

/**
 * @brief Convenience macro for iterating through all characters of the string.
 *
 * @param String String to iterate.
 * @param Pointer Iterator variable.
 */
#define lluna_Container_String_ForEach(String, Pointer) \
        for((Pointer) = (String)->Data; (Pointer) < (byte*)(String)->Data + (String)->Offset; (Pointer) += sizeof(char))
/**
 * @brief Convenience macro for iterating through all characters of the string in reversed order.
 *
 * @param String String to iterate.
 * @param Pointer Iterator variable.
 */
#define lluna_Container_String_ReversedForEach(String, Pointer) \
        for((Pointer) = (byte*)(String)->Data + (String)->Offset - sizeof(char); (Pointer) >= (String)->Data; (byte*)(Pointer) -= sizeof(char))
