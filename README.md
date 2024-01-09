# 42 Minishell Project README

## Overview
Welcome to Minishell, a simple UNIX command-line shell implementation developed as part of the 42 school curriculum. This project aims to provide a basic understanding of how shells work and how commands are executed in a UNIX-like environment.

## Installation
This project should compile under Mac OS and Unix:
```
git clone https://github.com/Alphacharge/minishell.git
cd minishell
make
```
### Dependencies
[libft Lib](https://github.com/Alphacharge/mylibft/releases/tag/v1.0.0)

## Description
This minishell should behave like Bash.

### Following builtins are built in:
- cd      (relative and absolute paths)
- echo    (with -n)
- env     (no options)
- exit    (no options)
- export  (no options)
- pwd     (no options)
- unset   (no options)

### Signals:
- ctrl-C
- ctrl-D
- ctrl-\

### Operators:
- <<
- \>>
- <
- \>
- |

### Variables:
- normal variable expanding like $HOME
- $?

### Quotes:
- Single Quotes
- Double Quotes

## Usage
``./minishell``

## Contributors
- [fkernbac](https://github.com/fkernbac)
- [rbetz](https://github.com/Alphacharge)

## License
This project is licensed under the GPL-3.0 License - see the LICENSE file for details.

## Acknowledgments
+ Thank you to the 42 school for providing the opportunity to work on this project.
+ Inspiration from various UNIX shells and open-source projects.

Feel free to contribute, report issues, or suggest improvements! Happy coding!
