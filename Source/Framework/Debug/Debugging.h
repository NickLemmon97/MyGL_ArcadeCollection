#pragma once

#define CHECK_FOR_MEMORY_LEAKS 1

#if defined DEBUG || _DEBUG || defined DEVELOPMENT
#if CHECK_FOR_MEMORY_LEAKS
#define new   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif 
