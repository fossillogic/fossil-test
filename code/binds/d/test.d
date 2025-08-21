// fossil/pizza.d
module fossil.pizza;

import core.stdc.stdlib;
import core.stdc.string;
import core.stdc.stdint;

extern(C) {
    import "test.h";

    int fossil_pizza_start(fossil_pizza_engine_t* engine, int argc, char** argv);
    int fossil_pizza_add_suite(fossil_pizza_engine_t* engine, fossil_pizza_suite_t suite);
    int fossil_pizza_add_case(fossil_pizza_suite_t* suite, fossil_pizza_case_t test_case);
    int fossil_pizza_run_suite(const fossil_pizza_engine_t* engine, fossil_pizza_suite_t* suite);
    int fossil_pizza_run_all(fossil_pizza_engine_t* engine);
    void fossil_pizza_summary(const fossil_pizza_engine_t* engine);
    int32_t fossil_pizza_end(fossil_pizza_engine_t* engine);
}

struct PizzaEngine {
    fossil_pizza_engine_t engine;

    bool start(string[] args) {
        char** argv = cast(char**) malloc(args.length * void.sizeof);
        foreach (i, arg; args)
            argv[i] = cast(char*) arg.toStringz;
        int ret = fossil_pizza_start(&engine, args.length, argv);
        free(argv);
        return ret == FOSSIL_PIZZA_SUCCESS;
    }

    bool addSuite(fossil_pizza_suite_t suite) {
        return fossil_pizza_add_suite(&engine, suite) == FOSSIL_PIZZA_SUCCESS;
    }

    bool addCase(fossil_pizza_suite_t* suite, fossil_pizza_case_t testCase) {
        return fossil_pizza_add_case(suite, testCase) == FOSSIL_PIZZA_SUCCESS;
    }

    bool runSuite(fossil_pizza_suite_t* suite) {
        return fossil_pizza_run_suite(&engine, suite) == FOSSIL_PIZZA_SUCCESS;
    }

    bool runAll() {
        return fossil_pizza_run_all(&engine) == FOSSIL_PIZZA_SUCCESS;
    }

    void summary() {
        fossil_pizza_summary(&engine);
    }

    bool end() {
        return fossil_pizza_end(&engine) == 0;
    }
}
