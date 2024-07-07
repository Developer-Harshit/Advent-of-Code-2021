import os
import sys
import subprocess

args = sys.argv 
if (len(args) < 2):
    print("NO ARGS GIVEN")
    exit()

CC = "gcc"
DAY = f"src/day_{args[1]}.c"
FILES = "src/main.c src/utils.c"
EXE_PATH = "bin/output.exe"
COMMAND = f"{CC} -Wall {FILES} {DAY} -o {EXE_PATH}"
try:
    open(DAY,"r")
except :
    print("undefined file path ->",DAY)
    exit()
subprocess.run(COMMAND)
print(f"--------------------- running day_{DAY} ---------------------\n")

COMMAND = [EXE_PATH]
if (len(args) > 2):
    COMMAND.append(args[2])
subprocess.run(COMMAND)