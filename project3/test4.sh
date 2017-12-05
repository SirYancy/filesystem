#!/bin/bash
# Project 3 File System Simulator
# Jared Willard and Eric Kuha
# CSCI 5103
./mkfs filesys.dat 256 40

echo "foo" | ./tee "/foo.txt"
echo "foo" | ./tee "/bar.txt"
echo "foo" | ./tee "/baz.txt"
echo "foo" | ./tee "/zen.txt"


