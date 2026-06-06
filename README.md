# ternary-dissertation-c

Reference C implementation of ternary computing primitives from the SuperInstance dissertation series. Demonstrates Z₃ {-1, 0, +1} algebra operations at bare-metal level.

## Why This Matters

Before building GPU runtimes in Rust, you need to prove the math works. This C implementation provides the simplest, most auditable proofs of ternary algebra — suitable for academic citation and embedded targets.

## What's Inside

- **Core Z₃ algebra**: addition, multiplication, negation using explicit match semantics
- **Ternary matrices**: multiply, transpose, determinant
- **Conservation verification**: prove that {-1,0,+1} operations preserve quantity
- **Bit packing**: 2-bit encoding of ternary values for memory efficiency

## The Five-Layer Stack

```
┌─────────────────┐
│  cudaclaw        │  Persistent GPU kernels, warp consensus, SmartCRDT
├─────────────────┤
│  cuda-oxide      │  Flux → MIR → Pliron → NVVM → PTX compiler
├─────────────────┤
│  flux-core       │  Bytecode VM + A2A agent protocol
├─────────────────┤
│  pincher         │  "Vector DB as runtime, LLM as compiler"
├─────────────────┤
│  open-parallel   │  Async runtime (tokio fork)
└─────────────────┘
```

## Building

```bash
mkdir build && cd build
cmake ..
make
./test_ternary
```

## Design

Z₃ arithmetic MUST use explicit match on all 9 pairs:

```c
int z3_add(int a, int b) {
    switch(a) {
        case -1: return (b == -1) ? -1 : (b == 0) ? -1 : 0;
        case  0: return b;
        case  1: return (b == -1) ? 0 : (b == 0) ? 1 : 1;
    }
    return 0;
}
```

**Wrong**: `(a + b + 3) % 3 - 1` — gives incorrect results for edge cases.

## License

Apache-2.0
