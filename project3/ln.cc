/**
 * Creates a hard link between a file path
 * and an already existing file
 */
#include "Kernel.h"
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char ** argv)
{
    char PROGRAM_NAME[8];
    strcpy(PROGRAM_NAME, "ln");

    char oldname[64];
    char newname[64];

    memset(oldname, '\0', 64);
    memset(newname, '\0', 64);

    if(Kernel::initialize() == false)
    {
        cout << "Failed to initialize Kernel" << endl;
        Kernel::exit(1);
    }

    if(argc < 3)
    {
        cout << PROGRAM_NAME << ": usage: " 
            << PROGRAM_NAME << " <old-file> <new-file" 
            << endl;
        Kernel::exit(1);
    }

    strcpy(oldname, argv[1]);
    strcpy(newname, argv[2]);

    int out_fd = Kernel::link(oldname, newname);


    Kernel::exit(0);
}
