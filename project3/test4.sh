
./mkfs filesys.dat 256 40

echo "foo" | ./tee "/foo.txt"
echo "foo" | ./tee "/bar.txt"
echo "foo" | ./tee "/baz.txt"
echo "foo" | ./tee "/zen.txt"


