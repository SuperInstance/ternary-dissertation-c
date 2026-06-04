#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../src/ternary_dissertation.h"

static int tests_passed = 0;
static int tests_failed = 0;

#define ASSERT(cond, msg) do {                                      \
    if (cond) { tests_passed++; printf("  ✓ %s\n", msg); }         \
    else     { tests_failed++; printf("  ✗ %s\n", msg); }          \
} while(0)

#define ASSERT_EQ_DBL(a, b, eps, msg) \
    ASSERT(fabs((a) - (b)) < (eps), msg)

/* ──────────────────────────────────────────── */

static void test_law_init(void)
{
    printf("Test 1: Law initialization\n");
    Law law;
    td_law_init(&law, TD_LAW_1, "Test statement");
    ASSERT(law.id == TD_LAW_1, "Law ID set correctly");
    ASSERT(strcmp(law.statement, "Test statement") == 0, "Statement set correctly");
    ASSERT(law.evidence.count == 0, "Evidence count starts at 0");
    ASSERT(law.stats_computed == 0, "Stats not computed initially");
}

static void test_evidence_collector(void)
{
    printf("Test 2: Evidence collector basic operations\n");
    EvidenceCollector ec;
    td_ec_init(&ec, "test evidence");
    ASSERT(ec.count == 0, "Starts empty");
    ASSERT(strcmp(ec.description, "test evidence") == 0, "Description set");

    int r = td_ec_add_sample(&ec, 3.14);
    ASSERT(r == 0, "Add sample succeeds");
    ASSERT(ec.count == 1, "Count incremented");
    ASSERT_EQ_DBL(ec.samples[0], 3.14, 1e-9, "Sample stored correctly");
}

static void test_evidence_overflow(void)
{
    printf("Test 3: Evidence overflow protection\n");
    EvidenceCollector ec;
    td_ec_init(&ec, "overflow test");
    for (size_t i = 0; i < TD_MAX_SAMPLES; i++)
        td_ec_add_sample(&ec, (double)i);
    int r = td_ec_add_sample(&ec, 999.0);
    ASSERT(r == -1, "Returns -1 on overflow");
    ASSERT(ec.count == TD_MAX_SAMPLES, "Count capped at max");
}

static void test_evidence_clear(void)
{
    printf("Test 4: Evidence clear\n");
    EvidenceCollector ec;
    td_ec_init(&ec, "clear test");
    td_ec_add_sample(&ec, 1.0);
    td_ec_add_sample(&ec, 2.0);
    td_ec_clear(&ec);
    ASSERT(ec.count == 0, "Count reset to 0");
}

static void test_statistics_basic(void)
{
    printf("Test 5: Statistical test computation\n");
    double data[] = {2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0};
    size_t n = sizeof(data) / sizeof(data[0]);
    StatisticalTest st = td_compute_stats(data, n, 4.0);

    ASSERT_EQ_DBL(st.mean, 5.0, 1e-9, "Mean computed correctly");
    ASSERT_EQ_DBL(st.std_dev, 2.1381, 0.01, "Std dev approximately correct");
    ASSERT(st.n == n, "Sample count correct");
    ASSERT(st.p_value >= 0.0 && st.p_value <= 1.0, "P-value in valid range");
}

static void test_statistics_single(void)
{
    printf("Test 6: Statistics with single sample\n");
    double data[] = {42.0};
    StatisticalTest st = td_compute_stats(data, 1, 42.0);
    ASSERT_EQ_DBL(st.mean, 42.0, 1e-9, "Mean of single value");
    ASSERT_EQ_DBL(st.std_dev, 0.0, 1e-9, "Std dev is 0 for single value");
}

static void test_law_full_workflow(void)
{
    printf("Test 7: Law full workflow (add evidence + compute stats)\n");
    Law law;
    td_law_init(&law, TD_LAW_1, td_law_statement(TD_LAW_1));

    srand(42);
    for (int i = 0; i < 100; i++)
        td_law_add_evidence(&law, td_simulate_emergence());

    ASSERT(law.evidence.count == 100, "100 samples added");
    int r = td_law_compute_statistics(&law, 0.0);
    ASSERT(r == 0, "Stats computation succeeds");
    ASSERT(law.stats_computed == 1, "Stats flag set");
    ASSERT(law.stats.mean > 0.5, "Emergence mean is positive (intelligence emerges)");
    ASSERT(law.stats.p_value < 0.05, "Result is statistically significant");
}

static void test_law_stats_insufficient(void)
{
    printf("Test 8: Statistics with insufficient data\n");
    Law law;
    td_law_init(&law, TD_LAW_2, "test");
    td_law_add_evidence(&law, 1.0);
    int r = td_law_compute_statistics(&law, 0.0);
    ASSERT(r == -1, "Fails with only 1 sample");
}

static void test_chapter_generation(void)
{
    printf("Test 9: Chapter generation\n");
    Law law;
    td_law_init(&law, TD_LAW_3, td_law_statement(TD_LAW_3));

    srand(123);
    for (int i = 0; i < 50; i++)
        td_law_add_evidence(&law, td_simulate_void());
    td_law_compute_statistics(&law, 0.0);

    char buf[TD_CHAPTER_BUF];
    int len = td_generate_chapter(&law, buf, sizeof(buf));
    ASSERT(len > 0, "Chapter generated (positive length)");
    ASSERT(strstr(buf, "Structural Void Principle") != NULL, "Contains law name");
    ASSERT(strstr(buf, "p-value") != NULL, "Contains p-value");
    ASSERT(strstr(buf, "mean") != NULL, "Contains mean");
}

static void test_law_metadata(void)
{
    printf("Test 10: Law metadata helpers\n");
    ASSERT(strcmp(td_law_name(TD_LAW_1), "Emergence of Negative-Space Intelligence") == 0,
           "Law 1 name");
    ASSERT(strcmp(td_law_name(TD_LAW_4), "Ternary Completeness Theorem") == 0,
           "Law 4 name");
    ASSERT(strlen(td_law_statement(TD_LAW_5)) > 0, "Law 5 statement non-empty");
    ASSERT(strcmp(td_law_name(99), "Unknown Law") == 0, "Invalid ID returns Unknown");
}

static void test_dissertation_compile(void)
{
    printf("Test 11: Full dissertation compilation\n");
    Dissertation d;
    td_dissertation_init(&d);

    srand(2024);
    typedef double (*sim_fn)(void);
    sim_fn sims[5] = {
        td_simulate_emergence,
        td_simulate_conservation,
        td_simulate_void,
        td_simulate_ternary,
        td_simulate_self_org
    };
    double hypo_means[5] = {0.0, 0.0, 0.0, 1.0, 0.0};

    for (int i = 0; i < 5; i++) {
        Law *law = td_dissertation_add_law(&d, i, td_law_statement(i));
        ASSERT(law != NULL, "Law added to dissertation");
        for (int j = 0; j < 200; j++)
            td_law_add_evidence(law, sims[i]());
        td_law_compute_statistics(law, hypo_means[i]);
    }

    int len = td_dissertation_compile(&d);
    ASSERT(len > 0, "Dissertation compiled");
    ASSERT(d.law_count == 5, "All 5 laws present");

    const char *text = td_dissertation_text(&d);
    ASSERT(strstr(text, "TERNARY DISSERTATION") != NULL, "Has title");
    ASSERT(strstr(text, "Chapter 1") != NULL, "Has Chapter 1");
    ASSERT(strstr(text, "Chapter 5") != NULL, "Has Chapter 5");
    ASSERT(strstr(text, "Conclusion") != NULL, "Has Conclusion");
    ASSERT(strstr(text, "statistically significant") != NULL, "Contains significance call");
}

static void test_dissertation_max_laws(void)
{
    printf("Test 12: Dissertation max law limit\n");
    Dissertation d;
    td_dissertation_init(&d);
    for (int i = 0; i < TD_MAX_LAWS; i++)
        td_dissertation_add_law(&d, i, "law");
    Law *extra = td_dissertation_add_law(&d, 0, "overflow");
    ASSERT(extra == NULL, "Returns NULL beyond max laws");
    ASSERT(d.law_count == TD_MAX_LAWS, "Count stays at max");
}

/* ──────────────────────────────────────────── */

int main(void)
{
    printf("╔═══════════════════════════════════════╗\n"
           "║  ternary-dissertation-c  test suite   ║\n"
           "╚═══════════════════════════════════════╝\n\n");

    test_law_init();
    test_evidence_collector();
    test_evidence_overflow();
    test_evidence_clear();
    test_statistics_basic();
    test_statistics_single();
    test_law_full_workflow();
    test_law_stats_insufficient();
    test_chapter_generation();
    test_law_metadata();
    test_dissertation_compile();
    test_dissertation_max_laws();

    printf("\n─────────────────────────────\n");
    printf("Results: %d passed, %d failed, %d total\n",
           tests_passed, tests_failed, tests_passed + tests_failed);
    printf("─────────────────────────────\n");

    return tests_failed ? 1 : 0;
}
