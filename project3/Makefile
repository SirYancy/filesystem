GCC = g++-5
GCCFLAGS = 
OBJECTS = Kernel.o ProcessContext.o FileDescriptor.o FileSystem.o Stat.o DirectoryEntry.o BitBlock.o IndexNode.o Block.o SuperBlock.o

debug: GCCFLAGS += -g
debug: $(OBJECTS)
debug: all

all: mkfs ls cat tee ln rm cp dump mkdir fsck

cp: cp.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o
	$(GCC) $(GCCFLAGS) cp.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o -o cp

tee: tee.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o
	$(GCC) $(GCCFLAGS) tee.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o -o tee

ln: ln.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o
	$(GCC) $(GCCFLAGS) ln.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o -o ln

rm: rm.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o
	$(GCC) $(GCCFLAGS) rm.cc Kernel.o IndexNode.o FileDescriptor.o DirectoryEntry.o ProcessContext.o FileSystem.o Stat.o BitBlock.o Block.o SuperBlock.o -o rm

ls: ls.cc Stat.o DirectoryEntry.o Kernel.o FileSystem.o FileDescriptor.o ProcessContext.o
	$(GCC) $(GCCFLAGS) ls.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o -o ls

fsck: fsck.cc Stat.o DirectoryEntry.o Kernel.o FileSystem.o FileDescriptor.o ProcessContext.o
	$(GCC) $(GCCFLAGS) fsck.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o -o fsck

mkdir: mkdir.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o
	$(GCC) $(GCCFLAGS) mkdir.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o -o mkdir

cat: cat.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o
	$(GCC) $(GCCFLAGS) cat.cc Stat.o FileDescriptor.o FileSystem.o BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o ProcessContext.o Kernel.o -o cat

mkfs: mkfs.cc BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o
	$(GCC) $(GCCFLAGS) mkfs.cc BitBlock.o IndexNode.o DirectoryEntry.o Block.o SuperBlock.o -o mkfs

dump: dump.cc
	$(GCC) $(GCCFLAGS) dump.cc -o dump

Kernel.o: Kernel.cc
	$(GCC) $(GCCFLAGS) -c Kernel.cc

ProcessContext.o: ProcessContext.cc
	$(GCC) $(GCCFLAGS) -c ProcessContext.cc 

FileDescriptor.o: FileDescriptor.cc
	$(GCC) $(GCCFLAGS) -c FileDescriptor.cc
	
FileSystem.o: FileSystem.cc 
	$(GCC) $(GCCFLAGS) -c FileSystem.cc 

Stat.o: Stat.cc
	$(GCC) $(GCCFLAGS) -c Stat.cc

DirectoryEntry.o: DirectoryEntry.cc
	$(GCC) $(GCCFLAGS) -c DirectoryEntry.cc

BitBlock.o: BitBlock.cc
	$(GCC) $(GCCFLAGS) -c BitBlock.cc

IndexNode.o: IndexNode.cc
	$(GCC) $(GCCFLAGS) -c IndexNode.cc 

Block.o: Block.cc
	$(GCC) $(GCCFLAGS) -c Block.cc

SuperBlock.o: SuperBlock.cc	
	$(GCC) $(GCCFLAGS) -c SuperBlock.cc

clean:
	rm *.o mkfs ls cat tee ln rm cp dump mkdir

