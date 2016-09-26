#UnixWordCount
I implement my own light-weight wc utility, called lwc.c, in C. 
- lwc only supports three options -l, -w, and –c.
- lwc assumes at least one option is provided.
- lwc only process files (ignore stdin).
- lwc supports multiple options.
- lwc ignore the order of options.
- lines printed first, followed by the no. words and characters.
- If an invalid option or filename is given, lwc prints the same error message wc would print to stderr, and return the same non-zero exit status.
And this code is compiled on Ubuntu 16.04 LTS.


##How to compile & run this program
This program is written in Linux environment, GUN make, and GCC(Gnu compiler collection.)
Just type the commands (in BASH shell),
```
make help
```

or

```
make clean dep all
```
It will automatically compile all the necessary files/codes, then generate the execution file.
Then type this,
```
./EXENAME
```

In the end, it will work successfully.

###2016 Advance UNIX Programmin HW1
