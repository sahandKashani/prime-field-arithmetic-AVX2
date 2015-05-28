#include "constants.h"

    #if PRIME_FIELD_BINARY_BIT_LENGTH == 131

        #if SIMD_PARALLEL_WALKS

        #else /* SIMD_PARALLEL_WALKS */

            #if FULL_LIMB_PRECISION

                #if LIMB_SIZE_IN_BITS == 16

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0xbc0b, 0x6b3a, 0x4318, 0x194c, 0x9e33, 0x9346, 0x43f2, 0x8e1d, 0x0004};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0xff0d, 0x21ee, 0xe203, 0x7ea4, 0x8021, 0x4a47, 0x236c, 0x30fb, 0x0001};

                #elif LIMB_SIZE_IN_BITS == 32

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x6b3abc0b, 0x194c4318, 0x93469e33, 0x8e1d43f2, 0x00000004};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x92600513, 0xf95d709f, 0xb65ef639, 0xf3d6fa1f, 0x00000003};

                #elif LIMB_SIZE_IN_BITS == 64

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x194c43186b3abc0b, 0x8e1d43f293469e33, 0x0000000000000004};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x7f8aade1eeebae5c, 0x5fc60ba5261f2555, 0x0000000000000001};

                #endif /* LIMB_SIZE_IN_BITS */

            #else /* FULL_LIMB_PRECISION */

                #if LIMB_SIZE_IN_BITS == 16

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x3c0b, 0x5675, 0x0c61, 0x4a62, 0x6331, 0x68d3, 0x7ca4, 0x0ea1, 0x048e};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x1938, 0x477b, 0x4022, 0x0cd3, 0x20ff, 0x35de, 0x69c2, 0x32c0, 0x02cf};

                #elif LIMB_SIZE_IN_BITS == 32

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x6b3abc0b, 0x32988630, 0x4d1a78cc, 0x70ea1f94, 0x00000048};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x3a8124f5, 0x50d8fba2, 0x3c6ef24f, 0x15101643, 0x00000047};

                #elif LIMB_SIZE_IN_BITS == 64

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x194c43186b3abc0b, 0x1c3a87e5268d3c66, 0x0000000000000012};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x776298d851741001, 0x4e666dcab3b212b0, 0x000000000000000c};

                #endif /* LIMB_SIZE_IN_BITS */

            #endif /* FULL_LIMB_PRECISION */

        #endif /* SIMD_PARALLEL_WALKS */

    #endif /* PRIME_FIELD_BINARY_BIT_LENGTH */
