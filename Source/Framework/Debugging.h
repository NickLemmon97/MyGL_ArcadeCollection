#pragma once

#ifdef _DEBUG
#define CHECK_FOR_MEMORY_LEAKS 1
#else
#define CHECK_FOR_MEMORY_LEAKS 0
#endif

#ifdef _DEBUG
#if CHECK_FOR_MEMORY_LEAKS
#define new   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif 

