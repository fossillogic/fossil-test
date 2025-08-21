# fossil_sanity.py
import os, ctypes
from ctypes import c_int, c_char_p, c_longlong


# --- Load the shared library ---
# Adjust path as needed relative to code/bind/python/
lib_path = os.path.join(os.path.dirname(__file__), "../../build/libfossil_sanity.so")
lib = ctypes.CDLL(os.path.abspath(lib_path))


# --- Function Signatures ---

# Executes a system command
lib.fossil_sanity_sys_execute.argtypes = [c_char_p]
lib.fossil_sanity_sys_execute.restype = c_int

# Get process ID
lib.fossil_sanity_sys_getpid.argtypes = []
lib.fossil_sanity_sys_getpid.restype = c_int

# Sleep
lib.fossil_sanity_sys_sleep.argtypes = [c_int]
lib.fossil_sanity_sys_sleep.restype = None

# File operations
lib.fossil_sanity_sys_create_file.argtypes = [c_char_p]
lib.fossil_sanity_sys_create_file.restype = c_int

lib.fossil_sanity_sys_file_exists.argtypes = [c_char_p]
lib.fossil_sanity_sys_file_exists.restype = c_int

lib.fossil_sanity_sys_delete_file.argtypes = [c_char_p]
lib.fossil_sanity_sys_delete_file.restype = c_int

lib.fossil_sanity_sys_read_file.argtypes = [c_char_p]
lib.fossil_sanity_sys_read_file.restype = c_char_p  # Caller must free

lib.fossil_sanity_sys_write_file.argtypes = [c_char_p, c_char_p]
lib.fossil_sanity_sys_write_file.restype = c_int

# Directory operations
lib.fossil_sanity_sys_create_dir.argtypes = [c_char_p]
lib.fossil_sanity_sys_create_dir.restype = c_int

lib.fossil_sanity_sys_dir_exists.argtypes = [c_char_p]
lib.fossil_sanity_sys_dir_exists.restype = c_int

# Environment variables
lib.fossil_sanity_sys_getenv.argtypes = [c_char_p]
lib.fossil_sanity_sys_getenv.restype = c_char_p

lib.fossil_sanity_sys_setenv.argtypes = [c_char_p, c_char_p]
lib.fossil_sanity_sys_setenv.restype = c_int

# Timestamp / uptime
lib.fossil_sanity_sys_timestamp.argtypes = []
lib.fossil_sanity_sys_timestamp.restype = c_char_p

lib.fossil_sanity_sys_uptime_ms.argtypes = []
lib.fossil_sanity_sys_uptime_ms.restype = c_longlong

# Process checks
lib.fossil_sanity_sys_is_running.argtypes = [c_int]
lib.fossil_sanity_sys_is_running.restype = c_int

lib.fossil_sanity_sys_kill.argtypes = [c_int]
lib.fossil_sanity_sys_kill.restype = c_int
