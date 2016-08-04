#include <assert.h>
#include <string.h>
#include <jni.h>
#include <jvmti.h>
#include <stdlib.h>

#include "agent_main.h"
#include "util.h"
#include "agent.h"


static const char *bda_parse_type_descriptor(const char *tdesc)
{
    const char *lookahead = tdesc;

    switch (*lookahead) {
    case 'V':
        break;
    case 'B': case 'C': case 'I':  case 'S':case 'Z':
    case 'F':
        break;
    case 'D':
    case 'J' :
        break;
    case 'L':
        while (*lookahead != ';') {
            assert(*lookahead != '\0');
                assert(*lookahead != '\0');
                lookahead++;
            }
            assert(*lookahead == ';');
            break;
    case '[':
        while (*lookahead == '[') 
            lookahead++;
        switch(*lookahead) {
        case 'B': case 'C': case 'F': case 'I':  case 'S':case 'Z':
        case 'D': case 'J':
            break;
        case 'L':
            while (*lookahead != ';') 
                    lookahead++;
            assert(*lookahead == ';');
            break;
        default:
            assert(0);
        }
        break;
    default:
        assert(0);
        break;
    }

    return lookahead;
}

void bda_parse_method_descriptor(
    const char *desc, const char ***arg_types, const char **ret_type)
{
    struct str_list {
        char *str;
        struct str_list *next;
    } *arguments = NULL;
    int num_arguments = 0;
    const char *lookahead = desc;
    const char *end;
    char **argument_types, *return_type;

    assert(*lookahead == '(');
    lookahead++;
    while (*lookahead != ')') {
        struct str_list *elem;
        char *tdesc;
        int len;

        end=bda_parse_type_descriptor(lookahead);
        len=end - lookahead + 1;
        tdesc= malloc(len+ 1);
        memcpy(tdesc, lookahead, len);
        tdesc[len]= '\0';

        elem=malloc(sizeof *elem);
        elem->str = tdesc;
        elem->next = arguments;
        arguments=elem;

        lookahead=end + 1;        
        num_arguments++;
    }
    assert(*lookahead == ')');
    lookahead++;
    end=bda_parse_type_descriptor(lookahead);
    return_type=malloc(end - lookahead + 1 + 1);
    memcpy(return_type, lookahead, end - lookahead + 1);
    return_type[end - lookahead + 1] = '\0';

    argument_types = malloc(sizeof *argument_types * (num_arguments + 1));
    argument_types[num_arguments] = NULL;
    while (num_arguments > 0) {
        struct str_list *elem;

        elem=arguments;
        arguments=elem->next;

        argument_types[num_arguments-1]=elem->str;
        free(elem);
        num_arguments--;
    }
    assert(arguments == NULL);

    *arg_types = (const char **)argument_types;
    *ret_type = (const char *)return_type;
}
