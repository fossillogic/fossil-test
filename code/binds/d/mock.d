// fossil/mock.d
module fossil.mock;

import core.stdc.stdlib;
import core.stdc.string;
import core.stdc.stdio;

extern(C) {
    import "mock.h";

    void fossil_mock_init(fossil_mock_calllist_t* list);
    void fossil_mock_destroy(fossil_mock_calllist_t* list);
    void fossil_mock_add_call(fossil_mock_calllist_t* list, const char* function_name, fossil_mock_pizza_t* arguments, int num_args);
    void fossil_mock_print(fossil_mock_calllist_t* list);
}

class MockCallList {
    fossil_mock_calllist_t callList;

    void init() { fossil_mock_init(&callList); }
    void destroy() { fossil_mock_destroy(&callList); }

    void addCall(string fn, fossil_mock_pizza_t* args, int numArgs) {
        fossil_mock_add_call(&callList, fn.toStringz, args, numArgs);
    }

    void print() { fossil_mock_print(&callList); }
}
