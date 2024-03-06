#ifndef SOURCE_API_MEMORY_API_H_
#define SOURCE_API_MEMORY_API_H_
/**********************************************************************************************************************
 * Includes
 *********************************************************************************************************************/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/**********************************************************************************************************************
 * Exported definitions and macros
 *********************************************************************************************************************/
#define Memory_API_Malloc(size)        Memory_API_Alloc(false, 1, (size))
#define Memory_API_Calloc(count, size) Memory_API_Alloc(true, (count), (size))
/**********************************************************************************************************************
 * Exported types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Prototypes of exported functions
 *********************************************************************************************************************/
bool Memory_API_Init(void);
void *Memory_API_Alloc(bool is_calloc, size_t count, size_t size);
void Memory_API_Free(void *ptr);
int32_t Memory_API_GetAllocCounter(void);
#endif /* SOURCE_API_MEMORY_API_H_ */
