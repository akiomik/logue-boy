# logue-boy

Game Boy-inspired oscillators for KORG logue synthesizers (minilogue xd, prologue, and Nu:Tekt NTS-1 digital kit).

## Overview

**logue-boy** is a collection of three custom oscillators that recreate the iconic sound chip characteristics of Nintendo's Game Boy handheld console. These oscillators are built using the KORG logue SDK and provide authentic 8-bit sound generation for modern synthesizers.

The Game Boy's sound hardware featured a simple but characterful audio processing unit with four sound channels. This project recreates three of those channels:
- **Pulse Wave Channel** with variable duty cycle
- **Wave Channel** with custom wavetables (inspired by Pokémon Gold/Silver)
- **Noise Channel** with configurable shift register

## Oscillators

### 1. Pulse Oscillator

Emulates the Game Boy's pulse wave channels (channels 1 and 2) with selectable duty cycles.

**Features:**
- Four duty cycle options: 12.5%, 25%, 50%, and 75%
- Envelope-based attenuation effect for authentic sound shaping
- Perfect for classic chiptune leads and bass lines

**Parameters:**
- **Shape**: Selects duty cycle (12.5% / 25% / 50% / 75%)
- **Shift+Shape**: Controls attenuation depth (0-100%)

### 2. Noise Oscillator

Recreates the Game Boy's noise channel (channel 4) using a Linear Feedback Shift Register (LFSR).

**Features:**
- 15-bit LFSR implementation matching Game Boy hardware
- Two noise modes: short (7-bit) and long (15-bit)
- Pitch tracking for tonal noise effects

**Parameters:**
- **Shape**: Switches between short mode (< 50%) and long mode (≥ 50%)

**Technical Details:**
- Uses XOR feedback between bits 0 and 1
- Short mode creates more periodic, tonal noise
- Long mode produces less repetitive, white-noise-like sound

### 3. PokeGold Oscillator

Implements the Game Boy's wave channel (channel 3) with wavetables inspired by Pokémon Gold and Silver sound design.

**Features:**
- 10 unique 32-sample wavetables
- Variable bit resolution (1-16 bit) for lo-fi effects
- Linear interpolation between wavetable samples

**Parameters:**
- **Shape**: Selects wavetable (0-9)
- **Shift+Shape**: Controls bit resolution (1-16 bit)

**Wavetables:**
Each wavetable contains 32 samples with 4-bit values (0-15), normalized to audio range [-1.0, 1.0]. The wavetables recreate various timbres used in Game Boy games, from smooth sine-like waves to more complex harmonic content.

## Supported Platforms

All oscillators are compatible with:
- **KORG minilogue xd**
- **KORG prologue**
- **KORG Nu:Tekt NTS-1 digital kit**

## Building

### Prerequisites

1. **KORG logue SDK**: The repository includes the SDK as a git submodule in `libs/logue-sdk/`
2. **GNU ARM Embedded Toolchain**: Required for cross-compilation
3. **GNU Make**: For building the oscillators
4. **logue-cli** (optional): For validating built units

### Setup

#### 1. Clone the repository with submodules

```bash
git clone --recursive https://github.com/yourusername/logue-boy.git
cd logue-boy
```

#### 2. Install ARM Toolchain

The logue SDK requires the GNU ARM Embedded Toolchain version 5.4 (5-2016-q3-update) for cross-compilation.

**macOS:**

```bash
cd libs/logue-sdk/tools/gcc
./get_gcc_osx.sh
cd ../../../..
```

Note: On Apple Silicon Macs, the Intel x86_64 toolchain will run via Rosetta 2.

**Linux:**

```bash
cd libs/logue-sdk/tools/gcc
./get_gcc_linux.sh
cd ../../../..
```

**Windows (MSYS2):**

```bash
cd libs/logue-sdk/tools/gcc
./get_gcc_msys.sh
cd ../../../..
```

#### 3. Install logue-cli (optional)

The logue-cli tool is used for validating built unit files and can also load them onto your device.

**macOS:**

```bash
cd libs/logue-sdk/tools/logue-cli
./get_logue_cli_osx.sh
cd ../../../..
```

**Linux:**

```bash
cd libs/logue-sdk/tools/logue-cli
./get_logue_cli_linux.sh
cd ../../../..
```

**Windows (MSYS2):**

```bash
cd libs/logue-sdk/tools/logue-cli
./get_logue_cli_msys.sh
cd ../../../..
```

### Build Instructions

**Option 1: Build all oscillators for all platforms**

Use the provided build script to build all 3 oscillators for all 3 platforms (9 units total):

```bash
./tools/build.sh
```

This will build and validate all units. Each build outputs `.mnlgxdunit`, `.prlgunit`, or `.ntkdigunit` files depending on the platform.

**Option 2: Build specific oscillators**

Build individual oscillators by navigating to their platform-specific directories:

```bash
# Example: Build pulse oscillator for minilogue xd
cd osc/pulse/platform/minilogue-xd
make

# Validate the built unit (requires logue-cli)
make check
```

Available oscillators and platforms:
- Oscillators: `pulse`, `noise`, `pokegold`
- Platforms: `minilogue-xd`, `prologue`, `nutekt-digital`
- Path pattern: `osc/{oscillator}/platform/{platform}/`

### Output

Compiled oscillators generate platform-specific unit files:
- **minilogue xd**: `.mnlgxdunit`
- **prologue**: `.prlgunit`
- **Nu:Tekt NTS-1**: `.ntkdigunit`

These files can be loaded onto your KORG device using:
- KORG's official librarian software
- logue-cli tool (see Installation section below)

## Testing

The project includes unit tests for each oscillator using Google Test framework.

### Running Tests

1. Install Meson and Ninja build system:

```bash
pip3 install meson ninja
```

2. Setup and run tests:

```bash
meson setup builddir
meson test -C builddir
```

Or run individual tests:

```bash
./builddir/pulse_test
./builddir/noise_test
./builddir/pokegold_test
```

## Installation

1. Build the oscillator for your platform
2. Use KORG's librarian software or logue-cli to transfer the `.ntkdigunit` file to your device
3. Select the oscillator from the user oscillator slots on your synthesizer

Refer to KORG's official documentation for detailed installation instructions.

## Technical Background

### Game Boy Sound Hardware

The original Game Boy (DMG-01) featured a custom sound chip with four channels:
- **Channel 1**: Pulse wave with sweep
- **Channel 2**: Pulse wave
- **Channel 3**: Programmable wave
- **Channel 4**: Noise

This project focuses on recreating the core sound generation algorithms rather than the complete hardware behavior (envelopes, sweep effects, etc.), allowing these sounds to be controlled by the logue synthesizer's own envelope and modulation capabilities.

### Implementation Details

- **Sample Rate**: 48kHz (logue platform standard)
- **Bit Depth**: 32-bit floating point internal processing
- **Wave Resolution**: Matched to Game Boy specifications (4-bit wavetable samples, LFSR periods)
- **Language**: C++11

## License

Copyright 2021 Akiomi Kamakura

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE) for details.

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.

## Links

- [KORG logue SDK](https://github.com/korginc/logue-sdk)
- [Game Boy Sound Hardware](https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware)
