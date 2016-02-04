#!/bin/bash
FAIL=0

# make a fresh copy of the target program
make clean
make reminder
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
  STARTFILE=$4
  FILE=$5
  EFILE=$6
  INPUT=$7
  EXP=$8
  ACT=$9
  LOCALFAIL=0
  rm -f $NAME/$ACT
  cp $NAME/$STARTFILE $NAME/$FILE
  ./$EXECUTABLE $NAME/$FILE < $NAME/$INPUT > $NAME/$ACT
  RETVAL=$?

  if [ $RETVAL -ne $EXPRETVAL ]; then
    echo "Test $NAME FAILED - RETVAL wrong. Expected: $EXPRETVAL Actual: $RETVAL"
    FAIL=1
    LOCALFAIL=1
  fi
  DIFFDATA=`diff -q $NAME/$EXP $NAME/$ACT`
  if [ $? -ne 0 ]; then
    echo "Test $NAME FAILED - diff did not match: $DIFFDATA"
    FAIL=1
    LOCALFAIL=1
  fi
  DIFFDATA=`diff -q $NAME/$EFILE $NAME/$FILE`
  if [ $? -ne 0 ]; then
    echo "Test $NAME FAILED - diff did not match: $DIFFDATA"
    FAIL=1
    LOCALFAIL=1
  fi
  if [ $LOCALFAIL -eq 0 ]; then
    echo "Test $NAME PASS"
  fi

}

runtest test0 reminder 0 start0 file0 efile0 input0 expected0 actual0
runtest test1 reminder 0 start1 file1 efile1 input1 expected1 actual1
runtest test2 reminder 0 start2 file2 efile2 input2 expected2 actual2
runtest test3 reminder 0 start3 file3 efile3 input3 expected3 actual3
runtest test4 reminder 0 start4 file4 efile4 input4 expected4 actual4
runtest test5 reminder 0 start5 file5 efile5 input5 expected5 actual5
runtest test6 reminder 0 start6 file6 efile6 input6 expected6 actual6
runtest test7 reminder 0 start7 file7 efile7 input7 expected7 actual7
runtest test8 reminder 0 start8 file8 efile8 input8 expected8 actual8
runtest test9 reminder 0 start9 file9 efile9 input9 expected9 actual9

# TEST10
LOCALFAIL=0
rm -f test10/actual10
./reminder test10/file10 > test10/actual10
RETVAL=$?

if [ $RETVAL -ne 1 ]; then
  echo "Test test10 FAILED - RETVAL wrong. Expected: 1 Actual: $RETVAL"
  FAIL=1
  LOCALFAIL=1
fi
DIFFDATA=`diff -q test10/expected10 test10/actual10`
if [ $? -ne 0 ]; then
  echo "Test test10 FAILED - diff did not match: $DIFFDATA"
  FAIL=1
  LOCALFAIL=1
fi
if [ $LOCALFAIL -eq 0 ]; then
  echo "Test test10 PASS"
fi


# TEST11
LOCALFAIL=0
rm -f test11/actual11
./reminder > test11/actual11
RETVAL=$?

if [ $RETVAL -ne 1 ]; then
  echo "Test test11 FAILED - RETVAL wrong. Expected: 1 Actual: $RETVAL"
  FAIL=1
  LOCALFAIL=1
fi
DIFFDATA=`diff -q test11/expected11 test11/actual11`
if [ $? -ne 0 ]; then
  echo "Test test11 FAILED - diff did not match: $DIFFDATA"
  FAIL=1
  LOCALFAIL=1
fi
if [ $LOCALFAIL -eq 0 ]; then
  echo "Test test11 PASS"
fi

# OVERALL FAILURE CHECK
if [ $FAIL -eq 1 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  exit 0
fi

