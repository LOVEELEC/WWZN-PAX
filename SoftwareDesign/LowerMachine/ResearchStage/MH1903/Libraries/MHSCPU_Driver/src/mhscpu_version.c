#include "mhscpu_version.h"

/**
 * The single version number has the following structure: MMNNPP00
 *    Major version | Minor version | Patch version
 *   ¿â°æ±¾ËµÃ÷£º
     03-------MH1903
     01-------Minor version
	 00-------version
 */


#define FWLIB_VERSION_NUMBER         0x03010000

uint32_t MH_GetFwlibVersion(void)
{
    return FWLIB_VERSION_NUMBER;
}
