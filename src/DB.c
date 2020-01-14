// Copyright (c) 2015-2019 The HomeKit ADK Contributors
//
// Licensed under the Apache License, Version 2.0 (the “License”);
// you may not use this file except in compliance with the License.
// See [CONTRIBUTORS.md] for the list of HomeKit ADK project authors.

// This file contains the accessory attribute database that defines the
// accessory information service, HAP Protocol Information Service, the Pairing
// service and finally the service signature exposed by the light bulb.

#include "DB.h"
#include "App.h"

#include "mgos.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * IID constants.
 */

#define kIID_LightBulb ((uint64_t) 0x0030)
#define kIID_LightBulbServiceSignature ((uint64_t) 0x0031)
#define kIID_LightBulbName ((uint64_t) 0x0032)
#define kIID_LightBulbOn ((uint64_t) 0x0033)

HAP_STATIC_ASSERT(kAttributeCount == 9 + 3 + 5 + 4, AttributeCount_mismatch);

/**
 * The 'Service Signature' characteristic of the Light Bulb service.
 */
static const HAPDataCharacteristic lightBulbServiceSignatureCharacteristic = {
    .format = kHAPCharacteristicFormat_Data,
    .iid = kIID_LightBulbServiceSignature,
    .characteristicType = &kHAPCharacteristicType_ServiceSignature,
    .debugDescription = kHAPCharacteristicDebugDescription_ServiceSignature,
    .manufacturerDescription = NULL,
    .properties = {.readable = true,
                   .writable = false,
                   .supportsEventNotification = false,
                   .hidden = false,
                   .requiresTimedWrite = false,
                   .supportsAuthorizationData = false,
                   .ip = {.controlPoint = true},
                   .ble = {.supportsBroadcastNotification = false,
                           .supportsDisconnectedNotification = false,
                           .readableWithoutSecurity = false,
                           .writableWithoutSecurity = false}},
    .constraints = {.maxLength = 2097152},
    .callbacks = {.handleRead = HAPHandleServiceSignatureRead,
                  .handleWrite = NULL}};

/**
 * The 'Name' characteristic of the Light Bulb service.
 */
static const HAPStringCharacteristic lightBulbNameCharacteristic = {
    .format = kHAPCharacteristicFormat_String,
    .iid = kIID_LightBulbName,
    .characteristicType = &kHAPCharacteristicType_Name,
    .debugDescription = kHAPCharacteristicDebugDescription_Name,
    .manufacturerDescription = NULL,
    .properties = {.readable = true,
                   .writable = false,
                   .supportsEventNotification = false,
                   .hidden = false,
                   .requiresTimedWrite = false,
                   .supportsAuthorizationData = false,
                   .ip = {.controlPoint = false,
                          .supportsWriteResponse = false},
                   .ble = {.supportsBroadcastNotification = false,
                           .supportsDisconnectedNotification = false,
                           .readableWithoutSecurity = false,
                           .writableWithoutSecurity = false}},
    .constraints = {.maxLength = 64},
    .callbacks = {.handleRead = HAPHandleNameRead, .handleWrite = NULL}};

/**
 * The 'On' characteristic of the Light Bulb service.
 */
const HAPBoolCharacteristic lightBulbOnCharacteristic = {
    .format = kHAPCharacteristicFormat_Bool,
    .iid = kIID_LightBulbOn,
    .characteristicType = &kHAPCharacteristicType_On,
    .debugDescription = kHAPCharacteristicDebugDescription_On,
    .manufacturerDescription = NULL,
    .properties = {.readable = true,
                   .writable = true,
                   .supportsEventNotification = true,
                   .hidden = false,
                   .requiresTimedWrite = false,
                   .supportsAuthorizationData = false,
                   .ip = {.controlPoint = false,
                          .supportsWriteResponse = false},
                   .ble = {.supportsBroadcastNotification = true,
                           .supportsDisconnectedNotification = true,
                           .readableWithoutSecurity = false,
                           .writableWithoutSecurity = false}},
    .callbacks = {.handleRead = HandleLightBulbOnRead,
                  .handleWrite = HandleLightBulbOnWrite}};

/**
 * The Light Bulb service that contains the 'On' characteristic.
 */
HAPService lightBulbService = {
    .iid = kIID_LightBulb,
    .serviceType = &kHAPServiceType_LightBulb,
    .debugDescription = kHAPServiceDebugDescription_LightBulb,
    .name = NULL,  // Set from config.
    .properties = {.primaryService = true,
                   .hidden = false,
                   .ble = {.supportsConfiguration = false}},
    .linkedServices = NULL,
    .characteristics = (const HAPCharacteristic *const[]){
        &lightBulbServiceSignatureCharacteristic, &lightBulbNameCharacteristic,
        &lightBulbOnCharacteristic, NULL}};
