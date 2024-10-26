#!/bin/sh

for t in 01
do
	echo === Test $t ===
	sort -n < tests/$t > tests/$t.expected
	./sortIntList < tests/$t > tests/$t.observed 2>&1

	if diff -Bb tests/$t.expected tests/$t.observed > /dev/null 2>&1
	then
		echo "Passed"
	else
		echo "Failed - check differences between tests/$t.expected and tests/$t.observed"
	fi
done
