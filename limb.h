#ifndef LIMB_H_
#define LIMB_H_

#include <inttypes.h>
#include "settings.h"

#if LIMB_SIZE_IN_BITS == 32
typedef uint32_t limb_t;
typedef uint64_t dlimb_t;
#define PRI_LIMB (PRIx32)
#elif LIMB_SIZE_IN_BITS == 64
typedef unsigned __int128 uint128_t;
typedef uint64_t limb_t;
typedef uint128_t dlimb_t;
#define PRI_LIMB (PRIx64)
#endif

#endif
