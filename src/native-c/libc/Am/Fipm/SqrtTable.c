#include <libc/core.h>
#include <Am/Fipm/SqrtTable.h>
#include <libc/Am/Fipm/SqrtTable.h>
#include <Am/Lang/ClassRef.h>
#include <Am/Lang/Object.h>
#include <Am/Lang/Int.h>
#include <Am/Lang/Array.h>
#include <Am/Lang/Exception.h>
#include <Am/Lang/String.h>
#include <libc/core_inline_functions.h>
#include <math.h>

unsigned int sqrt_table_fixed_4_28[101] = {
0x0, 
0x10000000, 
0x16a09e66, 
0x1bb67ae8, 
0x20000000, 
0x23c6ef37, 
0x27311c28, 
0x2a54ff53, 
0x2d413ccc, 
0x30000000, 
0x3298b075, 
0x3510e527, 
0x376cf5d0, 
0x39b05688, 
0x3bddd422, 
0x3df7bd62, 
0x40000000, 
0x41f83d9a, 
0x43e1db33, 
0x45be0cd1, 
0x478dde6e, 
0x49523ae4, 
0x4b0bf165, 
0x4cbbb9d5, 
0x4e623850, 
0x50000000, 
0x5195957c, 
0x532370b9, 
0x54a9fea7, 
0x5629a292, 
0x57a2b748, 
0x59159015, 
0x5a827999, 
0x5be9ba85, 
0x5d4b9436, 
0x5ea84346, 
0x60000000, 
0x6152fecd, 
0x62a17093, 
0x63eb8305, 
0x653160eb, 
0x66733266, 
0x67b11d28, 
0x68eb44a8, 
0x6a21ca4f, 
0x6b54cda5, 
0x6c846c71, 
0x6db0c2e0, 
0x6ed9eba1, 
0x70000000, 
0x71231800, 
0x72434a74, 
0x7360ad11, 
0x747b5481, 
0x75935478, 
0x76a8bfbe, 
0x77bba845, 
0x78cc1f31, 
0x79da34e6, 
0x7ae5f915, 
0x7bef7ac5, 
0x7cf6c85d, 
0x7dfbefae, 
0x7efefdfa, 
0x80000000, 
0x80ff01fb, 
0x81fc0fb1, 
0x82f73477, 
0x83f07b35, 
0x84e7ee6c, 
0x85dd983d, 
0x86d1826c, 
0x87c3b666, 
0x88b43d45, 
0x89a31fd1, 
0x8a906689, 
0x8b7c19a3, 
0x8c66410e, 
0x8d4ee47b, 
0x8e360b59, 
0x8f1bbcdc, 
0x90000000, 
0x90e2db86, 
0x91c45600, 
0x92a475c8, 
0x9383410c, 
0x9460bdc9, 
0x953cf1d1, 
0x9617e2ca, 
0x96f19633, 
0x97ca1161, 
0x98a15985, 
0x997773ab, 
0x9a4c64bd, 
0x9b203182, 
0x9bf2dea0, 
0x9cc470a0, 
0x9d94ebeb, 
0x9e6454cd, 
0x9f32af77, 
0xa0000000,
};

// returns a 16:16 fixed point square root of n
unsigned int sqrt_100(unsigned int n) {
	unsigned int nn = n; // 1034324
	unsigned int pow100 = 1;
	unsigned int pow10 = 1;
	while(nn > 99) {
		nn = nn / 100;
		pow100 *= 100;
		pow10 *= 10;
	}
	unsigned int sqrtn = sqrt_table_fixed_4_28[nn];

	if (nn != n) {
		unsigned int nnpow = nn * pow100;
		unsigned int next = (nn + 1) * pow100;
		unsigned int delta = n - nnpow;
		unsigned int max = next - nnpow;
		unsigned int ratio16 = ((unsigned long long) delta << 16) / max;
		if (ratio16 < 0x10000 && ratio16 > 0) {
			unsigned int diff = sqrt_table_fixed_4_28[nn + 1] - sqrtn;
			unsigned int offset = (((unsigned long long) diff * ratio16) >> 16);
			return (unsigned int) (((unsigned long long) (sqrtn + offset) * pow10) >> 12);
		} else {
			return (unsigned int) (((unsigned long long) sqrtn * pow10) >> 12);		
		}
	}
	return sqrtn >> 12;
}

function_result Am_Fipm_SqrtTable__native_init_0(aobject * const this)
{
	function_result __result = { .has_return_value = false };
	bool __returning = false;
	// Add reference count for this in SqrtTable._native_init
	if (this != NULL) {
		__increase_reference_count(this);
	}
	// TODO: implement native function Am_Fipm_SqrtTable__native_init_0
__exit: ;
	if (this != NULL) {
		__decrease_reference_count(this);
	}
	return __result;
}

function_result Am_Fipm_SqrtTable__native_release_0(aobject * const this)
{
	function_result __result = { .has_return_value = false };
	bool __returning = false;
	// TODO: implement native function Am_Fipm_SqrtTable__native_release_0
__exit: ;
	return __result;
}

function_result Am_Fipm_SqrtTable__native_mark_children_0(aobject * const this)
{
	function_result __result = { .has_return_value = false };
	bool __returning = false;
	// TODO: implement native function Am_Fipm_SqrtTable__native_mark_children_0
__exit: ;
	return __result;
}

function_result Am_Fipm_SqrtTable_initTable_0(aobject * const this, aobject * table, unsigned int size)
{
	function_result __result = { .has_return_value = false };
	bool __returning = false;
	// Add reference count for this in SqrtTable.initTable
	if (this != NULL) {
		__increase_reference_count(this);
	}
	// Add reference count for table in SqrtTable.initTable
	if (table != NULL) {
		__increase_reference_count(table);
	}

	unsigned int * values = (unsigned int *) get_array_holder(table)->array_data;

	for(unsigned int i = 0; i < size; i++) {
		values[i] = sqrt_100(i);
	}

__exit: ;
	if (this != NULL) {
		__decrease_reference_count(this);
	}
	if (table != NULL) {
		__decrease_reference_count(table);
	}
	return __result;
}

