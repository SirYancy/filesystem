#include "FileSystem.h"
#include "Kernel.h"
#include "DirectoryEntry.h"
#include "IndexNode.h"
#include "Stat.h"
#include "BitBlock.h"
#include "Block.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

/* Write  a  program  called fsck.cc which  checks  a  file  system  for  internal  consistency.  It  should 
verify that 
	- all the  inodes mentioned in directory entries have the correct number of
	nlinks
	- that all blocks mentioned in the inodes are marked as allocated blocks
	- all blocks NOT mentioned in the  inodes  are  marked  as  free  blocks.  
At  a  minimum  you  should  list  any  prob
lems  to  standard  out. You may need to manually induce errors in your file system to test this */ 
char* CD = new char[1];
char* PD = new char[2];
FileSystem* fileSystem = (FileSystem*)malloc(sizeof(FileSystem));
char* rootName = new char[5];
int verifyAllocatedBlocks(IndexNode* inode, short inodeId){
	//get block size
	fileSystem = Kernel::openFileSystems;
	ProcessContext * process = Kernel::getProcess();
	FileDescriptor * file = process->openFiles[0] ;
	int blockSize = file->getBlockSize();
	int blockCount = fileSystem->getBlockCount();
	int notBlock = IndexNode::NOT_A_BLOCK;
	int maxFileBlocks = IndexNode::MAX_FILE_BLOCKS;

	//verify that allocated are allocated and not allocated are free

	BitBlock * freeListBitBlock = fileSystem->getFreeListBitBlock();

	// for(int i = 0; i < blockCount; ++i){
	// 	cout << "input ti getBit " << i << endl;

	// 	cout << "getBit: " << freeListBitBlock->getBit(i) << endl;
	// }
	// return 0;


	for(int i = 0; i < maxFileBlocks; ++i){
		//loop through block addresses of inode
		int block = inode->getBlockAddress(i);

		//this is wrong
		bool isSet  = freeListBitBlock->isBitSet(block % (blockSize % 8 + 1));

		//print if unallocated block is listed as allocated
		if(block == IndexNode::NOT_A_BLOCK && isSet){
			cout << "For index node: " << inodeId << ", " <<
			" non-allocated blocks are not free in relative block " << i << endl;
		}
		else if(block != IndexNode::NOT_A_BLOCK && !isSet){
			//print if allocated block is listed as free
			// cout << block << endl;
			cout << "For index node: " << inodeId << ", " <<
			" allocated blocks listed as free in relative block " << i << endl;
		}
	}
	return 0;
}

int countLinks(char* name, short inodeId, vector<short>* checked_dir_inodes){

	char PROGRAM_NAME[8];
	strcpy(PROGRAM_NAME, "fsck");

	char temp2[512];
	int status = 0;
	Stat statParent;
	Stat stat;
	status = Kernel::stat( name , statParent ) ;

	//get status
	if( status < 0 )
	{
		cout << "fail stat" << endl;
		Kernel::perror( PROGRAM_NAME ) ;
		Kernel::exit( 1 ) ;
	}

	//verify it's indeed a directory
	short type = (short)( statParent.getMode() & Kernel::S_IFMT ) ;
	if(type != Kernel::S_IFDIR){
		cout << "not a directory" << endl;
		Kernel::perror( PROGRAM_NAME ) ;
		Kernel::exit( 1 );
	}

	//open directory
	int fd = Kernel::open( name , Kernel::O_RDONLY ) ;
	if( fd < 0 )
	{
		Kernel::perror( PROGRAM_NAME ) ;
		cout << PROGRAM_NAME << ": unable to open \"" << name << "\" for reading";
		Kernel::exit(1) ;
	}
	short parentIno = statParent.getIno();
	checked_dir_inodes->push_back(parentIno);
	DirectoryEntry directoryEntry;
	int count = 0;
	while( true ) 
	{
		// read an entry; quit loop if error or nothing read
		status = Kernel::readdir( fd , directoryEntry ) ;
		if( status <= 0 )
		{
			break ;
		}
		// get the name from the entry
		char * entryName = directoryEntry.getName() ;

		// call stat() to get info about the file
//		memcpy(temp, '\0', 512);
		strcpy(temp2, name);
		if(strcmp(name, "/") != 0){
			//avoid extra slash from root name
			strcat(temp2, "/");
		}
		strcat(temp2, entryName);
//name, entryName);

		status = Kernel::stat(temp2, stat);
		if( status < 0 )
		{
			Kernel::perror( PROGRAM_NAME ) ;
			Kernel::exit( 1 ) ;
		}
		short type = (short)( stat.getMode() & Kernel::S_IFMT );

		//if entry is nod a directory
		if(type != Kernel::S_IFDIR){
			//if directoryEntry is not a directory and has the same inode, add to count
			if(stat.getIno() == inodeId){
				count++;
			}
		}
		else{
					// else if(strcmp(entryName, CD) != 0 && strcmp(entryName, PD) != 0){

			//if entry IS a directory
			if(stat.getIno() == inodeId){
				//increase count, assume nothing in directory would also link
				count++;
			}
			else{
				//recursively count in subdirectory
				if(strcmp(entryName, CD) != 0 && strcmp(entryName, PD) != 0){
					if(!checked_dir_inodes->empty() && find(checked_dir_inodes->begin(), checked_dir_inodes->end(), stat.getIno()) == checked_dir_inodes->end())
					{
						//only check directories that haven't been checked
						int subCount = countLinks(temp2, inodeId, checked_dir_inodes);
						count = count + subCount; 
					}
				}
			}
		}
		//clear memory
		memset(temp2, '\0', 512);
	}
	int s = Kernel::close(fd);
	// if(s == 0){
	// 	// cout << "file closed at end of count ->" << fd << endl;
	// }
	// else if(s == -1){
	// 	// cout << "invalid fd to close-> " << fd << endl;
	// }
	return count;
}
int verifyDirectory(char * name, vector<short>* checked_inodes){
	ProcessContext * process = Kernel::getProcess();
	char PROGRAM_NAME[8];
	strcpy(PROGRAM_NAME, "fsck");
	char temp[512]; // to store directoryEntry name

	FileSystem * fileSystem = Kernel::openFileSystems;

	int status = 0;
	Stat stat;
	Stat parentStat;
	status = Kernel::stat( name , parentStat ) ;

	//get status
	if( status < 0 )
	{
		cout << "fail stat" << endl;
		Kernel::perror( PROGRAM_NAME ) ;
		Kernel::exit( 1 ) ;
	}

	//verify it's indeed a directory
	short type = (short)( parentStat.getMode() & Kernel::S_IFMT ) ;
	if(type != Kernel::S_IFDIR){
		cout << "not a directory" << endl;
		Kernel::perror( PROGRAM_NAME ) ;
		Kernel::exit( 1 );
	}

	//open directory
	int fd = Kernel::open( name , Kernel::O_RDONLY ) ;
	if( fd < 0 )
	{
		Kernel::perror( PROGRAM_NAME ) ;
		cout << PROGRAM_NAME << ": unable to open \"" << name << "\" for reading";
		Kernel::exit(1) ;
	}
	// print a heading for this directory
// 
	// create a directory entry structure to hold data as we read
	DirectoryEntry directoryEntry;
	IndexNode* inode = (IndexNode*)malloc(sizeof(IndexNode));

	while(true){
		//read through directory
		status = Kernel::readdir( fd , directoryEntry ) ;
		if( status <= 0 )
		{
			break ;
		}
		// get the name from the entry
		char * entryName = directoryEntry.getName() ;
		// call stat() to get info about the file

		//hacky bug fix
		char* temp2 = new char[512];
		char* entryNameComp = new char[512];
		strcpy(temp2, "/");
		strcat(entryNameComp, temp2);
		strcat(entryNameComp, entryName);
		if(strcmp(entryNameComp, name) == 0){
			break;
		}


		strcpy(temp, name);
		if(strcmp(name, "/") != 0){
			//avoid extra slash from root name
			strcat(temp, "/");
		}
		strcat(temp, entryName);
		// cout << temp << endl;
		status = Kernel::stat(temp, stat);
		if( status < 0 )
		{
			Kernel::perror( PROGRAM_NAME ) ;
			Kernel::exit( 1 ) ;
		}

		//get current entry inode
		short inodeId = directoryEntry.getIno();
		FileDescriptor* f = Kernel::getFileDescriptor(temp, 0);
		inode = f->getIndexNode(); 

		fileSystem->readIndexNode(inode, inodeId);



		short type = (short)( stat.getMode() & Kernel::S_IFMT );
		//if entry is not a directory

		if(type != Kernel::S_IFDIR){
			//check if inode has been checked
			if(!checked_inodes->empty() && find(checked_inodes->begin(), checked_inodes->end(), inodeId) != checked_inodes->end()){
				//already checked this one
				continue;
			}
			else{
				int nLink = inode->getNlink();
				//verify inode nLink is correct
				if(nLink == 0){
					checked_inodes->push_back(inodeId);
					//dont have to worry about previously deleted files
					continue;
				}
				else{
					//find other files with the same inode
					vector<short>* checked_dir_inodes = new vector<short>();
					int foundLinks = countLinks(rootName, inodeId, checked_dir_inodes);
					//int foundLinks = 0;
					if(foundLinks != nLink){
						cout << "nLink for the inode " << inodeId << " mismatched number of links found in the directory" << endl;
						cout << "nLink = " << nLink << ", foundLinks = " << foundLinks << endl;
					}
					else{
						cout << "nlinks matches links found in directory entries for IndexNode " << inodeId << endl; 
					}
					verifyAllocatedBlocks(inode, inodeId);
					checked_inodes->push_back(inodeId);
				}
			}
		}
		else{
			//if entry IS a directory, call recursively if needed
			if(strcmp(entryName, CD) != 0 && strcmp(entryName, PD) != 0){
							//check if inode has been checked
				if(!checked_inodes->empty() && find(checked_inodes->begin(), checked_inodes->end(), inodeId) != checked_inodes->end()){
					//already checked this one
					continue;
				}
				else{
					int nLink = inode->getNlink();
					//verify inode nLink is correct
					if(nLink == 0){
						checked_inodes->push_back(inodeId);
						//dont have to worry about previously deleted files
						continue;
					}
					else{
						//find other files with the same inode
						vector<short>* checked_dir_inodes = new vector<short>();
						// int foundLinks = 0;
						int foundLinks = countLinks(rootName, inodeId, checked_dir_inodes);
						if(foundLinks != nLink-1){
							//minus one for . dir
							cout << "nLink for the inode " << inodeId << "mismatched number of links found in the directory" << endl;
							cout << "nLink = " << nLink << ", foundLinks = " << foundLinks << endl;
						}
						else{
							cout << "nlinks matches links found in directory entries for IndexNode " << inodeId << endl; 
						}
						verifyAllocatedBlocks(inode, inodeId);
						checked_inodes->push_back(inodeId);

						//now call again with directory
						int status = verifyDirectory(temp, checked_inodes);
					}
				}	
			}
			else{
			}
		}
	memset(temp, '\0', 512);
}
if( status < 0 )
{
	Kernel::perror( "main" ) ;
	cout << "main: unable to read directory entry from /" ;
	Kernel::exit(2) ;
}

			// close the directory
// cout << "closing dir " << name << "with fd=" << fd << endl;
Kernel::close( fd ) ;

return 0;
}

int main(int argc, char ** argv)
{
	char PROGRAM_NAME[8];
	strcpy(PROGRAM_NAME, "fsck");

	//initialize current dir / parent dir
	string cd_str = ".";
	string pd_str = "..";
	strcpy(CD, cd_str.c_str());
	strcpy(PD, pd_str.c_str());


	// initialize the file system simulator kernel
	if(Kernel::initialize() == false)
	{
		cout << "Failed to initialized Kernel" << endl;
		Kernel::exit(1);
	}

	if(argc != 1)
	{
		cout << "fsck: no args needed\n";
		return -1;
	}

	//get file system
	FileSystem * fileSystem = Kernel::openFileSystems;


//verify all inodes mentioned in directory entries have the correct number of inode

	//get root node
	IndexNode rootIndexNode;
	fileSystem->getRootIndexNode()->copy(rootIndexNode);

	strcpy(rootName, "/");

	// char * name = new char[512];
	// strcpy(name, rootName.c_str());
	int status = 0;
	vector<short> * checked_inodes = new vector<short>();
	status = verifyDirectory(rootName, checked_inodes);
	cout << "FSCK Complete " << endl;
	return 0;
}


