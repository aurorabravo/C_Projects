#!/bin/bash
if [ -z "$1" ]; then
  echo "Please add a parameter - the number of tests."
  exit 1
fi
for i in `seq 1 $1`
do
  ./mixedBase < input$i >| actual$i
  if [ -z "$(diff actual$i expected$i)" ]; then
    echo "Test $i successful!"
  else
    echo "Test $i failed!"
    echo "Expected: $(cat expected$i)"
    echo "Actual: $(cat actual$i)"
  fi
done
