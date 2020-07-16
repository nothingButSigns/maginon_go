#ifndef MAGINON_H
#define MAGINON_H

//#include <qglobal.h>

/*
 * Returns 4 bytes notification.
 * 1st byte:
 *  00 lightbulb off
 *  01 lightbulb on
 * 2nd byte:
 *  22 -> minimal brightness
 *  32
 *  62
 *  92
 *  b2 -> maximal brightness
 * 3-5 bytes:
 *  RGB color code
 */
#define STATE_HND 0024
#define WRITE_HND 0021
#define CONTROL_CHARACTERISTICS "{0000fff1-0000-1000-8000-00805f9b34fb}"
#define NOTIFY_CHARACTERISTICS "{0000fff2-0000-1000-8000-00805f9b34fb}"
#define CONTROL_SERVICE "{0000fff0-0000-1000-8000-00805f9b34fb}"

#define ON 			"aa0afc3a86010a010100280d"
#define OFF			"aa0afc3a86010a010001280d"

#define MAX_LUM5 	"aa0afc3a86010c010bc1f50d"
#define LUM4 		"aa0afc3a86010c0109bff10d"
#define LUM3 		"aa0afc3a86010c010697c60d"
#define LUM2 		"aa0afc3a86010c0103e4100d"
#define MIN_LUM1 	"aa0afc3a86010c01020b360d"

// Light colors
#define STANDARD    "aa0afc3a86010d060280808080806f200d"
#define RED         "aa0afc3a86010d0601808080808074240d"
#define GREEN       "aa0afc3a86010d060124ff00808003560d"
#define YELLOW      "aa0afc3a86010d0601ffe5008080d3e70d"
#endif // MAGINON_H


