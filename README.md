# Ternary Dissertation (C)

The **Ternary Dissertation** library provides the computational framework for five empirical laws of ternary intelligence, including statistical testing, evidence collection, and automated dissertation chapter generation. Written in C with no external dependencies.

## Why It Matters

The five laws — Emergence of Negative-Space Intelligence, Conservation of Absence, Structural Void Principle, Ternary Completeness Theorem, and Negative-Space Self-Organization — form the theoretical foundation of the SuperInstance framework. But theory without empirical validation is philosophy, not science. This library provides the machinery to test each law: collect experimental samples, compute statistical tests (t-statistics, p-values, confidence intervals), and generate formatted chapters with the results. It bridges the gap between code that implements ternary systems and the scientific documentation that explains *why* those systems work.

## How It Works

### The Five Laws

1. **Emergence of Negative-Space Intelligence (TD_LAW_1)**: Intelligence arises from what is avoided, not what is chosen. Tested by measuring whether avoidance patterns emerge spontaneously in ternary agent populations.

2. **Conservation of Absence (TD_LAW_2)**: The avoidance ratio is conserved across scales — analogous to Noether's theorem where symmetry implies conservation. Tested via cross-scale variance measurement.

3. **Structural Void Principle (TD_LAW_3)**: Voids (gaps in the action space) carry structural information proportional to their size. Tested via inference engine knowledge estimates.

4. **Ternary Completeness Theorem (TD_LAW_4)**: A complete description of an agent's intelligence requires all three states {−1, 0, +1}. Binary descriptions are provably incomplete. Tested via information-theoretic comparison.

5. **Negative-Space Self-Organization (TD_LAW_5)**: Avoidance patterns organize themselves into stable structures without external coordination. Tested via autocorrelation and entropy measurement.

### Statistical Testing

For each law, the library computes:

```c
typedef struct {
    double mean;
    double std_dev;
    double p_value;       // two-tailed approximate
    double t_statistic;
    size_t n;
} StatisticalTest;
```

The t-statistic tests whether the sample mean differs from a hypothesized value:

```
t = (x̄ − μ₀) / (s / √n)
```

The p-value is approximated via the t-distribution with n−1 degrees of freedom. A law is supported when p < 0.05.

### Evidence Collection

```c
EvidenceCollector ec;
td_ec_init(&ec, "Avoidance ratio at N=1000");
for (int trial = 0; trial < 100; trial++) {
    td_ec_add_sample(&ec, simulate_avoidance_ratio(1000));
}
```

Each `Law` struct holds one `EvidenceCollector` and the resulting `StatisticalTest`.

### Dissertation Compilation

The `Dissertation` struct compiles all five laws into a single document:

```
td_dissertation_compile() → produces formatted text
td_dissertation_text()    → returns the full text
```

Each chapter includes: statement of the law, experimental methodology, evidence summary, statistical test results, and a conclusion paragraph auto-generated from the p-value.

## Quick Start

```c
#include "ternary_dissertation.h"
#include <stdio.h>

int main(void) {
    Dissertation d;
    td_dissertation_init(&d);

    // Add and populate Law 1
    Law *law1 = td_dissertation_add_law(&d, TD_LAW_1,
        "Intelligence arises from systematic avoidance patterns");
    for (int i = 0; i < 100; i++) {
        td_law_add_evidence(law1, td_simulate_emergence());
    }
    td_law_compute_statistics(law1, 0.5);

    // Compile and print
    td_dissertation_compile(&d);
    printf("%s\n", td_dissertation_text(&d));

    return 0;
}
```

Compile: `gcc -lm -o dissertation src/ternary_dissertation.c && ./dissertation`

## API

| Function | Description |
|----------|-------------|
| `td_dissertation_init` | Initialize empty dissertation |
| `td_dissertation_add_law` | Add a law with statement |
| `td_dissertation_compile` | Generate all chapters |
| `td_dissertation_text` | Get full formatted text |
| `td_law_add_evidence` | Add a sample to a law |
| `td_law_compute_statistics` | Run t-test on evidence |
| `td_compute_stats` | Compute mean, std, p-value |
| `td_simulate_*` | Monte Carlo simulators per law |

## Architecture Notes

The Ternary Dissertation is the formal scientific expression of the γ + η = C framework. Each law describes a different facet of how γ (constructive) and η (avoidant) intelligence combine into competence C. The statistical testing infrastructure ensures these claims are empirically grounded rather than merely asserted — each law must survive a t-test against experimental data. The chapter generator embodies γ (construction of knowledge) while the evidence collection and falsification attempts embody η (elimination of wrong hypotheses). See [ARCHITECTURE.md](https://github.com/SuperInstance/SuperInstance/blob/main/ARCHITECTURE.md).

## References

1. Student (Gosset, W. S.) (1908). "The Probable Error of a Mean." *Biometrika*, 6(1), 1–25. — The t-test.
2. Popper, K. (1959). *The Logic of Scientific Discovery*. — Falsification as the criterion of scientific status.
3. Fisher, R. A. (1925). *Statistical Methods for Research Workers*. — Foundations of significance testing.

## License

MIT
