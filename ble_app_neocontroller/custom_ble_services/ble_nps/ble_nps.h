
/* 
 * ble_nps.h  : file for the ble Custom Neopixel Controller ble service.
 * Author : Abdelali Boussetta  @rmptxf
 */

/*
 * Neopixel controller service uuid     :   f4581400-b000-4042-ba50-05ca45ba4512
 * command characteistic uuid           :   f4581401-b000-4042-ba50-05ca45ba4512
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"

#define BLE_NPS_BLE_OBSERVER_PRIO   2       

/**@brief   Macro for defining a ble_nps instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_NPS_DEF(_name)                                                            \
static ble_nps_t _name;                                                               \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                   \
                     BLE_NPS_BLE_OBSERVER_PRIO,                                       \
                     ble_nps_on_ble_evt, &_name)


#define NPS_SERVICE_UUID_BASE         {0x12, 0x45, 0xBA, 0x45, 0xCA, 0x05, 0x50, 0xBA,\
                                       0x42, 0x40, 0x00, 0xB0, 0x00, 0x00, 0x58, 0xF4}

#define NPS_SERVICE_UUID              0x1400
#define COMMAND_CHAR_UUID             0x1401

// Neocontroller ble service ble events																	
typedef enum
{      
    BLE_NPS_EVT_CONNECTED,
    BLE_NPS_EVT_DISCONNECTED,
    BLE_NPS_EVT_COMMAND_RX

} ble_nps_evt_type_t;


typedef struct 
{
    uint8_t const * p_data;   
    uint16_t   length;   

} ble_nps_evt_command_data_t;


typedef struct
{
    ble_nps_evt_type_t evt_type;                    

 union
  {
      ble_nps_evt_command_data_t command_data;
       
  } params_command;

} ble_nps_evt_t;


typedef struct ble_nps_s ble_nps_t;


typedef void (*ble_nps_evt_handler_t) (ble_nps_t * p_nps, ble_nps_evt_t * p_evt);


typedef struct
{
    ble_nps_evt_handler_t          evt_handler;                   /**< Event handler to be called for handling events in the Neocontroller Service. */  
    ble_srv_cccd_security_mode_t   command_char_attr_md;          /**< Initial security level for the command characteristic attribute */

} ble_nps_init_t;


// Neopixel controller Service structure. This contains various status information for the service. */
struct ble_nps_s
{
    ble_nps_evt_handler_t         evt_handler;                    /**< Event handler to be called for handling events in the Neocontroller Service. */
    uint16_t                      service_handle;                 /**< Handle of Neocontroller Service (as provided by the BLE stack). */
 
    ble_gatts_char_handles_t      command_char_handles;           /**< Handles related to the command Value characteristic (Written to data). */   

    uint16_t                      conn_handle;                    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint8_t                       uuid_type;                      /**< Holds the Neopixel controller Service UUID type. */
};


/**@brief Function for handling the Neopixel Controller ble events.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
void ble_nps_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for initializing the Neopixel controller service.
 *
 * @param[in]   p_nps        Neopixel controller Service structure.
 * @param[in]   p_nps_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_nps_init(ble_nps_t * p_nps, const ble_nps_init_t * p_nps_init);
