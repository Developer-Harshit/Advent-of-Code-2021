AOC 2021
> Advent of code 2021 using C language

## Folder Structure
    .
    |__ bin
    |
    |__ data
    |  |__ test.txt
    |  |__input.txt
    |
    |__ src
    |  |__ main.c
    |  |__ utils.c
    |  |__ day_{n}.c
    |  |__ include
    |     |__ utils.h
    |     |__ day.h
    |     |__ ...
    |
    |__ set.py
    |__ run.py
    |
    |__...

## build command

```bash
gcc src/main.c src/utils.c src/day_1.c -o bin/output
```
- replace gcc with your favourite compliler

# run command
```bash
./bin/output
```

# Python Scripts (ik i should have used Makefiles instead)
 - `set.py` is just creates a template for day_{x}.c files. Example `python set.py 1` creates day_1.c
 - `run.py` build and runs based on args given. Example `python run.py 1` builds and runs for day_1.c