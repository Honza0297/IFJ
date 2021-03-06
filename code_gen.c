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
*	@file code_gen.c
*	@author Matej Jelinek, Jan Carba, Daniel Bubenicek
*	@brief soubor s definicemi funkci ze code_gen.h
*/

#include "code_gen.h"
#include "scanner.h"    


char *whatType(int x)
{
    if(x == INTEGER) //int
    {
        return "int";
    }
    else if(x == STRING_1) //string
    {
        return "string";
    }
    else if(x == BOOLEAN) //bool
    {
        return "bool";
    }
    else if(x == FLOAT_2) //float
    {
        return "float";
    }
    else if(x == KEY_NIL) //nil
    {
        return "nil";
    }
    return "nobody_knows";
}

void pream()
{
    //pream
    printf(".IFJcode18\n");
    printf("JUMP main\n");

    //inputi
    printf("LABEL inputi\n");
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");
    printf("DEFVAR LF@var\n");
    printf("READ LF@var int\n");
    printf("PUSHS LF@var\n");
    printf("POPFRAME\n");
    printf("RETURN\n");

    //inputf
    printf("LABEL inputf\n");
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");
    printf("DEFVAR LF@var\n");
    printf("READ LF@var float\n");
    printf("PUSHS LF@var\n");
    printf("POPFRAME\n");
    printf("RETURN\n");

    //inputs
    printf("LABEL inputs\n");
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");
    printf("DEFVAR LF@var\n");
    printf("READ LF@var string\n");
    printf("PUSHS LF@var\n");
    printf("POPFRAME\n");
    printf("RETURN\n");

    //length -- toto jsem upravoval -- JC
    printf("LABEL length\n");
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");
    printf("DEFVAR LF@var\n");
    printf("DEFVAR LF@x\n");
    printf("DEFVAR LF@xtype\n");
    printf("POPS LF@x\n");
    printf("TYPE LF@xtype LF@x\n");
    printf("JUMPIFNEQ lengtherror LF@xtype string@string\n");
    printf("STRLEN LF@var LF@x\n");
    printf("PUSHS LF@var\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL lengtherror\n");
    printf("EXIT int@4\n");

    //print
    printf("LABEL print\n");
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");
    printf("DEFVAR LF@counter\n");
    printf("DEFVAR LF@test\n");
    printf("DEFVAR LF@term\n");
    printf("POPS LF@counter\n");
    printf("LABEL loop\n");
    printf("POPS LF@term\n");
    printf("WRITE LF@term\n");
    printf("SUB LF@counter LF@counter int@1\n");
    printf("GT LF@test LF@counter int@0\n");
    printf("JUMPIFEQ loop LF@test bool@true\n");
    printf("PUSHS nil@nil\n");
    printf("POPFRAME\n");
    printf("RETURN\n");

    //substr
    printf("LABEL substr\n");
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");
    printf("DEFVAR LF@podretezec\n");
    printf("DEFVAR LF@znak\n");
    printf("DEFVAR LF@delka\n");
    printf("DEFVAR LF@temp_bool\n");
    printf("DEFVAR LF@type\n");
    printf("DEFVAR LF@counter\n");
    printf("DEFVAR LF@s\n");
    printf("DEFVAR LF@i\n");
    printf("DEFVAR LF@n\n");
    printf("MOVE LF@counter int@0\n");
    printf("POPS LF@s\n");
    printf("POPS LF@i\n");
    printf("POPS LF@n\n");
    printf("TYPE LF@type LF@n\n");
    printf("JUMPIFNEQ label_type_substr LF@type string@int\n");
    printf("TYPE LF@type LF@i\n");
    printf("JUMPIFNEQ label_type_substr LF@type string@int\n");
    printf("TYPE LF@type LF@s\n");
    printf("JUMPIFNEQ label_type_substr LF@type string@string\n");
    printf("STRLEN LF@delka LF@s\n");
    printf("GT LF@temp_bool LF@i LF@delka\n");
    printf("JUMPIFEQ label_nil_substr LF@temp_bool bool@true\n");
    printf("LT LF@temp_bool LF@i int@0\n");
    printf("JUMPIFEQ label_nil_substr LF@temp_bool bool@true\n");
    printf("LT LF@temp_bool LF@n int@0\n");
    printf("JUMPIFEQ label_nil_substr LF@temp_bool bool@true\n");
    printf("JUMPIFEQ label_nil LF@n int@0\n");
    printf("JUMP while2\n");
    printf("LABEL first_substr\n");
    printf("MOVE LF@podretezec LF@znak\n");
    printf("JUMP first_substr_out\n");
    printf("LABEL while2\n");
    printf("JUMPIFEQ while2_end LF@counter LF@n\n");
    printf("JUMPIFEQ while2_end LF@delka LF@i\n");
    printf("GETCHAR LF@znak LF@s LF@i\n");
    printf("JUMPIFEQ first_substr LF@counter int@0\n");
    printf("CONCAT LF@podretezec LF@podretezec LF@znak\n");
    printf("LABEL first_substr_out\n");
    printf("ADD LF@i LF@i int@1\n");
    printf("ADD LF@counter LF@counter int@1\n");
    printf("JUMP while2\n");
    printf("LABEL label_nil_substr\n");
    printf("MOVE LF@podretezec nil@nil\n");
    printf("LABEL while2_end\n");
    printf("PUSHS LF@podretezec\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL label_type_substr\n");
    printf("EXIT int@4\n");

    //ord
    printf("LABEL ord\n");
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");
    printf("DEFVAR LF@hodnota\n");
    printf("DEFVAR LF@delka\n");
    printf("DEFVAR LF@varbool\n");
    printf("DEFVAR LF@s\n");
    printf("DEFVAR LF@i\n");
    printf("DEFVAR LF@vartype\n");
    printf("POPS LF@s\n");
    printf("TYPE LF@vartype LF@s\n");
    printf("JUMPIFNEQ orderror LF@vartype string@string\n");
    printf("POPS LF@i\n");
    printf("TYPE LF@vartype LF@i\n");
    printf("JUMPIFNEQ orderror LF@vartype string@int\n");
    printf("STRLEN LF@delka LF@s\n");
    printf("SUB LF@delka LF@delka int@1\n");
    printf("LT LF@varbool LF@i int@0\n");
    printf("JUMPIFEQ ordnil LF@varbool bool@true\n");
    printf("GT LF@varbool LF@i LF@delka\n");
    printf("JUMPIFEQ ordnil LF@varbool bool@true\n");
    printf("STRI2INT LF@hodnota LF@s LF@i\n");
    printf("LABEL end\n");
    printf("PUSHS LF@hodnota\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL ordnil\n");
    printf("MOVE LF@hodnota nil@nil\n");
    printf("JUMP end\n");
    printf("LABEL orderror\n");
    printf("EXIT int@4\n");

    //chr
    printf("LABEL chr\n");
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");
    printf("DEFVAR LF@znak\n");
    printf("DEFVAR LF@temp_bool\n");
    printf("DEFVAR LF@type\n");
    printf("DEFVAR LF@i\n");
    printf("POPS LF@i\n");
    printf("TYPE LF@type LF@i\n");
    printf("JUMPIFNEQ label_type_chr LF@type string@int\n");
    printf("GT LF@temp_bool LF@i int@255\n");
    printf("JUMPIFEQ label_type_chr LF@temp_bool bool@true\n");
    printf("LT LF@temp_bool LF@i int@0\n");
    printf("JUMPIFEQ label_type_chr LF@temp_bool bool@true\n");
    printf("INT2CHAR LF@znak LF@i\n");
    printf("PUSHS LF@znak\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL label_type_chr\n");
    printf("EXIT int@4\n");

    //začatek kódu
    printf("LABEL main\n");
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");

}

void gen_defvar(TThreeAC *instruct)
{
    printf("DEFVAR LF@%s\n", instruct->op_1->name);
    printf("MOVE LF@%s nil@nil\n", instruct->op_1->name);

}

void gen_move(TThreeAC *instruct)
{
    printf("MOVE LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name);
}

void gen_defmove_const(TThreeAC *instruct)
{
    char *typ = whatType(instruct->op_1->type);
    char *hodnota = instruct->op_1->name;
    printf("DEFVAR LF@%s\n", instruct->destination->name);
    if(!strcmp(typ,"bool"))
    {
        if(!strcmp(hodnota,"0"))
        {
            printf("MOVE LF@%s bool@false\n", instruct->destination->name);
        }
        else
        {
            printf("MOVE LF@%s bool@true\n", instruct->destination->name);
        }
    }
    else
    {
        printf("MOVE LF@%s %s@%s\n", instruct->destination->name, typ, instruct->op_1->name);
    }
}

void gen_loadparam_def(TThreeAC *instruct) //TODO zahodit tuto fci
{
    printf("DEFVAR LF@%s\n", instruct->names[0]);
}

void gen_loadparam(TThreeAC *instruct)
{
    printf("DEFVAR LF@%s\n", instruct->destination->name);
    printf("POPS LF@%s\n", instruct->destination->name);
}

void gen_push(TThreeAC *instruct)
{
    printf("PUSHS LF@%s\n", instruct->op_1->name);
}

void gen_add_def(TThreeAC *instruct)
{
    for(int i = 0;i<4;i++)
    {
        printf("DEFVAR LF@%s\n", instruct->names[i]);
    }
}

void gen_add(TThreeAC *instruct, Tgarbage_collector *collector)
{
    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *btype = instruct->names[2]; //promenna LF@btype
    char *btmp = instruct->names[3]; //promenna LF@btmp
    char *addastring = codegen_temp_id_generator(collector); //label skoku kdyz a je string
    char *addaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *addafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *addaintaretype = codegen_temp_id_generator(collector); //label skoku kdyz a je int "b" float -> nutno přetypovat a na float
    char *addafloatbretype = codegen_temp_id_generator(collector); //label skoku kdyz a je float a b int -> nutno přetypovat b na float
    char *addend = codegen_temp_id_generator(collector); //label skoku na konec instrukce add (po provedení add)
    char *adderrorend = codegen_temp_id_generator(collector); //label skoku kdyz dojde k typové chybě pro ukončení s navratovým kódem 4
    char *addasametypestring = codegen_temp_id_generator(collector); //label skoku kdyz je a i b string a chceme konkatenovat

    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);

    printf("JUMPIFEQ %s LF@%s string@string\n",addastring, atype);

    printf("JUMPIFEQ %s LF@%s string@int\n",addaint, atype);

    printf("JUMPIFEQ %s LF@%s string@float\n",addafloat , atype);

    printf("LABEL %s\n", addastring);
    printf("JUMPIFEQ %s LF@%s string@string\n", addasametypestring, btype);
    printf("JUMP %s\n", adderrorend);

    printf("LABEL %s\n", addaint);
    printf("JUMPIFEQ %s LF@%s string@float\n", addaintaretype, btype);
    printf("JUMPIFNEQ %s LF@%s string@int\n", adderrorend, btype);

    printf("ADD LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n", addend); //skočí na úspěšný konec add

    printf("LABEL %s\n", addaintaretype);
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("ADD LF@%s LF@%s LF@%s\n", instruct->destination->name, atmp, instruct->op_2->name);
    printf("JUMP %s\n", addend); //skočí na úspěšný konec add

    printf("LABEL %s\n", addafloat);
    printf("JUMPIFEQ %s LF@%s string@int\n", addafloatbretype, btype);
    printf("JUMPIFNEQ %s LF@%s string@float\n", adderrorend, btype);

    printf("ADD LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n", addend); //skočí na úspěšný konec add

    printf("LABEL %s\n", addafloatbretype);
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);
    printf("ADD LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, btmp);
    printf("JUMP %s\n", addend); //skočí na úspěšný konec add

    printf("LABEL %s\n", addasametypestring);
    printf("CONCAT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n", addend); //skočí na úspěšný konec add

    printf("LABEL %s\n", adderrorend);
    printf("EXIT int@4\n");

    printf("LABEL %s\n", addend);
}

void gen_sub(TThreeAC *instruct, Tgarbage_collector *collector)
{
    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *btype = instruct->names[2]; //promenna LF@btype
    char *btmp = instruct->names[3]; //promenna LF@btmp
    char *subaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *subafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *subaintaretype = codegen_temp_id_generator(collector); //label skoku kdyz a je int "b" float -> nutno přetypovat a na float
    char *subafloatbretype = codegen_temp_id_generator(collector); //label skoku kdyz a je float a b int -> nutno přetypovat b na float
    char *subend = codegen_temp_id_generator(collector); //label skoku na konec instrukce add (po provedení add)
    char *suberrorend = codegen_temp_id_generator(collector); //label skoku kdyz dojde k typové chybě pro ukončení s navratovým kódem 4


    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);

    printf("JUMPIFEQ %s LF@%s string@int\n",subaint, atype);

    printf("JUMPIFEQ %s LF@%s string@float\n",subafloat , atype);

    printf("LABEL %s\n", subaint);
    printf("JUMPIFEQ %s LF@%s string@float\n", subaintaretype, btype);
    printf("JUMPIFNEQ %s LF@%s string@int\n", suberrorend, btype);

    printf("SUB LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n", subend); //skočí na úspěšný konec sub

    printf("LABEL %s\n", subaintaretype);
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("SUB LF@%s LF@%s LF@%s\n", instruct->destination->name, atmp, instruct->op_2->name);
    printf("JUMP %s\n", subend); //skočí na úspěšný konec sub

    printf("LABEL %s\n", subafloat);
    printf("JUMPIFEQ %s LF@%s string@int\n", subafloatbretype, btype);
    printf("JUMPIFNEQ %s LF@%s string@float\n", suberrorend, btype);

    printf("SUB LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n", subend); //skočí na úspěšný konec sub

    printf("LABEL %s\n", subafloatbretype);
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);
    printf("SUB LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, btmp);
    printf("JUMP %s\n", subend); //skočí na úspěšný konec sub

    printf("LABEL %s\n", suberrorend);
    printf("EXIT int@4\n");

    printf("LABEL %s\n", subend);
}

void gen_mul(TThreeAC *instruct, Tgarbage_collector *collector)
{
    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *btype = instruct->names[2]; //promenna LF@btype
    char *btmp = instruct->names[3]; //promenna LF@btmp
    char* mulaint = codegen_temp_id_generator(collector);
    char* mulafloat = codegen_temp_id_generator(collector);
    char* mulaintaretype = codegen_temp_id_generator(collector);
    char* mulerrorend = codegen_temp_id_generator(collector);
    char* mulend = codegen_temp_id_generator(collector);
    char* mulafloatbretype = codegen_temp_id_generator(collector);

    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);

    printf("JUMPIFEQ %s LF@%s string@int\n", mulaint, atype);
    printf("JUMPIFEQ %s LF@%s string@float\n", mulafloat, atype);

    printf("LABEL %s\n", mulaint);

    printf("JUMPIFEQ %s LF@%s string@float\n", mulaintaretype, btype );
    printf("JUMPIFNEQ %s LF@%s string@int\n", mulerrorend,  btype);

    printf("MUL LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n",mulend);

    printf("LABEL %s\n", mulaintaretype);
    printf("INT2FLOAT LF@%s LF@%s\n",atmp, instruct->op_1->name);


    printf("MUL LF@%s LF@%s LF@%s\n", instruct->destination->name, atmp, instruct->op_2->name);
    printf("JUMP %s\n", mulend);


    printf("LABEL %s\n",mulafloat );
    printf("JUMPIFEQ %s LF@%s string@int\n",mulafloatbretype, btype );
    printf("JUMPIFNEQ %s LF@%s string@float\n",mulerrorend, btype );

    printf("MUL LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);

    printf("JUMP %s\n", mulend);

    printf("LABEL %s\n",mulafloatbretype );
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);

    printf("MUL LF@%s LF@%s LF@%s\n",instruct->destination->name, instruct->op_1->name, btmp );
    printf("JUMP %s\n", mulend);

    printf("LABEl %s\n", mulerrorend) ;
    printf("EXIT int@4\n");

    printf("LABEL %s\n", mulend);
}

void gen_div(TThreeAC *instruct, Tgarbage_collector *collector)
{
    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *btype = instruct->names[2]; //promenna LF@btype
    char *btmp = instruct->names[3]; //promenna LF@btmp
    char *divaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *divafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *divaintaretype = codegen_temp_id_generator(collector); //label skoku kdyz a je int "b" float -> nutno přetypovat a na float
    char *divafloatbretype = codegen_temp_id_generator(collector); //label skoku kdyz a je float a b int -> nutno přetypovat b na float
    char *divend = codegen_temp_id_generator(collector); //label skoku na konec instrukce add (po provedení add)
    char *diverrorend = codegen_temp_id_generator(collector); //label skoku kdyz dojde k typové chybě pro ukončení s navratovým kódem 4
    char *diverrorzero = codegen_temp_id_generator(collector); //label skoku kdyz dojde k dělení nulou pro ukončení s navratovým kódem 9

    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);

    printf("JUMPIFEQ %s LF@%s string@int\n",divaint, atype);

    printf("JUMPIFEQ %s LF@%s string@float\n",divafloat , atype);
    printf("JUMP %s\n", diverrorend); //skočí na chybu typů

    printf("LABEL %s\n", divaint);
    printf("JUMPIFEQ %s LF@%s string@float\n", divaintaretype, btype);
    printf("JUMPIFNEQ %s LF@%s string@int\n", diverrorend, btype);

    printf("JUMPIFEQ %s LF@%s int@0\n", diverrorzero, instruct->op_2->name);
    printf("IDIV LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n", divend); //skočí na úspěšný konec sub

    printf("LABEL %s\n", divaintaretype);
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("JUMPIFEQ %s LF@%s float@0x0p+0\n", diverrorzero, instruct->op_2->name);
    printf("DIV LF@%s LF@%s LF@%s\n", instruct->destination->name, atmp, instruct->op_2->name);
    printf("JUMP %s\n", divend); //skočí na úspěšný konec sub

    printf("LABEL %s\n", divafloat);
    printf("JUMPIFEQ %s LF@%s string@int\n", divafloatbretype, btype);
    printf("JUMPIFNEQ %s LF@%s string@float\n", diverrorend, btype);

    printf("JUMPIFEQ %s LF@%s float@0x0p+0\n", diverrorzero, instruct->op_2->name);
    printf("DIV LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n", divend); //skočí na úspěšný konec sub

    printf("LABEL %s\n", divafloatbretype);
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);
    printf("JUMPIFEQ %s LF@%s float@0x0p+0\n", diverrorzero, btmp);
    printf("DIV LF@%s LF@%s LF@%s\n",instruct->destination->name, instruct->op_1->name, btmp);
    printf("JUMP %s\n", divend); //skočí na úspěšný konec sub

    printf("LABEL %s\n", diverrorend);
    printf("EXIT int@4\n");

    printf("LABEL %s\n", diverrorzero);
    printf("EXIT int@9\n");

    printf("LABEL %s\n", divend);
}

void gen_call(TThreeAC *instruct)
{
    printf("CALL %s\n", instruct->op_1->name);
    printf("POPS LF@%s\n", instruct->destination->name);
}

void gen_return(TThreeAC *instruct)
{
    printf("PUSHS LF@%s\n", instruct->op_1->name);
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL %s\n", instruct->op_2->name);
}

void gen_lable(TThreeAC *instruct)
{
    printf("LABEL %s\n",instruct->op_1->name);
}

void gen_deffunc(TThreeAC *instruct)
{
    printf("JUMP %s\n"
           "LABEL %s\n"
           "CREATEFRAME\n"
           "PUSHFRAME\n", instruct->op_2->name ,instruct->op_1->name);
}

void gen_jump(TThreeAC *instruct)
{
    printf("JUMP %s\n", instruct->op_1->name);
}
void gen_jumpifeq_def(TThreeAC *instruct)
{
    for(int i = 0;i < 5;i++)
    {
        printf("DEFVAR LF@%s\n", instruct->names[i]);
    }
}

void gen_jumpifeq(TThreeAC *instruct, Tgarbage_collector *collector)
{
    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *btype = instruct->names[2]; //promenna LF@btype
    char *btmp = instruct->names[3]; //promenna LF@btmp
    char *tmp = instruct->names[4]; //promenna LF@atype

    char *eqaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *eqafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqastring = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqabool = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqanil = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqaretype = codegen_temp_id_generator(collector); //label skoku kdyz a je int "b" float -> nutno přetypovat a na float
    char *eqfloatsame = codegen_temp_id_generator(collector); //label skoku kdyz a je int "b" float -> nutno přetypovat a na float
    char *eqbretype = codegen_temp_id_generator(collector); //label skoku kdyz a je float a b int -> nutno přetypovat b na float
    char *eqend = codegen_temp_id_generator(collector); //label skoku na konec instrukce add (po provedení add)
    char *eqerrorend = codegen_temp_id_generator(collector); //label skoku kdyz dojde k typové chybě pro ukončení s navratovým kódem 4
    char *eqintsame = codegen_temp_id_generator(collector); //label skoku

    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);
    printf("JUMPIFEQ %s LF@%s string@float\n", eqafloat, atype);
    printf("JUMPIFEQ %s LF@%s string@int\n", eqaint, atype);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqanil, atype);
    printf("JUMPIFEQ %s LF@%s string@string\n", eqastring, atype);
    printf("JUMPIFEQ %s LF@%s string@bool\n", eqabool, atype);
    printf("JUMP %s \n", eqerrorend);

    printf("LABEL %s\n", eqafloat); //A JE FLOAT
    printf("JUMPIFEQ %s LF@%s string@int\n", eqbretype, btype);
    printf("JUMPIFEQ %s LF@%s string@float\n", eqfloatsame, btype);
    printf("JUMP %s \n", eqerrorend);

    printf("LABEL %s\n", eqfloatsame); //OBA JSOU FLOAT
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqbretype); //A JE FLOAT B JE INT
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, btmp);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqaint); //A JE INT
    printf("JUMPIFEQ %s LF@%s string@int\n", eqintsame, btype);
    printf("JUMPIFEQ %s LF@%s string@float\n", eqaretype, btype);
    printf("JUMP %s \n", eqerrorend);

    printf("LABEL %s\n", eqintsame); //OBA INT
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqaretype); //PŘETYPOVAT A
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, atmp, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqanil); //POROVNaNÍ NILŮ
    printf("JUMPIFNEQ %s LF@%s string@nil\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqabool); //POROVNaNÍ BOOLŮ
    printf("JUMPIFNEQ %s LF@%s string@bool\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqastring); //POROVNaNÍ STRINGŮ
    printf("JUMPIFNEQ %s LF@%s string@string\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqerrorend);
    printf("EXIT int@4\n");

    printf("LABEL %s\n", eqend);
    printf("JUMPIFEQ %s LF@%s bool@true\n", instruct->destination->name, tmp);
}

void gen_jumpifneq(TThreeAC *instruct, Tgarbage_collector *collector)
{

    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *btype = instruct->names[2]; //promenna LF@btype
    char *btmp = instruct->names[3]; //promenna LF@btmp
    char *tmp = instruct->names[4]; //promenna LF@atype

    char *eqaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *eqafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqastring = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqabool = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqanil = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqaretype = codegen_temp_id_generator(collector); //label skoku kdyz a je int "b" float -> nutno přetypovat a na float
    char *eqfloatsame = codegen_temp_id_generator(collector); //label skoku kdyz a je int "b" float -> nutno přetypovat a na float
    char *eqbretype = codegen_temp_id_generator(collector); //label skoku kdyz a je float a b int -> nutno přetypovat b na float
    char *eqend = codegen_temp_id_generator(collector); //label skoku na konec instrukce add (po provedení add)
    char *eqerrorend = codegen_temp_id_generator(collector); //label skoku kdyz dojde k typové chybě pro ukončení s navratovým kódem 4
    char *eqintsame = codegen_temp_id_generator(collector); //label skoku


    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);
    printf("JUMPIFEQ %s LF@%s string@float\n", eqafloat, atype);
    printf("JUMPIFEQ %s LF@%s string@int\n", eqaint, atype);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqanil, atype);
    printf("JUMPIFEQ %s LF@%s string@string\n", eqastring, atype);
    printf("JUMPIFEQ %s LF@%s string@bool\n", eqabool, atype);
    printf("JUMP %s \n", eqerrorend);

    printf("LABEL %s\n", eqafloat); //A JE FLOAT
    printf("JUMPIFEQ %s LF@%s string@int\n", eqbretype, btype);
    printf("JUMPIFEQ %s LF@%s string@float\n", eqfloatsame, btype);
    printf("JUMP %s \n", eqerrorend);

    printf("LABEL %s\n", eqfloatsame); //OBA JSOU FLOAT
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqbretype); //A JE FLOAT B JE INT
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, btmp);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqaint); //A JE INT
    printf("JUMPIFEQ %s LF@%s string@int\n", eqintsame, btype);
    printf("JUMPIFEQ %s LF@%s string@float\n", eqaretype, btype);
    printf("JUMP %s \n", eqerrorend);

    printf("LABEL %s\n", eqintsame); //OBA INT
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqaretype); //PŘETYPOVAT A
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, atmp, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqanil); //POROVNaNÍ NILŮ
    printf("JUMPIFNEQ %s LF@%s string@nil\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqabool); //POROVNaNÍ BOOLŮ
    printf("JUMPIFNEQ %s LF@%s string@bool\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqastring); //POROVNaNÍ STRINGŮ
    printf("JUMPIFNEQ %s LF@%s string@string\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", tmp, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqerrorend);
    printf("EXIT int@4\n");

    printf("LABEL %s\n", eqend);
    printf("JUMPIFNEQ %s LF@%s bool@true\n", instruct->destination->name, tmp);
}

void gen_dprint(TThreeAC *instruct)
{
    char *typ = whatType(instruct->op_1->type);
    printf("DPRINT %s@%s\n", typ, instruct->op_1->name);
}

void gen_eq(TThreeAC *instruct, Tgarbage_collector *collector)
{
    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *btype = instruct->names[2]; //promenna LF@btype
    char *btmp = instruct->names[3]; //promenna LF@btmp

    char *eqaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *eqafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqastring = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqabool = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqanil = codegen_temp_id_generator(collector); //label skoku kdyz a je float

    char *eqaretype = codegen_temp_id_generator(collector); //label skoku kdyz a je int "b" float -> nutno přetypovat a na float
    char *eqbretype = codegen_temp_id_generator(collector); //label skoku kdyz a je float a b int -> nutno přetypovat b na float

    char *eqend = codegen_temp_id_generator(collector); //label skoku na konec instrukce add (po provedení add)
    char *eqerrorend = codegen_temp_id_generator(collector); //label skoku kdyz dojde k typové chybě pro ukončení s navratovým kódem 4
    char *eqfalse = codegen_temp_id_generator(collector);


    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);
    printf("JUMPIFEQ %s LF@%s string@float\n", eqafloat, atype);
    printf("JUMPIFEQ %s LF@%s string@int\n", eqaint, atype);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqanil, atype);
    printf("JUMPIFEQ %s LF@%s string@string\n", eqastring, atype);
    printf("JUMPIFEQ %s LF@%s string@bool\n", eqabool, atype);
    printf("JUMP %s \n", eqerrorend);

    printf("LABEL %s\n", eqafloat); //A JE FLOAT
    printf("JUMPIFEQ %s LF@%s string@int\n", eqbretype, btype);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqfalse, btype);
    printf("JUMPIFNEQ %s LF@%s string@float\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqbretype);
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, btmp);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqaint); //A JE FLOAT
    printf("JUMPIFEQ %s LF@%s string@float\n", eqaretype, btype);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqfalse, btype);
    printf("JUMPIFNEQ %s LF@%s string@int\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqaretype);
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name,atmp , instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqastring);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqfalse, btype);
    printf("JUMPIFNEQ %s LF@%s string@string\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqabool);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqfalse, btype);
    printf("JUMPIFNEQ %s LF@%s string@bool\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);


    printf("LABEL %s\n", eqanil);
    printf("JUMPIFNEQ %s LF@%s string@bool\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqfalse);
    printf("MOVE LF@%s bool@false\n", instruct->destination->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s \n", eqerrorend);
    printf("EXIT int@4 \n");

    printf("LABEL %s\n", eqend);
}

void gen_gt(TThreeAC *instruct, Tgarbage_collector *collector)
{
    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *btype = instruct->names[2]; //promenna LF@btype
    char *btmp = instruct->names[3]; //promenna LF@btmp

    char *gtastring = codegen_temp_id_generator(collector); //label skoku kdyz a je string
    char *gtabool = codegen_temp_id_generator(collector); //label skoku kdyz a je bool
    char *gtaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *gtaintretype = codegen_temp_id_generator(collector); //label skoku kdyz intretype
    char *gtaintsame = codegen_temp_id_generator(collector); //label skoku kdyz intsame
    char *gtafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *gtafloatretype = codegen_temp_id_generator(collector); //label skoku kdyz floatretype
    char *gtafloatsame = codegen_temp_id_generator(collector); //label skoku kdyz floatsame
    char *gterror = codegen_temp_id_generator(collector); //label skoku kdyz error
    char *gtend = codegen_temp_id_generator(collector); //label skoku kdyz end

    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);

    printf("JUMPIFEQ %s LF@%s string@string\n",gtastring, atype);
    printf("JUMPIFEQ %s LF@%s string@int\n",gtaint, atype);
    printf("JUMPIFEQ %s LF@%s string@float\n",gtafloat , atype);
    printf("JUMPIFEQ %s LF@%s string@bool\n",gtabool , atype);
    printf("JUMP %s\n",gterror);


    printf("LABEL %s\n", gtafloat);
    printf("JUMPIFEQ %s LF@%s string@int\n",gtafloatretype , btype);
    printf("JUMPIFEQ %s LF@%s string@float\n",gtafloatsame , btype);
    printf("JUMP %s\n",gterror);

    printf("LABEL %s\n", gtafloatsame);
    printf("GT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n",gtend);

    printf("LABEL %s\n", gtafloatretype);
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);
    printf("GT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, btmp);
    printf("JUMP %s\n",gtend);


    printf("LABEL %s\n", gtaint);
    printf("JUMPIFEQ %s LF@%s string@int\n",gtaintsame , btype);
    printf("JUMPIFEQ %s LF@%s string@float\n",gtaintretype , btype);
    printf("JUMP %s\n",gterror);

    printf("LABEL %s\n", gtaintsame);
    printf("GT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n",gtend);

    printf("LABEL %s\n", gtaintretype);
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("GT LF@%s LF@%s LF@%s\n", instruct->destination->name, atmp, instruct->op_2->name);
    printf("JUMP %s\n",gtend);


    printf("LABEL %s\n", gtastring);
    printf("JUMPIFNEQ %s LF@%s string@string\n",gterror , btype);
    printf("GT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n",gtend);


    printf("LABEL %s\n", gtabool);
    printf("JUMPIFNEQ %s LF@%s string@bool\n",gterror , btype);
    printf("GT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n",gtend);


    printf("LABEL %s\n", gterror);
    printf("EXIT int@4\n");

    printf("LABEL %s\n", gtend);
}

void gen_lt(TThreeAC *instruct, Tgarbage_collector *collector)
{
    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *btype = instruct->names[2]; //promenna LF@btype
    char *btmp = instruct->names[3]; //promenna LF@btmp

    char *ltastring = codegen_temp_id_generator(collector); //label skoku kdyz a je string
    char *ltabool = codegen_temp_id_generator(collector); //label skoku kdyz a je bool
    char *ltaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *ltaintretype = codegen_temp_id_generator(collector); //label skoku kdyz intretype
    char *ltaintsame = codegen_temp_id_generator(collector); //label skoku kdyz intsame
    char *ltafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *ltafloatretype = codegen_temp_id_generator(collector); //label skoku kdyz floatretype
    char *ltafloatsame = codegen_temp_id_generator(collector); //label skoku kdyz floatsame
    char *lterror = codegen_temp_id_generator(collector); //label skoku kdyz error
    char *ltend = codegen_temp_id_generator(collector); //label skoku kdyz end

    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);

    printf("JUMPIFEQ %s LF@%s string@string\n",ltastring, atype);
    printf("JUMPIFEQ %s LF@%s string@int\n",ltaint, atype);
    printf("JUMPIFEQ %s LF@%s string@float\n",ltafloat , atype);
    printf("JUMPIFEQ %s LF@%s string@bool\n",ltabool , atype);
    printf("JUMP %s\n",lterror);


    printf("LABEL %s\n", ltafloat);
    printf("JUMPIFEQ %s LF@%s string@int\n",ltafloatretype , btype);
    printf("JUMPIFEQ %s LF@%s string@float\n",ltafloatsame , btype);
    printf("JUMP %s\n",lterror);

    printf("LABEL %s\n", ltafloatsame);
    printf("LT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n",ltend);

    printf("LABEL %s\n", ltafloatretype);
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);
    printf("LT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, btmp);
    printf("JUMP %s\n",ltend);


    printf("LABEL %s\n", ltaint);
    printf("JUMPIFEQ %s LF@%s string@int\n",ltaintsame , btype);
    printf("JUMPIFEQ %s LF@%s string@float\n",ltaintretype , btype);
    printf("JUMP %s\n",lterror);

    printf("LABEL %s\n", ltaintsame);
    printf("LT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n",ltend);

    printf("LABEL %s\n", ltaintretype);
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("LT LF@%s LF@%s LF@%s\n", instruct->destination->name, atmp, instruct->op_2->name);
    printf("JUMP %s\n",ltend);


    printf("LABEL %s\n", ltastring);
    printf("JUMPIFNEQ %s LF@%s string@string\n",lterror , btype);
    printf("LT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n",ltend);


    printf("LABEL %s\n", ltabool);
    printf("JUMPIFNEQ %s LF@%s string@bool\n",lterror , btype);
    printf("LT LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s\n",ltend);


    printf("LABEL %s\n", lterror);
    printf("EXIT int@4\n");

    printf("LABEL %s\n", ltend);
}

void gen_gteq_def(TThreeAC *instruct)
{
    for(int i = 0;i<6;i++)
    {
        printf("DEFVAR LF@%s\n", instruct->names[i]);
    }
}

void gen_gteq(TThreeAC *instruct, Tgarbage_collector *collector)
{
    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *xgt = instruct->names[2]; //promenna LF@agt
    char *xeq = instruct->names[3]; //promenna LF@aeq
    char *btype = instruct->names[4]; //promenna LF@btype
    char *btmp = instruct->names[5]; //promenna LF@btmp

    char *gteqastring = codegen_temp_id_generator(collector); //label skoku kdyz a je string
    char *gteqabool = codegen_temp_id_generator(collector); //label skoku kdyz a je bool
    char *gteqaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *gteqaintretype = codegen_temp_id_generator(collector); //label skoku kdyz intretype
    char *gteqaintsame = codegen_temp_id_generator(collector); //label skoku kdyz intsame
    char *gteqafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *gteqafloatretype = codegen_temp_id_generator(collector); //label skoku kdyz floatretype
    char *gteqafloatsame = codegen_temp_id_generator(collector); //label skoku kdyz floatsame
    char *gteqerror = codegen_temp_id_generator(collector); //label skoku kdyz error
    char *gteqend = codegen_temp_id_generator(collector); //label skoku kdyz end

    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);

    printf("JUMPIFEQ %s LF@%s string@string\n",gteqastring, atype);
    printf("JUMPIFEQ %s LF@%s string@int\n",gteqaint, atype);
    printf("JUMPIFEQ %s LF@%s string@float\n",gteqafloat , atype);
    printf("JUMPIFEQ %s LF@%s string@float\n",gteqabool , atype);
    printf("JUMP %s\n",gteqerror);


    printf("LABEL %s\n", gteqafloat);
    printf("JUMPIFEQ %s LF@%s string@int\n",gteqafloatretype , btype);
    printf("JUMPIFEQ %s LF@%s string@float\n",gteqafloatsame , btype);
    printf("JUMP %s\n",gteqerror);

    printf("LABEL %s\n", gteqafloatsame);
    printf("GT LF@%s LF@%s LF@%s\n", xgt, instruct->op_1->name, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, instruct->op_1->name, instruct->op_2->name);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xgt, xeq);
    printf("JUMP %s\n",gteqend);

    printf("LABEL %s\n", gteqafloatretype);
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);
    printf("GT LF@%s LF@%s LF@%s\n", xgt, instruct->op_1->name, btmp);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, instruct->op_1->name, btmp);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xgt, xeq);
    printf("JUMP %s\n",gteqend);


    printf("LABEL %s\n", gteqaint);
    printf("JUMPIFEQ %s LF@%s string@int\n",gteqaintsame , btype);
    printf("JUMPIFEQ %s LF@%s string@float\n",gteqaintretype , btype);
    printf("JUMP %s\n",gteqerror);

    printf("LABEL %s\n", gteqaintsame);
    printf("GT LF@%s LF@%s LF@%s\n", xgt, instruct->op_1->name, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, instruct->op_1->name, instruct->op_2->name);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xgt, xeq);
    printf("JUMP %s\n",gteqend);

    printf("LABEL %s\n", gteqaintretype);
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("GT LF@%s LF@%s LF@%s\n", xgt, atmp, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, atmp, instruct->op_2->name);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xgt, xeq);
    printf("JUMP %s\n",gteqend);


    printf("LABEL %s\n", gteqastring);
    printf("JUMPIFNEQ %s LF@%s string@string\n",gteqerror , btype);
    printf("GT LF@%s LF@%s LF@%s\n", xgt, instruct->op_1->name, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, instruct->op_1->name, instruct->op_2->name);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xgt, xeq);
    printf("JUMP %s\n",gteqend);


    printf("LABEL %s\n", gteqabool);
    printf("JUMPIFNEQ %s LF@%s string@bool\n",gteqerror , btype);
    printf("GT LF@%s LF@%s LF@%s\n", xgt, instruct->op_1->name, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, instruct->op_1->name, instruct->op_2->name);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xgt, xeq);
    printf("JUMP %s\n",gteqend);


    printf("LABEL %s\n", gteqerror);
    printf("EXIT int@4\n");

    printf("LABEL %s\n", gteqend);
}

void gen_lteq(TThreeAC *instruct, Tgarbage_collector *collector)
{

    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *xlt = instruct->names[2]; //promenna LF@xlt
    char *xeq = instruct->names[3]; //promenna LF@xeq
    char *btype = instruct->names[4]; //promenna LF@btype
    char *btmp = instruct->names[5]; //promenna LF@btmp

    char *lteqastring = codegen_temp_id_generator(collector); //label skoku kdyz a je string
    char *lteqabool = codegen_temp_id_generator(collector); //label skoku kdyz a je bool
    char *lteqaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *lteqaintretype = codegen_temp_id_generator(collector); //label skoku kdyz intretype
    char *lteqaintsame = codegen_temp_id_generator(collector); //label skoku kdyz intsame
    char *lteqafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *lteqafloatretype = codegen_temp_id_generator(collector); //label skoku kdyz floatretype
    char *lteqafloatsame = codegen_temp_id_generator(collector); //label skoku kdyz floatsame
    char *lteqerror = codegen_temp_id_generator(collector); //label skoku kdyz error
    char *lteqend = codegen_temp_id_generator(collector); //label skoku kdyz end

    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);

    printf("JUMPIFEQ %s LF@%s string@string\n",lteqastring, atype);
    printf("JUMPIFEQ %s LF@%s string@int\n",lteqaint, atype);
    printf("JUMPIFEQ %s LF@%s string@float\n",lteqafloat , atype);
    printf("JUMPIFEQ %s LF@%s string@bool\n",lteqabool , atype);
    printf("JUMP %s\n",lteqerror);


    printf("LABEL %s\n", lteqafloat);
    printf("JUMPIFEQ %s LF@%s string@int\n",lteqafloatretype , btype);
    printf("JUMPIFEQ %s LF@%s string@float\n",lteqafloatsame , btype);
    printf("JUMP %s\n",lteqerror);

    printf("LABEL %s\n", lteqafloatsame);
    printf("LT LF@%s LF@%s LF@%s\n", xlt, instruct->op_1->name, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, instruct->op_1->name, instruct->op_2->name);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xlt, xeq);
    printf("JUMP %s\n",lteqend);

    printf("LABEL %s\n", lteqafloatretype);
    printf("INT2FLOAT LF@%s LF@%s\n", btmp, instruct->op_2->name);
    printf("LT LF@%s LF@%s LF@%s\n", xlt, instruct->op_1->name, btmp);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, instruct->op_1->name, btmp);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xlt, xeq);
    printf("JUMP %s\n",lteqend);


    printf("LABEL %s\n", lteqaint);
    printf("JUMPIFEQ %s LF@%s string@int\n",lteqaintsame , btype);
    printf("JUMPIFEQ %s LF@%s string@float\n",lteqaintretype , btype);
    printf("JUMP %s\n",lteqerror);

    printf("LABEL %s\n", lteqaintsame);
    printf("LT LF@%s LF@%s LF@%s\n", xlt, instruct->op_1->name, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, instruct->op_1->name, instruct->op_2->name);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xlt, xeq);
    printf("JUMP %s\n",lteqend);

    printf("LABEL %s\n", lteqaintretype);
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("LT LF@%s LF@%s LF@%s\n", xlt, atmp, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, atmp, instruct->op_2->name);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xlt, xeq);
    printf("JUMP %s\n",lteqend);


    printf("LABEL %s\n", lteqastring);
    printf("JUMPIFNEQ %s LF@%s string@string\n",lteqerror , btype);
    printf("LT LF@%s LF@%s LF@%s\n", xlt, instruct->op_1->name, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, instruct->op_1->name, instruct->op_2->name);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xlt, xeq);
    printf("JUMP %s\n",lteqend);


    printf("LABEL %s\n", lteqabool);
    printf("JUMPIFNEQ %s LF@%s string@bool\n",lteqerror , btype);
    printf("LT LF@%s LF@%s LF@%s\n", xlt, instruct->op_1->name, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", xeq, instruct->op_1->name, instruct->op_2->name);
    printf("OR LF@%s LF@%s LF@%s\n", instruct->destination->name, xlt, xeq);
    printf("JUMP %s\n",lteqend);


    printf("LABEL %s\n", lteqerror);
    printf("EXIT int@4\n");

    printf("LABEL %s\n", lteqend);
}

void gen_neq(TThreeAC *instruct, Tgarbage_collector *collector)
{
    char *atype = instruct->names[0]; //promenna LF@atype
    char *atmp = instruct->names[1]; //promenna LF@atmp
    char *btype = instruct->names[2]; //promenna LF@btype
    char *btmp = instruct->names[3]; //promenna LF@btmp

    char *eqaint = codegen_temp_id_generator(collector); //label skoku kdyz a je int
    char *eqafloat = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqastring = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqabool = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqanil = codegen_temp_id_generator(collector); //label skoku kdyz a je float
    char *eqaretype = codegen_temp_id_generator(collector); //label skoku kdyz a je int "b" float -> nutno přetypovat a na float
    char *eqbretype = codegen_temp_id_generator(collector); //label skoku kdyz a je float a b int -> nutno přetypovat b na float
    char *eqend = codegen_temp_id_generator(collector); //label skoku na konec instrukce add (po provedení add)
    char *eqerrorend = codegen_temp_id_generator(collector); //label skoku kdyz dojde k typové chybě pro ukončení s navratovým kódem 4
    char *eqfalse = codegen_temp_id_generator(collector);

    printf("TYPE LF@%s LF@%s\n", atype, instruct->op_1->name);
    printf("TYPE LF@%s LF@%s\n", btype, instruct->op_2->name);
    printf("JUMPIFEQ %s LF@%s string@float\n", eqafloat, atype);
    printf("JUMPIFEQ %s LF@%s string@int\n", eqaint, atype);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqanil, atype);
    printf("JUMPIFEQ %s LF@%s string@string\n", eqastring, atype);
    printf("JUMPIFEQ %s LF@%s string@bool\n", eqabool, atype);
    printf("JUMP %s \n", eqerrorend);

    printf("LABEL %s\n", eqafloat); //A JE FLOAT
    printf("JUMPIFEQ %s LF@%s string@int\n", eqbretype, btype);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqfalse, btype);
    printf("JUMPIFNEQ %s LF@%s string@float\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqbretype);
    printf("INT2FLOAT LF@%s LF@%s \n", btmp, instruct->op_2->name);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, btmp);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqaint); //A JE FLOAT
    printf("JUMPIFEQ %s LF@%s string@float\n", eqaretype, btype);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqfalse, btype);
    printf("JUMPIFNEQ %s LF@%s string@int\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqaretype);
    printf("INT2FLOAT LF@%s LF@%s\n", atmp, instruct->op_1->name);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name,atmp , instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqastring);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqfalse, btype);
    printf("JUMPIFNEQ %s LF@%s string@string\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqabool);
    printf("JUMPIFEQ %s LF@%s string@nil\n", eqfalse, btype);
    printf("JUMPIFNEQ %s LF@%s string@bool\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);


    printf("LABEL %s\n", eqanil);
    printf("JUMPIFNEQ %s LF@%s string@bool\n", eqerrorend, btype);
    printf("EQ LF@%s LF@%s LF@%s\n", instruct->destination->name, instruct->op_1->name, instruct->op_2->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s\n", eqfalse);
    printf("MOVE LF@%s bool@false\n", instruct->destination->name);
    printf("JUMP %s \n", eqend);

    printf("LABEL %s \n", eqerrorend);
    printf("EXIT int@4 \n");

    printf("LABEL %s\n", eqend);
    printf("NOT LF@%s LF@%s\n", instruct->destination->name, instruct->destination->name);
}

void GEN_start(TTacList *list, Tgarbage_collector *collector)
{
    TThreeAC *inst = list->first;
    TThreeAC *temp = NULL;
    TThreeAC *tmp = NULL;

    TThreeAC *first_while = NULL;
    int while_count = 0;


    //generace .IFJcode18 a podobne
    pream();

    while(inst != NULL) //vyhozeni defvaru pred if
    {
        if(inst->name == STARTIF)
        {
            if(while_count == 0)
                first_while = inst->prev;
            while_count++;
        }
        if(inst->name == ENDIF)
        {
            if(while_count != 0)
                while_count--;
        }
        if((inst->name == DEFVAR && while_count != 0) || (inst->name == DEFMOVE && while_count != 0))
        {
            tmp = inst->next;
            temp = TAC_remove_this(list, inst);
            TAC_insert_post(list, first_while, temp);
            inst = tmp;
            continue;
        }
        inst = inst->next;
    }

    inst = list->first;
    tmp = NULL;
    temp = NULL;
    first_while = NULL;
    while_count = 0;


    while(inst != NULL) //vyhozeni defvaru pred while
    {
        if(inst->name == WHILE)
        {
            if(while_count == 0)
                first_while = inst->prev;
            while_count++;
        }
        if(inst->name == ENDWHILE)
        {
            if(while_count != 0)
                while_count--;
        }
        if((inst->name == DEFVAR && while_count != 0) || (inst->name == DEFMOVE && while_count != 0) || (inst->name == ADD_DEF && while_count != 0)
           || (inst->name == LOADPARAM_DEF && while_count != 0) || (inst->name == JUMPIFEQ_DEF && while_count != 0) || (inst->name == GTEQ_DEF && while_count != 0))
        {
            tmp = inst->next;
            temp = TAC_remove_this(list, inst);
            TAC_insert_post(list, first_while, temp);
            inst = tmp;
            continue;
        }
        inst = inst->next;
    }
    inst = TAC_remove(list);
    while (inst != NULL)
    {
        switch (inst->name)
        {
            case DEFVAR:
                printf("#_________toto je DEFVAR_____\n");
                gen_defvar(inst);
                break;
            case MOVE:
                printf("#_________toto je MOVE_____\n");
                gen_move(inst);
                break;
            case DEFMOVE:
                printf("#_________toto je DEFMOVE_____\n");
                gen_defmove_const(inst);
                break;
            case LOADPARAM:
                printf("#_________toto je LOADPARAM_____\n");
                gen_loadparam(inst);
                break;
            case PUSH:
                printf("#_________toto je PUSH_____\n");
                gen_push(inst);
                break;
            case ADD:
                printf("#_________toto je ADD _____\n");
                gen_add(inst, collector);
                break;
            case SUB:
                printf("#_________toto je SUB _____\n");
                gen_sub(inst, collector);
                break;
            case MUL:
                printf("#_________toto je MUL _____\n");
                gen_mul(inst, collector);
                break;
            case DIV:
                printf("#_________toto je DIV _____\n");
                gen_div(inst, collector);
                break;
            case CALL:
                printf("#_________toto je CALL _____\n");
                gen_call(inst);
                break;
            case RETURN:
                printf("#_________toto je RETURN _____\n");
                gen_return(inst);
                break;
            case LABLE:
                printf("#_________toto je LA BLEEEE _____\n");
                gen_lable(inst);
                break;
            case DEFFUNC:
                printf("#_________toto je DEFFUNC _____\n");
                gen_deffunc(inst);
                break;
            case JUMP:
                printf("#_________toto je JUMP _____\n");
                gen_jump(inst);
                break;
            case JUMPIFEQ:
                printf("#_________toto je JUMPIFEQ _____\n");
                gen_jumpifeq(inst, collector);
                break;
            case JUMPIFNEQ:
                printf("#_________toto je JUMPIFNEQ _____\n");
                gen_jumpifneq(inst, collector);
                break;
            case DPRINT:
                printf("#_________toto je DPRINT _____\n");
                gen_dprint(inst);
                break;
            case EQ:
                printf("#_________toto je EQ _____\n");
                gen_eq(inst, collector);
                break;
            case GT:
                printf("#_________toto je GT _____\n");
                gen_gt(inst, collector);
                break;
            case LT:
                printf("#_________toto je LT _____\n");
                gen_lt(inst, collector);
                break;
            case GTEQ:
                printf("#_________toto je GTEQ _____\n");
                gen_gteq(inst, collector);
                break;
            case LTEQ:
                printf("#_________toto je LTEQ _____\n");
                gen_lteq(inst, collector);
                break;
            case NEQ:
                printf("#_________toto je NEQ _____\n");
                gen_neq(inst, collector);
                break;
            case LOADPARAM_DEF:
                printf("#_________toto je LOADPARAM_DEF_____\n");
                gen_loadparam_def(inst);
                break;
            case ADD_DEF:
                printf("#_________toto je ADD_DEF_____\n");
                gen_add_def(inst);
                break;
            case JUMPIFEQ_DEF:
                printf("#_________toto je JUMPIFEQ_DEF_____\n");
                gen_jumpifeq_def(inst);
                break;
            case GTEQ_DEF:
                printf("#_________toto je GTEQ_DEF_____\n");
                gen_gteq_def(inst);
                break;
        }
        fflush(stdout);
        inst = TAC_remove(list);
    }
}
