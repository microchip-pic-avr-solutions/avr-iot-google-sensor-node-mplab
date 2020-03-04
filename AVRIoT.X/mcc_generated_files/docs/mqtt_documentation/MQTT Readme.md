# Microchip MQTT Library APIs

## Introduction

MQTT (Message Queuing Telemetry and Transport) is a publish/subscribe messaging transport protocol. It is widely used in many situations, such as communications in Machine to Machine (M2M) or Internet of Things (IoT) applications, especially in bandwidth and/or memory constrained environments. This protocol runs over TCP/IP, or can over other network protocols that provide ordered, lossless, bi-directional connections. In this implementation of MQTT is implemented over TCP.

This MQTT implementation supports all the required features and message types of this protocol along with some optional features.

Supported message types:
* CONNECT
* CONNACK
* PUBLISH (QoS level = 0)
* PINGREQ
* PINGRESP
* SUBSCRIBE (QoS level = 0, beta)
* DISCONNECT

This document describes the structure and the APIs implemented as part of the MQTT library. The public APIs are used by user application for performing all the MQTT specific tasks such as establishing a MQTT connection, publishing data, sending ping requests, etc. The private APIs are used internally by the MQTT library for maintaining its modularity.

## Core Public APIs

##### 1. INITIALISE STATE
* MQTT_initialiseState
  * **Description:**
    * void MQTT_initialiseState(void)
	* Returns the mqttState variable to DISCONNECTED.
  * **Parameters:**
    * None.
  * **Return Values:**
    * None.

##### 2. GET STATE
* MQTT_GetConnectionState
  * **Description:**
    * mqttCurrentState MQTT_GetConnectionState (void)
	* Returns the mqttState variable value.
  * **Parameters:**
    * None.
  * **Return Values:**
    * mqttState which is a type define of mqttCurrentState.

##### 3. CREATE CONNECT PACKET
* MQTT_CreateConnectPacket
  * **Description:**
    * bool MQTT_CreateConnectPacket(mqttConnectPacket *newConnectPacket*)
	* MQTT_CreateConnectPacket API creates a CONNECT packet structure, which follows MQTT standard.
  * **Parameters:**
    * A pointer that points to a MQTT CONNECT packet structure mqttConnectPacket.
  * **Return Values:**
    * A bool type value indicating whether a connect data packet structure is initialized successfully. A return value of â??trueâ?? implies that CONNECT packet has been successfully created.

##### 4. CREATE PUBLISH PACKET
* MQTT_CreatePublishPacket
  * **Description:**
    * bool MQTT_CreatePublishPacket(mqttPublishPacket *newPublishPacket*)
	* MQTT_CreatePublishPacket API creates a MQTT publish data packet structure, which follows MQTT standard.
  * **Parameters:**
    * A pointer that points to a MQTT PUBLISH packet structure mqttPublishPacket.
  * **Return Values:**
    * A bool value indicating whether a publish data packet structure is created successfully. A return value of â??trueâ?? means that the PUBLISH packet has been created correctly as per the parameters passed by the user application.

##### 5. CREATE SUBSCRIBE PACKET
* MQTT_CreateSubscribePacket
  * **Description:**
    * bool MQTT_CreateSubscribePacket(mqttSubscribePacket *newSubscribePacket*)
	* MQTT_CreateSubscribePacket API creates a MQTT subscribe data packet structure, which follows MQTT standard.
  * **Parameters:**
    * A pointer that points to a MQTT SUBSCRIBE packet structure mqttSubscribePacket.
  * **Return Values:**
    * A bool type value indicating whether a subscribe data packet structure is created successfully. A return value of â??trueâ?? means that the SUBSCRIBE packet has been created correctly as per the parameters passed by the user application.

##### 6. CREATE UNSUBSCRIBE PACKET
* MQTT_CreateUnsubscribePacket
  * **Description:**
    * bool MQTT_CreateUnsubscribePacket(mqttUnsubscribePacket  *newUnsubscribePacket*)
	* MQTT_CreateUnsubscribePacket API creates a MQTT unsubscribe data packet structure, which follows MQTT standard.
  * **Parameters:**
    * A pointer that points to a MQTT UNSUBSCRIBE packet structure.
  * **Return Values:**
    * A bool type value indicating whether a subscribe data packet unstructure is created successfully. A return value of â??trueâ?? means that the UNSUBSCRIBE packet has been created correctly as per the parameters passed by the user application.

##### 7. DISCONNECT
* MQTT_Disconnect
  * **Description:**
    * void MQTT_Disconnect(void)
	* This API sends a MQTT DISCONNECT packet. This disconnects the client cleanly from the MQTT server.
  * **Parameters:**
    * None.
  * **Return Values:**
    * None.

##### 8. LAST HANDLER STATE
* MQTT_GetLastHandlerState
  * **Description:**
    * mqttHandlerState_t MQTT_GetLastHandlerState (void);
	* The function returns the last MQTT Handler State used to detect transitions by observers.
  * **Parameters:**
    * None.
  * **Return Values:**
    * Variable value of type mqttHandlerState_t.

##### 9. LAST RECEIVED PACKET HEADER
* MQTT_GetLastReceivedPacketHeader
  * **Description:**
    * mqttHeaderFlags MQTT_GetLastReceivedPacketHeader (void);
	* The function returns a uint16_t value representing the last received data length.
  * **Parameters:**
    * None.
  * **Return Values:**
    * Variable value of a uint16_t type.

##### 10. TRANSMISSION HANDLER
* MQTT_TransmissionHandler
  * **Description:**
    * mqttCurrentState MQTT_TransmissionHandler(mqttTxRxInformation *mqttConnectionPtr*)
	* MQTT_TransmissionHandler API sends out an MQTT packet based on the settings of MQTT packet transmission flags and the current MQTT state, then set the current MQTT state to a proper state.
  * **Parameters:**
    * A pointer to the current MQTT connection information, which is essentially a structure with relevant exchange buffer details.
  * **Return Values:**
    * mqttCurrentState: An enum indicating the current MQTT connection state. Possible valid values: DISCONNECTED, CONNECTING, WAITFORCONNACK, CONNECTED.

##### 11. RECEPTION HANDLER
* MQTT_ReceptionHandler
  * **Description:**
    * mqttCurrentState MQTT_ReceptionHandler(mqttTxRxInformation *mqttConnectionPtr*)
	* MQTT_ReceptionHandler API handles the received MQTT packet based on the MQTT state and then sets the state to a proper value based on the data received.
  * **Parameters:**
    * A pointer to the current MQTT connection information, which is essentially a structure with relevant exchange buffer details.
  * **Return Values:**
    * mqttCurrentState: An enum indicating the current MQTT connection state.  Possible valid values: DISCONNECTED, CONNECTING, WAITFORCONNACK, CONNECTED.

## Private APIs

##### 1. SEND CONNECT
* mqttSendConnect
  * **Description:**
    * static bool mqttSendConnect(mqttTxRxInformation *mqttConnectionPtr*)
	* mqttSendConnect API sends the MQTT CONNECT packet using the underlying TCP layer.
  * **Parameters:**
    * A pointer to the MQTT connection structure *mqttConnectionPtr*.
  * **Return Values:**
    * Boolean value indicating whether the packet has been successfully sent. The value 'true' implies that the packet has been sent successfully to the server.

##### 2. SEND PUBLISH
* mqttSendPublish
  * **Description:**
    * static bool mqttSendPublish(mqttTxRxInformation *mqttConnectionPtr*)
	* mqttSendPublish API sends the MQTT PUBLISH packet using the underlying TCP layer.
  * **Parameters:**
    * A pointer to the MQTT connection structure *mqttConnectionPtr*.
  * **Return Values:**
    * Boolean value indicating whether the packet has been successfully sent. The value 'true' implies that the packet has been sent successfully to the server.

##### 3. SEND SUBSCRIBE
* mqttSendSubscribe
  * **Description:**
    * static bool mqttSendSubscribe (mqttContext*mqttConnectionPtr);
	* mqttSendSubscribe API sends the MQTT SUBSCRIBE packet using the underlying TCP layer.
  * **Parameters:**
    * Pointer to the MQTT connection structure *mqttConnectionPtr*.
  * **Return Values:**
    * Boolean value indicating whether the packet has been successfully sent. The value â??trueâ?? implies that the packet has been sent successfully to the server.

##### 4. SEND UNSUBSCRIBE
* mqttSendUnubscribe
  * **Description:**
    * static bool mqttSendUnsubscribe (mqttContext*mqttConnectionPtr);
	* mqttSendUnsubscribe API sends the MQTT SUBSCRIBE packet using the underlying TCP layer.
  * **Parameters:**
    * Pointer to the MQTT connection structure *mqttConnectionPtr*.
  * **Return Values:**
    * Boolean value indicating whether the packet has been successfully sent. The value â??trueâ?? implies that the packet has been sent successfully to the server.

##### 5. SEND PINGREQ
* mqttSendPingreq
  * **Description:**
    * static bool mqttSendPingreq(mqttTxRxInformation *mqttConnectionPtr*)
	* mqttSendPingreq API sends the MQTT PINGREQ packet using the underlying TCP layer.
  * **Parameters:**
    * A pointer to the MQTT connection structure *mqttConnectionPtr*.
  * **Return Values:**
    * Boolean value indicating whether the packet has been successfully sent. The value 'true' implies that the packet has been sent to the server.

##### 6. SEND DISCONNECT
* mqttSendDisconnect
  * **Description:**
    * static bool mqttSendDisconnect(mqttTxRxInformation *mqttConnectionPtr*)
	* mqttSendDisconnect API sends the MQTT DISCONNECT packet using the underlying TCP layer.
  * **Parameters:**
    * A pointer to the MQTT connection structure *mqttConnectionPtr*.
  * **Return Values:**
    * Boolean value indicating whether the packet has been successfully sent. The value 'true' implies that the packet has been sent to the server.

##### 7. ENCODING REMAINING LENGTH
* mqttEncodeLength
  * **Description:**
    * static uint8_t mqttEncodeLength(uint16_t length, uint8_t *output*)
	* The function encodes the text fields in MQTT packets as UTF-8 strings.
  * **Parameters:**
    * uint16_t length: the number of bytes remaining within the current packet, including data in the variable header and the payload.
	* uint8_t *output*: a pointer to the encoded bytes.
  * **Return Values:**
    * The number of bytes encoded.

##### 8. DECODING REMAINING LENGTH
* mqttDecodeLength
  * **Description:**
    * static absolutetime_t mqttEncodeLength(uint8_t *encodedData*)
	* The function decodes UTF-8 encoded string to text fields as per the requirement of MQTT standard.
  * **Parameters:**
    * uint8_t *encodedData*: a pointer to the encoded value of remaining length of a MQTT control packet.
  * **Return Values:**
    * The decoded value of the remaining length of an MQTT control packet header.

##### 9. PROCESS PINGRESP
* mqttProcessPingresp
  * **Description:**
    * static mqttCurrentState mqttProcessPingresp(mqttTxRxInformation *mqttConnectionPtr*)
	* Processes the PINGRESP packet received from the broker.
  * **Parameters:**
    * A pointer to the MQTT connection structure *mqttConnectionPtr*.
  * **Return Values:**
    * None.

##### 10. PROCESS SUBACK
* mqttProcessSuback
  * **Description:**
    * static mqttCurrentState mqttProcessSuback(mqttTxRxInformation *mqttConnectionPtr*)
	* Processes the PINGRESP packet received from the broker.
  * **Parameters:**
    * A pointer to the MQTT connection structure *mqttConnectionPtr*.
  * **Return Values:**
    * Pointer to the MQTT connection structure *mqttConnectionPtr*.

##### 11. PROCESS UNSUBACK
* mqttProcessUnsuback
  * **Description:**
    * static mqttCurrentState mqttProcessSuback(mqttTxRxInformation *mqttConnectionPtr*);
	* Processes the PINGRESP packet received from the broker.
  * **Parameters:**
    * Pointer to the MQTT connection structure *mqttConnectionPtr*.
  * **Return Values:**
    * Current state of the MQTT (CONNECTED if correct SUBACK packet is received correctly and DISCONNECTED if certain parameters in the SUBACK packet indicate that the server has acknowledged the SUBSCRIBE message completely).

##### 12. PROCESS PUBLISH
* mqttProcessPublish
  * **Description:**
    * static mqttCurrentState mqttProcessPublish (mqttContext *mqttConnectionPtr*);
	* Processes the PUBLISH packet received from the broker.   
  * **Parameters:**
    * Pointer to the MQTT Context structure *mqttConnectionPtr*.
  * **Return Values:**
    * Current state of the MQTT (CONNECTED if correct SUBACK packet is received correctly and DISCONNECTED if certain parameters in the PUBACK packet indicate that the server has acknowledged the PUBLISH message completely).

##### 13. PROCESS PUBACK
* mqttProcessPuback
  * **Description:**
    * static void mqttProcessPuback (mqttContext *mqttConnectionPtr*);
	* Processes the PUBLISH ACK packet received from the broker.   
  * **Parameters:**
    * Pointer to the MQTT Context structure *mqttConnectionPtr*.
  * **Return Values:**
    * None.

##### 14. PROCESS CONNACK
* mqttProcessConnack
  * **Description:**
    * static mqttCurrentState mqttProcessConnack(mqttTxRxInformation *mqttConnectionPtr*)
	* Processes the CONNACK packet received from the broker.
  * **Parameters:**
    * A pointer to the MQTT connection structure *mqttConnectionPtr*.
  * **Return Values:**
    * Current state of the MQTT (CONNECTED if correct CONNACK packet is received and DISCONNECTED if certain parameters in the CONNACK packet indicate that the server has not granted a connection).

## Core Timeouts

##### 1. CHECK CONNACK TIMEOUT STATE
* checkConnackTimeoutState
  * **Description:**
    * static absolutetime_t checkConnackTimeoutState ();
	* checkConnackTimeoutState is a call back function that will be called when a timeout (30s) has occurred after sending the CONNECT packet, since a CONNACK packet is expected from the broker within 30s.   
  * **Parameters:**
    * None.
  * **Return Values:**
    * Number of ticks until the connackTimer expires. In the current implementation it is 0, indicating that the timer function will be executed only once.

##### 2. CHECK PING REQUEST TIMEOUT STATE
* checkPingreqTimeoutState
  * **Description:**
    * static absolutetime_t checkPingreqTimeoutState ();
	* checkPingreqTimeoutState is a call back function that will be called when a â??keep-alive-timeoutâ?? defined in user application is near after a MQTT connection has been set up to make sure the connection keeps alive. In the current implementation it is 1 second before â??keep-alive-timeoutâ??.   
  * **Parameters:**
    * None.
  * **Return Values:**
    * Number of ticks until the pingreqTimer expires.

##### 3. CHECK PING RESPONSE TIMEOUT STATE
* checkPingrespTimeoutState
  * **Description:**
    * static absolutetime_t checkPingrespTimeoutState ();
	* checkPingrespTimeoutState is a call back function that will be called when a timeout (30s) has occurred after sending a PINGREQ packet.  In the current MQTT client implementation, the client waits for 30s after transmission of PINGREQ packet to receive a PINGRESP packet.   
  * **Parameters:**
    * None.
  * **Return Values:**
    * Number of ticks until the pingrespTimer expires.

##### 4. CHECK SUBSCRIBE ACKNOWLEDGE TIMEOUT STATE
* checkSubackTimeoutState
  * **Description:**
    * static absolutetime_t checkSubackTimeoutState ();
	* When a SUBSCRIBE packet is sent, the ACK is expected within a timeout period.
If the SUBACK is not received in the set time, this timeout will occur; and a flag will be set as a result. Otherwise this timeout will be deleted prior to completion.
  * **Parameters:**
    * None.
  * **Return Values:**
    * Zero (0); the timer is not reloaded.

##### 5. CHECK UNSUBSCRIBE ACKNOWLEDGE TIMEOUT STATE
* checkUnsubackTimeoutState
  * **Description:**
    * static absolutetime_t checkUnsubackTimeoutState ();
	* When a UNSUBSCRIBE packet is sent, the ACK is expected within a timeout period.
If the SUBACK is not received in the set time, this timeout will occur; and a flag will be set as a result. Otherwise this timeout will be deleted prior to completion.  
  * **Parameters:**
    * None.
  * **Return Values:**
    * Zero (0); the timer is not reloaded.

## Dependent APIs

###Exchange Buffers

##### 1. EXCHANGE BUFFER INIT
* ExchangeBufferInit
  * **Description:**
    * void MQTT_ExchangeBufferInit(exchangeBuffer *buffer*)
	* Sets the current location pointer to the beginning of the buffer and sets the length to zero.
  * **Parameters:**
    * A pointer to Exchange Buffer structure.
  * **Return Values:**
    * None.

##### 2. EXCHANGE BUFFER WRITE
* ExchangeBufferWrite
  * **Description:**
    * uint16_t MQTT_ExchangeBufferWrite(exchangeBuffer *buffer*, uint8_t *data*, uint16_t length)
	* Sets the current location pointer to the beginning of the buffer and sets the length to zero.
  * **Parameters:**
    * Copies a data buffer to the Exchange Buffer.
  * **Return Values:**
    * Length.

##### 3. EXCHANGE BUFFER PEEK
* ExchangeBufferPeek
  * **Description:**
    * uint16_t MQTT_ExchangeBufferPeek(exchangeBuffer *buffer*, uint8_t *data*, uint16_t length)
	* Copies data out of the Exchange buffer without modifying the data length or current pointer.
  * **Parameters:**
    * A pointer to Exchange Buffer structure, a pointer to Data Buffer, dataLength.
  * **Return Values:**
    * Number of bytes copied.

##### 4. EXCHANGE BUFFER READ
* ExchangeBufferRead
  * **Description:**
    * uint16_t MQTT_ExchangeBufferRead(exchangeBuffer *buffer*, uint8_t *data*, uint16_t length)
	* Copies the Exchange buffer to the data buffer.  Exchange buffer is reset in the process.
  * **Parameters:**
    * Copies a data buffer to the Exchange Buffer.
  * **Return Values:**
    * Number of bytes copied.

## Packet Transfer Interface

##### 1. SET PUBLISH RECEPTION HANDLER TABLE
* MQTT_SetPublishReceptionHandlerTable
  * **Description:**
    * void MQTT_SetPublishReceptionHandlerTable(publishReceptionHandler_t *appPublishReceptionInfo*)
	* MQTT_SetPublishReceptionHandlerTable is called by the user application to inform the MQTT core of the call back table defined to handle the PUBLISH messages received from the MQTT server.
  * **Parameters:**
    * A publishReceptionHandler_t table information defined in the user application, which involves a call back function pointer of a corresponding MQTT topic.
  * **Return Values:**
    * None.

##### 2. GET PUBLISH RECEPTION HANDLER TABLE
* MQTT_GetPublishReceptionHandlerTable
  * **Description:**
    * publishReceptionHandler_t *MQTT_GetPublishReceptionHandlerTable*()
	* MQTT_GetPublishReceptionHandlerTable API returns a publishReceptionHandler_t table information defined in the user application, which involves a call back function pointer of a corresponding MQTT topic.
  * **Parameters:**
    * None.
  * **Return Values:**
    * A publishReceptionHandler_t table information defined in the user application, which involves a call back function pointer of a corresponding MQTT topic.

## References
[MQTT Standard](http://mqtt.org/documentation)
[Click the link](https://guides.github.com/features/mastering-markdown/#examples)
