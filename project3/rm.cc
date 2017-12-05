/**
Project 3 File System Simulator
Jared Willard and Eric Kuha
CSCI 5103
Deletes a link to a file or deletes the file
if this is the only link
 */
#include "Kernel.h"
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char ** argv)
{
    char PROGRAM_NAME[8];
    strcpy(PROGRAM_NAME, "rm");

    char name[64];

    memset(name, '\0', 64);

    if(Kernel::initialize() == false)
    {
        cout << "Failed to initialize Kernel" << endl;
        Kernel::exit(1);
    }

    if(argc<2)
    {
        cout << PROGRAM_NAME << ": usage: "
            << PROGRAM_NAME << " <file path>"
            << endl;
        Kernel::exit(1);
    }

    strcpy(name, argv[1]);

    int out_fd = Kernel::unlink(name);

    Kernel::exit(0);
}
