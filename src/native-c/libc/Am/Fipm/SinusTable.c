#include <libc/core.h>
#include <Am/Fipm/SinusTable.h>
#include <libc/Am/Fipm/SinusTable.h>
#include <Am/Lang/ClassRef.h>
#include <Am/Lang/Object.h>
#include <Am/Lang/Int.h>
#include <Am/Lang/Array.h>
#include <Am/Lang/Exception.h>
#include <Am/Lang/String.h>
#include <libc/core_inline_functions.h>

function_result Am_Fipm_SinusTable__native_init_0(aobject * const this)
{
	function_result __result = { .has_return_value = false };
	bool __returning = false;
	// Add reference count for this in SinusTable._native_init
	if (this != NULL) {
		__increase_reference_count(this);
	}
	// TODO: implement native function Am_Fipm_SinusTable__native_init_0
__exit: ;
	if (this != NULL) {
		__decrease_reference_count(this);
	}
	return __result;
}

function_result Am_Fipm_SinusTable__native_release_0(aobject * const this)
{
	function_result __result = { .has_return_value = false };
	bool __returning = false;
	// TODO: implement native function Am_Fipm_SinusTable__native_release_0
__exit: ;
	return __result;
}

function_result Am_Fipm_SinusTable__native_mark_children_0(aobject * const this)
{
	function_result __result = { .has_return_value = false };
	bool __returning = false;
	// TODO: implement native function Am_Fipm_SinusTable__native_mark_children_0
__exit: ;
	return __result;
}

function_result Am_Fipm_SinusTable_initTable_0(aobject * const this, aobject * table, int size)
{
	function_result __result = { .has_return_value = false };
	bool __returning = false;
	// Add reference count for this in SinusTable.initTable
	if (this != NULL) {
		__increase_reference_count(this);
	}
	// Add reference count for table in SinusTable.initTable
	if (table != NULL) {
		__increase_reference_count(table);
	}
	// TODO: implement native function Am_Fipm_SinusTable_initTable_0
__exit: ;
	if (this != NULL) {
		__decrease_reference_count(this);
	}
	if (table != NULL) {
		__decrease_reference_count(table);
	}
	return __result;
}

