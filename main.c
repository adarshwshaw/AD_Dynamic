#include <stdio.h>


// static_assert(sizeof(unsigned long long) == 8,"Only support 64 bit systems.");

// typedef unsigned long long dynamic;

// #define SIGN_MASK (1LL<<63LL)
// #define EXP_MASK ((1LL<<11LL) - 1LL)<<52LL
// #define VAL_MASK ((1LL<<48LL) -1LL)

// #define TYPE_MASK ((1ULL << 4ULL) - 1ULL) << 48ULL

// #define TO_BYTES(x) *(uint64_t*)&x

// typedef enum {
//     N_NULL,
//     N_BOOL,
//     N_CHAR,
//     N_INT,
//     N_UINT,
//     N_SIZE_T,
//     N_STR,
//     N_PTR,
//     N_NAN =8
// }Ntypes;

// void printbits(uint64_t x){
//     uint8_t *y = (uint8_t*)&x;
//     for (int i=7;i>=0;i--){
//         uint8_t k = y[i];
//         for(int j=7;j>=0;j--){
//             printf("%d",(k&0x80)>>7);
//             k=k<<1;
//         }
//         printf(" ");
//     }
//     printf("\n");
// }

// dynamic set_val(dynamic res, uint64_t val){
//     res = (res & ~VAL_MASK)| (res|(val&VAL_MASK));
//     return res;
// }

// dynamic mkinf() {
//     dynamic x = EXP_MASK;
//     return x;
// }
// dynamic set_type(dynamic d, uint8_t type){
//     d = (d& ~TYPE_MASK)| ((uint64_t)(type&0xf) << 48);
//     return d;
// }
// char get_type(dynamic d){
//     d = (d&TYPE_MASK)>>48;
//     return (char)d;
// }
// int asint(dynamic d){
//     if (get_type(d) != N_INT){
//         assert(0 && "Type mismatch");
//     }
//     return (int)d;
// }

// char* asstr(dynamic d){
//     if (get_type(d) != N_STR){
//         assert(0 && "Type mismatch");
//     }
//     d = d&VAL_MASK;
//     return (char*)d;
// }
// _Bool isDouble(dynamic d){
//     _Bool isbox = (d&EXP_MASK) == EXP_MASK;
//     _Bool isnan = isbox && (get_type(d) == N_NAN);
//     _Bool isinf = isbox && (get_type(d) == N_NULL) && ((d&VAL_MASK) == 0);
//     return (!isbox || isnan || isinf);
// }
// void printDynamic(dynamic d){
//     if (isDouble(d)){
//         printf("%lf",*(double*)&d);
//         return ;
//     }
//     switch (get_type(d))
//     {
//     case N_NULL:
//         printf("null");
//         break;
//     case N_INT:
//         printf("%d",asint(d));
//         break;
//     case N_STR:
//         printf("%s",asstr(d));
//         break;
//     default:
//         assert(0 && "print not implemented");
//         break;
//     }

// }

// dynamic dfloat(double d){
//     return TO_BYTES(d);
// }

// int main2(int argc, char const *argv[])
// {
//     char *c = "here";
//     double da = 0.0/0.0;
//     dynamic d = set_val(set_type(mkinf(),N_STR),c);//TO_BYTES(da);
//     printf("%d\n", get_type(d));
//     printDynamic(d);
//     printf("\n");
//     // double d = 1.0/0.0;
//     printbits(TO_BYTES(d));
//     printbits(TO_BYTES(c));
//     return 0;
// }

#include "ad_dynamic.h"

#define LOG() {\
    ad_dyn_print(a);\
    printf("\n");\
}

int main(int argc, char const *argv[])
{
    dynamic a = ad_dyn_create_Bool(1);
    LOG();
    a = ad_dyn_create_Char('c');
    LOG();
    a = ad_dyn_create_double(445.7);
    LOG();
    a = ad_dyn_create_Int(-500);
    LOG();
    a = ad_dyn_create_UInt(500);
    LOG();
    a = ad_dyn_create_Size_t(1024*1024);
    LOG();
    a = ad_dyn_create_Str("hello world");
    LOG();
    return 0;
}
