#!/bin/sh

set -e

echo "Integration tests..."

printf "Hello, Base85!" | ./base85 -e | ./base85 -d > roundtrip.txt
ACTUAL="$(cat roundtrip.txt)"

if [ "$ACTUAL" != "Hello, Base85!" ]; then
    echo "Round-trip integration test failed"
    exit 1
fi

printf "1234567890" | ./base85 -e | ./base85 -d > numbers.txt
ACTUAL_NUMBERS="$(cat numbers.txt)"

if [ "$ACTUAL_NUMBERS" != "1234567890" ]; then
    echo "Numbers integration test failed"
    exit 1
fi

rm -f roundtrip.txt numbers.txt

echo "All integration tests passed"
