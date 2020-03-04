/*
    \file   google_cloud_service.c

    \brief  Cloud Service Abstraction Layer

    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/ 

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cloud_interface.h"
#include "../config/mqtt_config.h"
#include "../config/cloud_config.h"
#include "../mqtt/mqtt_winc_adapter.h"
#include "../mqtt/mqtt_comm_bsd/mqtt_comm_layer.h"
#include "../mqtt/mqtt_packetTransfer_interface.h"
#include "../mqtt/mqtt_core/mqtt_core.h"
#include "mqtt_service.h"
#include "../time_service.h"
#include "../cloud/crypto_client/crypto_client.h"
#include "../drivers/timeout.h"
#include "../debug_print.h"


#define PASSWORD_SPACE 456
#define CLOUD_MAX_DEVICEID_LENGTH 30

char mqttPassword[PASSWORD_SPACE];
const char projectId[] = CFG_PROJECT_ID;
const char projectRegion[] = CFG_PROJECT_REGION;
const char registryId[] = CFG_REGISTRY_ID;
char deviceId[CLOUD_MAX_DEVICEID_LENGTH];
publishReceptionHandler_t imqtt_publishReceiveCallBackTable[NUM_TOPICS_SUBSCRIBE];

static void updateJWT(uint32_t epoch);


void CLOUD_init(timerStruct_t* appProtocolTimeoutTaskTimer, timerStruct_t* cloudResetTaskTimer) 
{
    cloudStatus.isResetting = true;
    debug_printError("CLOUD: Cloud reset timer is set");
    timeout_delete(appProtocolTimeoutTaskTimer);
    timeout_create(cloudResetTaskTimer, CLOUD_RESET_TIMEOUT);
    cloudStatus.cloudResetTimerFlag = true;
}

int8_t CLOUD_connectSocket(uint32_t ipAddress)
{
    int8_t ret = BSD_SUCCESS;
    
    if (ipAddress > 0)
    {
        struct bsd_sockaddr_in addr;
        
        addr.sin_family = PF_INET;
        addr.sin_port = BSD_htons(CFG_MQTT_PORT);
        addr.sin_addr.s_addr = ipAddress;
        
        mqttContext  *context = MQTT_GetClientConnectionInfo();
        socketState_t  socketState = BSD_GetSocketState(*context->tcpClientSocket);
        
        // Todo: Check - Are we supposed to call close on the socket here to ensure we do not leak ?
        if (socketState == NOT_A_SOCKET)
        {
            *context->tcpClientSocket = BSD_socket(PF_INET, BSD_SOCK_STREAM, 1);
            
            if (*context->tcpClientSocket >=0)
            {
                packetReceptionHandler_t*  sockInfo = getSocketInfo(*context->tcpClientSocket);
                if (sockInfo != NULL)
                {
                    sockInfo->socketState = SOCKET_CLOSED;
                }
            }
        }
        
        socketState = BSD_GetSocketState(*context->tcpClientSocket);
        if (socketState == SOCKET_CLOSED) 
        {
         debug_print("CLOUD: Connect socket");
         ret = BSD_connect(*context->tcpClientSocket, (struct bsd_sockaddr *)&addr, sizeof(struct bsd_sockaddr_in));

         if (ret != BSD_SUCCESS) 
         {
            debug_printError("CLOUD connect received %d",ret);
            
            BSD_close(*context->tcpClientSocket);
         }
      }
   }   
   return ret;
}

void CLOUD_connectAppProtocol(void)
{
    uint32_t timeStampReference;
    timeStampReference = TIME_getCurrent(); 
    if (timeStampReference > 0)
    {
        // The JWT takes time in UNIX format (seconds since 1970), AVR-LIBC uses seconds from 2000 ...
        uint32_t offsetValue = TIME_getOffset_UNIX();
        updateJWT(timeStampReference + offsetValue);	  
        MQTT_CLIENT_connect();
        debug_print("CLOUD: MQTT Connect"); 
    }      
       
    // MQTT SUBSCRIBE packet will be sent after the MQTT connection is established.
    cloudStatus.sendSubscribe = true;
}

static void updateJWT(uint32_t epoch)
{
    char ateccsn[20];
    CRYPTO_CLIENT_printSerialNumber(ateccsn);
    sprintf(deviceId, "d%s", ateccsn);
    
    sprintf(cid, "projects/%s/locations/%s/registries/%s/devices/%s", projectId, projectRegion, registryId, deviceId);
    
    debug_printInfo("MQTT: cid=%s", cid);
    uint8_t cyptoResult = CRYPTO_CLIENT_createJWT((char*)mqttPassword, PASSWORD_SPACE, epoch, projectId);
    
    uint32_t offsetValue = TIME_getOffset_UNIX();
    uint32_t adjustTime = epoch - offsetValue;
    
    debug_printInfo("JWT: Result(%d) at %s", cyptoResult == 0 ? 1 : -1);
    debug_printInfo("JWT TimeStamp: %s", TIME_GetcTime(adjustTime));
}

void CLOUD_subscribe(void)
{
    if(MQTT_CLIENT_subscribe())
    {
        cloudStatus.sendSubscribe = 0;
    }
}

void CLOUD_publish(uint8_t* refToPublishTopic, uint8_t* data, unsigned int len)
{
    MQTT_CLIENT_publish(refToPublishTopic, data, len);
}

void CLOUD_disconnect(void)
{
    debug_printError("CLOUD: Disconnect");
    if (MQTT_GetConnectionState() == CONNECTED)
    {
        if (MQTT_Disconnect(MQTT_GetClientConnectionInfo()) == DISCONNECTED)
		{
			debug_print("MQTT: sendresult (%d)", MQTT_LastSentSize());
        }
    }
}

bool CLOUD_isConnected(void)
{
    if (MQTT_GetConnectionState() == CONNECTED)
    {
        return true;
    } 
    else 
    {
        return false;
    }
}

bool CLOUD_isDisconnected(void)
{
    if (MQTT_GetConnectionState() == DISCONNECTED)
    {
        return true;
    } 
    else 
    {
        return false;
    }
}

