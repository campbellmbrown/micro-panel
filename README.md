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
2. [clang-format](https://pypi.org/project/clang-format/) (for C/C++ code formatting)

Install Python packages:

```bash
pip install -r requirements.txt
```

### Code Formatting

To format C/C++ code, use the VS Code task or run the following command:

```bash
python scripts/format.py
```

To format Python code, use the VS Code task or run the following command:

```bash
ruff format
```

### Code Linting

To lint Python code, use the VS Code task or run the following command:

```bash
ruff check
```
