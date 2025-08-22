#include "so_long.h"

/*need to (read) map content
1:width should be >1
2:flag for each character, at least each of them
3:height > 1

0 for an empty space,
1 for a wall,
C for a collectible,
E for a map exit,
P for the player’s starting position.


• The map must be rectangular.
• The map must be enclosed/surrounded by walls. If it is not, the program must
return an error.
• You must verify if there is a valid path in the map.
• You must be able to parse any kind of map, as long as it respects the above rules.
• Another example of a minimal .ber map:
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
• If any misconfiguration is encountered in the file, the program must exit cleanly,
and return "Error\n" followed by an explicit error message of your choice.
*/

