#!/bin/bash
FAIL=0

# make a fresh copy of the target program
make clean
make interpreter
if [ $? -ne 0 ]; then
  echo "**** Make (compilation) FAILED"
  FAIL=1
fi

# Generic function for running tests, checking output with diff
# and checking the exit status against an expected status.
runtest() {
  NAME=$1
  EXECUTABLE=$2
  METHOD=$3
  EXPSTATUS=$4
  INFILE=$5
  EXPFILE=$6
  AOUTFILE=$7

  LOCALFAIL=0
  rm -f $AOUTFILE
  if [ $METHOD = "stdin" ]; then
      ./$EXECUTABLE < $INFILE > $AOUTFILE
      STATUS=$?
  else
      ./$EXECUTABLE $INFILE > $AOUTFILE
      STATUS=$?
  fi

  if [ $EXPSTATUS -eq 0 ]; then
      if [ $STATUS -ne 0 ]; then
	  echo "Test $NAME FAILED - expected successful exit status, exited unsuccessfully"
	  FAIL=1
	  LOCALFAIL=1
      fi
  else
      if [ $STATUS -eq 0 ]; then
	  echo "Test $NAME FAILED - expected unsuccessful exit status, exited successfully"
	  FAIL=1
	  LOCALFAIL=1
      fi
  fi
  DIFFDATA=`diff -q $EXPFILE $AOUTFILE`
  if [ $? -ne 0 ]; then
    echo "Test $NAME FAILED - actual output doesn't match expected output"
    #echo "Expected: $(cat $EXPFILE)"
    #echo "Actual: $(cat $AOUTFILE)"
    FAIL=1
    LOCALFAIL=1
  fi
  if [ $LOCALFAIL -eq 0 ]; then
    echo "Test $NAME PASS"
  fi
}

runtest test_00 interpreter stdin 0 program00.txt expected00.txt actual00.txt
runtest test_01 interpreter stdin 0 program01.txt expected01.txt actual01.txt
runtest test_02 interpreter stdin 0 program02.txt expected02.txt actual02.txt
runtest test_03 interpreter file  0 program03.txt expected03.txt actual03.txt
runtest test_04 interpreter file  0 program04.txt expected04.txt actual04.txt
runtest test_05 interpreter file  0 program05.txt expected05.txt actual05.txt
runtest test_06 interpreter file  0 program06.txt expected06.txt actual06.txt
runtest test_07 interpreter file  0 program07.txt expected07.txt actual07.txt
runtest test_10 interpreter file  1 program10.txt expected10.txt actual10.txt
runtest test_11 interpreter file  1 program11.txt expected11.txt actual11.txt
runtest test_12 interpreter file  1 program12.txt expected12.txt actual12.txt

# This input file doesn't exist.
runtest test_13 interpreter file  1 program13.txt expected13.txt actual13.txt

# Test for bad command-line arguments.
LOCALFAIL=0
./interpreter this will not work > actual14.txt
if [ $? -eq 0 ]; then
    echo "Test test_14 FAILED - expected unsuccessful exit status, exited successfully"
    FAIL=1
    LOCALFAIL=1
fi
DIFFDATA=`diff -q $EXPFILE $AOUTFILE`
if [ $? -ne 0 ]; then
    echo "Test test_14 FAILED - actual output doesn't match expected output"
    FAIL=1
    LOCALFAIL=1
fi
if [ $LOCALFAIL -eq 0 ]; then
    echo "Test test_14 PASS"
fi

if [ $FAIL -eq 1 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  exit 0
fi

