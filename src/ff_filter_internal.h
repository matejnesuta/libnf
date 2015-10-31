
#ifndef _LNF_FILTER_INTERNAL_H
#define _LNF_FILTER_INTERNAL_H

#include <libnf_internal.h>
#include <libnf.h>

/* supported operations */
typedef enum {
	FF_OP_NOT,
	FF_OP_OR,
	FF_OP_AND,
	FF_OP_EQ,
	FF_OP_NE,
	FF_OP_LT,
	FF_OP_GT,
} ff_oper_t;

/* node of syntax tree */
typedef struct ff_filter_node_s {
	int field;                  /* field ID */
	char *value;                /*buffer allocated for data */
	int vsize;                  /* size of data in lvalue */
	int type;                   /* data type for lvalue */
	int numbits;                /* number of bits for IP adres */
	ff_oper_t oper;            /* operation */

	struct ff_filter_node_s *left;
	struct ff_filter_node_s *right;

} ff_filter_node_t;


/* scanner instance */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif


YY_BUFFER_STATE ff_filter_yy_scan_string(const char *str, yyscan_t yyscanner);
int ff_filter_yyparse(yyscan_t yyscanner, ff_filter_t *filter);
//int lnf_filter_yylex(YYSTYPE *yylval, void *scanner);



/* error function for scanner */
void yyerror(yyscan_t yyscanner, ff_filter_t *filter, char *);

/* conversion from string to numeric/bit value */
int str_to_uint(char *str, int type, char **res, int *vsize);
int str_to_addr(char *str, char **res, int *numbits);

/* add new node into parse tree */
ff_filter_node_t* ff_filter_new_leaf(yyscan_t scanner, char *fieldstr, ff_oper_t oper, char *valstr);
ff_filter_node_t* ff_filter_new_node(yyscan_t scanner, ff_filter_node_t* left, ff_oper_t oper, ff_filter_node_t* right);

/* evaluate filter */
int ff_filter_eval_node(ff_filter_node_t *node, void *rec);

#endif /* _LNF_FILTER_INTERNAL_H */

