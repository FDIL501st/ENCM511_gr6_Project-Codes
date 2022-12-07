#ifndef DRIVER7_IO_H
#define	DRIVER7_IO_H

#include <xc.h> // include processor files - each processor file is guarded.  

void IOinit();
// PROMISES: Set port RA3 as analog input

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* DRIVER7_IO_H */

