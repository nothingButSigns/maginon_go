#ifndef MAGINON_H
#define MAGINON_H

/*
 * Returns 4 bytes notification.
 * 1st byte:
 *  00 lightbulb off
 *  01 lightbulb on
 * 2nd byte (when standard color):
 *  22 -> minimal brightness
 *  32
 *  62
 *  92
 *  b2 -> maximal brightness
 * 3-5 bytes:
 *  RGB color code
 *
 *  * 2nd byte (when rgb color):
 *  20 -> minimal brightness
 *  30
 *  ...
 *  90
 *  a0 -> maximal brightness
 * 3-5 bytes:
 *  RGB color code
 */
#define STATE_HND                   0x0024
#define WRITE_HND                   0x0021
#define CONTROL_CHARACTERISTICS     "{0000fff1-0000-1000-8000-00805f9b34fb}"
#define NOTIFY_CHARACTERISTICS      "{0000fff2-0000-1000-8000-00805f9b34fb}"
#define CONTROL_SERVICE             "{0000fff0-0000-1000-8000-00805f9b34fb}"

////////////////////////
#define SERVICE_0_CHAR      "{00002a05-0000-1000-8000-00805f9b34fb}"
#define SERVICE_3_CHAR_1    "{f000ffc1-0451-4000-b000-000000000000}"
////////////////////////

#define _ON 			"aa0afc3a86010a010100280d"
#define _OFF			"aa0afc3a86010a010001280d"

#define _MAX_LUM5 	"aa0afc3a86010c010bc1f50d"
#define _LUM4 		"aa0afc3a86010c0109bff10d"
#define _LUM3 		"aa0afc3a86010c010697c60d"
#define _LUM2 		"aa0afc3a86010c0103e4100d"
#define _MIN_LUM1 	"aa0afc3a86010c01020b360d"

// Light colors
#define STANDARD      "aa0afc3a86010d060280808080806f200d"
#define RGB           "aa0afc3a86010d0601808080808074240d"
#define GREEN_1       "aa0afc3a86010d060124ff00808003560d"
#define YELLOW_1      "aa0afc3a86010d0601ffe5008080d3e70d"
#define YELLOW_2      "aa0afc3a86010d0601c5e1008080a0760d"
#define MAGENTA       "aa0afc3a86010d0601e100c18080b5870d"
#define WHITE         "aa0afc3a86010d0601ffffff808039660d"
#define GREEN_2       "aa0afc3a86010d06010ce10080802c490d"
#define OCHRE         "aa0afc3a86010d0601e18b008080912d0d"
#define LIME          "aa0afc3a86010d0601e1d80080807c650d"
#define AQUA          "aa0afc3a86010d060100c9e18080835d0d"
#define BLUE          "aa0afc3a86010d06010700e18080c8e00d"
#define PURPLE        "aa0afc3a86010d060115001e8080b81b0d"
#define REDDISH       "aa0afc3a86010d06011e0100808067b60d"

// RGB light intensity
#define _RMAX_LUM9   "aa0afc3a86010c010ae5180d"
#define _RLUM8       "aa0afc3a86010c01099dcf0d"
#define _RLUM7       "aa0afc3a86010c01084b7c0d"
#define _RLUM6       "aa0afc3a86010c010739690d"
#define _RLUM5       "aa0afc3a86010c01060d3c0d"
#define _RLUM4       "aa0afc3a86010c0105214f0d"
#define _RLUM3       "aa0afc3a86010c0104ff2c0d"
#define _RLUM2       "aa0afc3a86010c010395c10d"
#define _RMIN_LUM1   "aa0afc3a86010c01023b660d"

#endif // MAGINON_H


//start time: 35.528068 (ON command)
