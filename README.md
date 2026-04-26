# Dasm - Display Assembly

## Compiler and Interpreter

The compiler turns code like this

```
Main:
SCR = 0x1
STR A SCR	# First Screen
DIS
```

into the associated binary data in the instruction set.

> See `dasm.txt` for more info

### Usage:

```
dasm [source file] [output]
```
