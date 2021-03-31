#pragma once

/**
 * @file Types.h
 * @brief Common base types.
 */

/**
 * @brief Unsigned 8 bit integer.
 */
typedef unsigned char uint8;
/**
 * @brief Unsigned 16 bit integer.
 */
typedef unsigned short int uint16;
/**
 * @brief Unsigned 32 bit integer.
 */
typedef unsigned int uint32;
/**
 * @brief Unsigned 64 bit integer.
 */
typedef unsigned long long uint64;

/**
 * @brief Signed 8 bit integer.
 */
typedef signed char int8;
/**
 * @brief Signed 16 bit integer.
 */
typedef signed short int int16;
/**
 * @brief Signed 32 bit integer.
 */
typedef signed int int32;
/**
 * @brief Signed 64 bit integer.
 */
typedef signed long long int64;

/**
 * @brief Generic byte.
 *
 * Alternate name for uint8.
 *
 * @see uint8
 */
typedef uint8 byte;

/**
 * @brief Boolean.
 */
typedef uint8 boolean;
/**
 * @brief Logic true.
 */
#define true 1
/**
 * @brief Logic false.
 */
#define false 0

/**
 * @brief Container for sized text.
 *
 * @see lluna_Macros_Text
 */
struct lluna_Core_Types_Text
{
        const char* Data; /**< Text data. */
        uint64 Size; /**< Text size. */
};
