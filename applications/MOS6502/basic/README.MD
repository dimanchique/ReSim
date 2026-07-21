# EhBasic

Enhanced BASIC for the MOS 6502 processor, written by Lee Davison

>This is a modified version of [EhBasic](https://github.com/Klaus2m5/6502_EhBASIC_V2.22) taken from Klaus2m5 repo

## Details
This subproject is an EhBasic (version 2.22) running inside ReSim emulator with cc65 toolchain support. Sources and assembled binary are located in `src` folder.

## Build

```bash
cd src
./build.sh <path to cc65 folder>

cd ../
./6502-basic
```

If everything is okay you'll see the EhBasic startup message and prompt:
```bash
6502 EhBASIC [C]old/[W]arm ?    # need to press C here, Warm stat is not supported

Memory size ? 8096              # type EhBasic memory size. Minimal value is 1028

7071 Bytes free

Enhanced BASIC 2.22

Ready
```

## Usage 

EhBasic provides a standard BASIC interpreter environment. Once running, you can:

### Enter Programs
```basic
10 PRINT "HELLO WORLD"
20 FOR I = 1 TO 10
30 PRINT I
40 NEXT I
RUN
```

### Direct Commands
- `LIST` - List current program
- `RUN` - Execute program
- `NEW` - Clear program from memory
- `CLEAR` - Clear variables
- `LOAD` - Load program from storage (do nothing, can be user-defined)
- `SAVE` - Save program to storage (do nothing, can be user-defined)
- ... and etc. You can learn EhBasic syntax in [Language Reference page](http://retro.hansotten.nl/6502-sbc/lee-davison-web-site/enhanced-6502-basic/ehbasic-language-reference/)

### Example Session
```basic
> 10 PRINT "HELLO"
> RUN
HELLO
> LIST
10 PRINT "HELLO"
> NEW
> 
```

## Keyboard Mapping

The emulator uses the `keyboard.h` and `tty.h` modules for I/O handling. Standard ASCII characters are supported through the keyboard interface.
