# fossil_mark.py
import ctypes
from ctypes import c_char_p, c_double, c_int, c_uint64, Structure, POINTER, byref
import os

# Load shared library
lib_path = os.path.join(os.path.dirname(__file__), "../../build/libfossil_benchmark.so")
lib = ctypes.CDLL(os.path.abspath(lib_path))

# --- Structures ---
class fossil_mark_t(Structure):
    _fields_ = [
        ("name", c_char_p),
        ("start_time", ctypes.c_long),  # clock_t is usually long
        ("end_time", ctypes.c_long),
        ("num_samples", c_int),
        ("total_duration", c_double),
        ("min_duration", c_double),
        ("max_duration", c_double),
        ("running", c_int),
    ]

class fossil_scoped_mark_t(Structure):
    _fields_ = [
        ("benchmark", POINTER(fossil_mark_t)),
    ]

# --- Function bindings ---
lib.fossil_benchmark_init.argtypes = [POINTER(fossil_mark_t), c_char_p]
lib.fossil_benchmark_init.restype = None

lib.fossil_benchmark_start.argtypes = [POINTER(fossil_mark_t)]
lib.fossil_benchmark_start.restype = None

lib.fossil_benchmark_stop.argtypes = [POINTER(fossil_mark_t)]
lib.fossil_benchmark_stop.restype = None

lib.fossil_benchmark_elapsed_seconds.argtypes = [POINTER(fossil_mark_t)]
lib.fossil_benchmark_elapsed_seconds.restype = c_double

lib.fossil_benchmark_min_time.argtypes = [POINTER(fossil_mark_t)]
lib.fossil_benchmark_min_time.restype = c_double

lib.fossil_benchmark_max_time.argtypes = [POINTER(fossil_mark_t)]
lib.fossil_benchmark_max_time.restype = c_double

lib.fossil_benchmark_avg_time.argtypes = [POINTER(fossil_mark_t)]
lib.fossil_benchmark_avg_time.restype = c_double

lib.fossil_benchmark_reset.argtypes = [POINTER(fossil_mark_t)]
lib.fossil_benchmark_reset.restype = None

lib.fossil_benchmark_report.argtypes = [POINTER(fossil_mark_t)]
lib.fossil_benchmark_report.restype = None

lib.fossil_scoped_benchmark_init.argtypes = [POINTER(fossil_scoped_mark_t), POINTER(fossil_mark_t)]
lib.fossil_scoped_benchmark_init.restype = None

lib.fossil_scoped_benchmark_destroy.argtypes = [POINTER(fossil_scoped_mark_t)]
lib.fossil_scoped_benchmark_destroy.restype = None

lib.fossil_test_benchmark.argtypes = [c_char_p, c_double, c_double]
lib.fossil_test_benchmark.restype = None

lib.fossil_test_start_benchmark.argtypes = []
lib.fossil_test_start_benchmark.restype = None

lib.fossil_test_stop_benchmark.argtypes = []
lib.fossil_test_stop_benchmark.restype = c_uint64
