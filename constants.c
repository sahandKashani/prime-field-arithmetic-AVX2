#include <assert.h>
#include "constants.h"
#include "gmp_int.h"
#include "utilities.h"

#if PRIME_FIELD_BINARY_BIT_LENGTH == 131

    char *m_hex_glo = "048e1d43f293469e33194c43186b3abc0b";
    char *a_hex_glo = "041cb121ce2b31f608a76fc8f23d73cb66";
    char *b_hex_glo = "02f74f717e8dec90991e5ea9b2ff03da58";
    char *points_x_hex_glo[NUM_POINTS] = {"3bab0d982fb9d0de59bc0bec8e1050b13", "94a8389f671759ec2e55dde5dfd41750", "3c694fcbf0ed043b27968368f04766015", "1959ca8a3cee525c0c55e8c3d91bbc64b", "299378a49a7c3db974f5c2086ab3c3c82", "21933fcb129bb1f296ae89f9b15cf04f7", "22a3847ba75fe435da1f23447259e6b6f", "37130ab3a5b64a8d41f693e0400b71bd8", "145a6dc76e79167352ea6baa362d2a86a", "2615b64b1e182498b4b6ea0f960593786", "27ea2cc6cb9050863a6f0305c121b7c7f", "437c37d4a7654760a7592d2749fb4b8f", "3528698d1205a8c601f2fd6f71af0112a", "31c925d10fec9345d2376ba9ea2b902cb", "327c0386de2461f1dc019cf764f60f707", "2e42584142c19a5c6a314ded03da6d50", "422888fe9e6d2522198aff100f7cae47d", "57b046d33488e5abd66fa2c5969301fa", "1dee12d3c5c4c6a15cd453034250d05a8", "34bfb1d90aefbb56eafee888e854efc56", "2d56073838f7da30daaa025ee93f04410", "191123f7c0afa7a86485dbc6ededcb7af", "45ba5f04567160d76d45601cd825226a2", "1237fb72aa4208c44aefca4c8d5c7b8ab", "40274b78d9d141695bfaf03c2cf14f783", "209a363bbcdd7fedf6724922b23af880", "2bbdf8e1f90f9a4ec0b86c8d827b946e7", "445dbee8a63cd3f836354c54efec977c3", "416d76c67c895700ecc4968cdaf8dde87", "46ea3db94333ebd44afbd718bd9845a30", "23e3f1fffab9898952d402734f717f1d3", "1b48c922a33d164672e921ad80638ca34", "476aa243c380b4e173a4dff53aff019cb", "3e9a8e901d5b7aa05b3654bb6a21f01eb", "2c89d53468c7f6818dcb6d9cf48ea16d1", "1a9c31ffe8f2b25dede48971b4131f3ab", "3e2db16ce01c0c5c5b7af69822a6db54f", "23f837c62ca368534cda88538afa72510", "1ab015b81ccc20b2cffe2966ef31ce5f4", "1d1e4088720020d47ce9a94d7b19f5c23", "2c463b0bc879a496cc25fb9be4bccbb58", "38a578962c8c53d072aa367a99245c544", "16ade7f5f72d27528feeebd940f0aed77", "6202cd2c246fe6a875676bb54767361e", "23e559e5984c0565f4fa0c09e5363588a", "436df1882bafbe7e9acaf9f720818c914", "4649c9f8680e93b6ac926c9ef59d18fc8", "3feff5ff560f3dde129a071b57283f203", "2f8c69b7fc7956f518bbb80fb503ec1a", "66d939f309b4657cc37773fe83c565c3", "5bcccafa54d68a74454b125dea9a74eb", "23507e9a15294b340c640c786bfa195", "1c4091a17a04d404de3837f2a636e7caf", "41ad310f57b935376f1b5401636d46040", "24134ddb2c75d7e7b5b67a1f7e119c643", "3b38fabefc0b0ab79999b748f00865035", "3dc39734683062e94cb5457122a1232de", "48643d4bb8a1fd568eeeec7674d2594dc", "2efa7aa1cf21a8357e92cab485564a9a", "9c395d940371fba89982be12b267a310", "17553ebf3f28e37b5105c612a847d24b1", "1c9eb39d6b1c4eefb7257e6a333bd0390", "231c82ebe2ffdd9fddd7271ec52644686", "1972b3547e8d1669c03d0715a668098f4", "44fd12e95ee435d799a23458afbb9b4d", "3e3fe173b9b3164c7f88ee69babb894c6", "ee708104f33134f96d72c6773a41025a", "3242ab865630a5b60d0792d04cc08db4d", "1a29de3c96e7924e8aa5fcf6abfd289c8", "388df26f9d0a40a50a36a7486fb0d0785", "3a894381c3ce90272a3e9d704dcae838c", "26197293155d3f4255a42f6b6d432e9ad", "3b2975130bd89f0d53752e48eab247b97", "74fe182049511d4d21f9aee43189b2aa", "3be6d971b2d0239fe678d66055b425c2d", "42cb0a86a32ce248281319c3345a777d1", "8fa13265bc7aaf6871918a56fd97ed24", "3e1974eafc262bc0524b2a91f6e448096", "64bdb27a3e7d9a77717b01f47e085dfa", "297af9d689b83617c2b53f1a5e9b07fcd", "5ba96b2edaadcc2f3e3ab6fa74e05846", "44157731b1af35a83c0650edadfd57b46", "1d9747720fbae57d0635b4a2b1675a16c", "3e0aeac85d1cb1b9a81a4796f33b1b5f", "37e79ea3a6b9e240c56a0672bc4b0d860", "2bb342e51fa6e1a006a46a49ec2a5acd1", "265a7431de6dc4947dde4ea649f573bb", "57282694750707d1abaa48d9fc3669a0", "cb25662dd83bd14a8ffc8bf00cb90c33", "2d6676dc9ec0ad372cc9f898a5e5d49ca", "237e6f654562b61bab113af09163f568f", "fa3364dd195d2567c01148e0fefc0958", "4a728dc3bdc42b270d05e41381986d92", "28bdfe48ed37500cadf712d19bd5ff0dc", "357b8b51be32a3946718949061b831f6e", "f6c96807bd9765e4143d802c3f2371c8", "3f28716fb878aa887c1d37541bf537200", "25e2eff716cdc04326fc5ea892e6b8769", "39b31bf35015b4dcdc734991dda64b525", "211788bac8e7dee9dd1cda7a3f82cda6", "36529279981ca52c8b8794c59696fa771", "2c865b1fe964e9fb18750276ab6ff7688", "a52647fdef0a802767cf0d886e87a223", "56bc1252c3abf453dd6b7741d8707e84", "135849d412a979401bc62d21967d48429", "11ea38d569cf5eb42bd779377269df79e", "44b78734aa32f340b79483af4f125f7e", "2702b1d9f01b5f877ab94a8459fd2e7", "a258d8706adc5b89f4107eb265d5c5da", "235f53e30663fd31478a141a07802feba", "cbac231f97fa52ce7e345977609b3f43", "4000d8899720cf77978db854de6266a86", "31bf8d58d1171b595c8ea53fe56ca0109", "fd673961487100046b954a8dd69ee3e0", "39c3be312198482aa9d3a26250762228d", "24a2e0c427d5631cf093d06cec66dbfed", "2703caf316d91bddfee581567297cb363", "3113cd8a0251c05cd3fbe7e1cd14aa8cc", "26832d4edbf113508a44f182969d4e779", "bab30f0b506099401559a57b75dfee61", "253aae4f7ac6acdc4f33d2db00d226aa5", "253a8e533752fa446c654bf952f3babcd", "21df1b6ff43470b3ffb3b1a89ece6297c", "23aafc0815db313a789f12beaf289aefc", "2d58d413e2449730a072f8c8ca1c8203c", "3fdad95b82b5a52c282dff45d8af07262", "df4dff0e5d5926bb0e9c68696dd73728", "247943cf861177dd731073de8fb7a3f3c"};
    char *points_y_hex_glo[NUM_POINTS] = {"10253d893b53debdd5e52f87e25b8c0a3", "b54ec3ee9f25281fcaa52add0be7fb54", "16b9cdc810185e25bef1853878be33741", "159b9e06091f30a9b5edff216229e74f2", "13405dea071e5d30b6b2349a43df2979f", "1613c19bf63e239cb1cc39302e58e3f9a", "7da71edd0263aec91f07ce5894e6d78", "123f9387b35bfd5ff7059a708f44f46a0", "edd5f8d6ed91dbecf3144ac25d8da71a", "32bbca6e787324bb53823c758aa395d", "18e712d0c16172feedfffc8477f9fe3b0", "20876e276102572a9189b0360457a6cda", "1e89bddb0170ae6714d293c7d34cda0d2", "13b0467c49c5d93b6e3bf06d9f8e916a4", "124089494da50266755286d7c725599dc", "22f7b32ca54fc4fe902fcb38b1a21ea77", "1dbcc631759700af323c3579502b13cd3", "246f81a63ac72ad65f9b0a4654f9bb4fc", "13f631ff47165192d7ab636c2b5a0c69c", "3d045449dd4466ebd72ffcc077c2a60d", "d0070f1370ba0fba3d4bd309ce48c0aa", "1e645d17913cb8a50ef49c0f4bb669705", "2414c8807ad77542525248e4b79ab0d02", "200c489cc6c2b3825ddcfec03ef444dc9", "15fe6d8af761e3db39fd52cd2e0950f", "2fcc4210e20a4b816f4b7d22edb4b742", "21fdb394de0817f995988e4f30efd34c0", "b467cb8eeb7fbab3f4ea5c8e06a63563", "8cc516a43b22f83fa23b7100ea86e903", "954a04f5ab3a4b4bbe7832796bf221c8", "53f45c66060283942fa96d61cf4e6ee0", "36826369dc2efdf65200922a84b4b60e", "4453abfb90e08ecdf114a6705f87829f", "109fc15791437280ac68714d70b5cbf1f", "9b1624bb282b4f9bfdf8bfab8a3d5d96", "206715a7016774ed0679940dbb26806e1", "54d60d9b0c7922851b8c0ebf9e3af871", "1acb49d690146027e5bdfae2ff8833d4c", "e30dc1833d695e17c5c419de57c771fd", "102ebde6578c8971a878c39e34c94b048", "242a7c6501df0e1015232c8475383bb12", "130b41374509f1b2e44452b1b8bb45a77", "1ae52812c9c15522c6496f0823e65adc1", "44681455d82db9de8f0af6c05972dd0a", "192262fc9aefca9c7e7ac46972d638c5f", "1709ecf203393f2d3aaae004921debff7", "14750501b9c01bacb7aea718550595bb1", "f3d01b64f82bee58ff76b9e9f87ca472", "65d6220a00427c98a56dadcf06b4d07e", "1e12657709c6464877b23717cb7c7c33", "112f217c24ab3c2992222a70e3ed299b2", "7c3e4e1fe927a8248924b603483d77e7", "1e9c8adef89e225cfc0d252b25f510b38", "17d3169415dbaf9329b589c839eb9bc74", "13720c101b2254e1b13687a39dc39e02c", "15733fc30a04e12c80d24ee03a082e925", "12968d9d2eb4ec6bf6406e1ecbf5b70d", "71ae4bafc62e37313ec2efdd6dd34ce5", "f6d6b7db1498d8cec1aee01a907e09be", "21db2786210a08f032fc851e3f6797f15", "22050af7efba0976ef948168eef43864f", "3df737b3fb0559960b219f3e7ad51664", "1f20d3b1285f8b5f91a07acd28a25e466", "38b7ccfc9401fedc922ab7fae97c266b", "1ff66a67039116723f8fb17fbd6db5047", "201ec938a29b490d141e9e1d6bd7c0582", "f346192dd122a1e80937cdba67a9b29b", "9fbd88035a6d6d2e406a896b91a5dbcf", "13e6b79f8a8cefe0ac944106a4784366", "3e4c02c56dee17c268c272713a9dfef8", "22af76078baab55cc2bff364da172d1e0", "bac488f0aec1e2a569eb2d654462268a", "1850c109bca4ab1187e2743e62226d16", "1345bbf1fe712cc9409b34c2bdcf48854", "1313b248e235fbd3f71c8f091acc274b4", "f5a74dd863231d67d97ed51b71e77896", "27af50707d322d1ca35b693fe86fd077", "7264a321d00104ce4c33b01abb6dce76", "1807b5116877e96613d321d6b2ec4455f", "73ab94bb3dab5ec48e3eff32046483fd", "222e4f5ab86a8108b2e1106b4880aaed7", "2134014ef10c23cc1da8aaebcb71d1402", "483bcb2926fac056c5f7398159d38390", "1b8d842adb78136483609d1ab83e3e7da", "1e22c1becabf735766053bc7b11f23636", "14927ae61fe98ddbfc9bbe91b01a0c0c8", "268de5a6c14e9d822089f0c8a7154344", "ac8e474f331afc6ba309d3343a00040f", "1bbcfdc51ee4e32fa75020c2eb17f11a7", "18aee9f5a9554446c937746e1146f45dd", "17e2fe7c831c598ef9241a3dae4418be7", "21d4b8df07c41bb083f8896da72a3e42b", "17a55fb0cce1db369a6801a83bd7018e9", "11f345a9b8a79c3d800433d1c34071bbf", "13fa47a645ea3c2c3a5452667b239c4f3", "3a87cf697cea0a9800bb00ec0e9c0653", "157d61668bcf133a7d9bd7874cbc7d775", "b45eb20c2226eb7ac03ca09477342b56", "1da68098d40b1da8d2424a70d454f310a", "c1c21e630a8a2219513b8fc679bfa930", "16919e04269b4dc93e9aa31a27feb78d2", "199bcc6da1b766f1f47dd6715a50a91cc", "221da3e7ad86ba236436a962038dd72d4", "1cf1df226ad2ae576425ae2cfef16f1f1", "4dfa2d166ab1b1db04c4678501038c18", "22f148970891f4ab97200b4e2b73c8cb6", "b58b4de07860ca34c181cd9fd2dc157b", "85358cca0f582f2c4c8e5a850ce56c2e", "215859043c12a85ea1e9273566b1e00fa", "5379f5902ec8a510f8df3def17572e12", "16f63320da5a6ade4ace43305ac450dbe", "11941c9a37a5b24a8206dbee7be510018", "2b6df18bc178cd3f1831fbdb3e30b332", "7a22eb2c3dddcaa8ea842efd83fa4151", "19a1b952e5fc5a71fefd04ce70dc78a0b", "624dc037b4716a5d2d79526cafb92825", "804b3f0a51dd46ee9f148c68ee38b11", "23d49e2d7557f2dd78e65a42c3519227b", "1b02b03abae4e64c8d7dca411a78f6039", "10853a71d8fdb86f5b54f952e8e19a95b", "cc59ee3c925ca5635f58022503c14225", "1c86539cae9fba2218f57b511366f306b", "1cce11543c96a317a0a85100ba9a2c37c", "5e847ff69070643e4921590574c8ff", "1e95e27dfe8e7cc0fd17f303977e8fa30", "279410cd6c98b6272b255c3533e453f", "61f2f4db36b914fc4e3ad28de71f6a02", "b841253cc142c8dfbdde463d12e17b21"};

#endif /* PRIME_FIELD_BINARY_BIT_LENGTH */

limb_t m_glo[NUM_LIMBS];
limb_t a_glo[NUM_LIMBS];
limb_t b_glo[NUM_LIMBS];
limb_t points_x_glo[NUM_POINTS / NUM_ENTRIES_IN_LIMB][NUM_LIMBS];
limb_t points_y_glo[NUM_POINTS / NUM_ENTRIES_IN_LIMB][NUM_LIMBS];
limb_t R_2_mod_m_glo[NUM_LIMBS];
limb_t m_prime_glo;

gmp_int_t m_glo_gmp;
gmp_int_t a_glo_gmp;
gmp_int_t b_glo_gmp;
gmp_int_t points_x_glo_gmp[NUM_POINTS / NUM_ENTRIES_IN_LIMB];
gmp_int_t points_y_glo_gmp[NUM_POINTS / NUM_ENTRIES_IN_LIMB];
gmp_int_t R_2_mod_m_glo_gmp;
gmp_int_t m_prime_glo_gmp;

void initialize_constants() {
    /* initializing global gmp */
    gmp_int_init(m_glo_gmp);
    gmp_int_init(a_glo_gmp);
    gmp_int_init(b_glo_gmp);
    gmp_int_init(R_2_mod_m_glo_gmp);
    gmp_int_init(m_prime_glo_gmp);
    for (unsigned int i = 0; i < (NUM_POINTS / NUM_ENTRIES_IN_LIMB); i++) {
        gmp_int_init(points_x_glo_gmp[i]);
        gmp_int_init(points_y_glo_gmp[i]);
    }

    /* initializing local gmp */
    gmp_int_t base_gmp;
    gmp_int_t R_gmp;
    gmp_int_init(base_gmp);
    gmp_int_init(R_gmp);

    /* assign values to gmp representatives */
    gmp_int_ui_pow_ui(base_gmp, 2, BASE_EXPONENT);
    gmp_int_set_str(m_glo_gmp, m_hex_glo, 16);
    gmp_int_ui_pow_ui(R_gmp, 2, BASE_EXPONENT * NUM_LIMBS);
    gmp_int_mul(R_2_mod_m_glo_gmp, R_gmp, R_gmp);
    gmp_int_mod(R_2_mod_m_glo_gmp, R_2_mod_m_glo_gmp, m_glo_gmp);
    int inverse_exists[NUM_ENTRIES_IN_LIMB];
    gmp_int_invert(inverse_exists, m_prime_glo_gmp, m_glo_gmp, base_gmp);
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        assert(inverse_exists[i] != 0);
    }
    gmp_int_neg(m_prime_glo_gmp, m_prime_glo_gmp);
    gmp_int_mod(m_prime_glo_gmp, m_prime_glo_gmp, base_gmp);
    gmp_int_set_str(a_glo_gmp, a_hex_glo, 16);
    gmp_int_set_str(b_glo_gmp, b_hex_glo, 16);
    for (unsigned int i = 0; i < (NUM_POINTS / NUM_ENTRIES_IN_LIMB); i++) {
        gmp_int_set_strings(points_x_glo_gmp[i], points_x_hex_glo + (i * NUM_ENTRIES_IN_LIMB), 16);
        gmp_int_set_strings(points_y_glo_gmp[i], points_y_hex_glo + (i * NUM_ENTRIES_IN_LIMB), 16);
    }

    /* assign values to limb_t representatives */
    convert_gmp_to_num(m_glo, m_glo_gmp, NUM_LIMBS);
    convert_gmp_to_num(R_2_mod_m_glo, R_2_mod_m_glo_gmp, NUM_LIMBS);
    convert_gmp_to_num(&m_prime_glo, m_prime_glo_gmp, 1);
    convert_gmp_to_num(a_glo, a_glo_gmp, NUM_LIMBS);
    convert_gmp_to_num(b_glo, b_glo_gmp, NUM_LIMBS);
    for (unsigned int i = 0; i < (NUM_POINTS / NUM_ENTRIES_IN_LIMB); i++) {
        convert_gmp_to_num(points_x_glo[i], points_x_glo_gmp[i], NUM_LIMBS);
        convert_gmp_to_num(points_y_glo[i], points_y_glo_gmp[i], NUM_LIMBS);
    }

    /* free gmp memory */
    gmp_int_clear(base_gmp);
    gmp_int_clear(R_gmp);
}

void free_constants() {
    gmp_int_clear(m_glo_gmp);
    gmp_int_clear(a_glo_gmp);
    gmp_int_clear(b_glo_gmp);
    gmp_int_clear(R_2_mod_m_glo_gmp);
    gmp_int_clear(m_prime_glo_gmp);
    for (unsigned int i = 0; i < (NUM_POINTS / NUM_ENTRIES_IN_LIMB); i++) {
        gmp_int_clear(points_x_glo_gmp[i]);
        gmp_int_clear(points_y_glo_gmp[i]);
    }
}
