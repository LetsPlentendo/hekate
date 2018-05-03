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
#include "btn.h"

int draw_image(gfx_con_t *con, char *ini_path) {
	char lbuf[8];
	char cbuf[8];
	FIL fp;
	int x = 0;
  int y = 0;

	if (f_open(&fp, ini_path, FA_READ) != FR_OK) {
    gfx_con_setpos(con, 0, 0);
    gfx_printf(con, "File not found. Please make sure image.txt is located on the SD card.");
		return 0;
  }
	f_gets(lbuf, 8, &fp);
	int width = strtoul(lbuf, NULL, 10);
	unsigned int currColor;
	char slbuf[width * 6];
	while (f_gets(slbuf, width * 6 + 2, &fp)) {
		for (int i = 1; i < width * 6 + 2; i += 6) {
			substring(slbuf, cbuf, i, 6);
			currColor = 0x00000000 + strtoul(cbuf, NULL, 16);
			con->gfx_ctxt->fb[x + y * 768] = currColor;
			x++;
		}
		x = 0;
		y++;
		u32 btn = btn_read();
		if (btn & BTN_POWER) {
			break;
		}
	}

	f_close(&fp);
}

void substring(char s[], char d[], int pos, int len) {
   int c = 0;

   while (c < len) {
      d[c] = s[pos+c-1];
      c++;
   }
   d[c] = '\0';
}
