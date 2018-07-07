/******************************************************************************

 @file       simple_gatt_profile.c

 @brief This file contains the Simple GATT profile sample GATT service profile
        for use with the BLE sample application.

 Group: CMCU, SCS
 Target Device: CC2640R2

 ******************************************************************************
 
 Copyright (c) 2010-2017, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 Release Name: simplelink_cc2640r2_sdk_1_40_00_45
 Release Date: 2017-07-20 17:16:59
 *****************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include <string.h>
#include <icall.h>
#include "util.h"
/* This Header file contains all BLE API and icall structure definition */
#include "icall_ble_api.h"

#include "simple_gatt_profile.h"

#include "simple_peripheral.h"
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

#define SERVAPP_NUM_ATTR_SUPPORTED        8//24//17

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */
// Simple GATT Profile Service UUID: 0xFFF0
CONST uint8 simpleProfileServUUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_SERV_UUID), HI_UINT16(SIMPLEPROFILE_SERV_UUID)
};

/***************************************************************************/
// Characteristic BTPWrite UUID: 0xFFF6
CONST uint8 simpleProfileBTPWriteUUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(BTPWriteChannel_UUID), HI_UINT16(BTPWriteChannel_UUID)
};

// Characteristic BTPNotify UUID: 0xFFF7
CONST uint8 simpleProfileBTPNotifyUUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(BTPNotifyChannel_UUID), HI_UINT16(BTPNotifyChannel_UUID)
};
/***************************************************************************/

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

static simpleProfileCBs_t *simpleProfile_AppCBs = NULL;

/*********************************************************************
 * Profile Attributes - variables
 */

// Simple Profile Service attribute
static CONST gattAttrType_t simpleProfileService = { ATT_BT_UUID_SIZE, simpleProfileServUUID };

/***************************************************************************/
BTP_DataMsg_Struct BTP_DataMsg;
// Simple Profile BTPWriteChannel Properties
static uint8 BTPWriteChannelProps = GATT_PROP_WRITE;
// BTPWriteChannel Value
//static uint8 BTPWriteChannelBuf[BTPWRITECHANNEL_LEN] = { 0, 0, 0, 0, 0, 0 };
// Simple Profile BTPWriteChannel User Description
static uint8 BTPWriteChannelUserDesp[16] = "BTPWriteChannel";

// Simple Profile BTPNotifyChannel Properties
static uint8 BTPNotifyChannelProps = GATT_PROP_NOTIFY;
// BTPNotifyChannel Value
static uint8 BTPNotifyChannelProfile[BTPNOTITYCHANNEL_LEN] = { 0, 0, 0, 0, 0, 0 };
// Simple Profile BTPNotifyChannel Configuration Each client has its own
// instantiation of the Client Characteristic Configuration. Reads of the
// Client Characteristic Configuration only shows the configuration for
// that client and writes only affect the configuration of that client.
static gattCharCfg_t *BTPNotifyChannelConfig;
// Simple Profile BTPNotifyChannel User Description
static uint8 BTPNotifyChannelUserDesp[17] = "BTPNotifyChannel";

/***************************************************************************/

/*********************************************************************
 * Profile Attributes - Table
 */

static gattAttribute_t simpleProfileAttrTbl[SERVAPP_NUM_ATTR_SUPPORTED] =
{
  // Simple Profile Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID }, /* type */
    GATT_PERMIT_READ,                         /* permissions */
    0,                                        /* handle */
    (uint8 *)&simpleProfileService            /* pValue */
  },
      /***************************************************************************/
      // BTPWriteChannel Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &BTPWriteChannelProps
    },

      // BTPWriteChannel Characteristic Value
      {
        { ATT_BT_UUID_SIZE, simpleProfileBTPWriteUUID },
        GATT_PERMIT_WRITE,
        0,
//        BTPWriteChannelBuf
        BTP_DataMsg.WriteServiceBuffer.dataBuf
      },

      // BTPWriteChannel User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        BTPWriteChannelUserDesp
      },

		// BTPNotifyChannel Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &BTPNotifyChannelProps
    },

      // BTPNotifyChannel Characteristic Value
      {
        { ATT_BT_UUID_SIZE, simpleProfileBTPNotifyUUID },
        0,
        0,
        BTPNotifyChannelProfile
//        BTP_DataMsg.NotifyServiceBuffer.dataBuf
      },

      // Characteristic BTPNotifyChannel configuration
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&BTPNotifyChannelConfig
      },

      // Characteristic BTPNotifyChannel User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        BTPNotifyChannelUserDesp
      },
      /***************************************************************************/
};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static bStatus_t simpleProfile_ReadAttrCB(uint16_t connHandle,
                                          gattAttribute_t *pAttr,
                                          uint8_t *pValue, uint16_t *pLen,
                                          uint16_t offset, uint16_t maxLen,
                                          uint8_t method);
static bStatus_t simpleProfile_WriteAttrCB(uint16_t connHandle,
                                           gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint16_t len,
                                           uint16_t offset, uint8_t method);

/*********************************************************************
 * PROFILE CALLBACKS
 */

// Simple Profile Service Callbacks
// Note: When an operation on a characteristic requires authorization and
// pfnAuthorizeAttrCB is not defined for that characteristic's service, the
// Stack will report a status of ATT_ERR_UNLIKELY to the client.  When an
// operation on a characteristic requires authorization the Stack will call
// pfnAuthorizeAttrCB to check a client's authorization prior to calling
// pfnReadAttrCB or pfnWriteAttrCB, so no checks for authorization need to be
// made within these functions.
CONST gattServiceCBs_t simpleProfileCBs =
{
  simpleProfile_ReadAttrCB,  // Read callback function pointer
  simpleProfile_WriteAttrCB, // Write callback function pointer
  NULL                       // Authorization callback function pointer
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      SimpleProfile_AddService
 *
 * @brief   Initializes the Simple Profile service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 *
 * @return  Success or Failure
 */
bStatus_t SimpleProfile_AddService( uint32 services )
{
  uint8 status;
  /***************************************************************************/
	// Allocate Client Characteristic Configuration table
  BTPNotifyChannelConfig = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) *
                                                            linkDBNumConns );
  if ( BTPNotifyChannelConfig == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( INVALID_CONNHANDLE, BTPNotifyChannelConfig );
  /***************************************************************************/

  if ( services & SIMPLEPROFILE_SERVICE )
  {
    // Register GATT attribute list and CBs with GATT Server App
    status = GATTServApp_RegisterService( simpleProfileAttrTbl,
                                          GATT_NUM_ATTRS( simpleProfileAttrTbl ),
                                          GATT_MAX_ENCRYPT_KEY_SIZE,
                                          &simpleProfileCBs );
  }
  else
  {
    status = SUCCESS;
  }

  return ( status );
}

/*********************************************************************
 * @fn      SimpleProfile_RegisterAppCBs
 *
 * @brief   Registers the application callback function. Only call
 *          this function once.
 *
 * @param   callbacks - pointer to application callbacks.
 *
 * @return  SUCCESS or bleAlreadyInRequestedMode
 */
bStatus_t SimpleProfile_RegisterAppCBs( simpleProfileCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    simpleProfile_AppCBs = appCallbacks;

    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}

/*********************************************************************
 * @fn      SimpleProfile_SetParameter
 *
 * @brief   Set a Simple Profile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   len - length of data to write
 * @param   value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
static uint8_t signTest = 0;
bStatus_t SimpleProfile_SetParameter( uint8 param, uint8 len, void *value )
{
  bStatus_t ret = SUCCESS;
  uint8_t realLen = 0;
  switch ( param )
  {
	  /***************************************************************************/
	  case SIMPLEPROFILE_BTPWrite:
	    realLen = BTP_DataMsg.WriteServiceBuffer.DataBufMaxSize - piLoopQueue->QueueLength(&BTP_DataMsg.WriteServiceBuffer);
	    if (realLen < len){
	        /* Êý¾Ý»º³åÇø¿Õ¼ä²»×ã  */
	        ret = bleInvalidRange;
	        break;
	    }
	    piLoopQueue->EnQueue(&BTP_DataMsg.WriteServiceBuffer, (LoopDataWidth *)value, len);
	    break;

	 case SIMPLEPROFILE_BTPNotify:
	     realLen = piLoopQueue->QueueLength(&BTP_DataMsg.NotifyServiceBuffer);
	     if (realLen == 0){
	         /* Êý¾Ý»º³åÇøÎÞÊý¾ÝÔò²»½øÐÐNotify  */
	         ret = bleInvalidRange;
	         break;
	     }
	     // See if Notification has been enabled
	     GATTServApp_ProcessCharCfg( BTPNotifyChannelConfig, BTPNotifyChannelProfile, FALSE,
	                                 simpleProfileAttrTbl, GATT_NUM_ATTRS( simpleProfileAttrTbl ),
	                                 INVALID_TASK_ID, simpleProfile_ReadAttrCB );
	     if (signTest){
        #ifdef USE_SERIAL_COMMUNICATION
	         SerialCommunication_SendBleTransferCMP();
        #else
	         piSerialTransfer->SendTransferCMPMsgToMCU();
        #endif
	         signTest = 0;
	     }else{
	         signTest = 1;
	     }
      break;
	/***************************************************************************/
	  
    default:
      ret = INVALIDPARAMETER;
      break;
  }

  return ( ret );
}

/*********************************************************************
 * @fn      SimpleProfile_GetParameter
 *
 * @brief   Get a Simple Profile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   value - pointer to data to put.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t SimpleProfile_GetParameter( uint8 param, void *value )
{
  bStatus_t ret = SUCCESS;
  uint8_t realLen = 0;
  switch ( param )
  {
	/***************************************************************************/
	case SIMPLEPROFILE_BTPWrite:
	    realLen = piLoopQueue->QueueLength(&BTP_DataMsg.WriteServiceBuffer);
	    if (realLen == 0){
	        break;
	    }
	    if (realLen > BTPWRITECHANNEL_LEN){
            /* Êý¾Ý»º³åÇøÒç³ö */
            realLen = BTPWRITECHANNEL_LEN;
	    }
	    piLoopQueue->DeQueue(&BTP_DataMsg.WriteServiceBuffer, value, realLen);
      break;
	
	case SIMPLEPROFILE_BTPNotify:
	    realLen = piLoopQueue->QueueLength(&BTP_DataMsg.NotifyServiceBuffer);
	    if (realLen == 0){
	        break;
	    }
	    if (realLen > BTPWRITECHANNEL_LEN){
	        /* Êý¾Ý»º³åÇøÒç³ö */
	        realLen = BTPWRITECHANNEL_LEN;
	    }
	    piLoopQueue->DeQueue(&BTP_DataMsg.NotifyServiceBuffer, value, realLen);
      break;
	/***************************************************************************/
	  
    default:
      ret = INVALIDPARAMETER;
      break;
  }

  return ( ret );
}

/*********************************************************************
 * @fn          simpleProfile_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 * @param       method - type of read message
 *
 * @return      SUCCESS, blePending or Failure
 */
static bStatus_t simpleProfile_ReadAttrCB(uint16_t connHandle,
                                          gattAttribute_t *pAttr,
                                          uint8_t *pValue, uint16_t *pLen,
                                          uint16_t offset, uint16_t maxLen,
                                          uint8_t method)
{
  bStatus_t status = SUCCESS;
#ifdef USE_SERIAL_COMMUNICATION
  uint8_t realLen = 0;
#endif
  // Make sure it's not a blob operation (no attributes in the profile are long)
  if ( offset > 0 )
  {
    return ( ATT_ERR_ATTR_NOT_LONG );
  }

  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    switch ( uuid )
    {
	/***************************************************************************/
//      case BTPWriteChannel_UUID:
//        *pLen = BTPWRITECHANNEL_LEN;
//        VOID memcpy( pValue, pAttr->pValue, BTPWRITECHANNEL_LEN );
//        break;
	#ifdef USE_SERIAL_COMMUNICATION
	  case BTPNotifyChannel_UUID:
	      realLen = piLoopQueue->QueueLength(&BTP_DataMsg.NotifyServiceBuffer);
	      if (realLen == 0){
	          break;
	      }
	      if (realLen > BTPWRITECHANNEL_LEN){
	          /* Êý¾Ý»º³åÇøÒç³ö */
	          realLen = BTPWRITECHANNEL_LEN;
	      }
	      *pLen = realLen;
	      piLoopQueue->DeQueue(&BTP_DataMsg.NotifyServiceBuffer, pValue, realLen);
        break;
	#else
	  case BTPNotifyChannel_UUID:
	    *pLen = BTPWRITECHANNEL_LEN;
		VOID memcpy( pValue, pAttr->pValue, BTPWRITECHANNEL_LEN );
        break;	
	#endif
	/***************************************************************************/
		
      default:
        // Should never get here! (characteristics 3 and 4 do not have read permissions)
        *pLen = 0;
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    // 128-bit UUID
    *pLen = 0;
    status = ATT_ERR_INVALID_HANDLE;
  }

  return ( status );
}

/*********************************************************************
 * @fn      simpleProfile_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 * @param   method - type of write message
 *
 * @return  SUCCESS, blePending or Failure
 */
static bStatus_t simpleProfile_WriteAttrCB(uint16_t connHandle,
                                           gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint16_t len,
                                           uint16_t offset, uint8_t method)
{
  bStatus_t status = SUCCESS;
  uint8 notifyApp = 0xFF;

  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    switch ( uuid )
    {
      /***************************************************************************/
	  case BTPWriteChannel_UUID:
	  	// Validate the value
        // Make sure it's not a blob oper
        if ( offset == 0 )
        {
            if ( len > BTPWRITECHANNEL_LEN )
            {
                status = ATT_ERR_INVALID_VALUE_SIZE;
            }
        }
        else
        {
          status = ATT_ERR_ATTR_NOT_LONG;
        }

		//Write the value
        if ( status == SUCCESS )
        {
#ifdef USE_SERIAL_COMMUNICATION
          UART_write(uart, pValue, len);
#else
          piSerialTransfer->SendMsgToMCU(pValue, len);
#endif
          if( pAttr->pValue == BTP_DataMsg.WriteServiceBuffer.dataBuf){
              notifyApp = SIMPLEPROFILE_BTPWrite;
          }
        }
      	break;
		/***************************************************************************/
		
      case GATT_CLIENT_CHAR_CFG_UUID:
        status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                                 offset, GATT_CLIENT_CFG_NOTIFY );
        break;

      default:
        // Should never get here! (characteristics 2 and 4 do not have write permissions)
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;    }
  }
  else
  {
    // 128-bit UUID
    status = ATT_ERR_INVALID_HANDLE;
  }

  // If a characteristic value changed then callback function to notify application of change
  if ( (notifyApp != 0xFF ) && simpleProfile_AppCBs && simpleProfile_AppCBs->pfnSimpleProfileChange )
  {
    simpleProfile_AppCBs->pfnSimpleProfileChange( notifyApp );
  }

  return ( status );
}

/*********************************************************************
*********************************************************************/
