import subprocess
import time
from pathlib import Path

INCLUDE_EXT = (".cpp", ".h", ".c", ".hpp")
SRC_DIRS = [
    "src",
]

EXCLUDE_DIRECTORIES: list[str] = []

EXCLUDE_FILES = [
    "src/config/sdk_config.h",
]


def is_excluded(file_path: Path) -> bool:
    """Check if the file path is in an excluded directory."""
    for excluded_dir in EXCLUDE_DIRECTORIES:
        if file_path.is_relative_to(excluded_dir):
            return True
    if file_path.as_posix() in EXCLUDE_FILES:
        return True
    return False


start_time = time.time()

all_files: list[Path] = []
for src_dir in SRC_DIRS:
    all_files.extend(f for f in Path(src_dir).rglob("*") if f.suffix in INCLUDE_EXT)

format_files = [f for f in all_files if not is_excluded(f)]
num_format_files = len(format_files)
num_skipped_files = len(all_files) - num_format_files

for idx, file in enumerate(format_files, start=1):
    print(f"[{idx}/{num_format_files}] Formatting {file}...")
    subprocess.run(["clang-format", "-i", str(file)], check=True)

elapsed_time = time.time() - start_time
print(f"\nFormatted {num_format_files} files in {elapsed_time:.2f} seconds ({num_skipped_files} files skipped).")
