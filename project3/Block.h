/*
Project 3 File System Simulator
Jared Willard and Eric Kuha
CSCI 5103
Block.h
*/
#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <fstream>

using namespace std;

class Block 
{
	private:
		short blockSize;

	public:
		char * bytes;

		Block();
		Block( short blockSize );
		~Block();

		void setBlockSize(short newBlockSize);
		short getBlockSize();
		void read(fstream& file);// throws IOException , EOFException
		void write(fstream& file);// throws IOException
};

#endif 
