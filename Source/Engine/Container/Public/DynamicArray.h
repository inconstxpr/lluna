#pragma once

/**
 * @file DynamicArray.h
 * @brief Dinamically resizing array.
 *
 * lluna_Container_DynamicArray is a general purpose, dynamically resizing array that stores copies of sized elements received as byte pointers.
 */

#include <Engine/Core/Public/Types.h>

/**
 * @brief Factor by wich the array size will increase when it's full.
 */
#define lluna_Container_DynamicArray_ResizeFactor 2

/**
 * @brief Describes a dynamic array.
 */
struct lluna_Container_DynamicArray {
        byte* Data; /**< Handle to the array data. */

        uint64 AllocatedSize; /**< Size of the currently allocated memory. */
        uint64 Offset; /**< Offset to the first empty position. */

        uint32 ElementSize; /**< Size of the stored data. Used for index calculations. */
};

/**
 * @brief Creates a dynamic array and returns a handle to it.
 *
 * Created arrays have to be manually destroyed.
 *
 * @param InitialSize Size of the initial memory allocation.
 * @param ElementSize Size of each element.
 * @return Handle to the created array.
 * 
 * @see lluna_Container_DynamicArray_Destroy
 */
struct lluna_Container_DynamicArray* lluna_Container_DynamicArray_Create(uint64 InitialSize, uint32 ElementSize);
/**
 * @brief Creates a dynamic array from the given data and returns a handle to it.
 *
 * Created arrays have to be manually destroyed.
 *
 * @param Data The data from which to create the array.
 * @param DataSize Size of the data.
 * @param ElementSize Size of each element.
 * @return Handle to the created array.
 *
 * @see lluna_Container_DynamicArray_Destroy
 */
struct lluna_Container_DynamicArray* lluna_Container_DynamicArray_CreateFromData(byte* Data, uint64 DataSize, uint32 ElementSize);
/**
 * @brief Destroys the given dynamic array.
 *
 * @param Handle Dynamic array to destroy.
 */
void lluna_Container_DynamicArray_Destroy(struct lluna_Container_DynamicArray* Handle);

/**
 * @brief Returns true if the array is empty.
 *
 * @param Handle Dynamic array to check.
 */
boolean lluna_Container_DynamicArray_Empty(struct lluna_Container_DynamicArray* Handle);
/**
 * @brief Returns the number of elements on the given array.
 *
 * @param Handle Dynamic array to count elements.
 */
uint64 lluna_Container_DynamicArray_Count(struct lluna_Container_DynamicArray* Handle);
/**
 * @brief Returns the maximum number of elements that will fit in the currently allocated space.
 *
 * @param Handle Dynamic array to get the capacity.
 */
uint64 lluna_Container_DynamicArray_Capacity(struct lluna_Container_DynamicArray* Handle);
/**
 * @brief Resizes the array to the given number of elements.
 *
 * If `Size` is smaller then the current number of elements, only `Size` elements will be kept.
 * 
 * @param Handle Dynamic array to resize.
 * @param Size New size.
 */
void lluna_Container_DynamicArray_Resize(struct lluna_Container_DynamicArray* Handle, uint64 Size);
/**
 * @brief Shrinks the array to fit the current number of elements.
 *
 * @param Handle Dynamic array to shrink.
 */
void lluna_Container_DynamicArray_Shrink(struct lluna_Container_DynamicArray* Handle);

/**
 * @brief Gets the first element.
 *
 * @param Handle Dynamic array from which to get the first element.
 */
byte* lluna_Container_DynamicArray_First(struct lluna_Container_DynamicArray* Handle);
/**
 * @brief Gets the last element.
 *
 * @param Handle Dynamic array from which to get the last element.
 */
byte* lluna_Container_DynamicArray_Last(struct lluna_Container_DynamicArray* Handle);
/**
 * @brief Gets the element at the given index.
 *
 * @param Handle Dynamic array to get the element from.
 * @param Index Index of the element to get.
 * @return Handle to the element.
 */
byte* lluna_Container_DynamicArray_Get(struct lluna_Container_DynamicArray* Handle, uint64 Index);

/**
 * @brief Inserts an element at the end of the array.
 *
 * @param Handle Dynamic array to apend the element at.
 * @param Data Pointer to the element to insert.
 */
void lluna_Container_DynamicArray_Append(struct lluna_Container_DynamicArray* Handle, byte* Data);
/**
 * @brief Inserts an element at the start of the array.
 * 
 * @param Handle Dynamic array to prepend the element at.
 * @param Data Pointer to the element to insert.
 */
void lluna_Container_DynamicArray_Prepend(struct lluna_Container_DynamicArray* Handle, byte* Data);
/**
 * @brief Inserts an element at the given index.
 *
 * If the order is not important, use lluna_Container_DynamicArray_Append instead.
 *
 * @param Handle Dynamic array to insert the element at.
 * @param Data Pointer to the element to insert.
 * @param Index Index to insert the element at.
 * 
 * @see lluna_Container_DynamicArray_Append
 */
void lluna_Container_DynamicArray_Insert(struct lluna_Container_DynamicArray* Handle, byte* Data, uint64 Index);
/**
 * @brief Removes the element at the given index.
 *
 * Replaces the element at the given index by the element at the end of the array.
 * **Does not** preserve the order of the elements.
 *
 * @param Handle Dynamic array to remove the element from.
 * @param Index Index of the data to get.
 *
 * @see lluna_Container_DynamicArray_RemoveStable
 */
void lluna_Container_DynamicArray_Remove(struct lluna_Container_DynamicArray* Handle, uint64 Index);
/**
 * @brief Removes the element at the given index.
 *
 * Preserves the order of elements.
 * If the order is not important, use lluna_Container_DynamicArray_Remove instead.
 *
 * @param Handle Dynamic array to remove the element from.
 * @param Index Index of the data to get.
 *
 * @see lluna_Container_DynamicArray_Remove
 */
void lluna_Container_DynamicArray_RemoveStable(struct lluna_Container_DynamicArray* Handle, uint64 Index);
/**
 * @brief Removes the first element.
 *
 * @param Handle Dynamic array to remove the first element from.
 */
void lluna_Container_DynamicArray_RemoveFirst(struct lluna_Container_DynamicArray* Handle);
/**
 * @brief Removes the last element.
 *
 * @param Handle Dynamic array to remove the last element from.
 */
void lluna_Container_DynamicArray_RemoveLast(struct lluna_Container_DynamicArray* Handle);
/**
 * @brief Clears the given dynamic array.
 *
 * Not the same as destroy. The memory will still be allocated.
 *
 * @param Handle Dynamic array to clear.
 */
void lluna_Container_DynamicArray_Clear(struct lluna_Container_DynamicArray* Handle);

/**
 * @brief Convenience macro for iterating through all elements of the array.
 *
 * @param DynamicArray Dynamic array to iterate.
 * @param Pointer Iterator variable.
 */
#define lluna_Container_DynamicArray_ForEach(DynamicArray, Pointer) \
        for((Pointer) = (DynamicArray)->Data; (Pointer) < (DynamicArray)->Offset; (Pointer) += (DynamicArray)->ElementSize)

 /**
  * @brief Convenience macro for iterating through all elements of the array in reversed order.
  *
  * @param DynamicArray Dynamic array to iterate.
  * @param Pointer Iterator variable.
  */
#define lluna_Container_DynamicArray_ReversedForEach(DynamicArray, Pointer) \
        for((Pointer) = (DynamicArray)->Offset - (DynamicArray)->ElementSize; (Pointer) >= (DynamicArray)->Data; (Pointer) -= (DynamicArray)->ElementSize)
