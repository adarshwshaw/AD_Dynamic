#include "ad_dynamic.h"
#include <assert.h>
#include <stdio.h>

static_assert(sizeof(unsigned long long) == 8,"Only support 64 bit systems.");

dynamic ad_dyn_setVal(dynamic d, dynamic val){
    d = (d & ~AD_DYN_VAL_MASK)| (d|(val&AD_DYN_VAL_MASK));
    return d;
}
dynamic ad_dyn_setType(dynamic d , ad_dyn_types type){
    d = (d& ~AD_DYN_TYPE_MASK)| ((dynamic)(type&0xf) << 48);
    return d;
}
ad_dyn_types ad_dyn_getType(dynamic d){
    d = (d&AD_DYN_TYPE_MASK)>>48;
    return (ad_dyn_types)d;
}
void ad_dyn_print(dynamic d){
    if (ad_dyn_isDouble(d)){
        printf("%lf",*(double*)&d);
        return ;
    }
    switch (ad_dyn_getType(d))
    {
    case AD_DYN_NULL:
        printf("null");
        break;
    case AD_DYN_BOOL:
        printf("%d", ad_dyn_asBool(d)?1:0);\
        break;
    case AD_DYN_CHAR:
        printf("%c",ad_dyn_asChar(d));
        break;
    case AD_DYN_INT:
        printf("%d",ad_dyn_asInt(d));
        break;
    case AD_DYN_UINT:
        printf("%u",ad_dyn_asUInt(d));
        break;
    case AD_DYN_Size_t:
        printf("%zu",ad_dyn_asSize_t(d));
        break;
    case AD_DYN_STR:
        printf("%s",ad_dyn_asStr(d));
        break;
    case AD_DYN_PTR:
        printf("%p",ad_dyn_asPtr(d));
        break;
    default:
        assert(0 && "print not implemented");
        break;
    }
}

// null
dynamic ad_dyn_create_null(){
    dynamic c = AD_DYN_EXP_MASK;
    c = ad_dyn_setVal(ad_dyn_setType(c,AD_DYN_NULL),1);
    return c;
}
// double and float
_Bool ad_dyn_isDouble(dynamic d){
    _Bool isbox = (d&AD_DYN_EXP_MASK) == AD_DYN_EXP_MASK;
    _Bool isnan = isbox && (ad_dyn_getType(d) == AD_DYN_NAN);
    _Bool isinf = isbox && (ad_dyn_getType(d) == AD_DYN_NULL) && ((d&AD_DYN_VAL_MASK) == 0);
    return (!isbox || isnan || isinf);
}
dynamic ad_dyn_create_double(double d){
    return AD_DYN_AS_DYNAMIC(d);
}
double ad_dyn_asDouble(dynamic d){
    return *(double*)&d;
}

static _Bool dyn_isType(dynamic d, ad_dyn_types t){
    if(ad_dyn_getType(d) == t)
        return 1;
    else
        return 0;
}

// char
_Bool ad_dyn_isChar(dynamic d){
    return dyn_isType(d,AD_DYN_CHAR) && (!ad_dyn_isDouble(d));
}
dynamic ad_dyn_create_Char(char d){
    dynamic c = AD_DYN_EXP_MASK;
    c = ad_dyn_setVal(ad_dyn_setType(c,AD_DYN_CHAR),d);
    return c;
}
char ad_dyn_asChar(dynamic d){
    assert(ad_dyn_isChar(d) && "ERROR: Type mismatch not a character");
    char c = (char)d;
    return c;
}

// bool
_Bool ad_dyn_isBool(dynamic d){
    return dyn_isType(d,AD_DYN_BOOL) && (!ad_dyn_isDouble(d));
}
dynamic ad_dyn_create_Bool(_Bool d){
    dynamic c = AD_DYN_EXP_MASK;
    c = ad_dyn_setVal(ad_dyn_setType(c,AD_DYN_BOOL),d);
    return c;
}
_Bool ad_dyn_asBool(dynamic d){
    assert(ad_dyn_isBool(d) && "ERROR: Type mismatch not a boolean");
    _Bool c = (_Bool)d;
    return c;
}

// int
_Bool ad_dyn_isInt(dynamic d){
    return dyn_isType(d,AD_DYN_INT) && (!ad_dyn_isDouble(d));
}
dynamic ad_dyn_create_Int(int d){
    dynamic c = AD_DYN_EXP_MASK;
    c = ad_dyn_setVal(ad_dyn_setType(c,AD_DYN_INT),d);
    return c;
}
int ad_dyn_asInt(dynamic d){
    assert(ad_dyn_isInt(d) && "ERROR: Type mismatch not a Integer");
    int c = (int)d;
    return c;
}

// unsigned int
_Bool ad_dyn_isUInt(dynamic d){
    return dyn_isType(d,AD_DYN_UINT) && (!ad_dyn_isDouble(d));
}
dynamic ad_dyn_create_UInt(unsigned int d){
    dynamic c = AD_DYN_EXP_MASK;
    c = ad_dyn_setVal(ad_dyn_setType(c,AD_DYN_UINT),d);
    return c;
}
unsigned int ad_dyn_asUInt(dynamic d){
    assert(ad_dyn_isUInt(d) && "ERROR: Type mismatch not a Unsigned Integer");
    unsigned int c = (unsigned int)d;
    return c;
}

// unsigned long long
_Bool ad_dyn_isSize_t(dynamic d){
    return dyn_isType(d,AD_DYN_Size_t) && (!ad_dyn_isDouble(d));
}
dynamic ad_dyn_create_Size_t(unsigned long long d){
    dynamic c = AD_DYN_EXP_MASK;
    c = ad_dyn_setVal(ad_dyn_setType(c,AD_DYN_Size_t),d);
    return c;
}
unsigned long long ad_dyn_asSize_t(dynamic d){
    assert(ad_dyn_isSize_t(d) && "ERROR: Type mismatch not a Size_t");
    unsigned long long c= d&AD_DYN_VAL_MASK;
    return c;
}

// char* / str
_Bool ad_dyn_isStr(dynamic d){
    return dyn_isType(d,AD_DYN_STR) && (!ad_dyn_isDouble(d));
}
dynamic ad_dyn_create_Str(const char* d){
    dynamic c = AD_DYN_EXP_MASK;
    c = ad_dyn_setVal(ad_dyn_setType(c,AD_DYN_STR),AD_DYN_AS_DYNAMIC(d));
    return c;
}
char* ad_dyn_asStr(dynamic d){
    assert(ad_dyn_isStr(d) && "ERROR: Type mismatch not a String pointer");
    char* c= (char*)(d&AD_DYN_VAL_MASK);
    return c;
}

// ptr
_Bool ad_dyn_isPtr(dynamic d){
    return dyn_isType(d,AD_DYN_PTR) && (!ad_dyn_isDouble(d));
}
dynamic ad_dyn_create_Ptr(void* d){
    dynamic c = AD_DYN_EXP_MASK;
    c = ad_dyn_setVal(ad_dyn_setType(c,AD_DYN_PTR),AD_DYN_AS_DYNAMIC(d));
    return c;
}
void* ad_dyn_asPtr(dynamic d){
    assert(ad_dyn_isPtr(d) && "ERROR: Type mismatch not a pointer");
    void* c= (void*) (d&AD_DYN_VAL_MASK);
    return c;
}

// array
_Bool ad_dyn_isArray(dynamic d){
    return dyn_isType(d,AD_DYN_ARR) && (!ad_dyn_isDouble(d));
}
dynamic ad_dyn_create_Array(void* d){
    dynamic c = AD_DYN_EXP_MASK;
    c = ad_dyn_setVal(ad_dyn_setType(c,AD_DYN_ARR),AD_DYN_AS_DYNAMIC(d));
    return c;
}
void* ad_dyn_asArray(dynamic d){
    assert(ad_dyn_isPtr(d) && "ERROR: Type mismatch not a array");
    void* c= (void*) (d&AD_DYN_VAL_MASK);
    return c;
}