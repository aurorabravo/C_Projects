#include "Expr.h"
#include <stdlib.h>
#include <stdbool.h>

/**
    @file Expr.c
    @author Aurora Bravo (aibravoe)

    This program does the work for interpreter.c. This program uses
    structs for bianry expressions and also evaluates, makes and
    destroys binary expressions
*/

/*********************************************************************
 Representation for an OR expression.
*********************************************************************/

/** typedef struct for OrExpr */
typedef struct {
    // Inherited fields from Expr.
    void (*eval)( struct ExprTag *, Binary *dest );
    void (*destroy)( struct ExprTag * );

    // Left and right operands.
    Expr *left, *right;
} OrExpr;

/**
    Function to eval an OrExpr object.
    @param expr expression to evaluate
    @param dest destination of expression
*/
static void evalOrExpr( Expr *expr, Binary *dest ) {
    OrExpr *this = (OrExpr *) expr;

    Binary *l = makeBinary(1);
    this->left->eval( this->left, l );

    Binary *r = makeBinary(1);
    this->right->eval( this->right, r );

    orBinary( dest, l, r );

    freeBinary( l );
    freeBinary( r );
}

/**
    Function to destroy an OrExpr object.
    @param expr expression to destroy
*/
static void destroyOrExpr( Expr *expr ) {
    OrExpr *this = (OrExpr *) expr;

    // Free our subexpressions.
    this->left->destroy( this->left );
    this->right->destroy( this->right );
    free( this );
}

/**
    Function to make an OrExpr object.
    @param left left side of the expression
    @param right right side of the expression
    @return new expression object
*/
Expr *makeOrExpr( Expr *left, Expr *right ) {
    OrExpr *this = (OrExpr *)malloc( sizeof( OrExpr ) );

    // Fill in virtual functions.
    this->eval = evalOrExpr;
    this->destroy = destroyOrExpr;

    // And other parts of the state.
    this->left = left;
    this->right = right;

    return (Expr *) this;
}


/*********************************************************************
 Representation for a XOR expression.
*********************************************************************/

 /** typedef struct for XorExpr */
typedef struct {
    // Inherited fields from Expr.
    void (*eval)( struct ExprTag *, Binary *dest );
    void (*destroy)( struct ExprTag * );

    // Left and right operands.
    Expr *left, *right;
} XorExpr;

/**
    Function to eval a XorExpr object.
    @param expr expression to evaluate
    @param dest destination of expression
*/
static void evalXorExpr( Expr *expr, Binary *dest ) {
    XorExpr *this = (XorExpr *) expr;

    Binary *l = makeBinary(1);
    this->left->eval( this->left, l );

    Binary *r = makeBinary(1);
    this->right->eval( this->right, r );

    xorBinary( dest, l, r );

    freeBinary( l );
    freeBinary( r );
}

/**
    Function to destroy a XorExpr object.
    @param expr expression to destroy
*/
static void destroyXorExpr( Expr *expr ) {
    XorExpr *this = (XorExpr *) expr;

    // Free our subexpressions.
    this->left->destroy( this->left );
    this->right->destroy( this->right );
    free( this );
}

/** Function to make a XorExpr object.
    @param left left side of the expression
    @param right right side of the expression
    @return new expression object
*/
Expr *makeXorExpr( Expr *left, Expr *right ) {
    XorExpr *this = (XorExpr *)malloc( sizeof( XorExpr ) );

    // Fill in virtual functions.
    this->eval = evalXorExpr;
    this->destroy = destroyXorExpr;

    // And other parts of the state.
    this->left = left;
    this->right = right;

    return (Expr *) this;
}


/*********************************************************************
 Representation for an AND expression.
*********************************************************************/

/** typedef struct for AndExpr */
typedef struct {
    // Inherited fields from Expr.
    void (*eval)( struct ExprTag *, Binary *dest );
    void (*destroy)( struct ExprTag * );

    // Left and right operands.
    Expr *left, *right;
} AndExpr;

/**
    Function to eval an AndExpr object.
    @param expr expression to evaluate
    @param dest destination of expression
*/
static void evalAndExpr( Expr *expr, Binary *dest ) {
    AndExpr *this = (AndExpr *) expr;

    Binary *l = makeBinary(1);
    this->left->eval( this->left, l );

    Binary *r = makeBinary(1);
    this->right->eval( this->right, r );

    andBinary( dest, l, r );

    freeBinary( l );
    freeBinary( r );
}

/**
    Function to destroy an AndExpr object.
    @param expr expression to destroy
*/
static void destroyAndExpr( Expr *expr ) {
    AndExpr *this = (AndExpr *) expr;

    // Free our subexpressions.
    this->left->destroy( this->left );
    this->right->destroy( this->right );
    free( this );
}

/** Function to make an AndExpr object.
    @param left left side of the expression
    @param right right side of the expression
    @return new expression object
*/
Expr *makeAndExpr( Expr *left, Expr *right ) {
    AndExpr *this = (AndExpr *)malloc( sizeof( AndExpr ) );

    // Fill in virtual functions.
    this->eval = evalAndExpr;
    this->destroy = destroyAndExpr;

    // And other parts of the state.
    this->left = left;
    this->right = right;

    return (Expr *) this;
}


/*********************************************************************
 Representation for an expression that just evaluates to a given
 binary value.
*********************************************************************/

/** typedef struct for ValueExpr */
typedef struct {
    // Inherited fields from Expr.
    void (*eval)( struct ExprTag *, Binary *dest );
    void (*destroy)( struct ExprTag * );

    // Binary value it evaluates to.
    Binary *val;
} ValueExpr;

/**
    Function to eval a ValueExpr object.
    @param expr expression to evaluate
    @param dest destination of expression
*/
static void evalValueExpr( Expr *expr, Binary *dest ) {
    ValueExpr *this = (ValueExpr *) expr;

    andBinary( dest, this->val, this->val );
}

/**
    Function to destroy an ValueExpr object.
    @param expr expression to destroy
*/
static void destroyValueExpr( Expr *expr ) {
    ValueExpr *this = (ValueExpr *) expr;

    freeBinary( this->val );
    free( this );
}

/**
    Function to make an ValueExpr object.
    @param val Binary value of the expression
    @return new expression object
*/
Expr *makeValueExpr( Binary *val ) {
    ValueExpr *this = (ValueExpr *)malloc( sizeof( ValueExpr ) );

    this->eval = evalValueExpr;
    this->destroy = destroyValueExpr;

    this->val = val;

    return (Expr *) this;
}

/*********************************************************************
 Representation for a left or a right shift expression.
*********************************************************************/

/** typedef struct for ShiftExpr */
typedef struct {
    // Inherited fields from Expr.
    void (*eval)( struct ExprTag *, Binary *dest );
    void (*destroy)( struct ExprTag * );

    // True if this is this a left shift (vs. right)
    bool leftward;

    // Left and right operands.
    Expr *left, *right;
} ShiftExpr;

/**
    Function to eval a ShiftExpr object.
    @param expr expression to evaluate
    @param dest destination of expression
*/
static void evalShiftExpr( Expr *expr, Binary *dest ) {
    ShiftExpr *this = (ShiftExpr *) expr;

    this->left->eval( this->left, dest );

    Binary *v = makeBinary( getLength( dest ) );
    this->right->eval( this->right, v );

    // Convert the binary value in v to an int, so we can use it
    // in the shift calls.
    unsigned int offset = 0;
    unsigned int bit = 1;
    for ( int i = 0; i < getLength( v ); i++ ) {
        if ( getBit( v, i ) )
            offset += bit;
        bit <<= 1;
    }

    if ( this->leftward )
        shiftLeft( dest, dest, offset );
    else
        logicalShiftRight( dest, dest, offset );

    freeBinary( v );
}

/**
    Function to destroy an ShiftExpr object.
    @param expr expression to destroy
*/
static void destroyShiftExpr( Expr *expr ) {
    ShiftExpr *this = (ShiftExpr *) expr;

    // Free our subexpressions.
    this->left->destroy( this->left );
    this->right->destroy( this->right );
    free( this );
}

/**
    Utility function to make either a leftward or a rightward
    ShfitExpr object.
    @param left target subexpression to be shifted
    @param right subexpression giving the number of bits to shift
    @param leftward true if we're making a leftward shift
    @return new expression object
*/
static Expr *makeShiftExpr( Expr *left, Expr *right, bool leftward ) {
    ShiftExpr *this = (ShiftExpr *)malloc( sizeof( ShiftExpr ) );

    // Fill in virtual functions.
    this->eval = evalShiftExpr;
    this->destroy = destroyShiftExpr;

    // And other parts of the state.
    this->leftward = leftward;
    this->left = left;
    this->right = right;

    return (Expr *) this;
}

/**
    Function to make an expressionw with shift right.
    @param left target subexpression to be shifted
    @param right subexpression to give shift.
    @return new expression object
*/
Expr *makeShiftRightExpr( Expr *left, Expr *right ) {
    return makeShiftExpr( left, right, false );
}

/**
    Function to make an expressionw with shift left.
    @param left target subexpression to be shifted
    @param right subexpression to give shift.
    @return new expression object
*/
Expr *makeShiftLeftExpr( Expr *left, Expr *right ) {
    return makeShiftExpr( left, right, true );
}


/*********************************************************************
 Representation for an Complement expression.
*********************************************************************/

/** typedef struct for CompExpr */
typedef struct {
    // Inherited fields from Expr.
    void (*eval)( struct ExprTag *, Binary *dest );
    void (*destroy)( struct ExprTag * );

    // Complement
    Expr *next;
} CompExpr;

/**
    Function to eval a CompExpr object.
    @param expr expression to evaluate
    @param dest destination of expression
*/
static void evalComplementExpr( Expr *expr, Binary *dest ) {
    CompExpr *this = (CompExpr *) expr;

    Binary *c = makeBinary(1);
    this->next->eval( this->next, c );

    complementBinary( dest, c );

    freeBinary( c );
}

/**
    Function to destroy a CompExpr object.
    @param expr expression to destroy
*/
static void destroyComplementExpr( Expr *expr ) {
    CompExpr *this = (CompExpr *) expr;

    // Free our subexpressions.
    this->next->destroy( this->next );
    free( this );
}

/**
    Function to make a CompExpr object.
    @param expr expression to complement
    @return new expression object
*/
Expr *makeComplementExpr( Expr *expr ) {
    CompExpr *this = (CompExpr *)malloc( sizeof( CompExpr ) );

    // Fill in virtual functions.
    this->eval = evalComplementExpr;
    this->destroy = destroyComplementExpr;

    // And other parts of the state.
    this->next = expr;

    return (Expr *) this;
}
