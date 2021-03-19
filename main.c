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

unsigned char o = 0;

// Data that should be auto-generated in the future
#define width 32
#define height 21

#define horizon 11

// height - horizon
// Calculate maybe?
#define realHeight 10

#define precision 32

// Will probably be SLOW on a Z80 (signed 16-bit integers), but ¯\_(ツ)_/¯
short angles[][realHeight][2] = {
  {{0, 1711}, {0, 569}, {0, 341}, {0, 243}, {0, 188}, {0, 153}, {0, 129}, {0, 111}, {0, 97}, {0, 86}},
  {{74, 1709}, {24, 569}, {14, 340}, {10, 242}, {8, 188}, {6, 153}, {5, 128}, {4, 110}, {4, 97}, {3, 86}},
  {{149, 1704}, {49, 567}, {29, 339}, {21, 242}, {16, 187}, {13, 152}, {11, 128}, {9, 110}, {8, 96}, {7, 85}},
  {{223, 1696}, {74, 564}, {44, 338}, {31, 240}, {24, 186}, {20, 152}, {16, 127}, {14, 110}, {12, 96}, {11, 85}},
  {{297, 1685}, {98, 561}, {59, 336}, {42, 239}, {32, 185}, {26, 151}, {22, 127}, {19, 109}, {16, 95}, {14, 84}},
  {{370, 1670}, {123, 556}, {73, 333}, {52, 237}, {40, 183}, {33, 149}, {27, 125}, {24, 108}, {21, 94}, {18, 84}},
  {{442, 1652}, {147, 550}, {88, 329}, {62, 234}, {48, 181}, {39, 148}, {33, 124}, {28, 107}, {25, 93}, {22, 83}},
  {{514, 1631}, {171, 543}, {102, 325}, {73, 231}, {56, 179}, {46, 146}, {38, 123}, {33, 105}, {29, 92}, {25, 82}},
  {{585, 1607}, {194, 535}, {116, 320}, {83, 228}, {64, 176}, {52, 144}, {44, 121}, {37, 104}, {33, 91}, {29, 81}},
  {{654, 1580}, {218, 526}, {130, 315}, {93, 224}, {72, 174}, {58, 141}, {49, 119}, {42, 102}, {37, 89}, {33, 79}},
  {{723, 1550}, {240, 516}, {144, 309}, {102, 220}, {79, 170}, {64, 138}, {54, 116}, {46, 100}, {41, 88}, {36, 78}},
  {{790, 1517}, {263, 505}, {157, 302}, {112, 215}, {86, 167}, {70, 136}, {59, 114}, {51, 98}, {44, 86}, {39, 76}},
  {{855, 1481}, {284, 493}, {170, 295}, {121, 210}, {94, 163}, {76, 132}, {64, 111}, {55, 96}, {48, 84}, {43, 74}},
  {{919, 1443}, {306, 480}, {183, 287}, {130, 204}, {101, 158}, {82, 129}, {69, 108}, {59, 93}, {52, 82}, {46, 72}},
  {{981, 1401}, {326, 466}, {195, 279}, {139, 199}, {108, 154}, {87, 125}, {74, 105}, {63, 90}, {55, 79}, {49, 70}},
  {{1041, 1357}, {346, 452}, {207, 270}, {147, 192}, {114, 149}, {93, 121}, {78, 102}, {67, 88}, {59, 77}, {52, 68}},
  {{1099, 1310}, {366, 436}, {219, 261}, {156, 186}, {121, 144}, {98, 117}, {82, 98}, {71, 85}, {62, 74}, {55, 66}},
  {{1155, 1261}, {384, 420}, {230, 251}, {164, 179}, {127, 138}, {103, 113}, {87, 95}, {75, 81}, {65, 71}, {58, 63}},
  {{1209, 1209}, {402, 402}, {241, 241}, {171, 171}, {133, 133}, {108, 108}, {91, 91}, {78, 78}, {68, 68}, {60, 60}},
  {{1261, 1155}, {420, 384}, {251, 230}, {179, 164}, {138, 127}, {113, 103}, {95, 87}, {81, 75}, {71, 65}, {63, 58}},
  {{1310, 1099}, {436, 366}, {261, 219}, {186, 156}, {144, 121}, {117, 98}, {98, 82}, {85, 71}, {74, 62}, {66, 55}},
  {{1357, 1041}, {452, 346}, {270, 207}, {192, 147}, {149, 114}, {121, 93}, {102, 78}, {88, 67}, {77, 59}, {68, 52}},
  {{1401, 981}, {466, 326}, {279, 195}, {199, 139}, {154, 108}, {125, 87}, {105, 74}, {90, 63}, {79, 55}, {70, 49}},
  {{1443, 919}, {480, 306}, {287, 183}, {204, 130}, {158, 101}, {129, 82}, {108, 69}, {93, 59}, {82, 52}, {72, 46}},
  {{1481, 855}, {493, 284}, {295, 170}, {210, 121}, {163, 94}, {132, 76}, {111, 64}, {96, 55}, {84, 48}, {74, 43}},
  {{1517, 790}, {505, 263}, {302, 157}, {215, 112}, {167, 86}, {136, 70}, {114, 59}, {98, 51}, {86, 44}, {76, 39}},
  {{1550, 723}, {516, 240}, {309, 144}, {220, 102}, {170, 79}, {138, 64}, {116, 54}, {100, 46}, {88, 41}, {78, 36}},
  {{1580, 654}, {526, 218}, {315, 130}, {224, 93}, {174, 72}, {141, 58}, {119, 49}, {102, 42}, {89, 37}, {79, 33}},
  {{1607, 585}, {535, 194}, {320, 116}, {228, 83}, {176, 64}, {144, 52}, {121, 44}, {104, 37}, {91, 33}, {81, 29}},
  {{1631, 514}, {543, 171}, {325, 102}, {231, 73}, {179, 56}, {146, 46}, {123, 38}, {105, 33}, {92, 29}, {82, 25}},
  {{1652, 442}, {550, 147}, {329, 88}, {234, 62}, {181, 48}, {148, 39}, {124, 33}, {107, 28}, {93, 25}, {83, 22}},
  {{1670, 370}, {556, 123}, {333, 73}, {237, 52}, {183, 40}, {149, 33}, {125, 27}, {108, 24}, {94, 21}, {84, 18}},
  {{1685, 297}, {561, 98}, {336, 59}, {239, 42}, {185, 32}, {151, 26}, {127, 22}, {109, 19}, {95, 16}, {84, 14}},
  {{1696, 223}, {564, 74}, {338, 44}, {240, 31}, {186, 24}, {152, 20}, {127, 16}, {110, 14}, {96, 12}, {85, 11}},
  {{1704, 149}, {567, 49}, {339, 29}, {242, 21}, {187, 16}, {152, 13}, {128, 11}, {110, 9}, {96, 8}, {85, 7}},
  {{1709, 74}, {569, 24}, {340, 14}, {242, 10}, {188, 8}, {153, 6}, {128, 5}, {110, 4}, {97, 4}, {86, 3}},
  {{1711, 0}, {569, 0}, {341, 0}, {243, 0}, {188, 0}, {153, 0}, {129, 0}, {111, 0}, {97, 0}, {86, 0}},
  {{1709, -74}, {569, -24}, {340, -14}, {242, -10}, {188, -8}, {153, -6}, {128, -5}, {110, -4}, {97, -4}, {86, -3}},
  {{1704, -149}, {567, -49}, {339, -29}, {242, -21}, {187, -16}, {152, -13}, {128, -11}, {110, -9}, {96, -8}, {85, -7}},
  {{1696, -223}, {564, -74}, {338, -44}, {240, -31}, {186, -24}, {152, -20}, {127, -16}, {110, -14}, {96, -12}, {85, -11}},
  {{1685, -297}, {561, -98}, {336, -59}, {239, -42}, {185, -32}, {151, -26}, {127, -22}, {109, -19}, {95, -16}, {84, -14}},
  {{1670, -370}, {556, -123}, {333, -73}, {237, -52}, {183, -40}, {149, -33}, {125, -27}, {108, -24}, {94, -21}, {84, -18}},
  {{1652, -442}, {550, -147}, {329, -88}, {234, -62}, {181, -48}, {148, -39}, {124, -33}, {107, -28}, {93, -25}, {83, -22}},
  {{1631, -514}, {543, -171}, {325, -102}, {231, -73}, {179, -56}, {146, -46}, {123, -38}, {105, -33}, {92, -29}, {82, -25}},
  {{1607, -585}, {535, -194}, {320, -116}, {228, -83}, {176, -64}, {144, -52}, {121, -44}, {104, -37}, {91, -33}, {81, -29}},
  {{1580, -654}, {526, -218}, {315, -130}, {224, -93}, {174, -72}, {141, -58}, {119, -49}, {102, -42}, {89, -37}, {79, -33}},
  {{1550, -723}, {516, -240}, {309, -144}, {220, -102}, {170, -79}, {138, -64}, {116, -54}, {100, -46}, {88, -41}, {78, -36}},
  {{1517, -790}, {505, -263}, {302, -157}, {215, -112}, {167, -86}, {136, -70}, {114, -59}, {98, -51}, {86, -44}, {76, -39}},
  {{1481, -855}, {493, -284}, {295, -170}, {210, -121}, {163, -94}, {132, -76}, {111, -64}, {96, -55}, {84, -48}, {74, -43}},
  {{1443, -919}, {480, -306}, {287, -183}, {204, -130}, {158, -101}, {129, -82}, {108, -69}, {93, -59}, {82, -52}, {72, -46}},
  {{1401, -981}, {466, -326}, {279, -195}, {199, -139}, {154, -108}, {125, -87}, {105, -74}, {90, -63}, {79, -55}, {70, -49}},
  {{1357, -1041}, {452, -346}, {270, -207}, {192, -147}, {149, -114}, {121, -93}, {102, -78}, {88, -67}, {77, -59}, {68, -52}},
  {{1310, -1099}, {436, -366}, {261, -219}, {186, -156}, {144, -121}, {117, -98}, {98, -82}, {85, -71}, {74, -62}, {66, -55}},
  {{1261, -1155}, {420, -384}, {251, -230}, {179, -164}, {138, -127}, {113, -103}, {95, -87}, {81, -75}, {71, -65}, {63, -58}},
  {{1209, -1209}, {402, -402}, {241, -241}, {171, -171}, {133, -133}, {108, -108}, {91, -91}, {78, -78}, {68, -68}, {60, -60}},
  {{1155, -1261}, {384, -420}, {230, -251}, {164, -179}, {127, -138}, {103, -113}, {87, -95}, {75, -81}, {65, -71}, {58, -63}},
  {{1099, -1310}, {366, -436}, {219, -261}, {156, -186}, {121, -144}, {98, -117}, {82, -98}, {71, -85}, {62, -74}, {55, -66}},
  {{1041, -1357}, {346, -452}, {207, -270}, {147, -192}, {114, -149}, {93, -121}, {78, -102}, {67, -88}, {59, -77}, {52, -68}},
  {{981, -1401}, {326, -466}, {195, -279}, {139, -199}, {108, -154}, {87, -125}, {74, -105}, {63, -90}, {55, -79}, {49, -70}},
  {{919, -1443}, {306, -480}, {183, -287}, {130, -204}, {101, -158}, {82, -129}, {69, -108}, {59, -93}, {52, -82}, {46, -72}},
  {{855, -1481}, {284, -493}, {170, -295}, {121, -210}, {94, -163}, {76, -132}, {64, -111}, {55, -96}, {48, -84}, {43, -74}},
  {{790, -1517}, {263, -505}, {157, -302}, {112, -215}, {86, -167}, {70, -136}, {59, -114}, {51, -98}, {44, -86}, {39, -76}},
  {{723, -1550}, {240, -516}, {144, -309}, {102, -220}, {79, -170}, {64, -138}, {54, -116}, {46, -100}, {41, -88}, {36, -78}},
  {{654, -1580}, {218, -526}, {130, -315}, {93, -224}, {72, -174}, {58, -141}, {49, -119}, {42, -102}, {37, -89}, {33, -79}},
  {{585, -1607}, {194, -535}, {116, -320}, {83, -228}, {64, -176}, {52, -144}, {44, -121}, {37, -104}, {33, -91}, {29, -81}},
  {{514, -1631}, {171, -543}, {102, -325}, {73, -231}, {56, -179}, {46, -146}, {38, -123}, {33, -105}, {29, -92}, {25, -82}},
  {{442, -1652}, {147, -550}, {88, -329}, {62, -234}, {48, -181}, {39, -148}, {33, -124}, {28, -107}, {25, -93}, {22, -83}},
  {{370, -1670}, {123, -556}, {73, -333}, {52, -237}, {40, -183}, {33, -149}, {27, -125}, {24, -108}, {21, -94}, {18, -84}},
  {{297, -1685}, {98, -561}, {59, -336}, {42, -239}, {32, -185}, {26, -151}, {22, -127}, {19, -109}, {16, -95}, {14, -84}},
  {{223, -1696}, {74, -564}, {44, -338}, {31, -240}, {24, -186}, {20, -152}, {16, -127}, {14, -110}, {12, -96}, {11, -85}},
  {{149, -1704}, {49, -567}, {29, -339}, {21, -242}, {16, -187}, {13, -152}, {11, -128}, {9, -110}, {8, -96}, {7, -85}},
  /* {{74, -1709}, {24, -569}, {14, -340}, {10, -242}, {8, -188}, {6, -153}, {5, -128}, {4, -110}, {4, -97}, {3, -86}},
  {{0, -1711}, {0, -569}, {0, -341}, {0, -243}, {0, -188}, {0, -153}, {0, -129}, {0, -111}, {0, -97}, {0, -86}},
  {{-74, -1709}, {-24, -569}, {-14, -340}, {-10, -242}, {-8, -188}, {-6, -153}, {-5, -128}, {-4, -110}, {-4, -97}, {-3, -86}},
  {{-149, -1704}, {-49, -567}, {-29, -339}, {-21, -242}, {-16, -187}, {-13, -152}, {-11, -128}, {-9, -110}, {-8, -96}, {-7, -85}},
  {{-223, -1696}, {-74, -564}, {-44, -338}, {-31, -240}, {-24, -186}, {-20, -152}, {-16, -127}, {-14, -110}, {-12, -96}, {-11, -85}},
  {{-297, -1685}, {-98, -561}, {-59, -336}, {-42, -239}, {-32, -185}, {-26, -151}, {-22, -127}, {-19, -109}, {-16, -95}, {-14, -84}},
  {{-370, -1670}, {-123, -556}, {-73, -333}, {-52, -237}, {-40, -183}, {-33, -149}, {-27, -125}, {-24, -108}, {-21, -94}, {-18, -84}},
  {{-442, -1652}, {-147, -550}, {-88, -329}, {-62, -234}, {-48, -181}, {-39, -148}, {-33, -124}, {-28, -107}, {-25, -93}, {-22, -83}},
  {{-514, -1631}, {-171, -543}, {-102, -325}, {-73, -231}, {-56, -179}, {-46, -146}, {-38, -123}, {-33, -105}, {-29, -92}, {-25, -82}},
  {{-585, -1607}, {-194, -535}, {-116, -320}, {-83, -228}, {-64, -176}, {-52, -144}, {-44, -121}, {-37, -104}, {-33, -91}, {-29, -81}},
  {{-654, -1580}, {-218, -526}, {-130, -315}, {-93, -224}, {-72, -174}, {-58, -141}, {-49, -119}, {-42, -102}, {-37, -89}, {-33, -79}},
  {{-723, -1550}, {-240, -516}, {-144, -309}, {-102, -220}, {-79, -170}, {-64, -138}, {-54, -116}, {-46, -100}, {-41, -88}, {-36, -78}},
  {{-790, -1517}, {-263, -505}, {-157, -302}, {-112, -215}, {-86, -167}, {-70, -136}, {-59, -114}, {-51, -98}, {-44, -86}, {-39, -76}},
  {{-855, -1481}, {-284, -493}, {-170, -295}, {-121, -210}, {-94, -163}, {-76, -132}, {-64, -111}, {-55, -96}, {-48, -84}, {-43, -74}},
  {{-919, -1443}, {-306, -480}, {-183, -287}, {-130, -204}, {-101, -158}, {-82, -129}, {-69, -108}, {-59, -93}, {-52, -82}, {-46, -72}},
  {{-981, -1401}, {-326, -466}, {-195, -279}, {-139, -199}, {-108, -154}, {-87, -125}, {-74, -105}, {-63, -90}, {-55, -79}, {-49, -70}},
  {{-1041, -1357}, {-346, -452}, {-207, -270}, {-147, -192}, {-114, -149}, {-93, -121}, {-78, -102}, {-67, -88}, {-59, -77}, {-52, -68}},
  {{-1099, -1310}, {-366, -436}, {-219, -261}, {-156, -186}, {-121, -144}, {-98, -117}, {-82, -98}, {-71, -85}, {-62, -74}, {-55, -66}},
  {{-1155, -1261}, {-384, -420}, {-230, -251}, {-164, -179}, {-127, -138}, {-103, -113}, {-87, -95}, {-75, -81}, {-65, -71}, {-58, -63}},
  {{-1209, -1209}, {-402, -402}, {-241, -241}, {-171, -171}, {-133, -133}, {-108, -108}, {-91, -91}, {-78, -78}, {-68, -68}, {-60, -60}},
  {{-1261, -1155}, {-420, -384}, {-251, -230}, {-179, -164}, {-138, -127}, {-113, -103}, {-95, -87}, {-81, -75}, {-71, -65}, {-63, -58}},
  {{-1310, -1099}, {-436, -366}, {-261, -219}, {-186, -156}, {-144, -121}, {-117, -98}, {-98, -82}, {-85, -71}, {-74, -62}, {-66, -55}},
  {{-1357, -1041}, {-452, -346}, {-270, -207}, {-192, -147}, {-149, -114}, {-121, -93}, {-102, -78}, {-88, -67}, {-77, -59}, {-68, -52}},
  {{-1401, -981}, {-466, -326}, {-279, -195}, {-199, -139}, {-154, -108}, {-125, -87}, {-105, -74}, {-90, -63}, {-79, -55}, {-70, -49}},
  {{-1443, -919}, {-480, -306}, {-287, -183}, {-204, -130}, {-158, -101}, {-129, -82}, {-108, -69}, {-93, -59}, {-82, -52}, {-72, -46}},
  {{-1481, -855}, {-493, -284}, {-295, -170}, {-210, -121}, {-163, -94}, {-132, -76}, {-111, -64}, {-96, -55}, {-84, -48}, {-74, -43}},
  {{-1517, -790}, {-505, -263}, {-302, -157}, {-215, -112}, {-167, -86}, {-136, -70}, {-114, -59}, {-98, -51}, {-86, -44}, {-76, -39}},
  {{-1550, -723}, {-516, -240}, {-309, -144}, {-220, -102}, {-170, -79}, {-138, -64}, {-116, -54}, {-100, -46}, {-88, -41}, {-78, -36}},
  {{-1580, -654}, {-526, -218}, {-315, -130}, {-224, -93}, {-174, -72}, {-141, -58}, {-119, -49}, {-102, -42}, {-89, -37}, {-79, -33}},
  {{-1607, -585}, {-535, -194}, {-320, -116}, {-228, -83}, {-176, -64}, {-144, -52}, {-121, -44}, {-104, -37}, {-91, -33}, {-81, -29}},
  {{-1631, -514}, {-543, -171}, {-325, -102}, {-231, -73}, {-179, -56}, {-146, -46}, {-123, -38}, {-105, -33}, {-92, -29}, {-82, -25}},
  {{-1652, -442}, {-550, -147}, {-329, -88}, {-234, -62}, {-181, -48}, {-148, -39}, {-124, -33}, {-107, -28}, {-93, -25}, {-83, -22}},
  {{-1670, -370}, {-556, -123}, {-333, -73}, {-237, -52}, {-183, -40}, {-149, -33}, {-125, -27}, {-108, -24}, {-94, -21}, {-84, -18}},
  {{-1685, -297}, {-561, -98}, {-336, -59}, {-239, -42}, {-185, -32}, {-151, -26}, {-127, -22}, {-109, -19}, {-95, -16}, {-84, -14}},
  {{-1696, -223}, {-564, -74}, {-338, -44}, {-240, -31}, {-186, -24}, {-152, -20}, {-127, -16}, {-110, -14}, {-96, -12}, {-85, -11}},
  {{-1704, -149}, {-567, -49}, {-339, -29}, {-242, -21}, {-187, -16}, {-152, -13}, {-128, -11}, {-110, -9}, {-96, -8}, {-85, -7}},
  {{-1709, -74}, {-569, -24}, {-340, -14}, {-242, -10}, {-188, -8}, {-153, -6}, {-128, -5}, {-110, -4}, {-97, -4}, {-86, -3}},
  {{-1711, 0}, {-569, 0}, {-341, 0}, {-243, 0}, {-188, 0}, {-153, 0}, {-129, 0}, {-111, 0}, {-97, 0}, {-86, 0}},
  {{-1709, 74}, {-569, 24}, {-340, 14}, {-242, 10}, {-188, 8}, {-153, 6}, {-128, 5}, {-110, 4}, {-97, 4}, {-86, 3}},
  {{-1704, 149}, {-567, 49}, {-339, 29}, {-242, 21}, {-187, 16}, {-152, 13}, {-128, 11}, {-110, 9}, {-96, 8}, {-85, 7}},
  {{-1696, 223}, {-564, 74}, {-338, 44}, {-240, 31}, {-186, 24}, {-152, 20}, {-127, 16}, {-110, 14}, {-96, 12}, {-85, 11}},
  {{-1685, 297}, {-561, 98}, {-336, 59}, {-239, 42}, {-185, 32}, {-151, 26}, {-127, 22}, {-109, 19}, {-95, 16}, {-84, 14}},
  {{-1670, 370}, {-556, 123}, {-333, 73}, {-237, 52}, {-183, 40}, {-149, 33}, {-125, 27}, {-108, 24}, {-94, 21}, {-84, 18}},
  {{-1652, 442}, {-550, 147}, {-329, 88}, {-234, 62}, {-181, 48}, {-148, 39}, {-124, 33}, {-107, 28}, {-93, 25}, {-83, 22}},
  {{-1631, 514}, {-543, 171}, {-325, 102}, {-231, 73}, {-179, 56}, {-146, 46}, {-123, 38}, {-105, 33}, {-92, 29}, {-82, 25}},
  {{-1607, 585}, {-535, 194}, {-320, 116}, {-228, 83}, {-176, 64}, {-144, 52}, {-121, 44}, {-104, 37}, {-91, 33}, {-81, 29}},
  {{-1580, 654}, {-526, 218}, {-315, 130}, {-224, 93}, {-174, 72}, {-141, 58}, {-119, 49}, {-102, 42}, {-89, 37}, {-79, 33}},
  {{-1550, 723}, {-516, 240}, {-309, 144}, {-220, 102}, {-170, 79}, {-138, 64}, {-116, 54}, {-100, 46}, {-88, 41}, {-78, 36}},
  {{-1517, 790}, {-505, 263}, {-302, 157}, {-215, 112}, {-167, 86}, {-136, 70}, {-114, 59}, {-98, 51}, {-86, 44}, {-76, 39}},
  {{-1481, 855}, {-493, 284}, {-295, 170}, {-210, 121}, {-163, 94}, {-132, 76}, {-111, 64}, {-96, 55}, {-84, 48}, {-74, 43}},
  {{-1443, 919}, {-480, 306}, {-287, 183}, {-204, 130}, {-158, 101}, {-129, 82}, {-108, 69}, {-93, 59}, {-82, 52}, {-72, 46}},
  {{-1401, 981}, {-466, 326}, {-279, 195}, {-199, 139}, {-154, 108}, {-125, 87}, {-105, 74}, {-90, 63}, {-79, 55}, {-70, 49}},
  {{-1357, 1041}, {-452, 346}, {-270, 207}, {-192, 147}, {-149, 114}, {-121, 93}, {-102, 78}, {-88, 67}, {-77, 59}, {-68, 52}},
  {{-1310, 1099}, {-436, 366}, {-261, 219}, {-186, 156}, {-144, 121}, {-117, 98}, {-98, 82}, {-85, 71}, {-74, 62}, {-66, 55}},
  {{-1261, 1155}, {-420, 384}, {-251, 230}, {-179, 164}, {-138, 127}, {-113, 103}, {-95, 87}, {-81, 75}, {-71, 65}, {-63, 58}},
  {{-1209, 1209}, {-402, 402}, {-241, 241}, {-171, 171}, {-133, 133}, {-108, 108}, {-91, 91}, {-78, 78}, {-68, 68}, {-60, 60}},
  {{-1155, 1261}, {-384, 420}, {-230, 251}, {-164, 179}, {-127, 138}, {-103, 113}, {-87, 95}, {-75, 81}, {-65, 71}, {-58, 63}},
  {{-1099, 1310}, {-366, 436}, {-219, 261}, {-156, 186}, {-121, 144}, {-98, 117}, {-82, 98}, {-71, 85}, {-62, 74}, {-55, 66}},
  {{-1041, 1357}, {-346, 452}, {-207, 270}, {-147, 192}, {-114, 149}, {-93, 121}, {-78, 102}, {-67, 88}, {-59, 77}, {-52, 68}},
  {{-981, 1401}, {-326, 466}, {-195, 279}, {-139, 199}, {-108, 154}, {-87, 125}, {-74, 105}, {-63, 90}, {-55, 79}, {-49, 70}},
  {{-919, 1443}, {-306, 480}, {-183, 287}, {-130, 204}, {-101, 158}, {-82, 129}, {-69, 108}, {-59, 93}, {-52, 82}, {-46, 72}},
  {{-855, 1481}, {-284, 493}, {-170, 295}, {-121, 210}, {-94, 163}, {-76, 132}, {-64, 111}, {-55, 96}, {-48, 84}, {-43, 74}},
  {{-790, 1517}, {-263, 505}, {-157, 302}, {-112, 215}, {-86, 167}, {-70, 136}, {-59, 114}, {-51, 98}, {-44, 86}, {-39, 76}},
  {{-723, 1550}, {-240, 516}, {-144, 309}, {-102, 220}, {-79, 170}, {-64, 138}, {-54, 116}, {-46, 100}, {-41, 88}, {-36, 78}},
  {{-654, 1580}, {-218, 526}, {-130, 315}, {-93, 224}, {-72, 174}, {-58, 141}, {-49, 119}, {-42, 102}, {-37, 89}, {-33, 79}},
  {{-585, 1607}, {-194, 535}, {-116, 320}, {-83, 228}, {-64, 176}, {-52, 144}, {-44, 121}, {-37, 104}, {-33, 91}, {-29, 81}},
  {{-514, 1631}, {-171, 543}, {-102, 325}, {-73, 231}, {-56, 179}, {-46, 146}, {-38, 123}, {-33, 105}, {-29, 92}, {-25, 82}},
  {{-442, 1652}, {-147, 550}, {-88, 329}, {-62, 234}, {-48, 181}, {-39, 148}, {-33, 124}, {-28, 107}, {-25, 93}, {-22, 83}},
  {{-370, 1670}, {-123, 556}, {-73, 333}, {-52, 237}, {-40, 183}, {-33, 149}, {-27, 125}, {-24, 108}, {-21, 94}, {-18, 84}},
  {{-297, 1685}, {-98, 561}, {-59, 336}, {-42, 239}, {-32, 185}, {-26, 151}, {-22, 127}, {-19, 109}, {-16, 95}, {-14, 84}},
  {{-223, 1696}, {-74, 564}, {-44, 338}, {-31, 240}, {-24, 186}, {-20, 152}, {-16, 127}, {-14, 110}, {-12, 96}, {-11, 85}},
  {{-149, 1704}, {-49, 567}, {-29, 339}, {-21, 242}, {-16, 187}, {-13, 152}, {-11, 128}, {-9, 110}, {-8, 96}, {-7, 85}},
  {{-74, 1709}, {-24, 569}, {-14, 340}, {-10, 242}, {-8, 188}, {-6, 153}, {-5, 128}, {-4, 110}, {-4, 97}, {-3, 86}} */
};

bool samplePixel(short xPos, short yPos) {
    return (((xPos / precision) + (yPos / precision)) % 2);
}

bool getScreenPixel(unsigned char x, unsigned char y) {
    // Used to indicate framerate
    if (x == 0 && y == 0) {
        return o == 0;
    }

    // Temporary for small screen sizes
    if (y >= height) return false;
    if (x >= width) return false;
    
    if (y < horizon) return false;

    // If both samples are 0 in the Python, the horizon colour is set but that doesn't seem to be needed

    return samplePixel(
        angles[x + o][y - horizon][0],
        angles[x + o][y - horizon][1]
    );
}

unsigned char getScreenByte(unsigned char x, unsigned char y) {
    unsigned char result = 0;
    for (unsigned char ox = 0; ox < 8; ox++) {
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
        unsigned char *byte = plotSScreen;

        for (unsigned char y = 0; y < /*64 */ height; y++) {
            for (unsigned char x = 0; x < 96; x += 8) {
                if (x < (width + 8))
                    *byte = getScreenByte(x, y);
                byte++;
            }
        }

        FastCopy();

        unsigned char key = CGetKey();
        if (key == 0) break;
        o++;
    }

    CClrLCDFull();

    CRunIndicatorOn();
    /* The OS seems to do this anyways, but it's good to be safe */
    CDisable15MHz();

    return 0;
}
