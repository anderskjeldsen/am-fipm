# AmLang Fixed Point Math Library (am-fipm)

This repository contains the Fixed Point Math (FIPM) library for the AmLang programming language ecosystem. AmLang is a modern object-oriented programming language designed for systems programming with cross-platform compatibility, particularly targeting niche platforms like AmigaOS, MorphOS, and legacy systems.

## Repository Overview

**am-fipm** provides high-performance fixed-point mathematics operations for AmLang applications running on platforms without floating-point units (FPUs) or where precise decimal arithmetic is required. This library is essential for mathematical calculations on classic computing platforms like AmigaOS 68k systems and embedded environments.

### Key Features

- **Fixed-Point Arithmetic**: High-precision mathematical operations without floating-point hardware
- **Lookup Tables**: Pre-computed sine and square root tables for fast trigonometric operations
- **Cross-Platform**: Optimized for 68k, ARM, x86, and PowerPC architectures
- **Memory Efficient**: Designed for resource-constrained embedded and legacy systems
- **Performance Optimized**: Native C implementations for critical mathematical functions
- **Retro Computing**: Essential for classic Amiga, Atari, and other legacy platforms

### Core Classes

- **`SinusTable`**: Pre-computed sine/cosine lookup table for trigonometric operations
- **`SqrtTable`**: Pre-computed square root lookup table for efficient square root calculations

## Mathematical Concepts

### Fixed-Point Representation

Fixed-point numbers represent fractional values using integer arithmetic:

```
Fixed-Point = Integer × 2^(-scale)
```

Common scales:
- **16.16 format**: 16 bits integer, 16 bits fractional (scale = 16)
- **8.24 format**: 8 bits integer, 24 bits fractional (scale = 24)

### Why Fixed-Point?

1. **No FPU Required**: Works on processors without floating-point units
2. **Deterministic**: Exact results, no floating-point precision issues  
3. **Fast**: Integer operations are faster than floating-point on many platforms
4. **Compact**: Smaller code size compared to software floating-point libraries

## API Usage Patterns

### Square Root Calculations

```amlang
import Am.Fipm
import Am.Lang

// Create square root lookup table
var sqrtTable = SqrtTable.newSqrtTable(100000UI)

// Calculate square root of 10000 (result in 16.16 fixed-point)
var input = 10000UI
var sqrtResult = sqrtTable.getSqrt(input)

// Convert back to integer (remove fractional part)
var integerSqrt = sqrtResult >> 16
"Square root of ${input} is approximately ${integerSqrt}".println()
```

### Trigonometric Operations

```amlang
import Am.Fipm
import Am.Lang

// Create sine lookup table with 360 entries (one per degree)
var sinusTable = SinusTable.newSinusTable(360)

// Calculate sine of 45 degrees (result in fixed-point format)
var angle = 45  // degrees
var sineValue = sinusTable.getSin(angle)

// Convert to readable format
var sineFloat = sineValue.toDouble() / 65536.0  // Convert from 16.16 format
"Sine of ${angle} degrees = ${sineFloat}".println()
```

### Fixed-Point Arithmetic Example

```amlang
class FixedPointMath {
    import Am.Lang
    import Am.Fipm
    
    // 16.16 fixed-point format helpers
    static fun toFixed(value: Double): Int {
        return (value * 65536.0).toInt()
    }
    
    static fun fromFixed(fixed: Int): Double {
        return fixed.toDouble() / 65536.0
    }
    
    static fun calculateCircleArea(radius: UInt): UInt {
        var sqrtTable = SqrtTable.newSqrtTable(radius * radius)
        
        // π ≈ 3.14159 in 16.16 fixed-point
        var pi = 205887  // 3.14159 * 65536
        
        // Area = π * r²
        var radiusSquared = radius * radius
        var area = (pi * radiusSquared) >> 16  // Divide by 2^16 to maintain scale
        
        return area
    }
}
```

### Gaming/Graphics Applications

```amlang
class RetroGraphics {
    import Am.Fipm
    
    private var sinTable: SinusTable
    private var cosTable: SinusTable  // Offset by 90 degrees
    
    fun initialize() {
        this.sinTable = SinusTable.newSinusTable(360)
        // Cosine is sine offset by 90 degrees
        this.cosTable = SinusTable.newSinusTable(360)
    }
    
    fun rotatePoint(x: Int, y: Int, angle: Int): Point {
        var sinValue = this.sinTable.getSin(angle)
        var cosValue = this.cosTable.getSin((angle + 90) % 360)
        
        // Rotation matrix in fixed-point
        var newX = ((x * cosValue) - (y * sinValue)) >> 16
        var newY = ((x * sinValue) + (y * cosValue)) >> 16
        
        return new Point(newX, newY)
    }
}
```

## Project Structure

```
src/Am/Fipm/
├── SinusTable.aml          # Trigonometric lookup table
├── SqrtTable.aml           # Square root lookup table
└── Startup.aml             # Demo/test application

src/native-c/
├── libc/Am/Fipm/          # Common C implementations
├── amigaos/Am/Fipm/       # AmigaOS 68k optimizations
├── macos/Am/Fipm/         # macOS implementations
└── linux-x64/Am/Fipm/    # Linux x64 implementations
```

## Building and Testing

### Prerequisites

- AmLang compiler (`amlc`) v0.6.4 or later
- AmLang core library (`am-lang-core`) as dependency
- Platform-specific C compilers for cross-compilation

### Build Commands

```bash
# Build for current platform
java -jar amlc.jar build . -bt linux-x64

# Build for AmigaOS 68k (requires Docker)
java -jar amlc.jar build . -bt amigaos_docker

# Build for macOS ARM (Apple Silicon)
java -jar amlc.jar build . -bt macos-arm
```

### Running Tests

```bash
# Run the demo application
cd builds/bin/linux-x64
./app

# Expected output:
# Sqrt of 100 is 10
# Sqrt of 123456 is 351
```

## Development Guidelines

### Fixed-Point Best Practices

1. **Consistent Scale**: Use the same fixed-point scale throughout calculations
   ```amlang
   // CORRECT: Consistent 16.16 format
   var a = 3.14 * 65536  // Convert to 16.16
   var b = 2.71 * 65536  // Convert to 16.16
   var result = (a * b) >> 16  // Maintain scale
   
   // WRONG: Mixed scales
   var a = 3.14 * 65536   // 16.16 format
   var b = 2.71 * 256     // 8.8 format - inconsistent!
   ```

2. **Overflow Prevention**:
   ```amlang
   // Check for overflow before multiplication
   if (a > (Int.maxValue / b)) {
       throw new Exception("Multiplication would overflow")
   }
   var result = (a * b) >> 16
   ```

3. **Precision Management**:
   ```amlang
   // Use appropriate table sizes for required precision
   var smallTable = SqrtTable.newSqrtTable(1000UI)    // Fast, less memory
   var largeTable = SqrtTable.newSqrtTable(1000000UI) // Slower, more precision
   ```

### Performance Optimization

- **Table Size**: Balance memory usage vs. calculation range
- **Native Methods**: Critical math operations implemented in optimized C
- **68k Optimizations**: Special assembly routines for Amiga platforms
- **Cache-Friendly**: Lookup tables designed for good cache locality

### Platform-Specific Considerations

- **AmigaOS 68k**: No FPU, optimized for 16-bit operations
- **MorphOS PowerPC**: Some FPU available, fixed-point still beneficial
- **ARM Embedded**: Good integer performance, ideal for fixed-point
- **x86/x64**: Used for development and testing

## Platform Support

| Platform | Status | Optimizations | Table Support |
|----------|---------|---------------|---------------|
| Linux x64 | ✅ Full | Standard C | Sqrt, Sinus |
| macOS ARM64 | ✅ Full | ARM optimizations | Sqrt, Sinus |
| AmigaOS 68k | ✅ Full | 68k assembly | Sqrt, Sinus |
| MorphOS PPC | 🚧 Partial | PowerPC optimizations | Sqrt, Sinus |
| Linux ARM64 | 🚧 Partial | Standard C | Sqrt, Sinus |
| AROS x86-64 | 🚧 Partial | Standard C | Sqrt, Sinus |

## Dependencies

- **am-lang-core**: Core AmLang standard library
  - `Am.Lang.*`: Basic types and functionality
  - Memory management and reference counting
  - Exception handling

## Mathematical Operations Reference

### Square Root Table

```amlang
// Create table for values 0 to maxValue
var table = SqrtTable.newSqrtTable(maxValue: UInt)

// Get square root (returns 16.16 fixed-point)
var sqrt = table.getSqrt(value: UInt): UInt
```

### Sine Table

```amlang
// Create sine table with specified resolution
var table = SinusTable.newSinusTable(tableSize: Int)

// Get sine value for angle index
var sineValue = table.getSin(angleIndex: Int): Int
```

### Fixed-Point Conversion Utilities

```amlang
// Convert floating-point to 16.16 fixed-point
fun toFixed16_16(value: Double): Int {
    return (value * 65536.0).toInt()
}

// Convert 16.16 fixed-point to floating-point
fun fromFixed16_16(fixed: Int): Double {
    return fixed.toDouble() / 65536.0
}

// Multiply two fixed-point numbers
fun fixedMultiply(a: Int, b: Int): Int {
    return (a.toLong() * b.toLong() >> 16).toInt()
}

// Divide two fixed-point numbers
fun fixedDivide(a: Int, b: Int): Int {
    return ((a.toLong() << 16) / b.toLong()).toInt()
}
```

## Use Cases and Applications

### Retro Gaming
- Sprite rotation and scaling
- Physics calculations
- Collision detection
- Animation interpolation

### Embedded Systems
- Sensor data processing
- Control system calculations
- Digital signal processing
- Real-time mathematical operations

### Legacy Platforms
- AmigaOS graphics programming
- Atari ST/TT mathematics
- Classic game console development
- Embedded microcontroller applications

## Common Issues and Solutions

### Table Size vs. Memory
**Problem**: Large lookup tables consume too much memory
**Solution**: Use smaller tables with interpolation or on-demand calculation

### Precision Loss
**Problem**: Fixed-point calculations lose precision
**Solution**: Use higher bit precision (e.g., 8.24 instead of 16.16) for critical calculations

### Overflow in Multiplication
**Problem**: Fixed-point multiplication causes integer overflow
**Solution**: Use 64-bit intermediate values and proper scaling

### Performance on Modern Systems
**Problem**: Fixed-point may be slower than hardware floating-point on modern CPUs
**Solution**: Use conditional compilation - fixed-point for legacy, floating-point for modern

## Examples and Learning Resources

1. **Mathematical Demos**: Built-in test applications showing square root and trigonometric calculations
2. **Fixed-Point Arithmetic**: Practical examples of fixed-point number manipulation
3. **Gaming Applications**: Examples suitable for retro game development
4. **Embedded Use Cases**: Resource-constrained mathematical processing

## Contributing Guidelines

1. **Cross-Platform Testing**: Verify functionality on both modern and legacy platforms
2. **Performance Focus**: Optimize for speed and memory usage on constrained systems
3. **Mathematical Accuracy**: Ensure lookup tables provide sufficient precision
4. **Assembly Optimizations**: Consider platform-specific assembly for critical functions
5. **Documentation**: Provide clear examples for mathematical concepts

## Version Compatibility

- **AmLang Compiler**: Requires v0.6.4+ for proper native method support
- **am-lang-core**: Must be compatible version for basic math operations
- **Legacy Platforms**: Designed to work on systems from the 1980s onwards

---

This library is part of the AmLang ecosystem. For broader context and cross-repository development, see the main AmLang workspace documentation.