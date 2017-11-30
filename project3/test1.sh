#!/bin/bash

rm -f filesys.dat

./mkfs filesys.dat 256 40

./mkdir /home
./mkdir /docs

echo "We hold these truths to be self-evident: that all men are created equal; that they are endowed by their Creator with certain unalienable rights; that among these are life, liberty, and the pursuit of happiness." | ./tee /home/rights.txt

./ln "/home/rights.txt" "/docs/other.txt"

