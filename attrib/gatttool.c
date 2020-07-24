/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2010  Nokia Corporation
 *  Copyright (C) 2010  Marcel Holtmann <marcel@holtmann.org>
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/signalfd.h>

#include <glib.h>

#include "lib/bluetooth.h"
#include "lib/hci.h"
#include "lib/hci_lib.h"
#include "lib/sdp.h"
#include "lib/uuid.h"

#include "src/shared/util.h"
#include "att_attrib.h"
#include "btio/btio.h"
#include "gattrib.h"
#include "gatt.h"
#include "gatttool.h"
#include "actuators.h"




static char *opt_src = NULL;
const char *opt_dst = NULL;
static char *opt_dst_type = "";
const char *opt_value = "";
const char *opt_sec_level = "";
//static bt_uuid_t *opt_uuid = NULL;
//static int opt_start = 0x0001;
//static int opt_end = 0xffff;
int opt_handle = 0;
static int opt_mtu = 0;
static int opt_psm = 0;


GAttrib *someAttr = NULL;

static enum state {
    STATE_DISCONNECTED,
    STATE_CONNECTING,
    STATE_CONNECTED
} conn_state;

struct characteristic_data {
    GAttrib *attrib;
    uint16_t start;
    uint16_t end;
};

static void events_handler(const uint8_t *pdu, uint16_t len, gpointer user_data)
{
    GAttrib *attrib = user_data;
    uint8_t *opdu;
    uint16_t handle, i, olen = 0;
    size_t plen;

    handle = get_le16(&pdu[1]);

    switch (pdu[0]) {
    case ATT_OP_HANDLE_NOTIFY:
        g_print("Notification handle = 0x%04x value: ", handle);
        break;
    case ATT_OP_HANDLE_IND:
        g_print("Indication   handle = 0x%04x value: ", handle);
        break;
    default:
        g_print("Invalid opcode\n");
        return;
    }

    for (i = 3; i < len; i++)
        g_print("%02x ", pdu[i]);

    g_print("\n");

    if (pdu[0] == ATT_OP_HANDLE_NOTIFY)
        return;

    opdu = g_attrib_get_buffer(attrib, &plen);
    olen = enc_confirmation(opdu, plen);

    if (olen > 0)
        g_attrib_send(attrib, 0, opdu, olen, NULL, NULL, NULL);
}


static void set_state(enum state st)
{
    conn_state = st;
}

static gboolean listen_start(gpointer user_data)
{
    GAttrib *attrib = user_data;

    g_attrib_register(attrib, ATT_OP_HANDLE_NOTIFY, GATTRIB_ALL_HANDLES,
                      events_handler, attrib, NULL);
    g_attrib_register(attrib, ATT_OP_HANDLE_IND, GATTRIB_ALL_HANDLES,
                      events_handler, attrib, NULL);

    return FALSE;
}

static void connect_cb(GIOChannel *io, GError *err, gpointer user_data)
{
    GAttrib *attrib;
    uint16_t mtu;
    uint16_t cid;
    GError *gerr = NULL;

    if (err) {
        g_printerr("%s\n", err->message);
        got_error = TRUE;
        g_main_loop_quit(event_loop);
    }

    bt_io_get(io, &gerr, BT_IO_OPT_IMTU, &mtu,
              BT_IO_OPT_CID, &cid, BT_IO_OPT_INVALID);


    if (gerr) {
        g_printerr("Can't detect MTU, using default: %s",
                   gerr->message);
        g_error_free(gerr);
        mtu = ATT_DEFAULT_LE_MTU;
    }

    if (cid == ATT_CID)
        mtu = ATT_DEFAULT_LE_MTU;


    attrib = g_attrib_new(io, mtu, false);

    someAttr = g_attrib_ref(attrib);
    if (opt_listen)
    {
        g_idle_add(listen_start, attrib);

        printf("attrib in connected: %d", attrib);
        printf("someAttr in connected: %d", attrib);
    }

    g_print("COnnected");
    set_state(STATE_CONNECTED);
    //operation(attrib);
}


static void char_read_cb(guint8 status, const guint8 *pdu, guint16 plen,
                         gpointer user_data)
{
    uint8_t value[plen];
    ssize_t vlen;
    int i;

    if (status != 0) {
        g_printerr("Characteristic value/descriptor read failed: %s\n",
                   att_ecode2str(status));
        goto done;
    }

    vlen = dec_read_resp(pdu, plen, value, sizeof(value));
    if (vlen < 0) {
        g_printerr("Protocol error\n");
        goto done;
    }
    g_print("Characteristic value/descriptor: ");
    for (i = 0; i < vlen; i++)
        g_print("%02x ", value[i]);
    g_print("\n");

done:
    if (!opt_listen)
        g_main_loop_quit(event_loop);
}

//static void char_read_by_uuid_cb(guint8 status, const guint8 *pdu,
//                                 guint16 plen, gpointer user_data)
//{
//    struct att_data_list *list;
//    int i;

//    if (status != 0) {
//        g_printerr("Read characteristics by UUID failed: %s\n",
//                   att_ecode2str(status));
//        goto done;
//    }

//    list = dec_read_by_type_resp(pdu, plen);
//    if (list == NULL)
//        goto done;

//    for (i = 0; i < list->num; i++) {
//        uint8_t *value = list->data[i];
//        int j;

//        g_print("handle: 0x%04x \t value: ", get_le16(value));
//        value += 2;
//        for (j = 0; j < list->len - 2; j++, value++)
//            g_print("%02x ", *value);
//        g_print("\n");
//    }

//    att_data_list_free(list);

//done:
//    g_main_loop_quit(event_loop);
//}

static gboolean characteristics_read(gpointer user_data)
{
    GAttrib *attrib = user_data;

//    if (opt_uuid != NULL) {

//        gatt_read_char_by_uuid(attrib, opt_start, opt_end, opt_uuid,
//                               char_read_by_uuid_cb, NULL);

//        return FALSE;
//    }

    if (opt_handle <= 0) {
        g_printerr("A valid handle is required\n");
        g_main_loop_quit(event_loop);
        return FALSE;
    }

    gatt_read_char(attrib, opt_handle, char_read_cb, attrib);

    return FALSE;
}

static void mainloop_quit(gpointer user_data)
{
    uint8_t *value = user_data;

    g_free(value);
    g_main_loop_quit(event_loop);
}

//static gboolean characteristics_write(gpointer user_data)
//{
//    GAttrib *attrib = user_data;
//    uint8_t *value;
//    size_t len;

//    if (opt_handle <= 0) {
//        g_printerr("A valid handle is required\n");
//        goto error;
//    }

//    if (opt_value == NULL || opt_value[0] == '\0') {
//        g_printerr("A value is required\n");
//        goto error;
//    }

//    len = gatt_attr_data_from_string(opt_value, &value);
//    if (len == 0) {
//        g_printerr("Invalid value\n");
//        goto error;
//    }

//    gatt_write_cmd(attrib, opt_handle, value, len, mainloop_quit, value);

//    g_free(value);
//    return FALSE;

//error:
//    g_main_loop_quit(event_loop);
//    return FALSE;
//}

static void char_write_req_cb(guint8 status, const guint8 *pdu, guint16 plen,
                              gpointer user_data)
{
    if (status != 0) {
        g_printerr("Characteristic Write Request failed: "
                   "%s\n", att_ecode2str(status));
        goto done;
    }

    if (!dec_write_resp(pdu, plen) && !dec_exec_write_resp(pdu, plen)) {
        g_printerr("Protocol error\n");
        goto done;
    }

    g_print("Characteristic value was written successfully\n");

done:
    if (!opt_listen)
        g_main_loop_quit(event_loop);
}

static gboolean characteristics_write_req(gpointer user_data)
{
    GAttrib *attrib = user_data;
    uint8_t *value;
    size_t len;

    g_print("inside write char..");

    if (opt_handle <= 0) {
        g_printerr("A valid handle is required\n");
        goto error;
    }

    if (opt_value == NULL || opt_value[0] == '\0') {
        g_printerr("A value is required\n");
        goto error;
    }

    len = gatt_attr_data_from_string(opt_value, &value);
    if (len == 0) {
        g_printerr("Invalid value\n");
        goto error;
    }

    if(!attrib)
        printf("attrib == null");
    gatt_write_char(attrib, opt_handle, value, len, char_write_req_cb,
                    NULL);

    g_free(value);
    return FALSE;

error:
    g_main_loop_quit(event_loop);
    return FALSE;
}

static void disconnect(GIOChannel *iochannel)
{

    opt_mtu = 0;

    g_io_channel_shutdown(iochannel, FALSE, NULL);
    g_io_channel_unref(iochannel);
    iochannel = NULL;
    printf("disconnected");

}

void interrupt_handler(sig_t i)
{
    printf("Program interrupted\n");
    disconnect(chan);

    g_free(opt_src);
    g_free(opt_dst);
   // g_free(opt_uuid);
    g_free(opt_sec_level);

    if (got_error)
        exit(EXIT_FAILURE);
    else
        exit(EXIT_SUCCESS);

}


//void writeCharValue(const char* address, const char* value, int handler)
//{
//    GError *gerr = NULL;
//    // parameters of communication
//    opt_dst_type = g_strdup("public");
//    opt_sec_level = g_strdup("low");

//    opt_dst = address;
//    opt_value = value;
//    opt_handle = handler;

//    operation = characteristics_write_req;
//    chan = gatt_connect(opt_src, opt_dst, opt_dst_type, opt_sec_level,
//                        opt_psm, opt_mtu, connect_cb, &gerr);


//    if (chan == NULL)
//    {
//        g_printerr("%s\n", gerr->message);
//        g_clear_error(&gerr);
//        got_error = TRUE;
//        goto done;
//    }

//    event_loop = g_main_loop_new(NULL, FALSE);
//    g_main_loop_run(event_loop);
//    g_main_loop_unref(event_loop);

//    disconnect(chan);

//done:
//   // g_free(opt_uuid);
//    g_free(opt_sec_level);

//}

void writeCharValue(const char* value, int handler)
{
    GError *gerr = NULL;
    // parameters of communication
    opt_dst_type = g_strdup("public");
    opt_sec_level = g_strdup("low");

    opt_value = value;
    opt_handle = handler;

    operation = characteristics_write_req;

    if(!someAttr)
        printf("someAttr == null");
    else
        printf("someAttr ref: %d", someAttr);

    operation(someAttr);


    event_loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(event_loop);
    g_main_loop_unref(event_loop);


done:
   // g_free(opt_uuid);
    g_free(opt_sec_level);

}


void connectToBulb()
{

    GError *gerr = NULL;
    // parameters of communication
    opt_dst_type = g_strdup("public");
    opt_sec_level = g_strdup("low");

    opt_dst = "80:30:DC:05:A9:96";


    //operation = characteristics_write_req;
    chan = gatt_connect(opt_src, opt_dst, opt_dst_type, opt_sec_level,
                        opt_psm, opt_mtu, connect_cb, &gerr);


    if (chan == NULL)
    {
        g_printerr("%s\n", gerr->message);
        g_clear_error(&gerr);
        got_error = TRUE;
        goto done;
    }

    event_loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(event_loop);
    g_main_loop_unref(event_loop);

done:
   // g_free(opt_uuid);
    g_free(opt_sec_level);

}
