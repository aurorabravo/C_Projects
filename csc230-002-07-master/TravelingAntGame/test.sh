#!/bin/bash
FAIL=0

# make a fresh copy of the target program
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make (compilation) FAILED"
  FAIL=1
fi

# Generic function for running tests, checking output with diff
# and checking the exit status against an expected status.
runtest() {
  NAME=$1
  EXECUTABLE=$2
  EXPRETVAL=$3
  INFILE=$4
  EXPFILE=$5
  AOUTFILE=$6
  LOCALFAIL=0
  rm -f $AOUTFILE
  ./$EXECUTABLE  $INFILE > $AOUTFILE
  RETVAL=$?

  if [ $RETVAL -ne $EXPRETVAL ]; then
    echo "Test $NAME FAILED - RETVAL wrong. Expected: $EXPRETVAL Actual: $RETVAL"
    FAIL=1
    LOCALFAIL=1
  fi
  DIFFDATA=`diff -q $EXPFILE $AOUTFILE`
  if [ $? -ne 0 ]; then
    echo "Test $NAME FAILED - diff did not match: $DIFFDATA"
    FAIL=1
    LOCALFAIL=1
  fi
  if [ $LOCALFAIL -eq 0 ]; then
    echo "Test $NAME PASS"
  fi

}

runtest test_0 travelingAnt 0 input0 expected0 actual0
runtest test_1 travelingAnt 0 input1 expected1 actual1
runtest test_2 travelingAnt 0 input2 expected2 actual2
runtest test_3 travelingAnt 0 input3 expected3 actual3
runtest test_4 travelingAnt 0 input4 expected4 actual4
runtest test_5 travelingAnt 0 input5 expected5 actual5
runtest test_6 travelingAnt 0 input6 expected6 actual6
runtest test_7 travelingAnt 1 input7 expected7 actual7
runtest test_8 travelingAnt 1 input8 expected8 actual8
runtest test_9 travelingAnt 1 input9 expected9 actual9
runtest test_10 travelingAnt 1 input10 expected10 actual10
runtest test_11 travelingAnt 1 input11 expected11 actual11
runtest test_12 travelingAnt 1 input12 expected12 actual12
runtest test_13 travelingAnt 1 input13 expected13 actual13
runtest test_14 travelingAnt 1 input14 expected14 actual14
runtest test_15 travelingAnt 1 input15 expected15 actual15
runtest test_16 travelingAnt 1 input16 expected16 actual16
runtest test_17 travelingAnt 1 input17 expected17 actual17
runtest test_18 travelingAnt 1 input18 expected18 actual18
runtest test_19 travelingAnt 1 input19 expected19 actual19
runtest test_20 travelingAnt 1 input20 expected20 actual20

LOCALFAIL=0
rm -f actual21
./travelingAnt > actual21
RETVAL=$?

if [ $RETVAL -ne 1 ]; then
  echo "Test test_21 FAILED - RETVAL wrong. Expected: 1 Actual: $RETVAL"
  FAIL=1
  LOCALFAIL=1
fi
DIFFDATA=`diff -q expected21 actual21`
if [ $? -ne 0 ]; then
  echo "Test test_21 FAILED - diff did not match: $DIFFDATA"
  FAIL=1
  LOCALFAIL=1
fi
if [ $LOCALFAIL -eq 0 ]; then
  echo "Test test_21 PASS"
fi


if [ $FAIL -eq 1 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  exit 0
fi

