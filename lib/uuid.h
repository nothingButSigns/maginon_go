/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2011  Nokia Corporation
 *  Copyright (C) 2011  Marcel Holtmann <marcel@holtmann.org>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __BLUETOOTH_UUID_H
#define __BLUETOOTH_UUID_H

#ifdef __cplusplus
extern "C" {
#endif

#define GENERIC_AUDIO_UUID	"00001203-0000-1000-8000-00805f9b34fb"

#define HSP_HS_UUID		"00001108-0000-1000-8000-00805f9b34fb"
#define HSP_AG_UUID		"00001112-0000-1000-8000-00805f9b34fb"

#define HFP_HS_UUID		"0000111e-0000-1000-8000-00805f9b34fb"
#define HFP_AG_UUID		"0000111f-0000-1000-8000-00805f9b34fb"

#define ADVANCED_AUDIO_UUID	"0000110d-0000-1000-8000-00805f9b34fb"

#define A2DP_SOURCE_UUID	"0000110a-0000-1000-8000-00805f9b34fb"
#define A2DP_SINK_UUID		"0000110b-0000-1000-8000-00805f9b34fb"

#define AVRCP_REMOTE_UUID	"0000110e-0000-1000-8000-00805f9b34fb"
#define AVRCP_TARGET_UUID	"0000110c-0000-1000-8000-00805f9b34fb"

#define PANU_UUID		"00001115-0000-1000-8000-00805f9b34fb"
#define NAP_UUID		"00001116-0000-1000-8000-00805f9b34fb"
#define GN_UUID			"00001117-0000-1000-8000-00805f9b34fb"
#define BNEP_SVC_UUID		"0000000f-0000-1000-8000-00805f9b34fb"

#define PNPID_UUID		"00002a50-0000-1000-8000-00805f9b34fb"
#define DEVICE_INFORMATION_UUID	"0000180a-0000-1000-8000-00805f9b34fb"

#define GATT_UUID		"00001801-0000-1000-8000-00805f9b34fb"
#define IMMEDIATE_ALERT_UUID	"00001802-0000-1000-8000-00805f9b34fb"
#define LINK_LOSS_UUID		"00001803-0000-1000-8000-00805f9b34fb"
#define TX_POWER_UUID		"00001804-0000-1000-8000-00805f9b34fb"
#define BATTERY_UUID		"0000180f-0000-1000-8000-00805f9b34fb"
#define SCAN_PARAMETERS_UUID	"00001813-0000-1000-8000-00805f9b34fb"

#define SAP_UUID		"0000112D-0000-1000-8000-00805f9b34fb"

#define HEART_RATE_UUID			"0000180d-0000-1000-8000-00805f9b34fb"
#define HEART_RATE_MEASUREMENT_UUID	"00002a37-0000-1000-8000-00805f9b34fb"
#define BODY_SENSOR_LOCATION_UUID	"00002a38-0000-1000-8000-00805f9b34fb"
#define HEART_RATE_CONTROL_POINT_UUID	"00002a39-0000-1000-8000-00805f9b34fb"

#define HEALTH_THERMOMETER_UUID		"00001809-0000-1000-8000-00805f9b34fb"
#define TEMPERATURE_MEASUREMENT_UUID	"00002a1c-0000-1000-8000-00805f9b34fb"
#define TEMPERATURE_TYPE_UUID		"00002a1d-0000-1000-8000-00805f9b34fb"
#define INTERMEDIATE_TEMPERATURE_UUID	"00002a1e-0000-1000-8000-00805f9b34fb"
#define MEASUREMENT_INTERVAL_UUID	"00002a21-0000-1000-8000-00805f9b34fb"

#define CYCLING_SC_UUID		"00001816-0000-1000-8000-00805f9b34fb"
#define CSC_MEASUREMENT_UUID	"00002a5b-0000-1000-8000-00805f9b34fb"
#define CSC_FEATURE_UUID	"00002a5c-0000-1000-8000-00805f9b34fb"
#define SENSOR_LOCATION_UUID	"00002a5d-0000-1000-8000-00805f9b34fb"
#define SC_CONTROL_POINT_UUID	"00002a55-0000-1000-8000-00805f9b34fb"

#define RFCOMM_UUID_STR		"00000003-0000-1000-8000-00805f9b34fb"

#define HDP_UUID		"00001400-0000-1000-8000-00805f9b34fb"
#define HDP_SOURCE_UUID		"00001401-0000-1000-8000-00805f9b34fb"
#define HDP_SINK_UUID		"00001402-0000-1000-8000-00805f9b34fb"

#define HID_UUID		"00001124-0000-1000-8000-00805f9b34fb"

#define DUN_GW_UUID		"00001103-0000-1000-8000-00805f9b34fb"

#define GAP_UUID		"00001800-0000-1000-8000-00805f9b34fb"
#define PNP_UUID		"00001200-0000-1000-8000-00805f9b34fb"

#define SPP_UUID		"00001101-0000-1000-8000-00805f9b34fb"

#define OBEX_SYNC_UUID		"00001104-0000-1000-8000-00805f9b34fb"
#define OBEX_OPP_UUID		"00001105-0000-1000-8000-00805f9b34fb"
#define OBEX_FTP_UUID		"00001106-0000-1000-8000-00805f9b34fb"
#define OBEX_PCE_UUID		"0000112e-0000-1000-8000-00805f9b34fb"
#define OBEX_PSE_UUID		"0000112f-0000-1000-8000-00805f9b34fb"
#define OBEX_PBAP_UUID		"00001130-0000-1000-8000-00805f9b34fb"
#define OBEX_MAS_UUID		"00001132-0000-1000-8000-00805f9b34fb"
#define OBEX_MNS_UUID		"00001133-0000-1000-8000-00805f9b34fb"
#define OBEX_MAP_UUID		"00001134-0000-1000-8000-00805f9b34fb"

/* GATT UUIDs section */
#define GATT_PRIM_SVC_UUID				0x2800
#define GATT_SND_SVC_UUID				0x2801
#define GATT_INCLUDE_UUID				0x2802
#define GATT_CHARAC_UUID				0x2803

/* GATT Characteristic Types */
#define GATT_CHARAC_DEVICE_NAME				0x2A00
#define GATT_CHARAC_APPEARANCE				0x2A01
#define GATT_CHARAC_PERIPHERAL_PRIV_FLAG		0x2A02
#define GATT_CHARAC_RECONNECTION_ADDRESS		0x2A03
#define GATT_CHARAC_PERIPHERAL_PREF_CONN		0x2A04
#define GATT_CHARAC_SERVICE_CHANGED			0x2A05
#define GATT_CHARAC_BATTERY_LEVEL			0x2A19
#define GATT_CHARAC_SYSTEM_ID				0x2A23
#define GATT_CHARAC_MODEL_NUMBER_STRING			0x2A24
#define GATT_CHARAC_SERIAL_NUMBER_STRING		0x2A25
#define GATT_CHARAC_FIRMWARE_REVISION_STRING		0x2A26
#define GATT_CHARAC_HARDWARE_REVISION_STRING		0x2A27
#define GATT_CHARAC_SOFTWARE_REVISION_STRING		0x2A28
#define GATT_CHARAC_MANUFACTURER_NAME_STRING		0x2A29
#define GATT_CHARAC_PNP_ID				0x2A50

/* GATT Characteristic Descriptors */
#define GATT_CHARAC_EXT_PROPER_UUID			0x2900
#define GATT_CHARAC_USER_DESC_UUID			0x2901
#define GATT_CLIENT_CHARAC_CFG_UUID			0x2902
#define GATT_SERVER_CHARAC_CFG_UUID			0x2903
#define GATT_CHARAC_FMT_UUID				0x2904
#define GATT_CHARAC_AGREG_FMT_UUID			0x2905
#define GATT_CHARAC_VALID_RANGE_UUID			0x2906
#define GATT_EXTERNAL_REPORT_REFERENCE			0x2907
#define GATT_REPORT_REFERENCE				0x2908

/* GATT Mesh Services */
#define MESH_PROV_SVC_UUID	"00001827-0000-1000-8000-00805f9b34fb"
#define MESH_PROXY_SVC_UUID	"00001828-0000-1000-8000-00805f9b34fb"

/* GATT Mesh Characteristic Types */
#define MESH_PROVISIONING_DATA_IN			0x2ADB
#define MESH_PROVISIONING_DATA_OUT			0x2ADC
#define MESH_PROXY_DATA_IN				0x2ADD
#define MESH_PROXY_DATA_OUT				0x2ADE

typedef struct {
	enum {
		BT_UUID_UNSPEC = 0,
		BT_UUID16 = 16,
		BT_UUID32 = 32,
		BT_UUID128 = 128,
	} type;
	union {
		uint16_t  u16;
		uint32_t  u32;
		uint128_t u128;
	} value;
} bt_uuid_t;

int bt_uuid_strcmp(const void *a, const void *b);

int bt_uuid16_create(bt_uuid_t *btuuid, uint16_t value);
int bt_uuid32_create(bt_uuid_t *btuuid, uint32_t value);
int bt_uuid128_create(bt_uuid_t *btuuid, uint128_t value);

int bt_uuid_cmp(const bt_uuid_t *uuid1, const bt_uuid_t *uuid2);
void bt_uuid_to_uuid128(const bt_uuid_t *src, bt_uuid_t *dst);

#define MAX_LEN_UUID_STR 37

int bt_uuid_to_string(const bt_uuid_t *uuid, char *str, size_t n);
int bt_string_to_uuid(bt_uuid_t *uuid, const char *string);

int bt_uuid_to_le(const bt_uuid_t *uuid, void *dst);

static inline int bt_uuid_len(const bt_uuid_t *uuid)
{
	return uuid->type / 8;
}

#ifdef __cplusplus
}
#endif

#endif /* __BLUETOOTH_UUID_H */
