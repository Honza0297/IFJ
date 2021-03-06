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
*	@file scanner.c
*	@author Daniel Bubenicek, Jan Beran
*	@brief implementace konecneho automatu pro lexikalni analyzator
 *	v2.0: prvni stabilni a otestovana verze
 *
*/

#include <string.h>
#include "scanner.h"
#include "err_codes.h"
#include "garbage_collector.h"

char *key_words[10] = {"def", "do", "else", "end", "if", "not", "nil", "then", "while"};

Ttoken *get_token(Tarray *token_value, Tgarbage_collector *collector)
{
    int actual_state = START;
    int next_state = LEX_ERROR;
    bool final_state = false;
    int c; //znak ze stdin nebo bufferu
    static int first = 1; //pokud ==1, tak se jedna o prvni vstupni token
    Ttoken *token = (Ttoken *) malloc(sizeof(Ttoken));
    gc_add_garbage(collector, token);

    if(token == NULL)
        return  NULL;
    token_init(token);

    while(!final_state)
    {
        switch (actual_state)
        {
            case START:
                c = get_next_char(token_value);
                arr_reset(token_value);
                switch(c)
                {
                    case ' ': //mezera
                    case '\t': //tabulator
                        next_state = START;
                        break;
                    case EOL:
                        next_state = EOL_0;
                        break;
                    case '+':
                        next_state = OP_PLUS;
                        break;
                    case '-':
                        next_state = OP_MINUS;
                        break;
                    case '*':
                        next_state = OP_MULT;
                        break;
                    case '/':
                        next_state = OP_DIV;
                        break;
                    case '(':
                        next_state = LEFT_BRACKET;
                        break;
                    case ')':
                        next_state = RIGHT_BRACKET;
                        break;
                    case '=':
                        if (first) //kvuli komentu na prvni radce
                            next_state = BLOCK_COMMENT_0;
                        else
                            next_state = OP_EQAL_0;
                        break;
                    case '0':
                        next_state = NUMBER_0;
                        break;
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        next_state = NUMBER_1;
                        break;
                    case '!':
                        next_state = OP_NOT_EQ_0;
                        break;
                    case '>':
                        next_state = OP_MORE_0;
                        break;
                    case '<':
                        next_state = OP_LESS_0;
                        break;
                    case',':
                        next_state = OP_COMMA;
                        break;
                    case'"':
                        next_state = STRING_0;
                        break;
                    case '#':
                        next_state = ONE_LINE_COMMENT;
                        break;
                    case EOF:
                        next_state = EOF_STATE;
                        break;
                    default:
                        if(type_of_char(c) == SMALL || c == '_')
                            next_state = ID_0;
                        else
                            next_state = LEX_ERROR;
                }
                if(c != '"') //aby se pocatectni uvozovka nenarvala do stringu...
                {
                    if(arr_add_char(token_value, (char)c) == ERR_INTERNAL)
                    {
                        token_set_type(token, ERR_INTERNAL);
                        return token;
                    }
                }
                break; //konec START
            case LEX_ERROR: //DONE
                token_set_type(token, LEX_ERROR);
                final_state = true;
                fprintf(stderr, MESSAGE_LEX);
                fflush(stderr);
                break;
            case OP_PLUS: //DONE
                token_set_type(token, OP_PLUS); //token ready
                final_state = true;
                break;
            case OP_MINUS: //DONE
                token_set_type(token, OP_MINUS); //token ready
                final_state = true;
                break;
            case OP_DIV: //DONE
                token_set_type(token, OP_DIV); //token ready
                final_state = true;
                break;
            case OP_MULT: //DONE
                token_set_type(token, OP_MULT); //token ready
                final_state = true;
                break;
            case OP_EQAL_0: //DONE
                c = get_next_char(token_value);
                if(c == '=')
                    next_state = OP_EQAL_1;
                else
                {
                    next_state = OP_EQAL_2;
                    arr_set_buffer(token_value, c);
                }
                break;
            case OP_EQAL_1: //DONE
                token_set_type(token, actual_state);
                final_state = true;
                break;
            case OP_EQAL_2: //DONE
                token_set_type(token, actual_state);
                final_state = true;
                break;
            case OP_NOT_EQ_0: //DONE
                c = get_next_char(token_value);
                if(c == '=')
                    next_state = OP_NOT_EQ_1;
                else
                    next_state = LEX_ERROR;
                break;
            case OP_NOT_EQ_1: //DONE
                token_set_type(token, actual_state);
                final_state = true;
                break;
            case OP_MORE_0: //DONE
                c = get_next_char(token_value);
                if(c == '=')
                    next_state = OP_MORE_EQUAL;
                else
                {
                    next_state = OP_MORE_1;
                    arr_set_buffer(token_value, c);
                }
                break;
            case OP_MORE_1: //DONE
                token_set_type(token, actual_state);
                final_state = true;
                break;
            case OP_MORE_EQUAL: //DONE
                token_set_type(token, actual_state);
                final_state = true;
                break;
            case OP_LESS_0: //DONE
                c = get_next_char(token_value);
                if(c == '=')
                    next_state = OP_LESS_EQUAL;
                else
                {
                    next_state = OP_LESS_1;
                    arr_set_buffer(token_value, c);
                }
                break;
            case OP_LESS_1: //DONE
                token_set_type(token, actual_state);
                final_state = true;
                break;
            case OP_LESS_EQUAL: //DONE
                token_set_type(token, actual_state);
                final_state = true;
                break;
            case LEFT_BRACKET: //DONE
                token_set_type(token, LEFT_BRACKET); //token ready
                final_state = true;
                break;
            case RIGHT_BRACKET: //DONE
                token_set_type(token, RIGHT_BRACKET); //token ready
                final_state = true;
                break;
            case OP_COMMA: //DONE
                token_set_type(token, OP_COMMA); //token ready
                final_state = true;
                break;
            case EOL_0: //DONE
                c = get_next_char(token_value);
                if(c == '=') //
                    next_state = BLOCK_COMMENT_0;
                else
                {
                    next_state = EOL_1;
                    arr_set_buffer(token_value, c);
                }
                break;
            case EOL_1: //DONE
                token_set_type(token, actual_state);
                final_state = true;
                break;
            case BLOCK_COMMENT_0: //DONE
            {
                c = get_next_char(token_value);
                char comm_begin[] = "begin";
                int begin_compared_successfully = 0;
                for (int i = 0; comm_begin[i] != '\0'; i++)
                {
                    if(comm_begin[i] != c)
                    {
                        next_state = LEX_ERROR;
                        break; //break for
                    }
                    else
                    {
                        if(arr_add_char(token_value, (char)c) == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                    }
                    c = get_next_char(token_value);
                    if(comm_begin[i] == 'n')
                    {
                        arr_reset(token_value);
                        begin_compared_successfully =1;
                    }
                }
                if ((c == ' ' || c == '\t' || c == '\n') && begin_compared_successfully) //c == whitespace, musi byt za =begin
                {
                    next_state = BLOCK_COMMENT_1;
                }
                else
                    next_state = LEX_ERROR;}
                break; //konec BLOCK_COMMENT_0
            case BLOCK_COMMENT_1: // DONE
                c = get_next_char(token_value);
                while(c != EOL && c != EOF)
                {
                    c = get_next_char(token_value);
                }
                if(c == EOF)
                    next_state = LEX_ERROR;
                else if(c == EOL) //muze nasledovat =end
                    next_state = BLOCK_COMMENT_2;
                else
                    next_state = BLOCK_COMMENT_1;
                break;//konec BLOCK_COMMENT_1
            case BLOCK_COMMENT_2:
            {
                c = get_next_char(token_value);
                char comm_end[] = "=end";
                int end_compared_successfully = 0;
                for (int i = 0; comm_end[i] != '\0'; i++)
                {
                    if(comm_end[i] != c)
                    {
                        next_state = BLOCK_COMMENT_1;
                        break; //break for
                    }
                    else
                    {
                        end_compared_successfully++;
                        if(arr_add_char(token_value, (char)c) == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                    }
                    c = get_next_char(token_value);
                }
                if ((c == ' ' || c == '\t' || c == EOL) && end_compared_successfully == 4)
                {
                    next_state = BLOCK_COMMMENT_3;
                    arr_set_buffer(token_value, c);
                }
                else if (c == EOF) //konec souboru
                    next_state = LEX_ERROR;
                else
                    next_state = BLOCK_COMMENT_1;}
                break;
            case BLOCK_COMMMENT_3:
                while(c != EOL)
                {
                    c = get_next_char(token_value);
                    if (c == EOF)
                    {
                        next_state = LEX_ERROR;
                        break;
                    }
                }
                token_set_type(token, EOL_1);
                final_state = true;
                break;
            case ONE_LINE_COMMENT://DONE
                c = get_next_char(token_value);
                while(c != EOL && c != EOF)
                {
                    c = get_next_char(token_value);
                }
                if(c == EOF)
                    next_state = EOF_STATE;
                if(c == EOL)
                    next_state = EOL_1;
                break; //konec OONE_LINE_COMMENT
            case ID_0: //DONE
                c = get_next_char(token_value);
                int type = type_of_char(c);
                if(type == NUM || type == SMALL || type == CAPITAL || c == '_') //actual state zustava
                    ;
                else if(c == '!' || c == '?')
                    next_state = ID_FCE;
                else
                {
                    next_state = ID_1;
                    arr_set_buffer(token_value, c);
                    break;
                }

                if(arr_add_char(token_value,(char) c) == ERR_INTERNAL)
                {
                    token_set_type(token, ERR_INTERNAL);
                    return token;
                }
                break;
            case ID_1: //DONE
                ;
                char *str = arr_get_value(token_value, collector); //pozor, dynamicky alokovane
                if(str == NULL) //chyba alokace
                {
                    token_set_type(token, ERR_INTERNAL);
                    return token;
                }
                int type_key; //pro keyword
                if((type_key = is_keyword(str)) != 0) //pokud je to keyword nastavim jako final state
                {
                    token_set_type(token, type_key); //token ready
                    final_state = true;
                }
                else if (!strcmp(str, "begin")) //shoda
                    next_state = LEX_ERROR; //begin nelze pouzit jako ID
                else
                    next_state = ID_2;
                break;
            case ID_2: //DONE
                if(token_set_attribute(token, token_value, collector) == ERR_INTERNAL)
                {
                    token_set_type(token, ERR_INTERNAL);
                    return token;
                }
                token_set_type(token, actual_state); //token ready
                final_state = true;
                break;
            case ID_FCE:
                c = get_next_char(token_value);
                if(c == '(' || c == '#' || c == ' ' || c == EOL || c == EOF || c == '\t') //validne ukoncene ID
                {
                    arr_set_buffer(token_value, c);
                    if(token_set_attribute(token, token_value, collector) == ERR_INTERNAL)
                    {
                        token_set_type(token, ERR_INTERNAL);
                        return token;
                    }
                    token_set_type(token, actual_state); //token ready
                    final_state = true;
                }
                else
                {
                 next_state = LEX_ERROR;
                }
                break;
            case EOF_STATE: //DONE
                token_set_type(token, EOF_STATE); //token ready
                final_state = true;
                break;
            case STRING_0: // dvojite lomitko \\ znamena ve skutecnosti jen jedno :D
                c = get_next_char(token_value);
                while (c != '"' && c != '\\' && c != EOF)
                {
                    if(c == ' ')
                    {
                        if(arr_add_char(token_value, '\\') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '0') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '3') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '2') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                    }
                    else if(c == '#')
                    {
                        if(arr_add_char(token_value, '\\') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '0') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '3') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '5') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                    }
                    else
                    {
                        if (arr_add_char(token_value, (char) c) == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                    }
                    c = get_next_char(token_value);
                }
                if (c == '"')
                    next_state = STRING_1;
                else if (c == '\\')

                    next_state = ESCAPE_0;
                else if(c == EOF)
                    next_state = LEX_ERROR;
                break; //konec STRING_0
            case STRING_1: //DONE
                token_set_type(token, STRING_1);
                token_set_attribute(token, token_value, collector); //token ready
                final_state = true;
                break;
            case ESCAPE_0:
                c = get_next_char(token_value);
                switch(c)
                {
                    case '"': // => \034
                         if(arr_add_char(token_value, '\\') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '0') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '3') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '4') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        next_state = STRING_0;
                        break;
                    case 'n': //EOL \010
                       if(arr_add_char(token_value, '\\') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '0') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '1') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '0') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        next_state = STRING_0;
                        break;
                    case 't': // \009
                        if(arr_add_char(token_value, '\\') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '0') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '0') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '9') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        next_state = STRING_0;
                        break;
                    case 's':
                         if(arr_add_char(token_value, '\\') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '0') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '3') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '2') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        next_state = STRING_0;
                        break;
                    case '\\':
                        if(arr_add_char(token_value, '\\') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '0') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '9') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '2') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        next_state = STRING_0;
                        break;
                    case 'x':
                        next_state = ESCAPE_1;
                        break;
                    case EOF:
                        next_state = LEX_ERROR;
                        break;
                    default:
                        if(arr_add_char(token_value, (char)c) == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        next_state = STRING_0;
                        break;
                }
                break;//konec ESCAPE_0
            case ESCAPE_1://DONE
            {   c = get_next_char(token_value);
                char hexa[2]; //musí  být char, jinak to nejde převést. EOF se ale vyfiltruje do větve else a nehrozí problém
                unsigned int num = 0;
                if((c >= '0' && c <= '9') ||
                   (c >= 'a' && c <= 'f') ||
                   (c >= 'A' && c <= 'F'))    //pokud je c 0..9a..fA..F
                {
                    hexa[0] = (char) c;
                    c = get_next_char(token_value);
                    if ((c >= '0' && c <= '9') ||
                        (c >= 'a' && c <= 'f') ||
                        (c >= 'A' && c <= 'F'))    //pokud je c 0..9a..fA..F
                    {
                        hexa[1] = (char) c;
                        sscanf(hexa, "%x", &num);
                        char numstr[4];
                        sprintf(numstr, "%i", num); //do  to dá hodnotu cisla num ve stringu
                        if(arr_add_char(token_value, '\\') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }
                        if(arr_add_char(token_value, '0') == ERR_INTERNAL)
                        {
                            token_set_type(token, ERR_INTERNAL);
                            return token;
                        }

                        for(int i = 0; i < 2; i++)
                        {
                            if(arr_add_char(token_value, numstr[i]) == ERR_INTERNAL)
                            {
                                token_set_type(token, ERR_INTERNAL);
                                return token;
                            }
                        }
                    }
                    else
                    {
                        next_state = LEX_ERROR;
                        break;
                    }
                }
                else
                {
                    next_state = LEX_ERROR;
                    break;
                }
                next_state = STRING_0;
                break;//konec case ESCAPE_1
            }
            case ESCAPE_2: // asi pryč
                break;
            case NUMBER_0: //DONE
                c = get_next_char(token_value);
                if(type_of_char((char)c) == NUM)
                    next_state = LEX_ERROR;
                else if(c == '.')
                    next_state = FLOAT_0;
                else if(c == 'e' || c == 'E')
                    next_state = FLOAT_EXP_0;
                else
                {
                    next_state = INTEGER;
                    arr_set_buffer(token_value, c);
                    break;
                }
                if(arr_add_char(token_value, (char)c) == ERR_INTERNAL)
                {
                    token_set_type(token, ERR_INTERNAL);
                    return token;
                }
                break;
            case NUMBER_1:
                c = get_next_char(token_value);
                if(c == '.')
                    next_state = FLOAT_0;
                else if(c == 'e' || c == 'E')
                    next_state = FLOAT_EXP_0;
                else if(type_of_char(c) == NUM)
                    ; //stav zustava
                else
                {
                    next_state = INTEGER;
                    arr_set_buffer(token_value, c);
                    break;
                }
                if(arr_add_char(token_value, (char) c) == ERR_INTERNAL)
                {
                    token_set_type(token, ERR_INTERNAL);
                    return token;
                }
                break;
            case INTEGER: //DONE
                if(token_set_attribute(token, token_value, collector) == ERR_INTERNAL) //nahrani atributu do tokeny a soucasne kontrola
                {
                    token_set_type(token, ERR_INTERNAL);
                    return token;
                }
                token_set_type(token, actual_state);
                final_state = true;
                break;
            case FLOAT_0: //DONE
                c = get_next_char(token_value);
                if(type_of_char(c) == NUM)
                {
                    next_state = FLOAT_1;
                    if(arr_add_char(token_value,(char) c) == ERR_INTERNAL)
                    {
                        token_set_type(token, ERR_INTERNAL);
                        return token;
                    }
                }
                else
                    next_state = LEX_ERROR;
                break;
            case FLOAT_1: //DONE
                c = get_next_char(token_value);
                if(type_of_char(c) == NUM) //zustavam ve stejnem stavu
                    ;
                else if(c == 'E' || c == 'e')
                    next_state = FLOAT_EXP_0;
                else
                {
                    next_state = FLOAT_2;
                    arr_set_buffer(token_value, c);
                    break;
                }
                if(arr_add_char(token_value,(char) c) == ERR_INTERNAL)
                {
                    token_set_type(token, ERR_INTERNAL);
                    return token;
                }
                break;
            case FLOAT_2: //DONE
                ;
                float num = 0.0;
                arr_add_char(token_value, '\0');
                sscanf(token_value->array, "%f", &num);
                char *temp = malloc(sizeof(char)*128);
                gc_add_garbage(collector, temp);
                sprintf(temp, "%.20a", num);

                arr_reset(token_value);
                for(int i = 0; temp[i] != '\0'; i++)
                {
                    arr_add_char(token_value, temp[i]);
                }
                if(token_set_attribute(token, token_value, collector) == ERR_INTERNAL) //nahrani atributu do tokeny a soucasne kontrola
                {
                    token_set_type(token, ERR_INTERNAL);
                    return token;
                }
                token_set_type(token, actual_state);
                final_state = true;
                break;
            case FLOAT_EXP_0: //DONE
                c = get_next_char(token_value);
                if(type_of_char(c) == NUM)
                    next_state = FLOAT_EXP_2;
                else if(c == '+' || c == '-')
                    next_state = FLOAT_EXP_1;
                else
                    next_state = LEX_ERROR;

                if(arr_add_char(token_value,(char) c) == ERR_INTERNAL)
                {
                    token_set_type(token, ERR_INTERNAL);
                    return token;
                }
                break;
            case FLOAT_EXP_1: //DONE
                c = get_next_char(token_value);
                if(type_of_char(c) == NUM)
                    next_state = FLOAT_EXP_2;
                else
                    next_state = LEX_ERROR;

                if(arr_add_char(token_value,(char) c) == ERR_INTERNAL)
                {
                    token_set_type(token, ERR_INTERNAL);
                    return token;
                }
                break;
            case FLOAT_EXP_2: //DONE
                c = get_next_char(token_value);
                if(type_of_char(c) != NUM)
                {
                    next_state = FLOAT_2;
                    arr_set_buffer(token_value, c);
                }
                else //==NUM
                {
                    if(arr_add_char(token_value,(char) c) == ERR_INTERNAL)
                    {
                        token_set_type(token, ERR_INTERNAL);
                        return token;
                    }
                }
                break;
            default:
                next_state = ERR_INTERNAL;
        }//konec switch
        actual_state = next_state;
        first = 0;
    }//konec for
    return token;
}//konec get_token()

int arr_init(Tarray *arr) //nepřidáváme do GC
{
    char *temp = (char *) malloc(sizeof(char) * INIT_SIZE);

    arr->array = temp;

    if(arr->array == NULL)
    {
        fprintf(stderr, MESSAGE_ALLOCATION);
        return ERR_INTERNAL;
    }
    arr->lenght = INIT_SIZE;
    arr->used = 0;
    arr->buffer_flag = false;
    arr->eol_flag = false;
    return SUCCESS;
}

int arr_add_char(Tarray *arr, char c)
{
    if(arr->lenght > arr->used) //pokud je misto
    {
        arr->array[arr->used++] = c; //pridani prvku na prvni volne misto a zvyseni used
        return SUCCESS;
    }
    char *temp_ptr = (char *) realloc(arr->array, sizeof(char) * arr->lenght * 2); //zvetseni pole na dvojnasobek
    if(temp_ptr == NULL) //realokace neuspesna
    {
        fprintf(stderr, MESSAGE_ALLOCATION);
        free(arr->array); //dealokace pole
        return ERR_INTERNAL;
    }
    arr->array = temp_ptr; //predani noveho ukazatele na pole
    arr->lenght *= 2; //velikost se nam zdvojnasobila
    arr->array[arr->used++] = c; //pridani prvku na prvni volne misto a zvyseni used
    return SUCCESS;
}

int arr_get_buffer(Tarray *arr)
{
    arr->buffer_flag = false;
    return arr->buffer;
}

int get_next_char(Tarray *arr) //TODO by Berry: problem CRLF vyresen tak, ze CR zahodim(libovolny pocet CR)
{
    int output;
    if(arr->buffer_flag == true)
        output = arr_get_buffer(arr);
    else
        output = getchar();
    if(output == 13) //CRLF reseno tady
        output = get_next_char(arr);
    return output;
}
int arr_set_buffer(Tarray *arr, int c)
{
    if(arr == NULL) return ERR_INTERNAL;
    arr->buffer = c;
    arr->buffer_flag = true;
    return SUCCESS;
}
int arr_reset(Tarray *arr)
{
    if(arr->lenght != INIT_SIZE) //pokud je pole vetsi nez vychozi velikost
    {
        char *temp_ptr = (char *) realloc(arr->array, sizeof(char) * INIT_SIZE); //zmenseni na INIT_SIZE
        if(temp_ptr == NULL) //realokace neuspesna
        {
            fprintf(stderr, MESSAGE_ALLOCATION);
            free(arr->array); //dealokace pole
            return ERR_INTERNAL;
        }
        arr->array = temp_ptr; //predani noveho ukazatele na pole
        arr->lenght = INIT_SIZE;
    }
    arr->used = 0;
    return SUCCESS;
}

void arr_free(Tarray *arr)
{
    free(arr->array);
}

char *arr_get_value(Tarray *arr, Tgarbage_collector *collector)
{
    char *output = (char *) malloc(sizeof(char) * (arr->used + 1)); //alokace pro predavany retezec, jedno misto navic pro \0
    gc_add_garbage(collector, output);
    if(output == NULL)
    {
        fprintf(stderr, MESSAGE_ALLOCATION);
        arr_free(arr);
        return NULL;
    }
    for(int i = 0; i < arr->used; i++) //kopirovani pole
        output[i] = arr->array[i];
    output[arr->used] = '\0'; //na konec retezce dam ukoncovaci znak
    return output;
}


int token_init(Ttoken *token)
{
    token->type = EMPTY;
    token->attribute = NULL;
    return SUCCESS;
}


int token_set_type(Ttoken *token, int token_type)
{
    token->type = token_type;
    return SUCCESS;
}

int token_set_attribute(Ttoken *token, Tarray *arr, Tgarbage_collector *collector)
{
    char *attribute = arr_get_value(arr, collector);
    if (attribute == NULL)
    {
        return ERR_INTERNAL;
    }
    token->attribute = attribute;
    return SUCCESS;
}


int type_of_char(const int c)
{
    if(c >= 'a' && c <= 'z')
        return SMALL;
    else if(c >= 'A' && c <= 'Z')
        return CAPITAL;
    else if(c >= '0' && c <= '9')
        return NUM;
    else
        return OTHER;
}

int is_keyword(const char *str)
{
    for (int i = 0; i < NUM_OF_KEYWORDS; i++)
    {
        if(!strcmp(str, key_words[i])) //shoda
            return KEY_DEF + i; //KEY_DEF je prvni z keywords, dalsi nasleduji
    }
    return false; //nenasel
}
