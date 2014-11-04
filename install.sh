#!/bin/bash
set -e
PREFIX="/usr/local"
MANPREFIX="$PREFIX/share/man"
BINDIR="$PREFIX/bin"

install -C -m 644 -o root -g root ./vocatrainer "$BINDIR/"
[ ! -f "./vocatrainer.1.gz" ] && gzip -9qc ./vocatrainer.1 > ./vocatrainer.1.gz
install -C -m 644 -o root -g root ./vocatrainer.1.gz "$MANPREFIX/man1/"
mandb -q
