#ifndef ACTUATORS_H_
#define ACTUATORS_H_


#endif /* STEROWANIE_H_ */

#pragma once

#include <glib.h>
#include "attrib/gattrib.h"

//Żarówki
#define HAND_LAMP 	0x0021

#define ON 			"aa0afc3a86010a010100280d"
#define OFF			"aa0afc3a86010a010001280d"

#define MAX_LUM5 	"aa0afc3a86010c010bc1f50d"
#define LUM4 		"aa0afc3a86010c0109bff10d"
#define LUM3 		"aa0afc3a86010c010697c60d"
#define LUM2 		"aa0afc3a86010c0103e4100d"
#define MIN_LUM1 	"aa0afc3a86010c01020b360d"

//EQIVA
#define HAND_EQ		0x0411

#define AUTO_ON     "4000"
#define AUTO_OFF    "4040"
#define BLOCK_BTN   "8001"
#define WINDOW_MODE "14181e"


#ifdef __cplusplus
extern "C" {
#endif

static GAttrib *attrib = NULL;
static gboolean opt_listen = FALSE;
static GMainLoop *event_loop;
static gboolean got_error = FALSE;
static GSourceFunc operation;
static GIOChannel *chan = NULL;

//void writeCharValue(const char* address, const char* value, int handler);
void writeCharValue(const char* value, int handler);
void connectToBulb();





#ifdef __cplusplus
}
#endif


















