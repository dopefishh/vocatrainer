#!/bin/bash
set -e
PREFIX="/usr/local"
MANPREFIX="$PREFIX/share/man"
BINDIR="$PREFIX/bin"

install -C -m 755 ./vocatrainer "$BINDIR/"
[ ! -f "./vocatrainer.1.gz" ] && gzip -9qc ./vocatrainer.1 > ./vocatrainer.1.gz
install -C -m 755 ./vocatrainer.1.gz "$MANPREFIX/man1/"
mandb -q
