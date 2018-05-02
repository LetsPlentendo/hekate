/*
* Copyright (c) 2018 letsplentendo
*
* This program is free software; you can redistribute it and/or modify it
* under the terms and conditions of the GNU General Public License,
* version 2, as published by the Free Software Foundation.
*
* This program is distributed in the hope it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <stdlib.h>

#include "image.h"
#include "ff.h"
#include "heap.h"
#include "util.h"

int draw_image(gfx_con_t *con, char *ini_path) {
	char lbuf[512];
	FIL fp;
  int x = 0;
  int y = 0;
  int width = 0;
  unsigned int currColor;
  char color[8];

	if (f_open(&fp, ini_path, FA_READ) != FR_OK) {
    gfx_con_setpos(con, 0, 0);
    gfx_printf(con, "File not found. Please make sure image.txt is located on the SD card.");
		return 0;
  }

  int line = 0;
	do {
		//Fetch one line.
		lbuf[0] = 0;
		f_gets(lbuf, 512, &fp);

    if (line != 0) {
  		memcpy(color, lbuf, 8);
      currColor = strtoul(color, NULL, 10);
      gfx_set_pixel(con->gfx_ctxt, x, y, currColor);
  		if (x == width) {
  			x = 0;
  			y++;
  		}
      x++;
    } else {
      width = strtoul(lbuf, NULL, 10);
    }

    line = -1;
	} while (!f_eof(&fp));

	f_close(&fp);
}
