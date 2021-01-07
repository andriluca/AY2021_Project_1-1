/* =========================================================================
 * Project01-1, Luca Andriotto, Matteo Cavicchioli, Alessandro Pirelli
 * =========================================================================
*/

#include "states.h"

int main(void)
{
    init();     // Initializing peripherals and variables.
    loop();     // Executing the states machine.
}


// N.B. All used delays are for stabilization in sequential reading/writing