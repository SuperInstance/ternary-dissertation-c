# ternary-dissertation-c

C implementation of the dissertation engine — generates structured output proving the 5 laws of negative-space intelligence.

## Components

- **Law** — represent one of the 5 laws (statement, evidence, statistics)
- **EvidenceCollector** — gather evidence from simulation runs
- **StatisticalTest** — perform basic statistical tests (mean, std, p-value approximation)
- **ChapterGenerator** — generate formatted text chapters proving each law
- **Dissertation** — assemble all chapters into a complete document

## Build & Test

```bash
gcc -o test_dissertation tests/test_dissertation.c src/ternary_dissertation.c -lm -Wall -O2
./test_dissertation
```

## The Five Laws

1. **Emergence of Negative-Space Intelligence** — Intelligence emerges from absent information
2. **Conservation of Absence** — Total absence in closed ternary systems is conserved
3. **Structural Void Principle** — Empty structures exhibit definable geometric properties
4. **Ternary Completeness Theorem** — Complete ternary systems require exactly three orthogonal states
5. **Negative-Space Self-Organization** — Negative-space structures spontaneously organize
