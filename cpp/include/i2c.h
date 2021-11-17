
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <SDR_Std.h>

char AppI2cWr(UI_32 fd, SI_8 devaddr, SI_8 regaddr, SI_8 *data, UI_32 size);
char AppI2cRd(SI_8 busno,SI_8 i2caddr, SI_8 addr, SI_8 *buf, UI_32 size);

