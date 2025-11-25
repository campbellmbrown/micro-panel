# micro-panel

## Development

### Dependencies

1. [Python 3](https://www.python.org/downloads/) (for tools and scripts)
2. [clang-format](https://pypi.org/project/clang-format/) (for C/C++ code formatting)

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
