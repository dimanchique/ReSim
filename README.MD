# ReSim - Retro Computing Simulator

## 🎯 Project Overview

**ReSim** (RetroSimulator) is a high-performance, cycle-accurate emulation framework for classic microprocessor units. Originally conceived as a 6502 functional simulator, it has evolved into a versatile platform supporting multiple historic CPU architectures.

## 📊 Project Status

| Processor | Completion                                                 | Status |
|-----------|------------------------------------------------------------|--------|
| **MOS6502** | ![100%](https://progress-bar.xyz/100?style=flat&width=200) | ✅ Complete |
| **Intel 8080** | ![100%](https://progress-bar.xyz/100?style=flat&width=200) | ✅ Complete |
| **Intel 8086** | ![82%](https://progress-bar.xyz/82?style=flat&width=200)   | 🚧 In Progress |
| **Z80** | ![1%](https://progress-bar.xyz/1?style=flat&width=200)     | 📋 Planned |

## ✨ Key Features

### 🕒 Cycle-Accurate Emulation
- **Precision Timing**: Each instruction emulates exact clock cycle behavior
- **Bus Operations**: Accurate memory read/write cycle counting
- **Multi-Architecture**: Consistent timing model across all supported CPUs

### ⚡ High-Performance Core
- **Optimized C++**: "C with classes" approach for minimal overhead
- **Efficient Design**: No STL containers, RTTI, or heavy templates

### 🧪 Comprehensive Testing
- **Test-Driven Development**: Full unit test coverage using Google Test
- **ASM Validation**: Additional assembly-level functional tests
- **Cross-CPU Consistency**: Uniform testing methodology across all architectures
- **Continuous Validation**: Automated test suites for regression prevention

### 🔧 Developer Friendly
- **Clean Architecture**: Consistent instruction decoding patterns
- **Extensible Design**: Easy to add new CPU architectures

## 🚀 Quick Start

### Prerequisites
- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.22+
- Google Test (for development and testing)

### Building from Source
```bash
git clone https://github.com/dimanchique/ReSim.git
cd ReSim
mkdir build && cd build
cmake ..
make
```
For building tests use `cmake .. -DRESIM_BUILD_TESTING=ON`. <br>
Testing suites will be located in `tests/<cpu_name>/<cpu_name>-test`

## 🏗️ Architecture
### Core Components
```
ReSim/
├── base/inc         # Shared infrastructure
│   ├── memory.h     # Memory management
│   ├── bus.h        # Bus and I/O system
│   ├── io_device.h  # I/O device interface
│   └── compute.h    # Base CPU interface
│
├── chips/           # CPU implementations
│   ├── MOS6502/     # 6502 processor core
│   ├── I8080/       # 8080/Z80 processor core  
│   ├── I8086/       # 8086 processor core
│   └── Z80/         # Z80 processor core
│
├── core/            # macro, functional libraries and types
│
└── tests/           # Test suites
```

### Design Philosophy
- Accuracy First: Prioritize cycle accuracy over convenience
- Performance Focus: Optimize for execution speed
- Maintainability: Clean, documented code over clever tricks
- Consistency: Uniform patterns across all CPU implementations

## 🎮 Example Usage
```cpp
// Sample code demonstrating ReSim integration
#include "ReSim/MOS6502.h"

MOS6502 cpu;
Memory ram(64 * 1024); // 64KB RAM
Bus bus{};

// Prepare infrastructure
ram.Reset();
cpu.Reset();
bus.Attach(&ram, 0x0000, 0xFFFF);
cpu.SetBusInstance(&bus);

// Load and execute program
cpu.LoadROM("program.bin", ram);
cpu.Run();

// Inspect results
printf("Program completed in %u cycles\n", cpu.cycles);
printf("Final state: A=0x%02X, PC=0x%04X\n", cpu.A, cpu.PC);
```

## 🔮 Roadmap & Future Plans
### Short Term (Next Release)
- Complete Intel 8086 instruction set
- Enhanced debugging capabilities
- Improved documentation

### Medium Term
- Basic I/O support
- Z80 implementation
- Simple BIOS framework

### Long Term Vision
- Full system emulation (CPU + peripherals)
- Graphical debugger interface
- Additional architectures (68000, 8051, etc.)
- Plugin system for custom peripherals

## ⚠️ Current Limitations
- No BIOS Support: Cannot run complex software or operating systems
- No I/O: Memory-mapped I/O is in WIP state
- Standalone Environment: Currently runs individual ASM programs only
- Debugging Tools: Basic execution tracing, no graphical debugger

💡 Note: Despite limitations, ReSim excels at running and testing assembly programs, making it ideal for education, prototyping, and low-level software development.

## 🤝 Contributing
We welcome contributions from the community! Whether you're interested in:
- Adding new CPU architectures
- Improving existing emulators
- Writing tests and documentation
- Enhancing performance

## 🙏 Acknowledgments
This project was originally inspired by DavePoo's 6502 Emulator but has evolved into a completely independent implementation with:
- Novel Architecture: Custom instruction decoding and execution flow 
- Enhanced Accuracy: Improved cycle counting and timing
- Multi-CPU Support: Consistent framework across different architectures
- Comprehensive Testing: Extensive test suites for validation
