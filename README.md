# MicroPanel

![License](https://img.shields.io/github/license/campbellmbrown/micro-panel?style=for-the-badge)
![docs](https://app.readthedocs.org/projects/micro-panel/badge/?style=for-the-badge)
![Pipeline](https://img.shields.io/github/actions/workflow/status/campbellmbrown/micro-panel/pipeline.yaml?branch=main&style=for-the-badge&logo=github)
![Release](https://img.shields.io/github/v/release/campbellmbrown/micro-panel?style=for-the-badge&logo=github)

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
![Ruff](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/astral-sh/ruff/main/assets/badge/v2.json&style=for-the-badge)
![Read the Docs](https://img.shields.io/badge/Read%20the%20Docs-%23000000?style=for-the-badge&logo=readthedocs&logoColor=white)

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
