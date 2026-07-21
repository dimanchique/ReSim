# Wozmon

The WOZ Monitor for the Apple 1 written by Steve Wozniak in 1976

>This is a slightly modified version of [Wozmon](https://github.com/jefftranter/6502/blob/master/asm/wozmon/wozmon.s) taken from jefftranter repo

## Details
This subproject is an original Wozmon running inside ReSim emulator with cc65 toolchain support. Sources and assembled binary is located in `src` folder.

## Build

```bash
cd src
./build.sh <path to cc65 folder>

cd ../
./6502-wozmon
```

If everything is okay you'll see:
```bash
Wozmon ready
\

```

## Usage 

> Wozmon is case-insensitive, btw

### Examine Single Byte: `[ADDRESS]`
```bash
3000

3000: 00
```

### Examine Memory Range: `[START_ADDRESS].[END_ADDRESS]`
```bash
3000.3008

3000: 00 00 00 00 00 00 00 00
3008: 00
```

### Write to Memory: `[ADDRESS]:[BYTE1] [BYTE2] ...`
```bash
3000.3008                        # read memory range

3000: 00 00 00 00 00 00 00 00    # got all zeros
3008: 00

3000:12 23 34 45 56 67 78        # writing into it

3000: 00                         # it prints old first location value for some reason
3000.3008                        # read memory range again

3000: 12 23 34 45 56 67 78 00    # got updated values
3008: 00
```

### Execute Program: `[ADDRESS]R`
> Pretty much useless in as-is solution, need to figure out how to patch wozmon binary to place some program inside
```bash
0300R
```
