# 42 minishell Project
This project is a selfcoded Shell from [fkernbac](https://github.com/fkernbac) and [rbetz](https://github.com/Alphacharge).
It's using the my [libft Lib](https://github.com/Alphacharge/mylibft/releases/tag/v1.0.0).

## Installation
This project should compile under Mac OS and Unix:
```
git clone https://github.com/Alphacharge/minishell.git
cd minishell
make
```

## Description
This minishell should behave like Bash.

Following builtins are built in:
- cd      (relative and absolute paths)
- echo    (with -n)
- env     (no options)
- exit    (no options)
- export  (no options)
- pwd     (no options)
- unset   (no options)

Signals:
- ctrl-C
- ctrl-D
- ctrl-\

Operators:
- <<
- >>
- <
- >
- |

Variables:
- normal variable expanding like $HOME
- $?

Quotes:
- Single Quotes
- Double Quotes

## Usage
``./minishell``
