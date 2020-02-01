# Demo application for HomeKit ADK

This is a demo applicatio for the [HomeKit ADK library](https://github.com/mongoose-os-libs/homekit-adk).

It is based on the [original light bulb app](https://github.com/apple/HomeKitADK/tree/master/Applications/Lightbulb) with minimal changes.

## Setup

 * Build and flash the firmware as usual.
 * Provision setup code via RPC:
```
 $ mos call HAP.Setup '{"code": "111-22-333"}'
Using port /dev/ttyUSB0
null
```
 * Set wifi credentials
```
 $ mos wifi MYSSID MYPASS
```
 * That's all! You should see "Acme Light Bulb 9000" appear in the list of accessories.
