// fossil/benchmark.d
module fossil.benchmark;

import core.stdc.stdlib;
import core.stdc.string;
import core.stdc.time;

extern(C) {
    import "mark.h";

    void fossil_benchmark_init(fossil_mark_t* benchmark, const char* name);
    void fossil_benchmark_start(fossil_mark_t* benchmark);
    void fossil_benchmark_stop(fossil_mark_t* benchmark);
    double fossil_benchmark_elapsed_seconds(const fossil_mark_t* benchmark);
    double fossil_benchmark_min_time(const fossil_mark_t* benchmark);
    double fossil_benchmark_max_time(const fossil_mark_t* benchmark);
    double fossil_benchmark_avg_time(const fossil_mark_t* benchmark);
    void fossil_benchmark_reset(fossil_mark_t* benchmark);
    void fossil_benchmark_report(const fossil_mark_t* benchmark);
}

class Benchmark {
    fossil_mark_t mark;

    this(string name) {
        fossil_benchmark_init(&mark, name.toStringz);
    }

    void start() { fossil_benchmark_start(&mark); }
    void stop() { fossil_benchmark_stop(&mark); }

    double elapsed() { return fossil_benchmark_elapsed_seconds(&mark); }
    double min() { return fossil_benchmark_min_time(&mark); }
    double max() { return fossil_benchmark_max_time(&mark); }
    double avg() { return fossil_benchmark_avg_time(&mark); }

    void reset() { fossil_benchmark_reset(&mark); }
    void report() { fossil_benchmark_report(&mark); }
}
