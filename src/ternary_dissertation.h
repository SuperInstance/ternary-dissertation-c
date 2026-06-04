#ifndef TERNARY_DISSERTATION_H
#define TERNARY_DISSERTATION_H

#include <stddef.h>

/* ── Constants ── */
#define TD_MAX_LAWS           5
#define TD_MAX_EVIDENCE       256
#define TD_MAX_SAMPLES        1024
#define TD_CHAPTER_BUF        8192
#define TD_FULLTEXT_BUF       (TD_CHAPTER_BUF * TD_MAX_LAWS + 2048)

#define TD_LAW_1 0   /* Emergence of Negative-Space Intelligence */
#define TD_LAW_2 1   /* Conservation of Absence */
#define TD_LAW_3 2   /* Structural Void Principle */
#define TD_LAW_4 3   /* Ternary Completeness Theorem */
#define TD_LAW_5 4   /* Negative-Space Self-Organization */

/* ── Statistical Test ── */
typedef struct {
    double mean;
    double std_dev;
    double p_value;       /* two-tailed approximate */
    double t_statistic;
    size_t n;
} StatisticalTest;

StatisticalTest td_compute_stats(const double *samples, size_t n, double hypothesized_mean);

/* ── Evidence Collector ── */
typedef struct {
    double  samples[TD_MAX_SAMPLES];
    size_t  count;
    char    description[256];
} EvidenceCollector;

void td_ec_init(EvidenceCollector *ec, const char *description);
int  td_ec_add_sample(EvidenceCollector *ec, double value);
void td_ec_clear(EvidenceCollector *ec);

/* ── Law ── */
typedef struct {
    int   id;                                 /* TD_LAW_1 … TD_LAW_5 */
    char  statement[512];
    EvidenceCollector evidence;
    StatisticalTest   stats;
    int   stats_computed;                     /* flag */
} Law;

void td_law_init(Law *law, int id, const char *statement);
int  td_law_add_evidence(Law *law, double value);
int  td_law_compute_statistics(Law *law, double hypothesized_mean);

/* ── Chapter Generator ── */
int td_generate_chapter(const Law *law, char *out, size_t out_size);

/* ── Dissertation ── */
typedef struct {
    Law  laws[TD_MAX_LAWS];
    int  law_count;
    char full_text[TD_FULLTEXT_BUF];
} Dissertation;

void td_dissertation_init(Dissertation *d);
Law *td_dissertation_add_law(Dissertation *d, int id, const char *statement);
int  td_dissertation_compile(Dissertation *d);
const char *td_dissertation_text(const Dissertation *d);

/* ── Helpers (for tests / simulation) ── */
const char *td_law_name(int id);
const char *td_law_statement(int id);
double td_simulate_emergence(void);
double td_simulate_conservation(void);
double td_simulate_void(void);
double td_simulate_ternary(void);
double td_simulate_self_org(void);

#endif /* TERNARY_DISSERTATION_H */
