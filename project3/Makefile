GCC = g++-5

all: mkfs ls cat tee ln cp dump mkdir

cp: cp.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o
	$(GCC) cp.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o -o cp

tee: tee.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o
	$(GCC) tee.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o -o tee

ln: ln.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o
	$(GCC) ln.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o -o ln

ls: ls.cc Stat.o DirectoryEntry.o Kernel.o FileSystem.o FileDescriptor.o ProcessContext.o
	$(GCC) ls.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o -o ls

mkdir: mkdir.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o
	$(GCC) mkdir.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o -o mkdir

cat: cat.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o
	$(GCC) cat.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o -o cat

mkfs: mkfs.cc BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o
	$(GCC) mkfs.cc BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o -o mkfs

dump: dump.cc
	$(GCC) dump.cc -o dump

Kernel.o: Kernel.cc
	$(GCC) -c Kernel.cc

ProcessContext.o: ProcessContext.cc
	$(GCC) -c ProcessContext.cc 

FileDescriptor.o: FileDescriptor.cc
	$(GCC) -c FileDescriptor.cc
	
FileSystem.o: FileSystem.cc 
	$(GCC) -c FileSystem.cc 

Stat.o: Stat.cc
	$(GCC) -c Stat.cc

DirectoryEntry.o: DirectoryEntry.cc
	$(GCC) -c DirectoryEntry.cc

BitBlock.o: BitBlock.cc
	$(GCC) -c BitBlock.cc

IndexNode.o: IndexNode.cc
	$(GCC) -c IndexNode.cc 

Block.o: Block.cc
	$(GCC) -c Block.cc

SuperBlock.o: SuperBlock.cc	
	$(GCC) -c SuperBlock.cc

clean:
	rm *.o mkfs ls cat tee cp dump mkdir

