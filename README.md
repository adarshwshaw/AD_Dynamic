# AD_DYNAMIC

It implements a dynamic type in c.

Using the technique of nan boxing.

### Usage:

```
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
```