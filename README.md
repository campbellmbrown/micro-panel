# MicroPanel

![License](https://img.shields.io/github/license/campbellmbrown/micro-panel)
![Release](https://img.shields.io/github/v/release/campbellmbrown/micro-panel)
![Contributors](https://img.shields.io/github/contributors/campbellmbrown/micro-panel)
![Issues](https://img.shields.io/github/issues/campbellmbrown/micro-panel)
![Pull Requests](https://img.shields.io/github/issues-pr/campbellmbrown/micro-panel)
[![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)

## Development

### Dependencies

1. [Python 3](https://www.python.org/downloads/) (for tools and scripts)
2. [ARM GNU Toolchain 10.3-2021.10](https://developer.arm.com/downloads/-/gnu-rm) (for compiling firmware)
3. [CMake](https://cmake.org/download/) (for build management)

Linting, formatting, and other development tools are managed via `pip` and listed in `requirements.txt`.

```bash
pip install -r requirements.txt
```

All development commands can be run via VS Code tasks or directly from the command line.

### Code Formatting

To format C/C++ code using `clang-format`:

```bash
python scripts/format.py
```

To format Python code using `ruff`:

```bash
ruff format
```

### Code Quality

To lint Python code using `ruff`:

```bash
ruff check
```

To type check Python code using `mypy`:

```bash
mypy .
```
