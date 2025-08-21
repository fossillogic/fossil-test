# fossil_pizza.py
import ctypes
from ctypes import c_int, c_int32, c_uint64, c_size_t, c_char_p, c_bool, c_double, c_void_p
from ctypes import POINTER, Structure


# --- Return Codes ---
FOSSIL_PIZZA_SUCCESS = 0
FOSSIL_PIZZA_FAILURE = -1


# --- Enum: Case Results ---
class fossil_pizza_case_result_t(ctypes.c_int):
    FOSSIL_PIZZA_CASE_EMPTY = 0
    FOSSIL_PIZZA_CASE_PASS = 1
    FOSSIL_PIZZA_CASE_FAIL = 2
    FOSSIL_PIZZA_CASE_TIMEOUT = 3
    FOSSIL_PIZZA_CASE_SKIPPED = 4
    FOSSIL_PIZZA_CASE_UNEXPECTED = 5


# --- Score Struct ---
class fossil_pizza_score_t(Structure):
    _fields_ = [
        ("passed", c_int),
        ("failed", c_int),
        ("skipped", c_int),
        ("timeout", c_int),
        ("unexpected", c_int),
        ("empty", c_int),
    ]


# --- Meta Struct ---
class fossil_pizza_meta_t(Structure):
    _fields_ = [
        ("hash", c_char_p),
        ("prev_hash", c_char_p),
        ("timestamp", ctypes.c_long),   # time_t (platform dependent: long is typical)
        ("origin_device_id", c_char_p),
        ("author", c_char_p),
        ("trust_score", c_double),
        ("confidence", c_double),
        ("immutable", c_bool),
        ("signature", c_char_p),
    ]


# --- Test Case Struct ---
class fossil_pizza_case_t(Structure):
    pass  # forward declare for function pointers


SETUP_FUNC = ctypes.CFUNCTYPE(None)
TEARDOWN_FUNC = ctypes.CFUNCTYPE(None)
RUN_FUNC = ctypes.CFUNCTYPE(None)

fossil_pizza_case_t._fields_ = [
    ("name", c_char_p),
    ("tags", c_char_p),
    ("criteria", c_char_p),

    ("setup", SETUP_FUNC),
    ("teardown", TEARDOWN_FUNC),
    ("run", RUN_FUNC),

    ("elapsed_ns", c_uint64),
    ("result", fossil_pizza_case_result_t),

    ("meta", fossil_pizza_meta_t),
]


# --- Test Suite Struct ---
class fossil_pizza_suite_t(Structure):
    _fields_ = [
        ("suite_name", c_char_p),
        ("cases", POINTER(fossil_pizza_case_t)),
        ("count", c_size_t),
        ("capacity", c_size_t),

        ("setup", SETUP_FUNC),
        ("teardown", TEARDOWN_FUNC),

        ("time_elapsed_ns", c_uint64),
        ("total_score", c_int),
        ("total_possible", c_int),

        ("score", fossil_pizza_score_t),
        ("meta", fossil_pizza_meta_t),
    ]


# --- Engine Struct ---
class fossil_pizza_engine_t(Structure):
    _fields_ = [
        ("suites", POINTER(fossil_pizza_suite_t)),
        ("count", c_size_t),
        ("capacity", c_size_t),

        ("score_total", c_int),
        ("score_possible", c_int),

        ("score", fossil_pizza_score_t),
        ("pallet", c_void_p),  # unknown fossil_pizza_pallet_t
        ("meta", fossil_pizza_meta_t),
    ]


# --- Load the compiled library ---
# On Linux: lib = ctypes.CDLL("./libfossil_pizza.so")
# On Windows: lib = ctypes.CDLL("fossil_pizza.dll")
# On macOS: lib = ctypes.CDLL("./libfossil_pizza.dylib")

lib = ctypes.CDLL("./libfossil_pizza.so")


# --- Function Bindings ---
lib.fossil_pizza_start.argtypes = [POINTER(fossil_pizza_engine_t), c_int, POINTER(c_char_p)]
lib.fossil_pizza_start.restype = c_int

lib.fossil_pizza_add_suite.argtypes = [POINTER(fossil_pizza_engine_t), fossil_pizza_suite_t]
lib.fossil_pizza_add_suite.restype = c_int

lib.fossil_pizza_add_case.argtypes = [POINTER(fossil_pizza_suite_t), fossil_pizza_case_t]
lib.fossil_pizza_add_case.restype = c_int

lib.fossil_pizza_run_suite.argtypes = [POINTER(fossil_pizza_engine_t), POINTER(fossil_pizza_suite_t)]
lib.fossil_pizza_run_suite.restype = c_int

lib.fossil_pizza_run_all.argtypes = [POINTER(fossil_pizza_engine_t)]
lib.fossil_pizza_run_all.restype = c_int

lib.fossil_pizza_summary.argtypes = [POINTER(fossil_pizza_engine_t)]
lib.fossil_pizza_summary.restype = None

lib.fossil_pizza_end.argtypes = [POINTER(fossil_pizza_engine_t)]
lib.fossil_pizza_end.restype = c_int32
