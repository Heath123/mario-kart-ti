/*
 * Copyright (C) 2021 Heath123 (Heath Mitchell)
 * Uses https://github.com/mortonsc/TIgameoflife as a template - (C) 2016 Scott Morton 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <string.h>
#include "lib/c_ti83p.h"

#define byte unsigned char

byte o = 0;

// Data that should be auto-generated in the future
#define width 48
#define height 64

#define horizon 32

#define sixteenBitHeight 20
#define eightBitHeight 12

#define angleWidth 54

#define precision 32

// Will probably be slow on a Z80 (16-bit integers), but ¯\_(ツ)_/¯
const unsigned short angles16[angleWidth][sixteenBitHeight][2] = {
    {{0, 0}, {0, 2607}, {0, 1303}, {0, 868}, {0, 651}, {0, 520}, {0, 433}, {0, 371}, {0, 324}, {0, 288}, {0, 259}, {0, 235}, {0, 215}, {0, 198}, {0, 184}, {0, 171}, {0, 160}, {0, 151}, {0, 142}, {0, 134}},
    {{0, 0}, {75, 2606}, {37, 1302}, {25, 868}, {18, 651}, {15, 520}, {12, 433}, {10, 371}, {9, 324}, {8, 288}, {7, 259}, {6, 235}, {6, 215}, {5, 198}, {5, 184}, {4, 171}, {4, 160}, {4, 151}, {4, 142}, {3, 134}},
    {{0, 0}, {151, 2603}, {75, 1301}, {50, 867}, {37, 650}, {30, 519}, {25, 433}, {21, 370}, {18, 324}, {16, 288}, {15, 259}, {13, 235}, {12, 215}, {11, 198}, {10, 184}, {9, 171}, {9, 160}, {8, 150}, {8, 142}, {7, 134}},
    {{0, 0}, {227, 2597}, {113, 1298}, {75, 865}, {56, 648}, {45, 518}, {37, 432}, {32, 370}, {28, 323}, {25, 287}, {22, 258}, {20, 234}, {18, 214}, {17, 198}, {16, 183}, {14, 171}, {14, 160}, {13, 150}, {12, 141}, {11, 134}},
    {{0, 0}, {302, 2589}, {151, 1294}, {100, 862}, {75, 646}, {60, 517}, {50, 430}, {43, 369}, {37, 322}, {33, 286}, {30, 257}, {27, 234}, {25, 214}, {23, 197}, {21, 183}, {19, 170}, {18, 159}, {17, 150}, {16, 141}, {15, 133}},
    {{0, 0}, {377, 2579}, {188, 1289}, {125, 859}, {94, 644}, {75, 515}, {62, 429}, {53, 367}, {47, 321}, {41, 285}, {37, 256}, {34, 233}, {31, 213}, {28, 196}, {26, 182}, {24, 170}, {23, 159}, {21, 149}, {20, 140}, {19, 133}},
    {{0, 0}, {452, 2567}, {226, 1283}, {150, 855}, {113, 641}, {90, 512}, {75, 427}, {64, 365}, {56, 319}, {50, 284}, {45, 255}, {40, 232}, {37, 212}, {34, 195}, {32, 181}, {29, 169}, {27, 158}, {26, 148}, {24, 140}, {23, 132}},
    {{0, 0}, {527, 2553}, {263, 1276}, {175, 850}, {131, 637}, {105, 510}, {87, 424}, {75, 363}, {65, 318}, {58, 282}, {52, 254}, {47, 230}, {43, 211}, {40, 194}, {37, 180}, {34, 168}, {32, 157}, {30, 148}, {28, 139}, {27, 131}},
    {{0, 0}, {601, 2537}, {300, 1268}, {200, 845}, {150, 633}, {120, 506}, {100, 422}, {85, 361}, {74, 316}, {66, 280}, {59, 252}, {54, 229}, {49, 209}, {45, 193}, {42, 179}, {39, 167}, {37, 156}, {34, 147}, {32, 138}, {31, 131}},
    {{0, 0}, {674, 2518}, {337, 1259}, {224, 839}, {168, 629}, {134, 503}, {112, 419}, {96, 358}, {84, 313}, {74, 278}, {67, 250}, {60, 227}, {55, 208}, {51, 192}, {47, 178}, {44, 166}, {41, 155}, {39, 146}, {36, 137}, {34, 130}},
    {{0, 0}, {747, 2497}, {373, 1248}, {249, 832}, {186, 624}, {149, 498}, {124, 415}, {106, 355}, {93, 311}, {82, 276}, {74, 248}, {67, 225}, {61, 206}, {57, 190}, {52, 176}, {49, 164}, {46, 154}, {43, 144}, {40, 136}, {38, 129}},
    {{0, 0}, {820, 2475}, {410, 1237}, {273, 824}, {204, 618}, {163, 494}, {136, 411}, {116, 352}, {102, 308}, {90, 273}, {81, 246}, {74, 223}, {67, 204}, {62, 188}, {58, 175}, {54, 163}, {50, 152}, {47, 143}, {44, 135}, {42, 127}},
    {{0, 0}, {891, 2450}, {445, 1224}, {297, 816}, {222, 612}, {178, 489}, {148, 407}, {127, 349}, {111, 305}, {98, 271}, {88, 243}, {80, 221}, {73, 202}, {68, 186}, {63, 173}, {58, 161}, {55, 151}, {51, 142}, {48, 133}, {46, 126}},
    {{0, 0}, {962, 2423}, {481, 1211}, {320, 807}, {240, 605}, {192, 484}, {160, 403}, {137, 345}, {119, 301}, {106, 268}, {95, 241}, {86, 218}, {79, 200}, {73, 184}, {68, 171}, {63, 159}, {59, 149}, {55, 140}, {52, 132}, {49, 125}},
    {{0, 0}, {1032, 2394}, {516, 1196}, {344, 797}, {257, 598}, {206, 478}, {171, 398}, {147, 341}, {128, 298}, {114, 264}, {102, 238}, {93, 216}, {85, 198}, {78, 182}, {73, 169}, {68, 157}, {63, 147}, {59, 138}, {56, 130}, {53, 123}},
    {{0, 0}, {1101, 2363}, {550, 1181}, {367, 787}, {275, 590}, {220, 472}, {183, 393}, {157, 336}, {137, 294}, {121, 261}, {109, 235}, {99, 213}, {91, 195}, {84, 180}, {77, 167}, {72, 155}, {67, 145}, {63, 136}, {60, 129}, {56, 122}},
    {{0, 0}, {1170, 2330}, {585, 1164}, {389, 776}, {292, 582}, {233, 465}, {194, 387}, {166, 332}, {145, 290}, {129, 257}, {116, 231}, {105, 210}, {96, 192}, {89, 177}, {82, 164}, {77, 153}, {72, 143}, {67, 135}, {63, 127}, {60, 120}},
    {{0, 0}, {1237, 2295}, {618, 1147}, {412, 764}, {309, 573}, {247, 458}, {205, 381}, {176, 327}, {154, 285}, {136, 253}, {123, 228}, {111, 207}, {102, 189}, {94, 175}, {87, 162}, {81, 151}, {76, 141}, {71, 133}, {67, 125}, {63, 118}},
    {{0, 0}, {1303, 2258}, {651, 1128}, {434, 752}, {325, 564}, {260, 451}, {216, 375}, {185, 321}, {162, 281}, {144, 249}, {129, 224}, {117, 204}, {107, 186}, {99, 172}, {92, 159}, {85, 148}, {80, 139}, {75, 130}, {71, 123}, {67, 116}},
    {{0, 0}, {1368, 2219}, {684, 1109}, {456, 739}, {341, 554}, {273, 443}, {227, 369}, {195, 316}, {170, 276}, {151, 245}, {136, 220}, {123, 200}, {113, 183}, {104, 169}, {96, 156}, {90, 146}, {84, 136}, {79, 128}, {74, 121}, {70, 114}},
    {{0, 0}, {1432, 2178}, {716, 1089}, {477, 725}, {357, 544}, {286, 435}, {238, 362}, {204, 310}, {178, 271}, {158, 241}, {142, 216}, {129, 196}, {118, 180}, {109, 166}, {101, 154}, {94, 143}, {88, 134}, {83, 126}, {78, 119}, {74, 112}},
    {{0, 0}, {1495, 2135}, {747, 1067}, {498, 711}, {373, 533}, {298, 426}, {248, 355}, {213, 304}, {186, 266}, {165, 236}, {148, 212}, {135, 193}, {123, 176}, {114, 162}, {105, 151}, {98, 140}, {92, 131}, {86, 123}, {81, 116}, {77, 110}},
    {{0, 0}, {1557, 2091}, {778, 1045}, {518, 696}, {388, 522}, {311, 417}, {259, 347}, {221, 298}, {194, 260}, {172, 231}, {154, 208}, {140, 188}, {128, 173}, {118, 159}, {110, 147}, {102, 137}, {96, 129}, {90, 121}, {85, 114}, {80, 108}},
    {{0, 0}, {1617, 2045}, {808, 1022}, {538, 681}, {404, 510}, {323, 408}, {269, 340}, {230, 291}, {201, 254}, {178, 226}, {160, 203}, {146, 184}, {133, 169}, {123, 156}, {114, 144}, {106, 134}, {99, 126}, {93, 118}, {88, 111}, {83, 105}},
    {{0, 0}, {1676, 1997}, {837, 998}, {558, 665}, {418, 498}, {334, 399}, {278, 332}, {238, 284}, {208, 248}, {185, 221}, {166, 198}, {151, 180}, {138, 165}, {127, 152}, {118, 141}, {110, 131}, {103, 123}, {97, 115}, {91, 109}, {86, 103}},
    {{0, 0}, {1733, 1947}, {866, 973}, {577, 649}, {433, 486}, {346, 389}, {288, 324}, {247, 277}, {215, 242}, {191, 215}, {172, 193}, {156, 176}, {143, 161}, {132, 148}, {122, 137}, {114, 128}, {106, 120}, {100, 112}, {94, 106}, {89, 100}},
    {{0, 0}, {1789, 1896}, {894, 948}, {596, 631}, {447, 473}, {357, 378}, {297, 315}, {255, 270}, {222, 236}, {198, 209}, {178, 188}, {161, 171}, {148, 156}, {136, 144}, {126, 134}, {117, 125}, {110, 117}, {103, 109}, {97, 103}, {92, 98}},
    {{0, 0}, {1843, 1843}, {921, 921}, {614, 614}, {460, 460}, {368, 368}, {306, 306}, {262, 262}, {229, 229}, {204, 204}, {183, 183}, {166, 166}, {152, 152}, {140, 140}, {130, 130}, {121, 121}, {113, 113}, {106, 106}, {100, 100}, {95, 95}},
    {{0, 0}, {1896, 1789}, {948, 894}, {631, 596}, {473, 447}, {378, 357}, {315, 297}, {270, 255}, {236, 222}, {209, 198}, {188, 178}, {171, 161}, {156, 148}, {144, 136}, {134, 126}, {125, 117}, {117, 110}, {109, 103}, {103, 97}, {98, 92}},
    {{0, 0}, {1947, 1733}, {973, 866}, {649, 577}, {486, 433}, {389, 346}, {324, 288}, {277, 247}, {242, 215}, {215, 191}, {193, 172}, {176, 156}, {161, 143}, {148, 132}, {137, 122}, {128, 114}, {120, 106}, {112, 100}, {106, 94}, {100, 89}},
    {{0, 0}, {1997, 1676}, {998, 837}, {665, 558}, {498, 418}, {399, 334}, {332, 278}, {284, 238}, {248, 208}, {221, 185}, {198, 166}, {180, 151}, {165, 138}, {152, 127}, {141, 118}, {131, 110}, {123, 103}, {115, 97}, {109, 91}, {103, 86}},
    {{0, 0}, {2045, 1617}, {1022, 808}, {681, 538}, {510, 404}, {408, 323}, {340, 269}, {291, 230}, {254, 201}, {226, 178}, {203, 160}, {184, 146}, {169, 133}, {156, 123}, {144, 114}, {134, 106}, {126, 99}, {118, 93}, {111, 88}, {105, 83}},
    {{0, 0}, {2091, 1557}, {1045, 778}, {696, 518}, {522, 388}, {417, 311}, {347, 259}, {298, 221}, {260, 194}, {231, 172}, {208, 154}, {188, 140}, {173, 128}, {159, 118}, {147, 110}, {137, 102}, {129, 96}, {121, 90}, {114, 85}, {108, 80}},
    {{0, 0}, {2135, 1495}, {1067, 747}, {711, 498}, {533, 373}, {426, 298}, {355, 248}, {304, 213}, {266, 186}, {236, 165}, {212, 148}, {193, 135}, {176, 123}, {162, 114}, {151, 105}, {140, 98}, {131, 92}, {123, 86}, {116, 81}, {110, 77}},
    {{0, 0}, {2178, 1432}, {1089, 716}, {725, 477}, {544, 357}, {435, 286}, {362, 238}, {310, 204}, {271, 178}, {241, 158}, {216, 142}, {196, 129}, {180, 118}, {166, 109}, {154, 101}, {143, 94}, {134, 88}, {126, 83}, {119, 78}, {112, 74}},
    {{0, 0}, {2219, 1368}, {1109, 684}, {739, 456}, {554, 341}, {443, 273}, {369, 227}, {316, 195}, {276, 170}, {245, 151}, {220, 136}, {200, 123}, {183, 113}, {169, 104}, {156, 96}, {146, 90}, {136, 84}, {128, 79}, {121, 74}, {114, 70}},
    {{0, 0}, {2258, 1303}, {1128, 651}, {752, 434}, {564, 325}, {451, 260}, {375, 216}, {321, 185}, {281, 162}, {249, 144}, {224, 129}, {204, 117}, {186, 107}, {172, 99}, {159, 92}, {148, 85}, {139, 80}, {130, 75}, {123, 71}, {116, 67}},
    {{0, 0}, {2295, 1237}, {1147, 618}, {764, 412}, {573, 309}, {458, 247}, {381, 205}, {327, 176}, {285, 154}, {253, 136}, {228, 123}, {207, 111}, {189, 102}, {175, 94}, {162, 87}, {151, 81}, {141, 76}, {133, 71}, {125, 67}, {118, 63}},
    {{0, 0}, {2330, 1170}, {1164, 585}, {776, 389}, {582, 292}, {465, 233}, {387, 194}, {332, 166}, {290, 145}, {257, 129}, {231, 116}, {210, 105}, {192, 96}, {177, 89}, {164, 82}, {153, 77}, {143, 72}, {135, 67}, {127, 63}, {120, 60}},
    {{0, 0}, {2363, 1101}, {1181, 550}, {787, 367}, {590, 275}, {472, 220}, {393, 183}, {336, 157}, {294, 137}, {261, 121}, {235, 109}, {213, 99}, {195, 91}, {180, 84}, {167, 77}, {155, 72}, {145, 67}, {136, 63}, {129, 60}, {122, 56}},
    {{0, 0}, {2394, 1032}, {1196, 516}, {797, 344}, {598, 257}, {478, 206}, {398, 171}, {341, 147}, {298, 128}, {264, 114}, {238, 102}, {216, 93}, {198, 85}, {182, 78}, {169, 73}, {157, 68}, {147, 63}, {138, 59}, {130, 56}, {123, 53}},
    {{0, 0}, {2423, 962}, {1211, 481}, {807, 320}, {605, 240}, {484, 192}, {403, 160}, {345, 137}, {301, 119}, {268, 106}, {241, 95}, {218, 86}, {200, 79}, {184, 73}, {171, 68}, {159, 63}, {149, 59}, {140, 55}, {132, 52}, {125, 49}},
    {{0, 0}, {2450, 891}, {1224, 445}, {816, 297}, {612, 222}, {489, 178}, {407, 148}, {349, 127}, {305, 111}, {271, 98}, {243, 88}, {221, 80}, {202, 73}, {186, 68}, {173, 63}, {161, 58}, {151, 55}, {142, 51}, {133, 48}, {126, 46}},
    {{0, 0}, {2475, 820}, {1237, 410}, {824, 273}, {618, 204}, {494, 163}, {411, 136}, {352, 116}, {308, 102}, {273, 90}, {246, 81}, {223, 74}, {204, 67}, {188, 62}, {175, 58}, {163, 54}, {152, 50}, {143, 47}, {135, 44}, {127, 42}},
    {{0, 0}, {2497, 747}, {1248, 373}, {832, 249}, {624, 186}, {498, 149}, {415, 124}, {355, 106}, {311, 93}, {276, 82}, {248, 74}, {225, 67}, {206, 61}, {190, 57}, {176, 52}, {164, 49}, {154, 46}, {144, 43}, {136, 40}, {129, 38}},
    {{0, 0}, {2518, 674}, {1259, 337}, {839, 224}, {629, 168}, {503, 134}, {419, 112}, {358, 96}, {313, 84}, {278, 74}, {250, 67}, {227, 60}, {208, 55}, {192, 51}, {178, 47}, {166, 44}, {155, 41}, {146, 39}, {137, 36}, {130, 34}},
    {{0, 0}, {2537, 601}, {1268, 300}, {845, 200}, {633, 150}, {506, 120}, {422, 100}, {361, 85}, {316, 74}, {280, 66}, {252, 59}, {229, 54}, {209, 49}, {193, 45}, {179, 42}, {167, 39}, {156, 37}, {147, 34}, {138, 32}, {131, 31}},
    {{0, 0}, {2553, 527}, {1276, 263}, {850, 175}, {637, 131}, {510, 105}, {424, 87}, {363, 75}, {318, 65}, {282, 58}, {254, 52}, {230, 47}, {211, 43}, {194, 40}, {180, 37}, {168, 34}, {157, 32}, {148, 30}, {139, 28}, {131, 27}},
    {{0, 0}, {2567, 452}, {1283, 226}, {855, 150}, {641, 113}, {512, 90}, {427, 75}, {365, 64}, {319, 56}, {284, 50}, {255, 45}, {232, 40}, {212, 37}, {195, 34}, {181, 32}, {169, 29}, {158, 27}, {148, 26}, {140, 24}, {132, 23}},
    {{0, 0}, {2579, 377}, {1289, 188}, {859, 125}, {644, 94}, {515, 75}, {429, 62}, {367, 53}, {321, 47}, {285, 41}, {256, 37}, {233, 34}, {213, 31}, {196, 28}, {182, 26}, {170, 24}, {159, 23}, {149, 21}, {140, 20}, {133, 19}},
    {{0, 0}, {2589, 302}, {1294, 151}, {862, 100}, {646, 75}, {517, 60}, {430, 50}, {369, 43}, {322, 37}, {286, 33}, {257, 30}, {234, 27}, {214, 25}, {197, 23}, {183, 21}, {170, 19}, {159, 18}, {150, 17}, {141, 16}, {133, 15}},
    {{0, 0}, {2597, 227}, {1298, 113}, {865, 75}, {648, 56}, {518, 45}, {432, 37}, {370, 32}, {323, 28}, {287, 25}, {258, 22}, {234, 20}, {214, 18}, {198, 17}, {183, 16}, {171, 14}, {160, 14}, {150, 13}, {141, 12}, {134, 11}},
    {{0, 0}, {2603, 151}, {1301, 75}, {867, 50}, {650, 37}, {519, 30}, {433, 25}, {370, 21}, {324, 18}, {288, 16}, {259, 15}, {235, 13}, {215, 12}, {198, 11}, {184, 10}, {171, 9}, {160, 9}, {150, 8}, {142, 8}, {134, 7}},
    {{0, 0}, {2606, 75}, {1302, 37}, {868, 25}, {651, 18}, {520, 15}, {433, 12}, {371, 10}, {324, 9}, {288, 8}, {259, 7}, {235, 6}, {215, 6}, {198, 5}, {184, 5}, {171, 4}, {160, 4}, {151, 4}, {142, 4}, {134, 3}}
};

const byte angles8[angleWidth][eightBitHeight][2] = {
    {{0, 127}, {0, 121}, {0, 115}, {0, 110}, {0, 105}, {0, 101}, {0, 96}, {0, 93}, {0, 89}, {0, 86}, {0, 82}, {0, 80}},
    {{3, 127}, {3, 121}, {3, 115}, {3, 110}, {3, 105}, {2, 100}, {2, 96}, {2, 92}, {2, 89}, {2, 86}, {2, 82}, {2, 79}},
    {{7, 127}, {7, 121}, {6, 115}, {6, 110}, {6, 105}, {5, 100}, {5, 96}, {5, 92}, {5, 89}, {5, 85}, {4, 82}, {4, 79}},
    {{11, 127}, {10, 120}, {10, 115}, {9, 109}, {9, 105}, {8, 100}, {8, 96}, {8, 92}, {7, 89}, {7, 85}, {7, 82}, {6, 79}},
    {{14, 126}, {14, 120}, {13, 114}, {12, 109}, {12, 104}, {11, 100}, {11, 96}, {10, 92}, {10, 88}, {9, 85}, {9, 82}, {9, 79}},
    {{18, 126}, {17, 120}, {16, 114}, {15, 109}, {15, 104}, {14, 99}, {14, 95}, {13, 92}, {12, 88}, {12, 85}, {12, 82}, {11, 79}},
    {{22, 125}, {21, 119}, {20, 113}, {19, 108}, {18, 103}, {17, 99}, {16, 95}, {16, 91}, {15, 88}, {14, 84}, {14, 81}, {13, 78}},
    {{25, 125}, {24, 118}, {23, 113}, {22, 108}, {21, 103}, {20, 98}, {19, 94}, {18, 91}, {18, 87}, {17, 84}, {16, 81}, {16, 78}},
    {{29, 124}, {27, 118}, {26, 112}, {25, 107}, {24, 102}, {23, 98}, {22, 94}, {21, 90}, {20, 87}, {19, 83}, {19, 80}, {18, 77}},
    {{33, 123}, {31, 117}, {29, 111}, {28, 106}, {27, 101}, {26, 97}, {25, 93}, {24, 89}, {23, 86}, {22, 83}, {21, 80}, {20, 77}},
    {{36, 122}, {34, 116}, {33, 110}, {31, 105}, {30, 101}, {28, 96}, {27, 92}, {26, 89}, {25, 85}, {24, 82}, {23, 79}, {22, 76}},
    {{40, 121}, {38, 115}, {36, 109}, {34, 104}, {33, 100}, {31, 95}, {30, 91}, {29, 88}, {28, 84}, {27, 81}, {26, 78}, {25, 75}},
    {{43, 120}, {41, 114}, {39, 108}, {37, 103}, {36, 99}, {34, 94}, {33, 91}, {31, 87}, {30, 84}, {29, 80}, {28, 77}, {27, 75}},
    {{47, 118}, {44, 112}, {42, 107}, {40, 102}, {38, 98}, {37, 93}, {35, 90}, {34, 86}, {33, 83}, {31, 80}, {30, 77}, {29, 74}},
    {{50, 117}, {48, 111}, {45, 106}, {43, 101}, {41, 96}, {40, 92}, {38, 88}, {36, 85}, {35, 82}, {34, 79}, {32, 76}, {31, 73}},
    {{53, 115}, {51, 110}, {48, 104}, {46, 100}, {44, 95}, {42, 91}, {40, 87}, {39, 84}, {37, 81}, {36, 78}, {35, 75}, {33, 72}},
    {{57, 114}, {54, 108}, {51, 103}, {49, 98}, {47, 94}, {45, 90}, {43, 86}, {41, 83}, {40, 79}, {38, 76}, {37, 74}, {35, 71}},
    {{60, 112}, {57, 106}, {54, 101}, {52, 97}, {50, 92}, {47, 88}, {45, 85}, {44, 81}, {42, 78}, {40, 75}, {39, 73}, {37, 70}},
    {{63, 110}, {60, 105}, {57, 100}, {55, 95}, {52, 91}, {50, 87}, {48, 83}, {46, 80}, {44, 77}, {43, 74}, {41, 71}, {40, 69}},
    {{67, 108}, {63, 103}, {60, 98}, {57, 93}, {55, 89}, {53, 85}, {50, 82}, {48, 79}, {46, 76}, {45, 73}, {43, 70}, {42, 68}},
    {{70, 106}, {66, 101}, {63, 96}, {60, 92}, {57, 88}, {55, 84}, {53, 80}, {51, 77}, {49, 74}, {47, 71}, {45, 69}, {43, 66}},
    {{73, 104}, {69, 99}, {66, 94}, {63, 90}, {60, 86}, {57, 82}, {55, 79}, {53, 76}, {51, 73}, {49, 70}, {47, 67}, {45, 65}},
    {{76, 102}, {72, 97}, {69, 92}, {65, 88}, {62, 84}, {60, 81}, {57, 77}, {55, 74}, {53, 71}, {51, 69}, {49, 66}, {47, 64}},
    {{79, 100}, {75, 95}, {71, 90}, {68, 86}, {65, 82}, {62, 79}, {60, 75}, {57, 72}, {55, 70}, {53, 67}, {51, 65}, {49, 62}},
    {{82, 97}, {78, 93}, {74, 88}, {70, 84}, {67, 80}, {64, 77}, {62, 74}, {59, 71}, {57, 68}, {55, 65}, {53, 63}, {51, 61}},
    {{84, 95}, {80, 90}, {76, 86}, {73, 82}, {70, 78}, {67, 75}, {64, 72}, {61, 69}, {59, 66}, {57, 64}, {55, 61}, {53, 59}},
    {{87, 92}, {83, 88}, {79, 84}, {75, 80}, {72, 76}, {69, 73}, {66, 70}, {63, 67}, {61, 65}, {59, 62}, {56, 60}, {54, 58}},
    {{90, 90}, {85, 85}, {81, 81}, {78, 78}, {74, 74}, {71, 71}, {68, 68}, {65, 65}, {63, 63}, {60, 60}, {58, 58}, {56, 56}},
    {{92, 87}, {88, 83}, {84, 79}, {80, 75}, {76, 72}, {73, 69}, {70, 66}, {67, 63}, {65, 61}, {62, 59}, {60, 56}, {58, 54}},
    {{95, 84}, {90, 80}, {86, 76}, {82, 73}, {78, 70}, {75, 67}, {72, 64}, {69, 61}, {66, 59}, {64, 57}, {61, 55}, {59, 53}},
    {{97, 82}, {93, 78}, {88, 74}, {84, 70}, {80, 67}, {77, 64}, {74, 62}, {71, 59}, {68, 57}, {65, 55}, {63, 53}, {61, 51}},
    {{100, 79}, {95, 75}, {90, 71}, {86, 68}, {82, 65}, {79, 62}, {75, 60}, {72, 57}, {70, 55}, {67, 53}, {65, 51}, {62, 49}},
    {{102, 76}, {97, 72}, {92, 69}, {88, 65}, {84, 62}, {81, 60}, {77, 57}, {74, 55}, {71, 53}, {69, 51}, {66, 49}, {64, 47}},
    {{104, 73}, {99, 69}, {94, 66}, {90, 63}, {86, 60}, {82, 57}, {79, 55}, {76, 53}, {73, 51}, {70, 49}, {67, 47}, {65, 45}},
    {{106, 70}, {101, 66}, {96, 63}, {92, 60}, {88, 57}, {84, 55}, {80, 53}, {77, 51}, {74, 49}, {71, 47}, {69, 45}, {66, 43}},
    {{108, 67}, {103, 63}, {98, 60}, {93, 57}, {89, 55}, {85, 53}, {82, 50}, {79, 48}, {76, 46}, {73, 45}, {70, 43}, {68, 42}},
    {{110, 63}, {105, 60}, {100, 57}, {95, 55}, {91, 52}, {87, 50}, {83, 48}, {80, 46}, {77, 44}, {74, 43}, {71, 41}, {69, 40}},
    {{112, 60}, {106, 57}, {101, 54}, {97, 52}, {92, 50}, {88, 47}, {85, 45}, {81, 44}, {78, 42}, {75, 40}, {73, 39}, {70, 37}},
    {{114, 57}, {108, 54}, {103, 51}, {98, 49}, {94, 47}, {90, 45}, {86, 43}, {83, 41}, {79, 40}, {76, 38}, {74, 37}, {71, 35}},
    {{115, 53}, {110, 51}, {104, 48}, {100, 46}, {95, 44}, {91, 42}, {87, 40}, {84, 39}, {81, 37}, {78, 36}, {75, 35}, {72, 33}},
    {{117, 50}, {111, 48}, {106, 45}, {101, 43}, {96, 41}, {92, 40}, {88, 38}, {85, 36}, {82, 35}, {79, 34}, {76, 32}, {73, 31}},
    {{118, 47}, {112, 44}, {107, 42}, {102, 40}, {98, 38}, {93, 37}, {90, 35}, {86, 34}, {83, 33}, {80, 31}, {77, 30}, {74, 29}},
    {{120, 43}, {114, 41}, {108, 39}, {103, 37}, {99, 36}, {94, 34}, {91, 33}, {87, 31}, {84, 30}, {80, 29}, {77, 28}, {75, 27}},
    {{121, 40}, {115, 38}, {109, 36}, {104, 34}, {100, 33}, {95, 31}, {91, 30}, {88, 29}, {84, 28}, {81, 27}, {78, 26}, {75, 25}},
    {{122, 36}, {116, 34}, {110, 33}, {105, 31}, {101, 30}, {96, 28}, {92, 27}, {89, 26}, {85, 25}, {82, 24}, {79, 23}, {76, 22}},
    {{123, 33}, {117, 31}, {111, 29}, {106, 28}, {101, 27}, {97, 26}, {93, 25}, {89, 24}, {86, 23}, {83, 22}, {80, 21}, {77, 20}},
    {{124, 29}, {118, 27}, {112, 26}, {107, 25}, {102, 24}, {98, 23}, {94, 22}, {90, 21}, {87, 20}, {83, 19}, {80, 19}, {77, 18}},
    {{125, 25}, {118, 24}, {113, 23}, {108, 22}, {103, 21}, {98, 20}, {94, 19}, {91, 18}, {87, 18}, {84, 17}, {81, 16}, {78, 16}},
    {{125, 22}, {119, 21}, {113, 20}, {108, 19}, {103, 18}, {99, 17}, {95, 16}, {91, 16}, {88, 15}, {84, 14}, {81, 14}, {78, 13}},
    {{126, 18}, {120, 17}, {114, 16}, {109, 15}, {104, 15}, {99, 14}, {95, 14}, {92, 13}, {88, 12}, {85, 12}, {82, 12}, {79, 11}},
    {{126, 14}, {120, 14}, {114, 13}, {109, 12}, {104, 12}, {100, 11}, {96, 11}, {92, 10}, {88, 10}, {85, 9}, {82, 9}, {79, 9}},
    {{127, 11}, {120, 10}, {115, 10}, {109, 9}, {105, 9}, {100, 8}, {96, 8}, {92, 8}, {89, 7}, {85, 7}, {82, 7}, {79, 6}},
    {{127, 7}, {121, 7}, {115, 6}, {110, 6}, {105, 6}, {100, 5}, {96, 5}, {92, 5}, {89, 5}, {85, 5}, {82, 4}, {79, 4}},
    {{127, 3}, {121, 3}, {115, 3}, {110, 3}, {105, 3}, {100, 2}, {96, 2}, {92, 2}, {89, 2}, {86, 2}, {82, 2}, {79, 2}}
};

bool samplePixel(short xPos, short yPos) {
    return (((xPos / precision) + ((yPos + (o * 4)) / precision)) % 2);
}

bool getScreenPixel(byte x, byte y) {
    // Used to indicate framerate
    /* if (x == 0 && y == 0) {
        return o == 0;
    } */

    x /= 2;

    // Temporary for small screen sizes
    if (y >= height) return false;
    if (x >= width) return false;
    
    if (y < horizon) return false;

    // If both samples are 0 in the Python, the horizon colour is set but that doesn't seem to be needed

    if ((y - horizon) < sixteenBitHeight) {
        unsigned short index = x + o;
        index = index % (angleWidth * 4);
        unsigned short element = index % angleWidth;

        if (index < angleWidth) {
            return samplePixel(
                angles16[element][y - horizon][0],
                angles16[element][y - horizon][1]
            );
        } else if (index < angleWidth * 2) {
            // Return 90 degree rotated position
            return samplePixel(
                angles16[element][y - horizon][1],
                -angles16[element][y - horizon][0]
            );
        } else if (index < angleWidth * 3) {
            // Return 180 degree rotated position
            return samplePixel(
                -angles16[element][y - horizon][0],
                -angles16[element][y - horizon][1]
            );
        } else if (index < angleWidth * 4) {
            // Return 270 degree rotated position
            return samplePixel(
                -angles16[element][y - horizon][1],
                angles16[element][y - horizon][0]
            );
        }
        
    } else {
        // TODO: no duplicated code?

        unsigned short index = x + o;
        index = index % (angleWidth * 4);
        unsigned short element = index % angleWidth;

        if (index < angleWidth) {
            return samplePixel(
                angles8[element][y - horizon - sixteenBitHeight][0],
                angles8[element][y - horizon - sixteenBitHeight][1]
            );
        } else if (index < angleWidth * 2) {
            // Return 90 degree rotated position
            return samplePixel(
                angles8[element][y - horizon - sixteenBitHeight][1],
                -angles8[element][y - horizon - sixteenBitHeight][0]
            );
        } else if (index < angleWidth * 3) {
            // Return 180 degree rotated position
            return samplePixel(
                -angles8[element][y - horizon - sixteenBitHeight][0],
                -angles8[element][y - horizon - sixteenBitHeight][1]
            );
        } else if (index < angleWidth * 4) {
            // Return 270 degree rotated position
            return samplePixel(
                -angles8[element][y - horizon - sixteenBitHeight][1],
                angles8[element][y - horizon - sixteenBitHeight][0]
            );
        }
    }
}

byte getScreenByte(byte x, byte y) {
    byte result = 0;
    for (byte ox = 0; ox < 8; ox++) {
        if (getScreenPixel(x + ox, y)) {
            result = result | (1 << (7 - ox));
        }
    }
    return result;
}

int main()
{
    CEnable15MHz();
    CRunIndicatorOff();

    CDispStr("Hello world from C!!! (press a key)");
    CNewLine();

    // Wait for input
    CGetKey();

    CDispStr("test");
    CNewLine();

    // Maybe we can draw to the screen?

    while (true) {
        byte *bytePointer = plotSScreen;

        for (byte y = 0; y < /*64 */ height; y++) {
            for (byte x = 0; x < 96; x += 8) {
                // if (x < (width + 8))
                    *bytePointer = getScreenByte(x, y);
                bytePointer++;
            }
        }

        FastCopy();

        byte key = 10; // CGetKey();
        if (key == 0) break;
        if (key == 2) {
            // Left arrow
            o--;
        } else {
            o++;
        }
    }

    CClrLCDFull();

    CRunIndicatorOn();
    /* The OS seems to do this anyways, but it's good to be safe */
    CDisable15MHz();

    return 0;
}
