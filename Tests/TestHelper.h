#pragma once

/**
 * @file
 * @brief Utilities for testing.
 *
 * Macros for common asserts.
 * Management functions for test sessions.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Represents the state of the current test session.
 *
 * Defines a session name for better logs.
 * Keeps track of the total number of ran and failed tests.
 * Session state is managed by the functions defined on this helper.
 * Should not be written to externally.
 */
struct lluna_TestHelper_Session
{
        const char* Name; /**< Name of the session. */
        unsigned int FinishedTestCount; /**< Number of finished tests. */
        unsigned int FailedTestCount; /**< Number of failed tests. */

        unsigned int DidLastTestFail; /**< Non zero if the last test failed. */
};

/**
 * @brief Initializes a test session.
 *
 * Sets up starting values for the session state.
 *
 * @param SessionState Pointer to the session state holder.
 * @param SessionName Name of the test session.
 */
#define lluna_TestHelper_StartSession(SessionState, SessionName) \
do \
{ \
        (SessionState)->Name = SessionName; \
        (SessionState)->FinishedTestCount = 0; \
        (SessionState)->FailedTestCount = 0; \
        (SessionState)->DidLastTestFail = 0; \
} while (0);

 /**
  * @brief Finishes a test session.
  *
  * Logs success or number of failures.
  *
  * @param SessionState Pointer to the session state holder.
  */
#define lluna_TestHelper_FinishSession(SessionState) \
do \
{ \
        if ((SessionState)->FailedTestCount == 0) \
        { \
                printf("All [%u] tests passed for %s.\n", \
                        (SessionState)->FinishedTestCount, \
                        (SessionState)->Name \
                ); \
                return EXIT_SUCCESS; \
        } \
        else \
        { \
                fprintf( \
                        stderr, \
                        "[%u/%u] tests failed for %s.\n", \
                        (SessionState)->FailedTestCount, \
                        (SessionState)->FinishedTestCount, \
                        (SessionState)->Name \
                ); \
                return EXIT_FAILURE; \
        } \
} while (0);

/**
 * @brief Prints a formatted info log.
 *
 * Indents and prints the message as an info.
 *
 * @param SessionState Pointer to the session state holder.
 * @param Message Info message.
 */
#define lluna_TestHelper_Info(SessionState, Message) \
do \
{ \
        printf("   - [INFO] %s\n", Message); \
} while (0);

/**
 * @brief Prints a formatted error log and flags an error in the current test.
 *
 * Indents and prints the message as an error.
 * Flags the current test as failed.
 * Only counts as one failure even if called multiple times inside a single
 * test.
 *
 * @param SessionState Pointer to the session state holder.
 * @param Message Error message.
 */
#define lluna_TestHelper_Error(SessionState, Message)   \
do \
{ \
        if (!(SessionState)->DidLastTestFail) \
        { \
                (SessionState)->DidLastTestFail = 1; \
                ++(SessionState)->FailedTestCount; \
        } \
        printf("   - [ERROR] %s\n", Message); \
    return; \
} while (0);

/**
 * @brief Runs a test and logs it's number, name and status.
 *
 * Prints information about the test that's about to be ran.
 * Runs the given test.
 * Takes care of counting the number of tests and test status.
 *
 * @param SessionState Pointer to the session state holder.
 * @param Test Test function name (not a string).
 */
#define lluna_TestHelper_RunTest(SessionState, Test) \
do \
{ \
        printf("- Running test: [%u] %s\n", (SessionState)->FinishedTestCount, #Test); \
        (SessionState)->DidLastTestFail = 0; \
        Test(); \
        printf("   - %s\n", (SessionState)->DidLastTestFail ? "FAILED" : "PASSED");  \
        ++(SessionState)->FinishedTestCount; \
} while (0);

/**
 * @brief Checks if the given values are equal.
 *
 * @param Left First value to be checked.
 * @param Right Second value to be checked.
 * @param SessionState Pointer to the session state holder.
 * @param Message Check failure message.
 */
#define lluna_TestHelper_CheckEqual(Left, Right, SessionState, Message) \
if (!((Left) == (Right))) \
{ \
        lluna_TestHelper_Error(SessionState, Message); \
}

/**
 * @brief Checks if the given values are not equal.
 *
 * @param Left First value to be checked.
 * @param Right Second value to be checked.
 * @param SessionState Pointer to the session state holder.
 * @param Message Check failure message.
 */
#define lluna_TestHelper_CheckNotEqual(Left, Right, SessionState, Message) \
if (!((Left) != (Right))) \
{ \
        lluna_TestHelper_Error(SessionState, Message); \
}

/**
 * @brief Checks if the given value is true.
 *
 * @param Value the value to be checked.
 * @param SessionState Pointer to the session state holder.
 * @param Message Check failure message.
 */
#define lluna_TestHelper_CheckTrue(Value, SessionState, Message) \
if (!(Value)) \
{ \
        lluna_TestHelper_Error(SessionState, Message) \
}

/**
 * @brief Checks if the given value is false.
 *
 * @param Value the value to be checked.
 * @param SessionState Pointer to the session state holder.
 * @param Message Check failure message.
 */
#define lluna_TestHelper_CheckFalse(Value, SessionState, Message) \
if (!!(Value)) \
{ \
        lluna_TestHelper_Error(SessionState, Message); \
}
