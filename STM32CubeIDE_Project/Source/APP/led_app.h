#ifndef SOURCE_APP_LED_APP_H_
#define SOURCE_APP_LED_APP_H_
/**********************************************************************************************************************
 * Includes
 *********************************************************************************************************************/
#include <stdint.h>
/**********************************************************************************************************************
 * Exported definitions and macros
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported types
 *********************************************************************************************************************/
typedef struct {
    uint32_t led_number;
} sLedBasicCommandParams_t;

typedef struct {
    uint32_t led_number;
    uint32_t time;
    uint32_t frequency;
} sBlinkCommandParams_t;

typedef enum {
    eLedAppCmd_First = 0,
    eLedAppCmd_Set = eLedAppCmd_First,
    eLedAppCmd_Reset,
    eLedAppCmd_Toggle,
    eLedAppCmd_Blink,
    eLedAppCmd_Last
} eLedAppCmdEnum_t;

typedef struct {
    eLedAppCmdEnum_t cmd;
    void *data;
} sLedAppCmd_t;
/**********************************************************************************************************************
 * Exported variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Prototypes of exported functions
 *********************************************************************************************************************/
bool LED_APP_Init(void);
bool LED_APP_AddTask(const sLedAppCmd_t *params);
bool LED_APP_IsTimeValid(uint32_t time);
bool LED_APP_IsFrequencyValid(uint32_t frequency);
#endif /* SOURCE_APP_LED_APP_H_ */
