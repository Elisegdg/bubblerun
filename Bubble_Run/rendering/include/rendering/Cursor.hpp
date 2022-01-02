/**
 * \file Cursor.hpp
 * \brief Initialization of cursors
*/


#ifndef _CURSOR_HPP
#define _CURSOR_HPP

static SDL_Cursor *init_system_cursor(const char *image[])
{
  int i, row, col;
  Uint8 data[4*32];
  Uint8 mask[4*32];
  int hot_x, hot_y;

  i = -1;
  for (row=0; row<32; ++row) {
    for (col=0; col<32; ++col) {
      if (col % 8) {
        data[i] <<= 1;
        mask[i] <<= 1;
      } else {
        ++i;
        data[i] = mask[i] = 0;
      }
      switch (image[4+row][col]) {
        case 'X':
          data[i] |= 0x01;
          mask[i] |= 0x01;
          break;
        case '.':
          mask[i] |= 0x01;
          break;
        case ' ':
          break;
      }
    }
  }
  sscanf(image[4+row], "%d,%d", &hot_x, &hot_y);
  return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}


void setCursors(bool& menu_bool, bool& menu_score, bool &menu_play_again, SDL_Cursor *cursor2, int& x, int&y){
  if (menu_bool & !menu_score & x > 764 & y > 425 & x < 932 & y < 467)
            SDL_SetCursor(cursor2);
        if (menu_bool & !menu_score & x > 764 & y > 540 & x < 932 & y < 583)
            SDL_SetCursor(cursor2);
        if (!menu_bool & menu_score & x > 1447 & y > 789 & x < 1613 & y < 829)
            SDL_SetCursor(cursor2);
        if (menu_play_again & !menu_bool & !menu_score & x > 764 & y > 540 & x < 932 & y < 583)
            SDL_SetCursor(cursor2);
        if (menu_play_again & !menu_bool & !menu_score & x > 679 & y > 423 & x < 1018 & y < 474)
            SDL_SetCursor(cursor2);
}

static const char *arrow[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  ". c #000000",
  "X c #ffffff",
  "  c None",
  /* pixels */
  ".                               ",
  "..                              ",
  ".X.                             ",
  ".XX.                            ",
  ".XXX.                           ",
  ".XXXX.                          ",
  ".XXXXX.                         ",
  ".XXXXXX.                        ",
  ".XXXXXXX.                       ",
  ".XXXXXXXX.                      ",
  ".XXXXX.....                     ",
  ".XXXXX.                         ",
  ".X. .XX.                        ",
  "..  .XX.                        ",
  ".    .XX.                       ",
  "     .XX.                       ",
  "      .XX.                      ",
  "      .XX.                      ",
  "       ..                       ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"
};

static const char *arrow2[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  ". c #000000",
  "X c #ffffff",
  "  c None",
  /* pixels */
  ".                               ",
  "..                              ",
  "...                             ",
  "....                            ",
  ".....                           ",
  "......                          ",
  ".......                         ",
  "........                        ",
  ".........                       ",
  "..........                      ",
  "...........                     ",
  ".......                         ",
  "... ....                        ",
  "..  ....                        ",
  ".    ....                       ",
  "     ....                       ",
  "      ....                      ",
  "      ....                      ",
  "       ..                       ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"
};



#endif