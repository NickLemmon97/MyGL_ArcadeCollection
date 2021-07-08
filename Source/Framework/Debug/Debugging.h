#pragma once

#define CHECK_FOR_MEMORY_LEAKS 1

#if defined DEBUG || defined _DEBUG
#if defined CHECK_FOR_MEMORY_LEAKS && defined _WINDOWS
//#define new   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif 
