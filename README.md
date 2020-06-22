# bfi

A POSIX compliant brainfuck interpreter.

Currently has no dynamic memory realoccation so if you go above the alloted 1 MiB of memory 
you will segfault.

# Installing

Start by compiling the binary.

```
make
```

This will place a binary called `bfi` in the same directory. You can then place it in a 
directory of your choice that is contained in your PATH variable.

# Usage
Simple run the binary with a single command line argument containing the path to a brainfuck source file.
There is an example piece of code which will print hello world in this repository. So you can try it out.

```bash
bfi helloworld.bfi
```


# Licence

MIT

