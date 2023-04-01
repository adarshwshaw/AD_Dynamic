@echo off
clang -std=c11 -c ad_dynamic.c -o build/ad_dynamic.o || exit /b
llvm-ar -r build/ad_dynamic.lib build/ad_dynamic.o || exit /b
clang -std=c11 -g main.c build/ad_dynamic.lib -o build/main.exe || exit /b
.\build\main.exe