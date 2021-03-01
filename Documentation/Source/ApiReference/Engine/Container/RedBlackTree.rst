Red Black Tree
==============

**Header:** `RedBlackTree.h`

.. doxyfile:: RedBlackTree.h
        :sections: briefdescription detaileddescription

.. contents:: Overview:

Handle
------
.. doxygenstruct:: lluna_Container_RedBlackTree_Node
        :members:

.. doxygenstruct:: lluna_Container_RedBlackTree
        :members:

.. doxygentypedef:: lluna_Container_RedBlackTree_Color

Constants
---------
.. doxygendefine:: lluna_Container_RedBlackTree_Black
.. doxygendefine:: lluna_Container_RedBlackTree_Red

Lifecycle
---------
.. doxygenfunction:: lluna_Container_RedBlackTree_Create
.. doxygenfunction:: lluna_Container_RedBlackTree_InitializeNode
.. doxygenfunction:: lluna_Container_RedBlackTree_Destroy

Capacity
--------
.. doxygenfunction:: lluna_Container_RedBlackTree_Empty
.. doxygenfunction:: lluna_Container_RedBlackTree_Count

Access
------
.. doxygenfunction:: lluna_Container_RedBlackTree_First
.. doxygenfunction:: lluna_Container_RedBlackTree_Last
.. doxygenfunction:: lluna_Container_RedBlackTree_Next
.. doxygenfunction:: lluna_Container_RedBlackTree_Previous

Traversal
---------
.. doxygendefine:: lluna_Container_RedBlackTree_ForEach
.. doxygendefine:: lluna_Container_RedBlackTree_ReversedForEach

Modifiers
---------
.. doxygenfunction:: lluna_Container_RedBlackTree_Link
.. doxygenfunction:: lluna_Container_RedBlackTree_InsertFixup
.. doxygenfunction:: lluna_Container_RedBlackTree_Remove
