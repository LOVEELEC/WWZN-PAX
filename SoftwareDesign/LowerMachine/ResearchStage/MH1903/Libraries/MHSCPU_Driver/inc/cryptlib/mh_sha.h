/* SHA.H - header file for SHA.C
 */

#ifndef __MH_SHA_H
#define __MH_SHA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "mh_crypt.h"

typedef enum
{
    SHA_160 = 0,
    SHA_224 = 1,
    SHA_256 = 2,
    SHA_384 = 3,
    SHA_512 = 4
}mh_sha_mode_def;


typedef struct
{
    uint32_t total[2];
    uint8_t buffer[64];
    uint32_t state[5];
}sha1_context;

typedef struct
{
    uint32_t total[2];
    uint8_t buffer[64];
    uint32_t state[8];
}sha2_context;



#define MH_RET_SHA_BUSY             (('R'<<24)|('S'<<16)|('B'<<8)|('U'))
#define MH_RET_SHA_MODE_ERR         (('R'<<24)|('S'<<16)|('M'<<8)|('E'))
#define MH_RET_SHA_SUCCESS          (('R'<<24)|('S'<<16)|('S'<<8)|('U'))

/**
  * @method mh_sha
  * @brief  Secure Hash Alogrithm
  * @param  mode        :SHA mode: SHA_160/SHA_224/SHA_256/SHA_384/SHA_512
  * @param  output      :output data buffer
  * @param  input       :input data buffer
  * @param  ibytes      :size of input data
  * @retval             :SHA_TYPE_ERR or SHA_CRYPT_BUSY
  */
uint32_t mh_sha(mh_sha_mode_def mode, uint8_t *output, uint8_t *input, uint32_t ibytes);

/**
  * @method mh_sha_sec
  * @brief  Secure Hash Alogrithm Rand Copy
  * @param  mode        :SHA mode: SHA_256/SHA_384/SHA_512
  * @param  output      :output data buffer
  * @param  input       :input data buffer
  * @param  ibytes      :size of input data
  * @param  f_rng       :true random number generation function point
  * @param  p_rng       :true random number generation para
  * @retval             :SHA_TYPE_ERR or SHA_CRYPT_BUSY
  */
uint32_t mh_sha_sec(mh_sha_mode_def type, uint8_t *output, uint8_t *input, uint32_t ibytes,
                            mh_rng_callback f_rng, void *p_rng);

/*****************************************************************************
 Prototype    : mh_sha_first
 Description  : continue calculator the SHA
 Input        : type
                uint8_t *output
                uint8_t *input
                uint32_t inputlenth
 Output       : None
 Return Value : uint32_t 

  History        :
  1.Date         : 2016/9/2
    Author       : Wangzhanbei
    Modification : Created function

*****************************************************************************/
//uint32_t mh_sha_first(mh_sha_mode_def type, uint8_t *output, uint8_t *input, uint32_t ibytes);

/*****************************************************************************
 Prototype    : mh_sha_second
 Description  : continue calculator the SHA
 Input        : type
                uint8_t *output
                uint8_t *input
                uint32_t inputlenth
 Output       : None
 Return Value : uint32_t 

  History        :
  1.Date         : 2016/9/2
    Author       : Wangzhanbei
    Modification : Created function

*****************************************************************************/
//uint32_t mh_sha_second(mh_sha_mode_def type, uint8_t *output, uint8_t *input, uint32_t inputlenth,uint8_t *datain);




void sha1_starts(sha1_context *ctx);
void sha1_update(sha1_context *ctx,const uint8_t *input,uint32_t i_len);
void sha1_finish(sha1_context *ctx,uint8_t digest[20]);


void sha256_starts(sha2_context *ctx);
void sha256_update(sha2_context *ctx,const uint8_t *input,uint32_t i_len);
void sha256_finish(sha2_context *ctx,uint8_t digest[32]);


#ifdef __cplusplus
}
#endif  

#endif
