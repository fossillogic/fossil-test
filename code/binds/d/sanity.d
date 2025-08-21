// fossil/sanity.d
module fossil.sanity;

import core.stdc.stdlib;
import core.stdc.string;

extern(C) {
    import "sanity.h";

    int fossil_sanity_sys_execute(const char* command);
    int fossil_sanity_sys_getpid(void);
    void fossil_sanity_sys_sleep(int milliseconds);
    int fossil_sanity_sys_file_exists(const char* filename);
    int fossil_sanity_sys_create_file(const char* filename);
    char* fossil_sanity_sys_read_file(const char* filename);
    int fossil_sanity_sys_write_file(const char* filename, const char* data);
    int fossil_sanity_sys_delete_file(const char* filename);
    const char* fossil_sanity_sys_getenv(const char* name);
    int fossil_sanity_sys_setenv(const char* name, const char* value);
    char* fossil_sanity_sys_timestamp(void);
    long long fossil_sanity_sys_uptime_ms(void);
    int fossil_sanity_sys_is_running(int pid);
    int fossil_sanity_sys_kill(int pid);
}

class Sanity {
    static int execute(string cmd) {
        return fossil_sanity_sys_execute(cmd.toStringz);
    }

    static int pid() {
        return fossil_sanity_sys_getpid();
    }

    static void sleep(int ms) {
        fossil_sanity_sys_sleep(ms);
    }

    static bool fileExists(string path) {
        return fossil_sanity_sys_file_exists(path.toStringz) != 0;
    }

    static int createFile(string path) {
        return fossil_sanity_sys_create_file(path.toStringz);
    }

    static string readFile(string path) {
        char* buf = fossil_sanity_sys_read_file(path.toStringz);
        if (!buf) return "";
        string result = to!string(buf);
        free(buf);
        return result;
    }

    static int writeFile(string path, string data) {
        return fossil_sanity_sys_write_file(path.toStringz, data.toStringz);
    }

    static bool isRunning(int pid) {
        return fossil_sanity_sys_is_running(pid) == 1;
    }

    static bool kill(int pid) {
        return fossil_sanity_sys_kill(pid) == 0;
    }
}
