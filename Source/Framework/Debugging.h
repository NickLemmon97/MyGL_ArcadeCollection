#pragma once

<<<<<<< HEAD
#ifdef DEBUG
=======
#ifdef _DEBUG
>>>>>>> 324a7d51fb6e75d4e8256223bc5b379d8845a53a
#define CHECK_FOR_MEMORY_LEAKS 1
#else
#define CHECK_FOR_MEMORY_LEAKS 0
#endif

#ifdef DEBUG
#if CHECK_FOR_MEMORY_LEAKS
#define new   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif 
