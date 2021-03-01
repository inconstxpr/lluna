#pragma once

/**
 * @file RedBlackTree.h
 * @brief Base logic for red-black trees.
 *
 * lluna_Container_RedBlackTree is a general purpose red black tree base implementation.
 */

#include <Engine/Core/Public/Macros.h>
#include <Engine/Core/Public/Types.h>

/**
 * @brief Renamed byte used to store color as a character.
 */
typedef byte lluna_Container_RedBlackTree_Color;
/**
 * @brief Color black.
 */
#define lluna_Container_RedBlackTree_Black 'B'
/**
 * @brief Color red.
 */
#define lluna_Container_RedBlackTree_Red 'R'

/**
 * @brief Describes a red-black tree node.
 */
struct lluna_Container_RedBlackTree_Node
{
        lluna_Container_RedBlackTree_Color Color; /**< Color of the node. */

        struct lluna_Container_RedBlackTree_Node* Parent; /**< Parent of this subtree. */
        struct lluna_Container_RedBlackTree_Node* Left; /**< Left subtree. */
        struct lluna_Container_RedBlackTree_Node* Right; /**< Right subtree. */
};
/**
 * @brief Describes a red-black tree.
 */
struct lluna_Container_RedBlackTree
{
        struct lluna_Container_RedBlackTree_Node* Root; /**< Root of the tree. */
};

/**
 * @brief Creates a red-black tree and returns a handle to it.
 *
 * Created red-black trees have to be manually destroyed.
 *
 * @return Handle to the created red-black tree.
 *
 * @see lluna_Container_RedBlackTree_Destroy
 */
struct lluna_Container_RedBlackTree* lluna_Container_RedBlackTree_Create();
/**
 * @brief Initializes a red-black tree node.
 *
 * Must be called on all nodes before they're used.
 *
 * @param Node Pointer to the node to initialize.
 */
void lluna_Container_RedBlackTree_InitializeNode(struct lluna_Container_RedBlackTree_Node* Node);
/**
 * @brief Destroys the given red-black tree.
 *
 * @param Handle Red-black tree to destroy.
 */
void lluna_Container_RedBlackTree_Destroy(struct lluna_Container_RedBlackTree* Handle);

/**
 * @brief Returns true if the tree is empty.
 *
 * @param Handle Red black tree to check.
 */
boolean lluna_Container_RedBlackTree_Empty(struct lluna_Container_RedBlackTree* Handle);
/**
 * @brief Returns the number of elements on the given red black tree.
 *
 * @param Handle Red black tree to count elements.
 */
uint64 lluna_Container_RedBlackTree_Count(struct lluna_Container_RedBlackTree* Handle);

/**
 * @brief Gets the leftmost node.
 *
 * @param Handle Tree from which to get the leftmost node.
 * @return Leftmost node.
 */
struct lluna_Container_RedBlackTree_Node* lluna_Container_RedBlackTree_First(struct lluna_Container_RedBlackTree* Handle);
/**
 * @brief Gets the rightmost node.
 *
 * @param Handle Tree from which to get the rightmost node.
 * @return Rightmost node.
 */
struct lluna_Container_RedBlackTree_Node* lluna_Container_RedBlackTree_Last(struct lluna_Container_RedBlackTree* Handle);
/**
 * @brief Gets the next node.
 *
 * @param Node Current node.
 * @return Next node.
 */
struct lluna_Container_RedBlackTree_Node* lluna_Container_RedBlackTree_Next(struct lluna_Container_RedBlackTree_Node* Node);
/**
 * @brief Gets the previous node.
 *
 * @param Node Current node.
 * @return Previous node.
 */
struct lluna_Container_RedBlackTree_Node* lluna_Container_RedBlackTree_Previous(struct lluna_Container_RedBlackTree_Node* Node);

/**
 * @brief Links a tree to the given parent.
 *
 * Only initialized nodes should be linked.
 *
 * @param Node Node to link.
 * @param Parent Node that will become the parent.
 * @param Link Parent link.
 * @return New tree root.
 *
 * @see lluna_Container_RedBlackTree_InitializeNode
 */
void lluna_Container_RedBlackTree_Link(struct lluna_Container_RedBlackTree_Node* Node, struct lluna_Container_RedBlackTree_Node* Parent, struct lluna_Container_RedBlackTree_Node** Link);
/**
 * @brief Rebalances the tree after the given node has been linked.
 *
 * @param Handle The tree to rebalance.
 * @param FixupTarget Node that was linked.
 */
void lluna_Container_RedBlackTree_InsertFixup(struct lluna_Container_RedBlackTree* Handle, struct lluna_Container_RedBlackTree_Node* FixupTarget);
/**
 * @brief Removes a node from the tree.
 *
 * @param Handle Tree to remove the element from.
 * @param Node Node to remove.
 */
void lluna_Container_RedBlackTree_Remove(struct lluna_Container_RedBlackTree* Handle, struct lluna_Container_RedBlackTree_Node* Node);

/**
 @brief Convenience macro for iterating through all nodes of the tree in order.

 @param RedBlackTree Red-black tree to iterate.
 @param Pointer Iterator variable.
 */
#define lluna_Container_RedBlackTree_ForEach(RedBlackTree, Pointer) \
        for((Pointer) = lluna_Container_RedBlackTree_First(RedBlackTree); (Pointer); (Pointer) = lluna_Container_RedBlackTree_Next(Pointer))
 /**
  @brief Convenience macro for iterating through all nodes of the tree in reverse order.

  @param RedBlackTree Red-black tree to iterate.
  @param Pointer Iterator variable.
  */
#define lluna_Container_RedBlackTree_ReversedForEach(RedBlackTree, Pointer) \
        for((Pointer) = lluna_Container_RedBlackTree_Last(RedBlackTree); (Pointer); (Pointer) = lluna_Container_RedBlackTree_Previous(Pointer))
