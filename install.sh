#!/bin/bash
set -e

# If you want to install on a different prefix change this variable
PREFIX="/usr/local"

MANPREFIX="$PREFIX/share/man"
BINDIR="$PREFIX/bin"

install -C -m 755 ./vocatrainer "$BINDIR/"
[ ! -f "./vocatrainer.1.gz" ] && gzip -9qc ./vocatrainer.1 > ./vocatrainer.1.gz
mkdir -vp "$MANPREFIX/man1"
install -C -m 755 ./vocatrainer.1.gz "$MANPREFIX/man1/"
mandb -q
