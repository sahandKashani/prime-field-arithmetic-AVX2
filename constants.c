#include "constants.h"

    #if PRIME_FIELD_BINARY_BIT_LENGTH == 131

        char *m_hex = "048e1d43f293469e33194c43186b3abc0b";
        char *a_hex = "041cb121ce2b31f608a76fc8f23d73cb66";
        char *b_hex = "02f74f717e8dec90991e5ea9b2ff03da58";

        #define NUM_POINTS (16)

        char *points_hex[NUM_POINTS][2] = {{"3bab0d982fb9d0de59bc0bec8e1050b13", "10253d893b53debdd5e52f87e25b8c0a3"},
                                           {"094a8389f671759ec2e55dde5dfd41750", "0b54ec3ee9f25281fcaa52add0be7fb54"},
                                           {"3c694fcbf0ed043b27968368f04766015", "16b9cdc810185e25bef1853878be33741"},
                                           {"1959ca8a3cee525c0c55e8c3d91bbc64b", "159b9e06091f30a9b5edff216229e74f2"},
                                           {"299378a49a7c3db974f5c2086ab3c3c82", "13405dea071e5d30b6b2349a43df2979f"},
                                           {"21933fcb129bb1f296ae89f9b15cf04f7", "1613c19bf63e239cb1cc39302e58e3f9a"},
                                           {"22a3847ba75fe435da1f23447259e6b6f", "007da71edd0263aec91f07ce5894e6d78"},
                                           {"37130ab3a5b64a8d41f693e0400b71bd8", "123f9387b35bfd5ff7059a708f44f46a0"},
                                           {"145a6dc76e79167352ea6baa362d2a86a", "0edd5f8d6ed91dbecf3144ac25d8da71a"},
                                           {"2615b64b1e182498b4b6ea0f960593786", "0032bbca6e787324bb53823c758aa395d"},
                                           {"27ea2cc6cb9050863a6f0305c121b7c7f", "18e712d0c16172feedfffc8477f9fe3b0"},
                                           {"0437c37d4a7654760a7592d2749fb4b8f", "20876e276102572a9189b0360457a6cda"},
                                           {"3528698d1205a8c601f2fd6f71af0112a", "1e89bddb0170ae6714d293c7d34cda0d2"},
                                           {"31c925d10fec9345d2376ba9ea2b902cb", "13b0467c49c5d93b6e3bf06d9f8e916a4"},
                                           {"327c0386de2461f1dc019cf764f60f707", "124089494da50266755286d7c725599dc"},
                                           {"02e42584142c19a5c6a314ded03da6d50", "22f7b32ca54fc4fe902fcb38b1a21ea77"}};

        #if SIMD_PARALLEL_WALKS

            #if FULL_LIMB_PRECISION

                #if LIMB_SIZE_IN_BITS == 16

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b, 0xbc0b,
                                                                                        0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a, 0x6b3a,
                                                                                        0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318, 0x4318,
                                                                                        0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c, 0x194c,
                                                                                        0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33, 0x9e33,
                                                                                        0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346, 0x9346,
                                                                                        0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2, 0x43f2,
                                                                                        0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d, 0x8e1d,
                                                                                        0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d, 0xff0d,
                                                                                        0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee, 0x21ee,
                                                                                        0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203, 0xe203,
                                                                                        0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4, 0x7ea4,
                                                                                        0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021, 0x8021,
                                                                                        0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47, 0x4a47,
                                                                                        0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c, 0x236c,
                                                                                        0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb, 0x30fb,
                                                                                        0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d};

                #elif LIMB_SIZE_IN_BITS == 32

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b,
                                                                                        0x194c4318, 0x194c4318, 0x194c4318, 0x194c4318, 0x194c4318, 0x194c4318, 0x194c4318, 0x194c4318,
                                                                                        0x93469e33, 0x93469e33, 0x93469e33, 0x93469e33, 0x93469e33, 0x93469e33, 0x93469e33, 0x93469e33,
                                                                                        0x8e1d43f2, 0x8e1d43f2, 0x8e1d43f2, 0x8e1d43f2, 0x8e1d43f2, 0x8e1d43f2, 0x8e1d43f2, 0x8e1d43f2,
                                                                                        0x00000004, 0x00000004, 0x00000004, 0x00000004, 0x00000004, 0x00000004, 0x00000004, 0x00000004};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x92600513, 0x92600513, 0x92600513, 0x92600513, 0x92600513, 0x92600513, 0x92600513, 0x92600513,
                                                                                        0xf95d709f, 0xf95d709f, 0xf95d709f, 0xf95d709f, 0xf95d709f, 0xf95d709f, 0xf95d709f, 0xf95d709f,
                                                                                        0xb65ef639, 0xb65ef639, 0xb65ef639, 0xb65ef639, 0xb65ef639, 0xb65ef639, 0xb65ef639, 0xb65ef639,
                                                                                        0xf3d6fa1f, 0xf3d6fa1f, 0xf3d6fa1f, 0xf3d6fa1f, 0xf3d6fa1f, 0xf3d6fa1f, 0xf3d6fa1f, 0xf3d6fa1f,
                                                                                        0x00000003, 0x00000003, 0x00000003, 0x00000003, 0x00000003, 0x00000003, 0x00000003, 0x00000003};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0x985b105d, 0x985b105d, 0x985b105d, 0x985b105d, 0x985b105d, 0x985b105d, 0x985b105d, 0x985b105d};

                #elif LIMB_SIZE_IN_BITS == 64

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x194c43186b3abc0b, 0x194c43186b3abc0b, 0x194c43186b3abc0b, 0x194c43186b3abc0b,
                                                                                        0x8e1d43f293469e33, 0x8e1d43f293469e33, 0x8e1d43f293469e33, 0x8e1d43f293469e33,
                                                                                        0x0000000000000004, 0x0000000000000004, 0x0000000000000004, 0x0000000000000004};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x7f8aade1eeebae5c, 0x7f8aade1eeebae5c, 0x7f8aade1eeebae5c, 0x7f8aade1eeebae5c,
                                                                                        0x5fc60ba5261f2555, 0x5fc60ba5261f2555, 0x5fc60ba5261f2555, 0x5fc60ba5261f2555,
                                                                                        0x0000000000000001, 0x0000000000000001, 0x0000000000000001, 0x0000000000000001};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0xe0587d72985b105d, 0xe0587d72985b105d, 0xe0587d72985b105d, 0xe0587d72985b105d};

                #endif /* LIMB_SIZE_IN_BITS */

            #else /* FULL_LIMB_PRECISION */

                #if LIMB_SIZE_IN_BITS == 16

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b, 0x3c0b,
                                                                                        0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675, 0x5675,
                                                                                        0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61, 0x0c61,
                                                                                        0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62, 0x4a62,
                                                                                        0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331, 0x6331,
                                                                                        0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3, 0x68d3,
                                                                                        0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4, 0x7ca4,
                                                                                        0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1, 0x0ea1,
                                                                                        0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e, 0x048e};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938, 0x1938,
                                                                                        0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b, 0x477b,
                                                                                        0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022, 0x4022,
                                                                                        0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3, 0x0cd3,
                                                                                        0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff, 0x20ff,
                                                                                        0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de, 0x35de,
                                                                                        0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2, 0x69c2,
                                                                                        0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0, 0x32c0,
                                                                                        0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf, 0x02cf};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d, 0x105d};

                #elif LIMB_SIZE_IN_BITS == 32

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b, 0x6b3abc0b,
                                                                                        0x32988630, 0x32988630, 0x32988630, 0x32988630, 0x32988630, 0x32988630, 0x32988630, 0x32988630,
                                                                                        0x4d1a78cc, 0x4d1a78cc, 0x4d1a78cc, 0x4d1a78cc, 0x4d1a78cc, 0x4d1a78cc, 0x4d1a78cc, 0x4d1a78cc,
                                                                                        0x70ea1f94, 0x70ea1f94, 0x70ea1f94, 0x70ea1f94, 0x70ea1f94, 0x70ea1f94, 0x70ea1f94, 0x70ea1f94,
                                                                                        0x00000048, 0x00000048, 0x00000048, 0x00000048, 0x00000048, 0x00000048, 0x00000048, 0x00000048};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x3a8124f5, 0x3a8124f5, 0x3a8124f5, 0x3a8124f5, 0x3a8124f5, 0x3a8124f5, 0x3a8124f5, 0x3a8124f5,
                                                                                        0x50d8fba2, 0x50d8fba2, 0x50d8fba2, 0x50d8fba2, 0x50d8fba2, 0x50d8fba2, 0x50d8fba2, 0x50d8fba2,
                                                                                        0x3c6ef24f, 0x3c6ef24f, 0x3c6ef24f, 0x3c6ef24f, 0x3c6ef24f, 0x3c6ef24f, 0x3c6ef24f, 0x3c6ef24f,
                                                                                        0x15101643, 0x15101643, 0x15101643, 0x15101643, 0x15101643, 0x15101643, 0x15101643, 0x15101643,
                                                                                        0x00000047, 0x00000047, 0x00000047, 0x00000047, 0x00000047, 0x00000047, 0x00000047, 0x00000047};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0x185b105d, 0x185b105d, 0x185b105d, 0x185b105d, 0x185b105d, 0x185b105d, 0x185b105d, 0x185b105d};

                #elif LIMB_SIZE_IN_BITS == 64

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x194c43186b3abc0b, 0x194c43186b3abc0b, 0x194c43186b3abc0b, 0x194c43186b3abc0b,
                                                                                        0x1c3a87e5268d3c66, 0x1c3a87e5268d3c66, 0x1c3a87e5268d3c66, 0x1c3a87e5268d3c66,
                                                                                        0x0000000000000012, 0x0000000000000012, 0x0000000000000012, 0x0000000000000012};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x776298d851741001, 0x776298d851741001, 0x776298d851741001, 0x776298d851741001,
                                                                                        0x4e666dcab3b212b0, 0x4e666dcab3b212b0, 0x4e666dcab3b212b0, 0x4e666dcab3b212b0,
                                                                                        0x000000000000000c, 0x000000000000000c, 0x000000000000000c, 0x000000000000000c};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0x60587d72985b105d, 0x60587d72985b105d, 0x60587d72985b105d, 0x60587d72985b105d};

                #endif /* LIMB_SIZE_IN_BITS */

            #endif /* FULL_LIMB_PRECISION */

        #else /* SIMD_PARALLEL_WALKS */

            #if FULL_LIMB_PRECISION

                #if LIMB_SIZE_IN_BITS == 16

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0xbc0b, 0x6b3a, 0x4318, 0x194c, 0x9e33, 0x9346, 0x43f2, 0x8e1d, 0x0004};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0xff0d, 0x21ee, 0xe203, 0x7ea4, 0x8021, 0x4a47, 0x236c, 0x30fb, 0x0001};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0x105d};

                #elif LIMB_SIZE_IN_BITS == 32

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x6b3abc0b, 0x194c4318, 0x93469e33, 0x8e1d43f2, 0x00000004};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x92600513, 0xf95d709f, 0xb65ef639, 0xf3d6fa1f, 0x00000003};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0x985b105d};

                #elif LIMB_SIZE_IN_BITS == 64

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x194c43186b3abc0b, 0x8e1d43f293469e33, 0x0000000000000004};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x7f8aade1eeebae5c, 0x5fc60ba5261f2555, 0x0000000000000001};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0xe0587d72985b105d};

                #endif /* LIMB_SIZE_IN_BITS */

            #else /* FULL_LIMB_PRECISION */

                #if LIMB_SIZE_IN_BITS == 16

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x3c0b, 0x5675, 0x0c61, 0x4a62, 0x6331, 0x68d3, 0x7ca4, 0x0ea1, 0x048e};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x1938, 0x477b, 0x4022, 0x0cd3, 0x20ff, 0x35de, 0x69c2, 0x32c0, 0x02cf};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0x105d};

                #elif LIMB_SIZE_IN_BITS == 32

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x6b3abc0b, 0x32988630, 0x4d1a78cc, 0x70ea1f94, 0x00000048};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x3a8124f5, 0x50d8fba2, 0x3c6ef24f, 0x15101643, 0x00000047};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0x185b105d};

                #elif LIMB_SIZE_IN_BITS == 64

                    limb_building_block_t m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS]         = {0x194c43186b3abc0b, 0x1c3a87e5268d3c66, 0x0000000000000012};
                    limb_building_block_t R_2_mod_m[NUM_ENTRIES_IN_LIMB * NUM_LIMBS] = {0x776298d851741001, 0x4e666dcab3b212b0, 0x000000000000000c};
                    limb_building_block_t m_prime[NUM_ENTRIES_IN_LIMB]               = {0x60587d72985b105d};

                #endif /* LIMB_SIZE_IN_BITS */

            #endif /* FULL_LIMB_PRECISION */

        #endif /* SIMD_PARALLEL_WALKS */

    #endif /* PRIME_FIELD_BINARY_BIT_LENGTH */
