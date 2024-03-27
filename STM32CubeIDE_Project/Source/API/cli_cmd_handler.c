/**********************************************************************************************************************
 * Includes
 *********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "debug_api.h"
#include "memory_api.h"
#include "led_app.h"
#include "led_api.h"
#include "cli_cmd_handler.h"
/**********************************************************************************************************************
 * Private definitions and macros
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private typedef
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private constants
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private variables
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 * Exported variables and references
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Prototypes of private functions
 *********************************************************************************************************************/
static bool CLI_CMD_CheckCmdParams (const sCommandParams_t *cmd_params);
/**********************************************************************************************************************
 * Definitions of private functions
 *********************************************************************************************************************/
static bool CLI_CMD_CheckCmdParams (const sCommandParams_t *cmd_params) {
    if (cmd_params == NULL) {
        return false;
    }
    if ((cmd_params->params == NULL) || (cmd_params->response == NULL) || (cmd_params->response_size == 0)) {
        snprintf(cmd_params->response, cmd_params->response_size, "Internal error\r");
        return false;
    }
    return true;
}
/**********************************************************************************************************************
 * Definitions of exported functions
 *********************************************************************************************************************/
bool CLI_CMD_LedSetHandler (const sCommandParams_t *cmd_params) {
    if (CLI_CMD_CheckCmdParams(cmd_params) == false) {
        return false;
    }
    if (isdigit((unsigned char)cmd_params->params[0]) == 0) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid Input\r");
        return false;
    }
    char *end_ptr = NULL;
    uint32_t led_number = strtoul(cmd_params->params, &end_ptr, 10);
    if ((cmd_params->params == end_ptr) || (*end_ptr != '\0')) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid Input: LED number is incorrect format.\r");
        return false;
    }
    if (LED_API_IsLEDValid(led_number) == false) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid Input: LED number out of range.\r");
        return false;
    }
    sLedBasicCommandParams_t *led_params = (sLedBasicCommandParams_t *)Memory_API_Malloc(sizeof(sLedBasicCommandParams_t));
    if (led_params == NULL) {
        snprintf(cmd_params->response, cmd_params->response_size, "Internal Error\r");
        return false;
    }
    led_params->led_number = led_number;
    sLedAppCmd_t led_app_cmd = {.cmd = eLedAppCmd_Set, .data = led_params};
    if (LED_APP_AddTask(&led_app_cmd) == false) {
        snprintf(cmd_params->response, cmd_params->response_size, "Error: LED task queue is full.\r");
        Memory_API_Free(led_params);
        return false;
    }
    snprintf(cmd_params->response, cmd_params->response_size, "Turning on %s LED\r", LED_API_LedEnumToString(led_number));
    return true;
}

bool CLI_CMD_LedResetHandler (const sCommandParams_t *cmd_params) {
    if (CLI_CMD_CheckCmdParams(cmd_params) == false) {
        return false;
    }
    if (isdigit((unsigned char)cmd_params->params[0]) == 0) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid Input\r");
        return false;
    }
    char *end_ptr = NULL;
    uint32_t led_number = strtoul(cmd_params->params, &end_ptr, 10);
    if ((cmd_params->params == end_ptr) || (*end_ptr != '\0')) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid Input: LED number is incorrect format.\r");
        return false;
    }
    if (LED_API_IsLEDValid(led_number) == false) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid Input: LED number out of range.\r");
        return false;
    }
    sLedBasicCommandParams_t *led_params = (sLedBasicCommandParams_t *)Memory_API_Malloc(sizeof(sLedBasicCommandParams_t));
    if (led_params == NULL) {
        snprintf(cmd_params->response, cmd_params->response_size, "Internal Error\r");
        return false;
    }
    led_params->led_number = led_number;
    sLedAppCmd_t led_app_cmd = {.cmd = eLedAppCmd_Reset, .data = led_params};
    if (LED_APP_AddTask(&led_app_cmd) == false) {
        snprintf(cmd_params->response, cmd_params->response_size, "Error: LED task queue is full.\r");
        Memory_API_Free(led_params);
        return false;
    }
    snprintf(cmd_params->response, cmd_params->response_size, "Turning off %s LED\r", LED_API_LedEnumToString(led_number));
    return true;
}

bool CLI_CMD_LedToggleHandler (const sCommandParams_t *cmd_params) {
    if (CLI_CMD_CheckCmdParams(cmd_params) == false) {
        return false;
    }
    if (isdigit((unsigned char)cmd_params->params[0]) == 0) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid Input\r");
        return false;
    }
    char *end_ptr = NULL;
    uint32_t led_number = strtoul(cmd_params->params, &end_ptr, 10);
    if ((cmd_params->params == end_ptr) || (*end_ptr != '\0')) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid Input: LED number is incorrect format.\r");
        return false;
    }
    if (LED_API_IsLEDValid(led_number) == false) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid Input: LED number out of range.\r");
        return false;
    }
    sLedBasicCommandParams_t *led_params = (sLedBasicCommandParams_t *)Memory_API_Malloc(sizeof(sLedBasicCommandParams_t));
    if (led_params == NULL) {
        snprintf(cmd_params->response, cmd_params->response_size, "Internal Error\r");
        return false;
    }
    led_params->led_number = led_number;
    sLedAppCmd_t led_app_cmd = {.cmd = eLedAppCmd_Toggle, .data = led_params};
    if (LED_APP_AddTask(&led_app_cmd) == false) {
        snprintf(cmd_params->response, cmd_params->response_size, "Error: LED task queue is full.\r");
        Memory_API_Free(led_params);
        return false;
    }
    snprintf(cmd_params->response, cmd_params->response_size, "Toggling %s LED\r", LED_API_LedEnumToString(led_number));
    return true;
}

bool CLI_CMD_LedBlinkHandler (const sCommandParams_t *cmd_params) {
    if (CLI_CMD_CheckCmdParams(cmd_params) == false) {
        return false;
    }
    const char *led_command_delimiter = ",";
    char *saveptr = NULL;
    char *token = NULL;
    token = strtok_r((char *)cmd_params->params, led_command_delimiter, &saveptr);
    if (token == NULL) {
        snprintf(cmd_params->response, cmd_params->response_size, "Missing LED number\r");
        return false;
    }
    char *end_ptr = NULL;
    uint32_t led_number = strtoul(token, &end_ptr, 10);
    if ((*end_ptr != '\0') || (LED_API_IsLEDValid(led_number) == false)) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid LED number\r");
        return false;
    }
    token = strtok_r(NULL, led_command_delimiter, &saveptr);
    if (token == NULL) {
        snprintf(cmd_params->response, cmd_params->response_size, "Missing time parameter.\r");
        return false;
    }
    uint32_t time = strtoul(token, &end_ptr, 10);
    if ((*end_ptr != '\0') || (LED_APP_IsTimeValid(time) == false)) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid time\r");
        return false;
    }
    token = strtok_r(NULL, led_command_delimiter, &saveptr);
    if (token == NULL) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid Input: Missing frequency\r");
        return false;
    }
    uint32_t frequency = strtoul(token, &end_ptr, 10);
    if ((*end_ptr != '\0') || (LED_APP_IsFrequencyValid(frequency) == false)) {
        snprintf(cmd_params->response, cmd_params->response_size, "Invalid frequency\r");
        return false;
    }
    sBlinkCommandParams_t *blink_params = (sBlinkCommandParams_t *)Memory_API_Malloc(sizeof(sBlinkCommandParams_t));
    if (blink_params == NULL) {
        snprintf(cmd_params->response, cmd_params->response_size, "Internal Error\r");
        return false;
    }
    blink_params->led_number = led_number;
    blink_params->time = time;
    blink_params->frequency = frequency;
    sLedAppCmd_t led_app_cmd = {.cmd = eLedAppCmd_Blink, .data = blink_params};
    if (LED_APP_AddTask(&led_app_cmd) == false) {
        snprintf(cmd_params->response, cmd_params->response_size, "LED task queue is full.\r");
        Memory_API_Free(blink_params);
        return false;
    }
    snprintf(cmd_params->response, cmd_params->response_size, "Blinking %s LED\r", LED_API_LedEnumToString(led_number));
    return true;
}
