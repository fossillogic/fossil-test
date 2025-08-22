import glob
import sys

# Collect all .c and .cpp files directly in the cases directory (not subdirectories)
source_files = glob.glob("cases/*.c") + glob.glob("cases/*.cpp")

# On Apple platforms, also include Objective-C and Objective-C++ files
if sys.platform == "darwin":
    source_files += glob.glob("cases/*.m") + glob.glob("cases/*.mm")

# Print each file name with "cases/" prefix
for file in source_files:
    print(file)
