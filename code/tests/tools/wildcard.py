import glob

# Collect all .c and .cpp files in the cases directory (including subdirectories)
source_files = glob.glob("cases/*.c", recursive=True) + glob.glob("cases/*.cpp", recursive=True)

# Print each file name with "cases/" prefix
for file in source_files:
    print("cases/" + (file[len("cases/"):] if file.startswith("cases/") else file))