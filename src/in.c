//
// https://github.com/webnefor/
// (c) Job
//


#include "scan.h"

//
//  Scan the input hosts and prints the results.
//  This args: -h (entering our start_ip-end_ip) EXAMPLE: (-h 0.0.0.0-1.1.255.255) 
//  This args: -p (entering ours ports) EXAMPLE: -p 80,443,22 
//

int main(int args, char *argv[]) {

    if (args < 4) {
        
        logo();
        printf("Usage: [-h <start_ip-end_ip>] [-p <22,80,443>]\n");
            
	    return 1;
    
    }

    setArgv(args, argv);

    return (0);
}
