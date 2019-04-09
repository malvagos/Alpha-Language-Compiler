#pragma once
#include "SymTable.h"
typedef enum iopcode_t {
	assign,
	add,
	sub,
	mul,
	divi,
	mod,
	uminus,
	and,
	or,
	not,
	if_eq,
	if_noteq,
	if_lesseq,
	if_gratereq,
	if_less,
	if_greater,
	call,
	param,
	ret,
	getretval,
	funcstart,
	funcend,
	tablecreate,
	tablegetelem,
	tablesetelem
} Iopcode;

typedef enum expr_t {
	var_e,
	tableitem_e,

	programfunc_e,
	libraryfunc_e,

	arithexpr_e,
	boolexpr_e,
	assignexpr_e,
	newtable_e,

	constnum_e,
	constbool_e,
	conststring_e,

	nil_e
} Expr_t;

// extern struct expr; 
// extern struct quad;
typedef struct expr Expr;
typedef struct quad Quad;

struct expr {
	Expr_t type;
	SymbolTableRecord *sym;
	Expr *index;
	double numConst;
	char *strConst;
	unsigned char boolConst;
	Expr *next;
};
struct quad {
	Iopcode op;
	Expr *result;
	Expr *arg1;
	Expr *arg2;
	unsigned label;
	unsigned line;
};

extern const char *iopcodeNames[];
extern const char *expr_tNames[];

typedef enum scopespace_t {
    programvar,
    functionlocal,
    formalarg
} Scopespace_t;

typedef enum symbol_t {
	var_s,
	programfunc_s,
	libraryfunc_s
} Symbol_t;

// -----


extern unsigned programVarOffset;
extern unsigned functionLocalOffset;
extern unsigned formalArgOffset;
extern unsigned scopeSpaceCounter;

SymbolTableRecord *new_temp();

void reset_temp();

Expr *new_expr(Expr_t type);
Expr* lvalue_expr (SymbolTableRecord* sym);

Expr *newexpr_conststring(const char* name);

// dialexi 9, diafania 41
void expand();

void emit(Iopcode iopcode, Expr *arg1, Expr *arg2, Expr *result, unsigned label, unsigned line);

Expr *emit_iftableitem(Expr *e);

Expr *member_item(Expr *lvalue,char *name);

enum scopespace_t currscopespace(void);