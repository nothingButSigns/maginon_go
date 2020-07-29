#ifndef ACTUATORS_H
#define ACTUATORS_H


#endif /* STEROWANIE_H_ */

#pragma once

#include <glib.h>

enum state {
    STATE_DISCONNECTED,
    STATE_CONNECTING,
    STATE_CONNECTED,
    STATE_CONNECTION_ERROR,
    WRITE_ERROR,
    READ_ERROR,
    WRITE_SUCCESS,
    READ_SUCCESS
};

#ifdef __cplusplus
extern "C" {
#endif

void readCharValue(void *classPtr, int handler);
void writeCharValue(const char* value, int handler);
void connectToBulb(void *classPtr, const char* dstAddress);
void setConnectionState(void *callerPtr, enum state currentState);
void sendStateData(void *rcvPtr, void* data);
void initiateDisconnection();

#ifdef __cplusplus
}
#endif


















