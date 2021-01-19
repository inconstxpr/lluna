Dynamic Array
=============

**Header:** `DynamicArray.h`

.. doxygenfile:: DynamicArray.h
        :sections: briefdescription detaileddescription

.. contents:: Overview:

Handle
------
.. doxygenstruct:: lluna_Container_DynamicArray
        :members:

Constants
---------
.. doxygendefine:: lluna_Container_DynamicArray_ResizeFactor

Lifecycle
---------
.. doxygenfunction:: lluna_Container_DynamicArray_Create
.. doxygenfunction:: lluna_Container_DynamicArray_CreateFromData
.. doxygenfunction:: lluna_Container_DynamicArray_Destroy

Capacity
--------
.. doxygenfunction:: lluna_Container_DynamicArray_Empty
.. doxygenfunction:: lluna_Container_DynamicArray_Count
.. doxygenfunction:: lluna_Container_DynamicArray_Capacity
.. doxygenfunction:: lluna_Container_DynamicArray_Resize
.. doxygenfunction:: lluna_Container_DynamicArray_Shrink

Access
------
.. doxygenfunction:: lluna_Container_DynamicArray_First
.. doxygenfunction:: lluna_Container_DynamicArray_Last
.. doxygenfunction:: lluna_Container_DynamicArray_Get

Traversal
---------
.. doxygendefine:: lluna_Container_DynamicArray_ForEach
.. doxygendefine:: lluna_Container_DynamicArray_ReversedForEach

Modifiers
---------
.. doxygenfunction:: lluna_Container_DynamicArray_Append
.. doxygenfunction:: lluna_Container_DynamicArray_Prepend
.. doxygenfunction:: lluna_Container_DynamicArray_Insert
.. doxygenfunction:: lluna_Container_DynamicArray_Remove
.. doxygenfunction:: lluna_Container_DynamicArray_RemoveStable
.. doxygenfunction:: lluna_Container_DynamicArray_RemoveFirst
.. doxygenfunction:: lluna_Container_DynamicArray_RemoveLast
.. doxygenfunction:: lluna_Container_DynamicArray_Clear
