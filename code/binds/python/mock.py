# fossil_mock.py
import ctypes
from ctypes import c_int, c_bool, c_char_p, c_size_t, POINTER, Structure

# Load shared library
import os
lib_path = os.path.join(os.path.dirname(__file__), "../../build/libfossil_mock.so")
lib = ctypes.CDLL(os.path.abspath(lib_path))

# --- Pizza Types ---
FOSSIL_MOCK_PIZZA_TYPE_I8 = 0
FOSSIL_MOCK_PIZZA_TYPE_I16 = 1
FOSSIL_MOCK_PIZZA_TYPE_I32 = 2
FOSSIL_MOCK_PIZZA_TYPE_I64 = 3
FOSSIL_MOCK_PIZZA_TYPE_U8 = 4
FOSSIL_MOCK_PIZZA_TYPE_U16 = 5
FOSSIL_MOCK_PIZZA_TYPE_U32 = 6
FOSSIL_MOCK_PIZZA_TYPE_U64 = 7
FOSSIL_MOCK_PIZZA_TYPE_HEX = 8
FOSSIL_MOCK_PIZZA_TYPE_OCTAL = 9
FOSSIL_MOCK_PIZZA_TYPE_FLOAT = 10
FOSSIL_MOCK_PIZZA_TYPE_DOUBLE = 11
FOSSIL_MOCK_PIZZA_TYPE_WSTR = 12
FOSSIL_MOCK_PIZZA_TYPE_CSTR = 13
FOSSIL_MOCK_PIZZA_TYPE_CCHAR = 14
FOSSIL_MOCK_PIZZA_TYPE_WCHAR = 15
FOSSIL_MOCK_PIZZA_TYPE_BOOL = 16
FOSSIL_MOCK_PIZZA_TYPE_SIZE = 17
FOSSIL_MOCK_PIZZA_TYPE_ANY = 18

# --- Structures ---

class fossil_mock_pizza_value_t(Structure):
    _fields_ = [
        ("data", c_char_p),
        ("mutable_flag", c_bool),
    ]

class fossil_mock_pizza_attribute_t(Structure):
    _fields_ = [
        ("name", c_char_p),
        ("description", c_char_p),
        ("id", c_char_p),
    ]

class fossil_mock_pizza_t(Structure):
    _fields_ = [
        ("type", c_int),  # fossil_mock_pizza_type_t
        ("value", fossil_mock_pizza_value_t),
        ("attribute", fossil_mock_pizza_attribute_t),
    ]

class fossil_mock_call_t(Structure):
    pass

fossil_mock_call_t._fields_ = [
    ("function_name", c_char_p),
    ("arguments", POINTER(fossil_mock_pizza_t)),
    ("num_args", c_int),
    ("next", POINTER(fossil_mock_call_t)),
]

class fossil_mock_calllist_t(Structure):
    _fields_ = [
        ("head", POINTER(fossil_mock_call_t)),
        ("tail", POINTER(fossil_mock_call_t)),
        ("size", c_int),
    ]

# --- Functions ---
lib.fossil_mock_init.argtypes = [POINTER(fossil_mock_calllist_t)]
lib.fossil_mock_init.restype = None

lib.fossil_mock_destroy.argtypes = [POINTER(fossil_mock_calllist_t)]
lib.fossil_mock_destroy.restype = None

lib.fossil_mock_add_call.argtypes = [
    POINTER(fossil_mock_calllist_t),
    c_char_p,
    POINTER(fossil_mock_pizza_t),
    c_int
]
lib.fossil_mock_add_call.restype = None

lib.fossil_mock_print.argtypes = [POINTER(fossil_mock_calllist_t)]
lib.fossil_mock_print.restype = None

lib.fossil_mock_capture_output.argtypes = [c_char_p, c_size_t, ctypes.CFUNCTYPE(None)]
lib.fossil_mock_capture_output.restype = c_int

lib.fossil_mock_compare_output.argtypes = [c_char_p, c_char_p]
lib.fossil_mock_compare_output.restype = c_bool
