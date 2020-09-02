/* 
 * ble_nps.c : file for the Neopixel Controller ble service.
 * Author : Abdelali Boussetta  @rmptxf
 */

#include <string.h>
#include "sdk_common.h"
#include "ble_srv_common.h"
#include "app_error.h"
#include "ble_nps.h"


/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_nps       Neopixel Controller Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_nps_t * p_nps, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);

    p_nps->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;

    ble_nps_evt_t evt;

    evt.evt_type = BLE_NPS_EVT_CONNECTED;

    p_nps->evt_handler(p_nps, &evt);

}

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_nps       Neopixel Controller service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_nps_t * p_nps, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);

    p_nps->conn_handle = BLE_CONN_HANDLE_INVALID; 
      
    ble_nps_evt_t evt;

    evt.evt_type = BLE_NPS_EVT_DISCONNECTED;

    p_nps->evt_handler(p_nps, &evt);

}


/**@brief Function for handling the Write event.
 *
 * @param[in]   p_nps       Neopixel Controller structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_nps_t * p_nps, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    ble_nps_evt_t                 evt;

    //writing to the command characteristic
   if ( p_evt_write->handle == p_nps->command_char_handles.value_handle)
    { 
        evt.params_command.command_data.p_data = p_evt_write->data;
        evt.params_command.command_data.length = p_evt_write->len;
        evt.evt_type = BLE_NPS_EVT_COMMAND_RX; 

        p_nps->evt_handler(p_nps, &evt);
    }
}

/**@brief Function for handling the Neopixel Controller ble events.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
void ble_nps_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_nps_t * p_nps = (ble_nps_t *) p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_nps, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_nps, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_nps, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}

/**@brief Function for adding the Write command characteristic.
 *
 * @param[in]   p_nps        Neopixel Controller structure.
 * @param[in]   p_nps_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t command_char_add(ble_nps_t * p_nps, const ble_nps_init_t * p_nps_init)
{

    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read   = 1;
    char_md.char_props.write  = 1;        
    char_md.char_props.notify = 0; 
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL; 
    char_md.p_sccd_md         = NULL;

    ble_uuid.type = p_nps->uuid_type;
    ble_uuid.uuid = COMMAND_CHAR_UUID;

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_nps_init->command_char_attr_md.read_perm;
    attr_md.write_perm = p_nps_init->command_char_attr_md.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = 0;
    attr_char_value.max_len   = 3;

    err_code = sd_ble_gatts_characteristic_add(p_nps->service_handle, &char_md,
                                               &attr_char_value,
                                               &p_nps->command_char_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;

}

/**@brief Function for initializing the Neopixel Controller service.
 *
 * @param[in]   p_nps       Neopixel Controller service structure.
 * @param[in]   p_nps_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */

uint32_t ble_nps_init(ble_nps_t * p_nps, const ble_nps_init_t * p_nps_init)
{

    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Initializing the  service structure
    p_nps->evt_handler               = p_nps_init->evt_handler;
    p_nps->conn_handle               = BLE_CONN_HANDLE_INVALID;

    // Add the Neopixel Controller Service UUID
    ble_uuid128_t base_uuid = NPS_SERVICE_UUID_BASE;
    err_code =  sd_ble_uuid_vs_add(&base_uuid, &p_nps->uuid_type);
    VERIFY_SUCCESS(err_code);
    
    ble_uuid.type = p_nps->uuid_type;
    ble_uuid.uuid = NPS_SERVICE_UUID;

    // Add the Service to the database
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_nps->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add the command characteristic
   err_code =  command_char_add(p_nps, p_nps_init);
   APP_ERROR_CHECK(err_code);


}
