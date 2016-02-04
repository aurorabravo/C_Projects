#ifndef _EXPR_H_
#define _EXPR_H_

#include <stdio.h>
#include "Binary.h"

/** A short name to use for the expression interface. */
typedef struct ExprTag Expr;

/**
   Representation for an Expr interface.  Classes implementing this
   have these two fields as their first members.  They will set eval
   to point to appropriate functions to evaluate the type of
   expression they represent, and they will set free to point to a
   function that frees memory for their type of expression.
*/
struct ExprTag {
  /** Pointer to a function to evaluate this expression expr set dest
      to the result.
      @param expr expression to be evaluated.
      @param dest destination to store the result.
   */
  void (*eval)( Expr *expr, Binary *dest );

  /** Free memory for this expression, including any subexpressions
      it contains.
      @param expr expression to free.
  */
  void (*destroy)( Expr *expr );
};

/** Make an expression object that just evaluates to the given Binary
    value.  The expression is responsible for freeing this value when
    it's destroyed.
    @param val Binary value this expression evaluates to
    @return new expression object
  */
Expr *makeValueExpr( Binary *val );

/** Make an expression object that represents a use of the & operator.
    It evaluates to the bitwise and of the values of its left and
    right subexpressions.  The expression is responsible for freeing
    its subexpressions when it's destroyed.
    @param left subexpression to the left of the operator
    @param right subexpression to the right of the operator
    @return new expression object
  */
Expr *makeAndExpr( Expr *left, Expr *right );

/** Make an expression object that represents a use of the | operator.
    It evaluates to the bitwise or of the values of its left and
    right subexpressions.  The expression is responsible for freeing
    its subexpressions when it's destroyed.
    @param left subexpression to the left of the operator
    @param right subexpression to the right of the operator
    @return new expression object
  */
Expr *makeOrExpr( Expr *left, Expr *right );

/** Make an expression object that represents a use of the ^ operator.
    It evaluates to the bitwise exclusive or of the values of its left
    and right subexpressions.  The expression is responsible for
    freeing its subexpressions when it's destroyed.
    @param left subexpression to the left of the operator
    @param right subexpression to the right of the operator
    @return new expression object
  */
Expr *makeXorExpr( Expr *left, Expr *right );

/** Make an expression object that represents a use of the ~ operator.
    It evaluates to the bitwise complement or of the value of its
    operand.  This expression is responsible for freeing its operand
    when it's destroyed.
    @param operand subexpression being complemented
    @return new expression object
  */
Expr *makeComplementExpr( Expr *operand );

/** Make an expression object that represents a use of the <<
    operator.  It evaluates to the bitwise left shift of its left
    operand by a number of bits given in the right operand.  The
    expression is responsible for freeing its subexpressions when it's
    destroyed.
    @param left target subexpression to be shifted
    @param right subexpression giving the number of bits to shift
    @return new expression object
  */
Expr *makeShiftLeftExpr( Expr *left, Expr *right );

/** Make an expression object that represents a use of the >>
    operator.  It evaluates to the bitwise logical right shift of its left
    operand by a number of bits given in the right operand.  The
    expression is responsible for freeing its subexpressions when it's
    destroyed.
    @param left target subexpression to be shifted
    @param right subexpression giving the number of bits to shift
    @return new expression object
  */
Expr *makeShiftRightExpr( Expr *left, Expr *right );

#endif
