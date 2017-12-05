#ifndef BITBLOCK_H
#define BITBLOCK_H

#include "Block.h"

class BitBlock : public Block
{
	public:
		BitBlock(short blockSize);
		void setBit(int whichBit);
		void setBit(int whichBit, bool value);
		int getBit(int whichBit);
		bool isBitSet(int whichBit);
		void resetBit(int whichBit);
};
#endif
