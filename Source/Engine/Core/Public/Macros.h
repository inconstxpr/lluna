#pragma once

/**
 * @file Types.h
 * @brief Utility macros.
 */

#include <Engine/Core/Public/Types.h>

/**
 * @brief Calculates the byte offset of a struct member.
 *
 * By casting 0 to a `Type*`, accessing a member gives us the offset in bytes from the address of the struct to the given member.
 *
 * @param Type Type of the struct.
 * @param Member Member from which to get the offset.
 */
#define lluna_Macros_OffsetOf(Type, Member) ((byte*)&((Type*)0)->Member)

/**
 * @brief Gets the container address for a given member pointer.
 *
 * @param Pointer Pointer to the member.
 * @param Type Type of the container struct.
 * @param Member Name of the member.
 */
#define lluna_Macros_ContainerOf(Pointer, Type, Member) ((Type*)((byte*)(Pointer) - lluna_Macros_OffsetOf(Type, Member)))

 /**
 * @brief Creates a sized text container from a string literal.
 *
 * @param Text String literal.
 */
#define lluna_Macros_Text(Text) ((struct lluna_Core_Types_Text){(Text), (uint64)sizeof(Text)})
