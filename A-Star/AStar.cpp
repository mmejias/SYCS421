/* My A* Search Algorithm has an error for the tenth case in which
 * it finds the path because the program does not print 'no path found'
 * However, the path is not printed. I believe the error is I am not keeping a moves list
 * and possibly only printing from the closed list.
 * Also, I think I am destroying the path in the closed list. MUST FIX.
*/

#include "Asearch.h"

int main()
{
    //Perform an A* Search Algorithm on a 2D array
    Asearch();
    
    return 0;
}
