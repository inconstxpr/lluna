String
======

**Header:** `String.h`

.. doxygenfile:: String.h
        :sections: briefdescription detaileddescription

.. contents:: Overview:

Handle
------
.. doxygenstruct:: lluna_Container_String
        :members:

Lifecycle
---------
.. doxygenfunction:: lluna_Container_String_Create
.. doxygenfunction:: lluna_Container_String_CreateFromText
.. doxygenfunction:: lluna_Container_String_CreateFormatted
.. doxygenfunction:: lluna_Container_String_Destroy

Capacity
--------
.. doxygenfunction:: lluna_Container_String_Empty
.. doxygenfunction:: lluna_Container_String_Length
.. doxygenfunction:: lluna_Container_String_Capacity
.. doxygenfunction:: lluna_Container_String_Resize
.. doxygenfunction:: lluna_Container_String_Shrink

Access
------
.. doxygenfunction:: lluna_Container_String_Equals
.. doxygenfunction:: lluna_Container_String_EqualsText
.. doxygenfunction:: lluna_Container_String_Compare
.. doxygenfunction:: lluna_Container_String_CompareText
.. doxygenfunction:: lluna_Container_String_First
.. doxygenfunction:: lluna_Container_String_Last
.. doxygenfunction:: lluna_Container_String_Get

Traversal
---------
.. doxygendefine:: lluna_Container_String_ForEach
.. doxygendefine:: lluna_Container_String_ReversedForEach

Modifiers
---------
.. doxygenfunction:: lluna_Container_String_Append
.. doxygenfunction:: lluna_Container_String_AppendText
.. doxygenfunction:: lluna_Container_String_Assign
.. doxygenfunction:: lluna_Container_String_AssignText
.. doxygenfunction:: lluna_Container_String_Format
.. doxygenfunction:: lluna_Container_String_Clear
