/***************************************
* 	IFJ projekt 2018                   *
* 						               *
*	Autori:			                   *
*	Jan Beran (xberan43)	           *
*	Daniel Bubenicek (xbuben05)	       *
*	Jan Carba (xcarba00)		       *
*	Matej Jelinek (xjelen49)	       *
*                                      *
***************************************/
/**
*	@file parser.c
*	@authors Daniel Bubenicek, Jan Beran, Jan Carba, Matej Jelinek
*	@brief syntakticky analyzator shora dolu - rekurzivni pristup
*/

#include "parser.h"
#include "parser_expr.h"
#include "err_codes.h"
#include <string.h>

void buffer_init(TBuffer *buffer_stack)
{
    buffer_stack->top = NULL;
    buffer_stack->bottom = NULL;
}

bool buffer_push_bottom(TBuffer *buffer, Ttoken *token, TSynCommon *sa_vars) //push na bottom == na dno. Pouzivat opatrne
{
    TBufferElem *temp = (TBufferElem *) malloc(sizeof(TBufferElem));
    gc_add_garbage(sa_vars->gc, temp);
    if (temp == NULL)
        return false;


    temp->data = token;
    temp->prev = NULL;
    if(buffer->bottom == NULL) //zasobnik prazdny
    {
        temp->next = NULL;
        buffer->bottom = temp;
        buffer->top = temp;
    }
    else
    {
        temp->next = buffer->bottom;
        buffer->bottom->prev = temp;
        buffer->bottom = temp;
    }
    return true;
}

bool buffer_push_top(TBuffer *buffer, Ttoken *token, TSynCommon *sa_vars) //pushnuti na top
{
    TBufferElem *temp = (TBufferElem *) malloc(sizeof(TBufferElem));
    gc_add_garbage(sa_vars->gc, temp);
    if (temp == NULL)
        return false;
    temp->data = token;
    temp->next = NULL;
    if(buffer->bottom == NULL) //zasobnik prazdny
    {
        temp->prev = NULL;
        buffer->bottom = temp;
        buffer->top = temp;
    }
    else
    {
        temp->prev = buffer->top;
        buffer->top->next = temp;
        buffer->top = temp;
    }
    return true;
}

Ttoken *buffer_popTop(TBuffer *buffer) //pro savo
{
    if(buffer == NULL || buffer->top == NULL) //err handle: bud predan ukazatel na neexistujici buffer, nebo na prazdny buffer
        return  NULL;
    TBufferElem *temp = buffer->top;
    Ttoken *ret = temp->data;
    if(buffer->top != buffer->bottom) // neni jediny prvek
    {
        buffer->top = temp->prev;
        buffer->top->next = NULL;
    }
    else
    {
        buffer->top = NULL;
        buffer->bottom = NULL;
    }
    return ret;
}

Ttoken *buffer_popBottom(TBuffer *buffer) //rpo sax
{
    if(buffer == NULL)
        return NULL;
    TBufferElem *temp = buffer->bottom;
    Ttoken *ret = temp->data;
    if(buffer->top == buffer->bottom) //zasobnik ma jediny prvek
    {
        buffer->top = NULL;
        buffer->bottom = NULL;
    }
    else
    {
        buffer->bottom = temp->next;
        buffer->bottom->prev = NULL;
    }
    return ret;
}

void delete_buffer(TBuffer *buffer)  //nevyuzito
{
    if(buffer != NULL)
    {
        TBufferElem *temp = NULL;// = stack->top;
        while (buffer->top != NULL)
        {
            temp = buffer->top;
            buffer->top = buffer->top->prev;
            if(temp != NULL)
            {
                if(temp->data != NULL)
                {
                    //dealok tokenu:
                    //free(temp->data->attribute); //dealok vnitrku tokenu
                    //free(temp->data); //dealok tokenu
                }
                //free(temp); //dealok buffer elem
            }
        }
        buffer->bottom = NULL;
       // free(buffer);
    }
}

bool buffer_empty(TBuffer *buffer)
{
    return (buffer->top == NULL);
}

//Funkce pro praci se stackem tabulek symbolů

void TS_stack_init(TSymtables_stack *stack)
{
    stack->top = NULL;
    stack->bottom = NULL;
}

bool TS_push(TSymtables_stack *stack, Tsymbol_table *table)
{
    TLTElem *temp = (TLTElem *) malloc(sizeof(TLTElem));  //TS si dealokaci resi sama
    if(temp == NULL)
        return false;
    temp->data = table;
    temp->prev = stack->top;
    if(stack->bottom == NULL) //zasobnik je prazdny
        stack->bottom = temp;
    stack->top = temp;
    return true;
}

Tsymbol_table *TS_pop(TSymtables_stack *stack)
{
    if(stack == NULL)
        return NULL;
    TLTElem *temp;
    Tsymbol_table *ret;
    temp = stack->top;
    ret = temp->data;
    if(stack->top == stack->bottom) // jeden prvek v zasobobniku
        stack->bottom = NULL;
    stack->top = stack->top->prev;
    free(temp);
    return ret;
}

Ttoken *get_next_token(TSynCommon *sa_vars)
{
    Ttoken *ret = NULL;
    if(!buffer_empty(sa_vars->buffer))
        ret = buffer_popBottom(sa_vars->buffer);
    else
    {
        ret = get_token(sa_vars->arr, sa_vars->gc);
    }
    return ret;
}

int startSA(TTacList *list, TSymtables_stack *symtabs_bin, Tgarbage_collector *gc)
{
    TSynCommon *sa_vars = alloc_sa(gc);
    if(sa_vars == NULL)
        return ERR_INTERNAL;

    sa_vars->tac_list = list;
    sa_vars->symtabs_bin = symtabs_bin;
    sa_vars->gc = gc;

    sa_vars->err_code = IN_PROGRESS;
    while(sa_vars->err_code == IN_PROGRESS) //dokud je co prekladat, prekladam
    {
        if (!progr(sa_vars))
        {
            if (sa_vars->err_code == IN_PROGRESS) //pokud neni doplnen jiny err_code, nastala syntakticka chyba
            {
                sa_vars->err_code = ERR_SYN;
                fprintf(stderr, MESSAGE_SYN);
            }
            break;
        }
    }
    TS_push(sa_vars->symtabs_bin, TS_pop(sa_vars->local_tables)); //prevedeni TS pro "main" do bin
    int ret = sa_vars->err_code;
    list = sa_vars->tac_list;
    symtabs_bin = sa_vars->symtabs_bin;
    dealloc_sa(sa_vars);
    return ret;
}

bool progr(TSynCommon *sa_vars)
{
    sa_vars->dest = NULL;
    sa_vars->ret = NULL;

    Ttoken *token = get_next_token(sa_vars);
    if(!err_check(token, sa_vars))
        return false;

    if(token->type == KEY_DEF)
    {
        buffer_push_bottom(sa_vars->buffer, token, sa_vars);
        return nt_deffunc(sa_vars);
    }
    else if(token->type == EOL_1 || token->type == EOF_STATE)
    {
        buffer_push_bottom(sa_vars->buffer, token, sa_vars);
        return nt_eolf(sa_vars);
    }
    else if(token->type == KEY_WHILE)
    {
        buffer_push_bottom(sa_vars->buffer, token, sa_vars);
        return nt_cycl(sa_vars);
    }
    else if(token->type == KEY_IF)
    {
        buffer_push_bottom(sa_vars->buffer, token, sa_vars);
        return nt_ifthenelse(sa_vars);
    }
    else if(token->type == ID_2) //prislo ID: hrozi expression, assignment, callfce
    {
       Ttoken *look_ahead = get_next_token(sa_vars);
        if(!err_check(token, sa_vars))
        {
            return false;
        }
       if(look_ahead->type == OP_EQAL_2) //prislo "=" tedy jednoznacne assignment
       {
           buffer_push_bottom(sa_vars->buffer, look_ahead, sa_vars); //vraceni tokenu ve spravnem poradi
           buffer_push_bottom(sa_vars->buffer, token, sa_vars);
           return nt_assignment(sa_vars);
       }
       else if(symtab_find(sa_vars->ts_fun, token->attribute) == NULL) //neni v TS funkci, a je vylouceno i assignment takze je to expression
       {
           buffer_push_bottom(sa_vars->buffer, look_ahead, sa_vars); //vraceni tokenu ve spravnem poradi
           buffer_push_bottom(sa_vars->buffer, token, sa_vars);
           return nt_expression(sa_vars);
       }
       else //ostatni jsem vyloucil, takze zbyva moznost volani fce
       {
            buffer_push_bottom(sa_vars->buffer, look_ahead, sa_vars); //vraceni tokenu ve spravnem poradi
            buffer_push_bottom(sa_vars->buffer, token, sa_vars);
            return nt_callfce(sa_vars);
       }
    }
    else if(token->type == ID_FCE) //muze byt jen volani fce
    {
        if(symtab_find(sa_vars->ts_fun, token->attribute) == NULL) //pokud neni v TS funkci, tak je to chyba
        {
            buffer_push_bottom(sa_vars->buffer, token, sa_vars);
            return false;
        }
        else
        {
            buffer_push_bottom(sa_vars->buffer, token, sa_vars);
            return nt_callfce(sa_vars);
        }
    }
    else //zbyva snad uz jen vyraz
    {
        buffer_push_bottom(sa_vars->buffer, token, sa_vars);
        return nt_expression(sa_vars);
    }
}

bool nt_deffunc(TSynCommon *sa_vars)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type != KEY_DEF)
        return false;
    t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;

    if(t1->type == ID_FCE || t1->type == ID_2)
    {
        if(symtab_find(sa_vars->ts_fun, t1->attribute) == NULL && !is_in_local_symtabs(sa_vars, t1->attribute)) // symtab_find(sa_vars->local_tables->bottom->data, t1->attribute) == NULL) //pokud jeste takove ID neexistuje
        {
            symtab_edit_add(sa_vars->ts_fun, t1->attribute, true, NOBODY_CARES);
            TS_push(sa_vars->local_tables, symtab_init(TS_SIZE)); //vytvorim novou lokalni TS pro telo fce
            Ttoken *t2 = get_next_token(sa_vars);
            if(!err_check(t1, sa_vars))
            {
                return false;
            }
            if (t2->type != LEFT_BRACKET)
                return false;

            //*****ZACATEK TVORBY KODU **************************************/
            char *label_str = sax_temp_id_generator(sa_vars->gc);
            if(label_str == NULL)
                return false;
            Toperand *label = op_init(KEY_NIL, label_str, sa_vars->gc);
            if(label == NULL)
            {
                sa_vars->err_code = ERR_INTERNAL;
                return false;
            }

            Toperand *op = op_init(t1->type, t1->attribute, sa_vars->gc);
            if(op == NULL)
            {
                sa_vars->err_code = ERR_INTERNAL;
                return false;
            }
            tac_deffunc(sa_vars->tac_list, op, label, sa_vars->gc);


            char *nil_str = sax_temp_id_generator(sa_vars->gc);
            if(nil_str == NULL)
                return false;

            char *nil_const_str = (char *) malloc(sizeof(char)*4); //nil\0
            gc_add_garbage(sa_vars->gc, nil_const_str);
            if(nil_const_str == NULL)
                return false;
            strcpy(nil_const_str, "nil");
            Toperand *op_nil_const = op_init(KEY_NIL, nil_const_str, sa_vars->gc);

            //vytvorim promennou kam mohou prikazy vracet svou navratovou hodnotu
            char *ret_str = sax_temp_id_generator(sa_vars->gc);
            if(ret_str == NULL)
                return false;
            Toperand *ret = op_init(KEY_NIL, ret_str, sa_vars->gc);
            if(ret == NULL)
            {
                sa_vars->err_code = ERR_INTERNAL;
                return false;
            }
            tac_defmove_const(sa_vars->tac_list, ret, op_nil_const, sa_vars->gc);
            sa_vars->ret = ret; //z tohodle operandu si vezmu navratovou hodnotu
            //******KONEC TVORBY KODU******************************************************************/

            if (!nt_params(sa_vars))
                return false;

            //uz znam pocet parametru fce
            symtab_edit_add(sa_vars->ts_fun, t1->attribute, true, (long int) symtab_get_size(sa_vars->local_tables->top->data));

            t1 = get_next_token(sa_vars);
            if(!err_check(t1, sa_vars))
                return false;

            if (t1->type != RIGHT_BRACKET)
                return false;

            t1 = get_next_token(sa_vars);
            if(!err_check(t1, sa_vars))
                return false;

            if (t1->type != EOL_1)
                return false;

            if (!nt_bodyfce(sa_vars))
                return false;

            t1 = get_next_token(sa_vars);
            if(!err_check(t1, sa_vars))
                return false;

            if (t1->type != KEY_END)
                return false;

            tac_return(sa_vars->tac_list, sa_vars->ret, label, sa_vars->gc);

            TS_push(sa_vars->symtabs_bin, TS_pop(sa_vars->local_tables)); //lokalni tabulku "hodim do kose", kam se pak divam kvuli kolizi nazvu promenne a fce

            if (!nt_eolf(sa_vars))
                return false;

            return true; //uz jsem na konci, vse probehlo OK
        }
        else
        {
            sa_vars->err_code = ERR_SEM_MISC;
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool nt_cycl(TSynCommon *sa_vars)       //cycl -> WHILE EXPR  DO EOL bodywhif END eolf
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type != KEY_WHILE)           //WHILE
    {
        return false;
    }

    //ZACATEK TVORBY KODU*************************************//
    tac_while(sa_vars->tac_list, sa_vars->gc); //"zarazka" pro zacatek while

    char *bool_str = sax_temp_id_generator(sa_vars->gc);
    if(bool_str == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    Toperand *bool_temp = op_init(BOOLEAN, bool_str, sa_vars->gc);
    if(bool_temp == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }

    char *cons_str = long_to_string(1, sa_vars->gc);
    if(cons_str == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    Toperand *cons_temp = op_init(BOOLEAN, cons_str, sa_vars->gc);
    if(cons_temp == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    tac_defmove_const(sa_vars->tac_list, bool_temp, cons_temp, sa_vars->gc); //true konstanta, kvuli urceni skoku

    char *temp_cond_str = sax_temp_id_generator(sa_vars->gc);
    if(temp_cond_str == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    Toperand *temp_cond = op_init(NOBODY_CARES, temp_cond_str, sa_vars->gc);
    if(temp_cond == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    tac_defvar(sa_vars->tac_list, temp_cond, sa_vars->gc);

    char *temp_label = sax_temp_id_generator(sa_vars->gc);
    if(temp_label == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    Toperand *label1 = op_init(NOBODY_CARES, temp_label, sa_vars->gc);
    if(label1 == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    tac_lable(sa_vars->tac_list, label1, sa_vars->gc);

    //KONEC TVORBY KODU*************************************//

    sa_vars->dest = temp_cond;

    sa_vars->boolean = true; //muze to byt typ boolean
    if(!savo(sa_vars))                       //EXPR
    {
        return false;
    }
    sa_vars->boolean = false; //vracim do vychoziho stavu
    sa_vars->dest = NULL; //vracim do vychoziho stavu

    //ZACATEK TVORBY KODU*************************************//
    char *temp_label2_str = sax_temp_id_generator(sa_vars->gc);
    if(temp_label2_str == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    Toperand *label2 = op_init(NOBODY_CARES, temp_label2_str, sa_vars->gc);
    if(label2 == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }

    tac_jumpifneq(sa_vars->tac_list, label2, bool_temp, temp_cond, sa_vars->gc);
    //KONEC TVORBY KODU*************************************//

    t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars)) {
        return false;
    }
    if(t1->type != KEY_DO)              //DO
    {
        return false;
    }
    t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars)) {
        return false;
    }
    if(t1->type != EOL_1)               //EOL
    {
        return false;
    }
    if(!nt_bodywhif(sa_vars))           //bodywhif
    {
        return false;
    }
    t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars)) {
        return false;
    }
    if(t1->type != KEY_END)             //END
    {
        return false;
    }

    tac_jump(sa_vars->tac_list, label1, sa_vars->gc);
    tac_lable(sa_vars->tac_list, label2, sa_vars->gc);
    tac_endwhile(sa_vars->tac_list, sa_vars->gc);

    if(nt_eolf(sa_vars))                //eolf
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool nt_eolf(TSynCommon *sa_vars)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(t1->type == EOL_1) //EOF NEBO EOL
    {
        return true;
    }
    else if(t1->type == EOF_STATE)
    {
        sa_vars->err_code = SUCCESS;
        return true;
    }
    else
    {
        return false;
    }
}

bool nt_expression(TSynCommon *sa_vars)
{
    bool dest = sa_vars->dest == NULL;
    if(dest) //pokud nikdo nepotrebuje vysledek, musim stejne nejaky vyrobit kvuli savu a pripadne navratove hodnote fce
    {
        char *temp = sax_temp_id_generator(sa_vars->gc);
        if(temp == NULL)
        {
            sa_vars->err_code = ERR_INTERNAL;
            return false;
        }
        sa_vars->dest = op_init(NOBODY_KNOWS, temp, sa_vars->gc);
        if(sa_vars->dest == NULL)
        {
            sa_vars->err_code = ERR_INTERNAL;
            return false;
        }
        tac_defvar(sa_vars->tac_list, sa_vars->dest, sa_vars->gc);
    }

    if(!savo(sa_vars))
    {
        return false;
    }

    if(sa_vars->ret != NULL)
        tac_move(sa_vars->tac_list, sa_vars->ret, sa_vars->dest, sa_vars->gc);

    if(dest) //vracim zpet na null jen pokud to byl null i predtim
        sa_vars->dest = NULL;

    return nt_eolf(sa_vars);
}

bool nt_ifthenelse(TSynCommon *sa_vars)
{
    //ZACATEK TVORBY KODU*************************************//
    ta_startif(sa_vars->tac_list, sa_vars->gc); //zarazka

    char *bool_str = sax_temp_id_generator(sa_vars->gc);
    if(bool_str == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    Toperand *bool_temp = op_init(BOOLEAN, bool_str, sa_vars->gc);
    if(bool_temp == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }

    char *cons_str = long_to_string(1, sa_vars->gc);
    if(cons_str == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    Toperand *cons_temp = op_init(BOOLEAN, cons_str, sa_vars->gc);
    if(cons_temp == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    tac_defmove_const(sa_vars->tac_list, bool_temp, cons_temp, sa_vars->gc); //true konstanta, kvuli urceni skoku

    char *temp_cond_str = sax_temp_id_generator(sa_vars->gc);
    if(temp_cond_str == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    Toperand *temp_cond = op_init(NOBODY_CARES, temp_cond_str, sa_vars->gc);
    if(temp_cond == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    tac_defvar(sa_vars->tac_list, temp_cond, sa_vars->gc); //promenna pro podminku

    char *temp_label = sax_temp_id_generator(sa_vars->gc); //label1
    if(temp_label == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    Toperand *label1 = op_init(NOBODY_CARES, temp_label, sa_vars->gc);
    if(label1 == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }

    char *temp_label2_str = sax_temp_id_generator(sa_vars->gc); //priprava pro label2
    if(temp_label2_str == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }
    Toperand *label2 = op_init(NOBODY_CARES, temp_label2_str, sa_vars->gc);
    if(label2 == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }

    //KONEC TVORBY KODU*************************************//
    sa_vars->dest = temp_cond; //sem mi da savo vysledek vyrazu

    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type != KEY_IF) //IF
    {
        return false;
    }

    sa_vars->boolean = true; //muze byt typu bool
    if(!savo(sa_vars)) //EXPR
    {
        return false;
    }
    sa_vars->boolean = false; //vracim do vychoziho stavu
    sa_vars->dest = NULL; //vravcim do vychoziho stavu

    t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type != KEY_THEN) //THEN
    {
        return false;
    }

    t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type != EOL_1) //EOL
    {
        return false;
    }

    tac_jumpifneq(sa_vars->tac_list, label1, temp_cond, bool_temp, sa_vars->gc);

    if(!nt_bodywhif(sa_vars))           //IFBODY
    {
        return false;
    }
    t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;

    tac_jump(sa_vars->tac_list, label2, sa_vars->gc);

    if(t1->type != KEY_ELSE) //ELSE
    {
        return false;
    }

    t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type != EOL_1) //EOL
    {
        return false;
    }

    tac_lable(sa_vars->tac_list, label1, sa_vars->gc);

    if(!nt_bodywhif(sa_vars))           //ELSEBODY
    {
        return false;
    }
    t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type != KEY_END)             //END
    {
        return false;
    }

    tac_lable(sa_vars->tac_list, label2, sa_vars->gc);
    ta_endif(sa_vars->tac_list, sa_vars->gc); //konec zarazky

    if(nt_eolf(sa_vars))                //EOLF
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool nt_args(TSynCommon *sa_vars, long *num_of_args)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if((t1->type == RIGHT_BRACKET) || (t1->type == EOL_1) || (t1->type == EOF_STATE))
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        return true;
    }
    buffer_push_bottom(sa_vars->buffer, t1, sa_vars);

    //***************ZACATEK TVROBY KODU*****************************************************************//
    Toperand *backup = sa_vars->dest; //zaloha operandu v dest, at uz null nebo neco konkretniho
    char *temp_id = sax_temp_id_generator(sa_vars->gc);
    if(temp_id == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }

    Toperand *op = op_init(NOBODY_KNOWS, temp_id, sa_vars->gc);
    if(op == NULL)
    {
        sa_vars->err_code = ERR_INTERNAL;
        return false;
    }

    tac_defvar(sa_vars->tac_list, op, sa_vars->gc);
    //**********KONEC TVORBY KODU*******************************************************************//

    sa_vars->dest = op; //reknu savu, aby mi ulozilo vyraz do teto promenne

    if(!savo(sa_vars))
    {
        sa_vars->dest = backup; //vracim do vychoziho stavu
        return false;
    }
    sa_vars->dest = backup; //vracim do vychoziho stavu

    (*num_of_args)++; //pribyl argument
    if(nt_nextargs(sa_vars, num_of_args))
    {
        tac_push(sa_vars->tac_list, op, sa_vars->gc);
        return true;
    }
    else
        return false;
}

bool nt_nextargs(TSynCommon *sa_vars, long *num_of_args)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type == OP_COMMA) //RULE33
    {
        //***************ZACATEK TVROBY KODU*****************************************************************//
        Toperand *backup = sa_vars->dest; //zaloha operandu v dest, at uz null nebo neco konkretniho
        //vygeneruju nejakou docasnou promennou a predam ji savu
        char *temp_id = sax_temp_id_generator(sa_vars->gc);
        if(temp_id == NULL)
        {
            sa_vars->err_code = ERR_INTERNAL;
            return false;
        }
        Toperand *op = op_init(NOBODY_KNOWS, temp_id, sa_vars->gc);
        if(op == NULL)
        {
            sa_vars->err_code = ERR_INTERNAL;
            return false;
        }
        tac_defvar(sa_vars->tac_list, op, sa_vars->gc);
        sa_vars->dest = op; //reknu savu aby mi to dal do te docasne promenne
        //**********KONEC TVORBY KODU*******************************************************************//

        if(!savo(sa_vars))
        {
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            sa_vars->dest = backup; //vracim do vychoziho stavu
            return false;
        }
        sa_vars->dest = backup; //vracim do vychoziho stavu

        (*num_of_args)++; //pribyl argument
        if(nt_nextargs(sa_vars, num_of_args))
        {
            tac_push(sa_vars->tac_list, op, sa_vars->gc);

            return true;
        }
        else
        {
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars); //nepovedlo se, musim vratit pro pripadny dalsi pokus
            return false;
        }
    }
    else if((t1->type == RIGHT_BRACKET) || (t1->type == EOL_1) || (t1->type == EOF_STATE)) //RULE 32
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        return true;
    }
    else
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        return false;
    }
}

bool nt_right(TSynCommon *sa_vars)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type == ID_FCE || t1->type == ID_2)
    {
        if (symtab_find(sa_vars->ts_fun, t1->attribute) != NULL)
        {
            //je to id_fce
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            if(nt_callfce(sa_vars))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    //cekam EXPR
    buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
    if(savo(sa_vars))
    {
        if(nt_eolf(sa_vars))                //eolf
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}

bool nt_assignment(TSynCommon *sa_vars)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type == ID_2)
    {
        if(symtab_find(sa_vars->ts_fun, t1->attribute) == NULL) //neni to funkce
        {
            if(symtab_find(sa_vars->local_tables->top->data, t1->attribute) == NULL) //jeste neni definovana
            {
                symtab_edit_add(sa_vars->local_tables->top->data, t1->attribute, 1, NOBODY_CARES); //pridani promenne do lokalni TS
                //zalozeni nove promenne
                Toperand *op = op_init(NOBODY_KNOWS, t1->attribute, sa_vars->gc);
                if(op == NULL)
                {
                    sa_vars->err_code = ERR_INTERNAL;
                    return false;
                }
                tac_defvar(sa_vars->tac_list, op, sa_vars->gc);
                sa_vars->dest = op;

            }
            else
            {
                Toperand *op = op_init(symtab_find(sa_vars->local_tables->top->data, t1->attribute)->type, t1->attribute, sa_vars->gc); //zakladam operand s typem z TS
                if(op == NULL)
                {
                    sa_vars->err_code = ERR_INTERNAL;
                    return false;
                }
                sa_vars->dest = op;
            }

            //uz je definovana
            t1 = get_next_token(sa_vars);
            if(!err_check(t1, sa_vars))
                return false;
            if(t1->type != OP_EQAL_2)       //=
            {
                return false;
            }

            if(nt_right(sa_vars))           //right
            {
                if(sa_vars->ret != NULL)
                    tac_move(sa_vars->tac_list, sa_vars->ret, sa_vars->dest, sa_vars->gc); //navratovou hodnotu z fce/vyrazu, ktera je v dest, ulozim do ret (pokud o to nekdo stoji)
                sa_vars->dest = NULL;
                return true;
            }
            else
            {
                return false;
            }
        }
        else //neni to validni leva strana prirazeni
        {
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            return false;
        }
    }
    else //neni to ID_2
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        return false;
    }
}

bool nt_nextparams(TSynCommon *sa_vars)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type == RIGHT_BRACKET || t1->type == OP_COMMA)
    {
        if(t1->type == RIGHT_BRACKET)
        {
            buffer_push_bottom(sa_vars->buffer,t1, sa_vars);
            return true;
        }
        else
        {
            t1 = get_next_token(sa_vars);
            if(!err_check(t1, sa_vars))
                return false;
            if(t1->type == ID_2)
            {
                if(symtab_find(sa_vars->local_tables->top->data, t1->attribute) != NULL)
                {
                    return false;
                    //je uz definovana
                }
                else
                {
                    if(symtab_find(sa_vars->ts_fun, t1->attribute) != NULL)
                    {
                        return false;
                        //je to id_fce
                    }
                    else
                    {
                        symtab_edit_add(sa_vars->local_tables->top->data, t1->attribute, true, NOBODY_CARES);

                        Toperand *op = op_init(t1->type, t1->attribute, sa_vars->gc);
                        if(op == NULL)
                        {
                            sa_vars->err_code = ERR_INTERNAL;
                            return false;
                        }
                        tac_loadparam(sa_vars->tac_list, op, sa_vars->gc);

                        if(nt_nextparams(sa_vars))
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                        //neni definovana ani ve func --> add_id
                    }
                }
            }
            else //neni ID_2
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
}


bool nt_params(TSynCommon *sa_vars)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type == RIGHT_BRACKET)
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        return true;
    }
    else
    {
        //t1 = get_next_token(sa_vars);
        if(t1->type == ID_2)
        {
            if(symtab_find(sa_vars->local_tables->top->data, t1->attribute) != NULL)
            {
                return false;
                //je uz definovana
            }
            else
            {
                if(symtab_find(sa_vars->ts_fun, t1->attribute) != NULL)
                {
                    return false;
                    //je to id_fce
                }
                else
                {
                    symtab_edit_add(sa_vars->local_tables->top->data, t1->attribute, true, NOBODY_CARES);

                    Toperand *op = op_init(t1->type, t1->attribute, sa_vars->gc);
                    if(op == NULL)
                    {
                        sa_vars->err_code = ERR_INTERNAL;
                        return false;
                    }
                    tac_loadparam(sa_vars->tac_list, op, sa_vars->gc);


                    if(nt_nextparams(sa_vars))
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                    //neni definovana ani ve func --> add_id
                }
            }
        }
        else //neni ID_2
        {
            return false;
        }
    }
}

bool nt_callfce(TSynCommon *sa_vars)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;

    if(!(t1->type == ID_2 || t1->type == ID_FCE)) //neni IDFCE
    {
        return false;
    }
    if(symtab_find(sa_vars->ts_fun, t1->attribute) == NULL) //neni v TS funkci
    {
        sa_vars->err_code = ERR_SEM_DEF;
        return false;
    }

    long num_of_args = 0; //pocitadlo argumentu pro overeni s TS
    if(!nt_args(sa_vars, &num_of_args)) //nepovedlo se, zkusim tedy jestli nebyla zavorka, pokud ano, zkusim to znovu
    {
        num_of_args = 0;
        Ttoken *t2 = get_next_token(sa_vars);
        if(!err_check(t2, sa_vars))
            return false;
        if(t2->type != LEFT_BRACKET) //zkusim sezrat levou zavorku a zavolat to znovu
            return false;
        if(!nt_args(sa_vars, &num_of_args))
            return false;

        t2 = get_next_token(sa_vars);
        if(!err_check(t2, sa_vars))
            return false;

        if(t2->type != RIGHT_BRACKET) //pokud neprisla i prava zavorka, fakt to nepujde...
            return false;
    } //muzu pokraovat normalne

    if(!check_num_of_params(sa_vars->ts_fun, t1, num_of_args)) //nesedi pocet parametru s definici
    {
        sa_vars->err_code = ERR_SEM_PARAM;
        fprintf(stderr, MESSAGE_SEM_PARAM);
        return false;
    }

    //*********************************ZACATEK TVORBY KODU ************************************************************//
    if(!strcmp(t1->attribute, "print")) //specialne pro fci print pushuju i pocet paramatru se kterymi je volana
    {
        char *temp_id = sax_temp_id_generator(sa_vars->gc);
        if (temp_id == NULL) {
            return false;
        }
        Toperand *new_op = op_init(INTEGER, temp_id, sa_vars->gc); //sem dam pocet argumentu
        if (new_op == NULL) {
            return false;
        }

        char *str_num_of_args = long_to_string(num_of_args, sa_vars->gc);
        if (str_num_of_args == NULL) {
            return false;
        }
        Toperand *cons = op_init(INTEGER, str_num_of_args, sa_vars->gc);
        if (cons == NULL) {
            return false;
        }
        //problem: do defmoveconst prijde &sax1 &sax1, ale zadna hodnota
        tac_defmove_const(sa_vars->tac_list, new_op, cons, sa_vars->gc);
        tac_push(sa_vars->tac_list, new_op, sa_vars->gc); //pushnuti informace o poctu argumentu na zasobnik
    }
    bool dest_bool = sa_vars->dest == NULL;
    if(dest_bool) //nikoho nezajima kam to hodim, presto musim nejakou dest. vytvorit protoze nase CALL vzdy popne zasobnik
    {
        char *temp = sax_temp_id_generator(sa_vars->gc);
        if(temp == NULL)
        {
            sa_vars->err_code = ERR_INTERNAL;
            return false;
        }
        sa_vars->dest = op_init(NOBODY_KNOWS, temp, sa_vars->gc);
        if(sa_vars->dest == NULL)
        {
            sa_vars->err_code = ERR_INTERNAL;
            return false;
        }
        tac_defvar(sa_vars->tac_list, sa_vars->dest, sa_vars->gc);
    }

    Toperand *label = op_init(t1->type,t1->attribute, sa_vars->gc);
    if(label == NULL)
    {
        return false;
    }

    tac_call(sa_vars->tac_list, sa_vars->dest, label, sa_vars->gc);

    if(sa_vars->ret != NULL)
        tac_move(sa_vars->tac_list, sa_vars->ret, sa_vars->dest, sa_vars->gc);
    //***********KONEC TVORBY KODU****************************************************************//

    if(dest_bool) //vratim do vychoziho stavu, pokus to nikoho nezajimalo
        sa_vars->dest = NULL;

    if(!nt_eolf(sa_vars))
        return false;

    return true;
}

bool nt_bodyfce(TSynCommon *sa_vars)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type == EOL_1) //RULE 8
    {
        if(nt_bodyfce(sa_vars))
        {
            return true;
        }
        return false;
    }
    else if(t1->type == KEY_DEF) //RULE 6
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        if(!nt_deffunc(sa_vars))
        {
            return false;
        }
        return nt_bodyfce(sa_vars);
    }
    else if(t1->type == KEY_IF) //RULE10
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        if(!nt_ifthenelse(sa_vars))
        {
            return false;
        }
        return nt_bodyfce(sa_vars);
    }
    else if(t1->type == KEY_WHILE) //RULE9
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        if(!nt_cycl(sa_vars))
        {
            return false;
        }
        return nt_bodyfce(sa_vars);
    }
    else if(t1->type == ID_2) //prislo ID: hrozi expression, assignment, callfce
    {
        Ttoken *look_ahead = get_next_token(sa_vars);
        if(!err_check(look_ahead, sa_vars))
            return false;
        if(look_ahead->type == OP_EQAL_2) //prislo "=" tedy jednoznacne assignment
        {
            buffer_push_bottom(sa_vars->buffer, look_ahead, sa_vars); //vraceni tokenu ve spravnem poradi
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            if(!nt_assignment(sa_vars))
            {
                return false;
            }
            return nt_bodyfce(sa_vars);
        }
        else if(symtab_find(sa_vars->ts_fun, t1->attribute) == NULL) //neni v TS funkci, a je vylouceno i assignment takze je to expression
        {
            buffer_push_bottom(sa_vars->buffer, look_ahead, sa_vars); //vraceni tokenu ve spravnem poradi
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            if(nt_expression(sa_vars))
            {
                return nt_bodyfce(sa_vars);
            }
            return false;
        }
        else //ostatni jsem vyloucil, takze zbyva moznost volani fce
        {
            buffer_push_bottom(sa_vars->buffer, look_ahead, sa_vars); //vraceni tokenu ve spravnem poradi
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            if(nt_callfce(sa_vars))
            {
                return nt_bodyfce(sa_vars);
            }
            return false;
        }
    }
    else if(t1->type == ID_FCE) //muze byt jen volani fce
    {
        if(symtab_find(sa_vars->ts_fun, t1->attribute) == NULL) //pokud neni v TS funkci, tak je to chyba
        {
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            return false;
        }
        else
        {
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            return nt_callfce(sa_vars);
        }
    }
    else if(t1->type == KEY_END)
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        return true;
    }
    else
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        return nt_expression(sa_vars); //zbyva snad jen vyraz z konstanty
    }
}

bool nt_bodywhif(TSynCommon *sa_vars)
{
    Ttoken *t1 = get_next_token(sa_vars);
    if(!err_check(t1, sa_vars))
        return false;
    if(t1->type == EOL_1) //RULE 8
    {
        if(nt_bodywhif(sa_vars))
        {
            return true;
        }
        return false;
    }
    else if(t1->type == KEY_IF) //RULE10
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        if(!nt_ifthenelse(sa_vars))
        {
            return false;
        }
        return nt_bodywhif(sa_vars);
    }
    else if(t1->type == KEY_WHILE) //RULE9
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        if(!nt_cycl(sa_vars))
        {
            return false;
        }
        return nt_bodywhif(sa_vars);
    }
    else if(t1->type == ID_2) //prislo ID: hrozi expression, assignment, callfce
    {
        Ttoken *look_ahead = get_next_token(sa_vars);
        if(!err_check(look_ahead, sa_vars))
            return false;
        if(look_ahead->type == OP_EQAL_2) //prislo "=" tedy jednoznacne assignment
        {
            buffer_push_bottom(sa_vars->buffer, look_ahead, sa_vars); //vraceni tokenu ve spravnem poradi
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            if(!nt_assignment(sa_vars))
            {
                return false;
            }
            return nt_bodywhif(sa_vars);
        }
        else if(symtab_find(sa_vars->ts_fun, t1->attribute) == NULL) //neni v TS funkci, a je vylouceno i assignment takze je to expression
        {
            buffer_push_bottom(sa_vars->buffer, look_ahead, sa_vars); //vraceni tokenu ve spravnem poradi
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            if(nt_expression(sa_vars))
            {
                return nt_bodywhif(sa_vars);
            }
            return false;
        }
        else //ostatni jsem vyloucil, takze zbyva moznost volani fce
        {
            buffer_push_bottom(sa_vars->buffer, look_ahead, sa_vars); //vraceni tokenu ve spravnem poradi
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            if(nt_callfce(sa_vars))
            {
                return nt_bodywhif(sa_vars);
            }
            return false;
        }
    }
    else if(t1->type == ID_FCE) //muze byt jen volani fce
    {
        if(symtab_find(sa_vars->ts_fun, t1->attribute) == NULL) //pokud neni v TS funkci, tak je to chyba
        {
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            return false;
        }
        else
        {
            buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
            return nt_callfce(sa_vars);
        }
    }
    else if(t1->type == KEY_END  || t1->type == KEY_ELSE)
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        return true;
    }
    else
    {
        buffer_push_bottom(sa_vars->buffer, t1, sa_vars);
        return nt_expression(sa_vars); //zbyva snad jen vyraz z konstanty
    }
}


bool init_ts_fun(TSynCommon *sa_vars, Tgarbage_collector *gc)
{
    sa_vars->ts_fun = symtab_init(TS_SIZE);
    if(sa_vars->ts_fun == NULL) //chyba alokace
        return false;


    char *inputs = (char *) malloc(sizeof(char) * 7); //7 je potrebna delka pro nejdelsi nazev integrovane fce (6znaku + ukoncovaci)
    char *inputi = (char *) malloc(sizeof(char) * 7); //7 je potrebna delka pro nejdelsi nazev integrovane fce (6znaku + ukoncovaci)
    char *inputf = (char *) malloc(sizeof(char) * 7); //7 je potrebna delka pro nejdelsi nazev integrovane fce (6znaku + ukoncovaci)
    char *print = (char *) malloc(sizeof(char) * 7); //7 je potrebna delka pro nejdelsi nazev integrovane fce (6znaku + ukoncovaci)
    char *length = (char *) malloc(sizeof(char) * 7); //7 je potrebna delka pro nejdelsi nazev integrovane fce (6znaku + ukoncovaci)
    char *substr = (char *) malloc(sizeof(char) * 7); //7 je potrebna delka pro nejdelsi nazev integrovane fce (6znaku + ukoncovaci)
    char *ord = (char *) malloc(sizeof(char) * 7); //7 je potrebna delka pro nejdelsi nazev integrovane fce (6znaku + ukoncovaci)
    char *chr = (char *) malloc(sizeof(char) * 7); //7 je potrebna delka pro nejdelsi nazev integrovane fce (6znaku + ukoncovaci)

    gc_add_garbage(gc, inputs);
    gc_add_garbage(gc, inputi);
    gc_add_garbage(gc, inputf);
    gc_add_garbage(gc, print);
    gc_add_garbage(gc, length);
    gc_add_garbage(gc, substr);
    gc_add_garbage(gc, ord);
    gc_add_garbage(gc, chr);

    if(inputs == NULL || inputi == NULL || inputf == NULL || print == NULL
        || length == NULL || substr == NULL || ord == NULL || chr == NULL) //nepovedena alokace
    {
        return false;
    }

    strcpy(inputs, "inputs");
    strcpy(inputi, "inputi");
    strcpy(inputf, "inputf");
    strcpy(print, "print");
    strcpy(length, "length");
    strcpy(substr, "substr");
    strcpy(ord, "ord");
    strcpy(chr, "chr");

    Tsymbol_table_item *a = symtab_edit_add(sa_vars->ts_fun, inputs, true, 0);
    Tsymbol_table_item *b = symtab_edit_add(sa_vars->ts_fun, inputi, true, 0);
    Tsymbol_table_item *c = symtab_edit_add(sa_vars->ts_fun, inputf, true, 0);
    Tsymbol_table_item *d = symtab_edit_add(sa_vars->ts_fun, print, true, ZERO_TO_INF);
    Tsymbol_table_item *e = symtab_edit_add(sa_vars->ts_fun, length, true, 1);
    Tsymbol_table_item *f = symtab_edit_add(sa_vars->ts_fun, substr, true, 3);
    Tsymbol_table_item *g = symtab_edit_add(sa_vars->ts_fun, ord, true, 2);
    Tsymbol_table_item *h = symtab_edit_add(sa_vars->ts_fun, chr, true, 1);

    if(a == NULL || b == NULL || c == NULL || d == NULL || e == NULL || f == NULL || g == NULL || h == NULL) //neuspesna alokace
        return false;

    return true;
}

bool err_check(Ttoken *t, TSynCommon *sa_vars)
{
    if(t == NULL) //chyba alokace
        sa_vars->err_code = ERR_INTERNAL;
    else if(t->type == LEX_ERROR) //lexikalni chyba
        sa_vars->err_code = ERR_LEX;
    else if(t->type == ERR_INTERNAL) //chyba alokace
        sa_vars->err_code = ERR_INTERNAL;
    else
        return true; //neni problem

    return false; //chyba
}

TSynCommon *alloc_sa(Tgarbage_collector *gc)
{
    TSynCommon *sa_vars = (TSynCommon *) malloc(sizeof(TSynCommon)); //struktura s promennymi pro komunikaci mezi castmi prekladace
    gc_add_garbage(gc, sa_vars);

    Tarray *arr = (Tarray *) malloc(sizeof(Tarray)); //struktura pole pro skener //arr nema prijit do garbage collectoru

    TBuffer *buffer = (TBuffer *) malloc(sizeof(TBuffer)); //buffer pro vraceni lookahead tokenu
    gc_add_garbage(gc, buffer);

    TSymtables_stack *local_tables = (TSymtables_stack *) malloc(sizeof(TSymtables_stack));
    gc_add_garbage(gc, local_tables);

    Tsymbol_table *symtab_local = symtab_init(TS_SIZE);



    if(sa_vars == NULL || arr == NULL || buffer == NULL || local_tables == NULL || symtab_local == NULL) //neuspesna alokace
        return NULL;

    if(arr_init(arr) == ERR_INTERNAL || !init_ts_fun(sa_vars, gc)) //neuspesna alokace
        return NULL;

    buffer_init(buffer );
    TS_stack_init(local_tables);

    sa_vars->local_tables = local_tables;
    sa_vars->buffer = buffer;
    sa_vars->arr = arr;
    sa_vars->boolean = false; //vychozi stav
    sa_vars->dest = NULL;
    sa_vars->ret = NULL;

    TS_push(sa_vars->local_tables, symtab_local);

    return sa_vars;
}

void dealloc_sa(TSynCommon *sa_vars)
{
    arr_free(sa_vars->arr); //jedine arr se ma dealokovat podle dohody
    free(sa_vars->arr);

    TS_stack_free(sa_vars->local_tables);
    symtab_free(sa_vars->ts_fun);
}

void TS_stack_free(TSymtables_stack *ts_stack)
{
    while (ts_stack->top != NULL)
    {
        symtab_free(TS_pop(ts_stack));
    }
}

bool check_num_of_params(Tsymbol_table *ts, Ttoken *t, long num_of_params)
{
    Tsymbol_table_item *item = symtab_find(ts, t->attribute);
    if(item == NULL) //nenalezeno
        return false;

    if(item->num_of_params == num_of_params)
        return true;
    else if(item->num_of_params == ZERO_TO_INF && num_of_params >= 0) //specialni pripad pro fci print
        return true;
    else
        return false;
}

char *sax_temp_id_generator(Tgarbage_collector *gc)
{
    static unsigned long long cnt = 0;
    char *name = (char *) malloc(sizeof(char)*32);
    gc_add_garbage(gc, name);
    if(name == NULL)
        return NULL;
    sprintf(name, "&sax%llu", cnt++);
    return name;
}

char *long_to_string(long num, Tgarbage_collector *gc)
{
    char *name = (char *) malloc(sizeof(char)*22); //22 znaku by melo bohate stacit pro delku longu
    gc_add_garbage(gc, name);
    if(name == NULL)
        return NULL;
    sprintf(name, "%li", num);
    return name;
}

bool is_in_local_symtabs(TSynCommon *sa_vars, const char *key)
{
    TLTElem *temp = sa_vars->symtabs_bin->top; //hledam v "kosi"
    while(temp != NULL)
    {
        if(symtab_find(temp->data, key) != NULL)
            return true;
        temp = temp->prev;
    }

    temp = sa_vars->local_tables->top; //hledam v aktualnich lokalnich tabulkach
    while(temp != NULL)
    {
        if(symtab_find(temp->data, key) != NULL)
            return true;
        temp = temp->prev;
    }
    return false; //nenasel jsem
}