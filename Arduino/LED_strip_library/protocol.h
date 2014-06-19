/* LED strip program serial protocol
 * Author: Carlos Chinchilla
 * 2013-2014
 * 
 * CIDERWARE LICENSE - TG version
 * The code is free to use and modify by the Thunder Gumbo community and
 * no one else. If you find the code useful and see the author
 * chinchillin' at a bar you may thank him with a cold apple cider.
*/

// All the following are constants for packets starting with a UID char
// and ending with a new line feed (\n). In other words, the packet size
// includes the UID byte and the new line character.

// Unique Identifier
#define UID '0'

// command variables
#define FAST 'f'
#define SLOW 's'
#define ON '.'
#define OFF ','

// 3-byte command
#define RANDOM_COLOR 'r'
#define RANDOM_EFFECT 'R'
#define RAINBOW_EFFECT 'a'

// 4-byte commands:
// send as command + variable from the list at top,
// except for EFFECT where the second byte is the effect number
// and THEME_SELECT where the second byte is the theme number
#define SPEED 's'
#define EFFECT 'e'
#define TOGGLE 't'
#define THEME_TOGGLE 'g'
#define THEME_SELECT 'h'

// 6-byte commands
// send as command + R + G + B 
#define COLOR 'c'
// Effect codes
#define FLASH_EFFECT 'f'
#define WIPE_EFFECT 'w'

// 8-byte commands
// send as command + effect number + effect continuity + theme continuity + speed
#define FULL_PACKET 'p'

// Themes codes
#define TRIANGLE_THEME '0'
#define CIRCLE_THEME '1'
#define CROSS_THEME '2'
#define SQUARE_THEME '3'
#define L1_THEME '4'
#define L2_THEME '5'
#define L3_THEME '6'
#define R1_THEME '7'
#define R2_THEME '8'
#define R3_THEME '9'
#define RANDOM_THEME ':'
