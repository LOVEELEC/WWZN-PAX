#ifndef __MHSCPU_VERSION_H
#define __MHSCPU_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

/**
  * @method	MH_GetFwlibVersion
  * @brief	Get the version number.
  * @param	void
  * @retval The constructed version number in the format:MMNNPP00 (Major, Minor, Patch).
  */
uint32_t MH_GetFwlibVersion(void);

#ifdef __cplusplus
}
#endif


#endif
