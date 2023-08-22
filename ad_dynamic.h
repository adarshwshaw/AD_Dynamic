#ifndef AD_DYNAMIC_INCLUDE_DEFS
#define AD_DYNAMIC_INCLUDE_DEFS

typedef unsigned long long dynamic;

#define AD_DYN_SIGN_MASK (1LL<<63LL)
#define AD_DYN_EXP_MASK ((1LL<<11LL) - 1LL)<<52LL
#define AD_DYN_VAL_MASK ((1LL<<48LL) -1LL)

#define AD_DYN_TYPE_MASK ((1ULL << 4ULL) - 1ULL) << 48ULL

#define AD_DYN_AS_DYNAMIC(x) *(dynamic*)&x
// pointers are actually 48 bit(6 BYTES) long
//sign exponent mantissa(52 = 4(unused) + 48)
//x xxxxxxxxxxx xxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//NAN - exponent bit all 1 and non zero mantissa
//x 11111111111 xxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   
//xxxx == 1000 (or non zero mantissa with first bit as zero for signalling)
//Inf - exponent and mantissa all bit to zero +inf/-inf based on sign bit
//x 11111111111 0000 000000000000000000000000000000000000000000000000     
//
typedef enum {
    AD_DYN_NULL = 0,
    AD_DYN_BOOL,
    AD_DYN_CHAR,
    AD_DYN_INT,
    AD_DYN_UINT,
    AD_DYN_Size_t,
    AD_DYN_STR,
    AD_DYN_PTR,
    AD_DYN_NAN, //0b1000
    AD_DYN_ARR
}ad_dyn_types;

dynamic ad_dyn_setVal(dynamic d, dynamic val);
dynamic ad_dyn_setType(dynamic d , ad_dyn_types type);
ad_dyn_types ad_dyn_getType(dynamic d);
void ad_dyn_print(dynamic d, void (*print_complex)(void*));

// type specific checker, getter and setter
// null
_Bool ad_dyn_isNull(dynamic d);
dynamic ad_dyn_create_null();
// double and float
_Bool ad_dyn_isDouble(dynamic d);
dynamic ad_dyn_create_double(double d);
double ad_dyn_asDouble(dynamic d);

// char
_Bool ad_dyn_isChar(dynamic d);
dynamic ad_dyn_create_Char(char d);
char ad_dyn_asChar(dynamic d);

// bool
_Bool ad_dyn_isBool(dynamic d);
dynamic ad_dyn_create_Bool(_Bool d);
_Bool ad_dyn_asBool(dynamic d);

// int
_Bool ad_dyn_isInt(dynamic d);
dynamic ad_dyn_create_Int(int d);
int ad_dyn_asInt(dynamic d);

// unsigned int
_Bool ad_dyn_isUInt(dynamic d);
dynamic ad_dyn_create_UInt(unsigned int d);
unsigned int ad_dyn_asUInt(dynamic d);

// unsigned long long
_Bool ad_dyn_isSize_t(dynamic d);
dynamic ad_dyn_create_Size_t(unsigned long long d);
unsigned long long ad_dyn_asSize_t(dynamic d);

// char* / str
_Bool ad_dyn_isStr(dynamic d);
dynamic ad_dyn_create_Str(const char* d);
char* ad_dyn_asStr(dynamic d);

// ptr
_Bool ad_dyn_isPtr(dynamic d);
dynamic ad_dyn_create_Ptr(void* d);
void* ad_dyn_asPtr(dynamic d);

// array
_Bool ad_dyn_isArray(dynamic d);
dynamic ad_dyn_create_Array(void* d);
void* ad_dyn_asArray(dynamic d);
#endif //AD_DYNAMIC_INCLUDE_DEFS
