#!/usr/bin/env bash

COLUMNS=$(tput cols)

WORD=$1
WORD_SIZE=${#WORD}

TOTAL_SIZE=$((COLUMNS - WORD_SIZE))
DIVIDED_SIZE=$((TOTAL_SIZE / 2 - 3))

EQUALS=$(printf "\033[0;35m=%.0s" $(seq 1 $DIVIDED_SIZE))

printf "$EQUALS \033[0;37m[ \033[0;33m$WORD \033[0;37m] $EQUALS\033[0;37m"
