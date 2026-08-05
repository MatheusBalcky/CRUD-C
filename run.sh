#!/bin/bash
# Compila o arquivo .c passado como argumento e gera um executável temporário
clear
gcc main.c inputs_outputs.c -o prog.exe -lm && ./prog.exe