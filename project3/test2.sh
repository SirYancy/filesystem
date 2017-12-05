#!/bin/bash
# Project 3 File System Simulator
# Jared Willard and Eric Kuha
# CSCI 5103

echo "deleting filesystem \n"
rm -f filesys.dat

echo "making filesystem \n"
./mkfs filesys.dat 256 40

echo "making home directory\n"
./mkdir /home
echo "making docs directory\n"
./mkdir /docs
echo "making docs/class"
./mkdir /docs/class
echo "making docs/work"
./mkdir /docs/work

echo "Making file \n"
echo "We hold these truths to be self-evident: that all men are created equal; that they are endowed by their Creator with certain unalienable rights; that among these are life, liberty, and the pursuit of happiness." | ./tee /home/rights.txt

echo "Making second file \n"
echo "Lorem ipsum dolor sit amet" | ./tee /home/lipsum.txt

echo "Making third file \n"
echo "Lorem ipsum dolor sit amet" | ./tee /home/test.txt

echo "making link \n"
./ln "/home/rights.txt" "/docs/other.txt"

echo "Testing Remove\n"
./rm "/home/lipsum.txt"

echo "listing directory\n"
./ls "/home"
