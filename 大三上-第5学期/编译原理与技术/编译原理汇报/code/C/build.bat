@echo off
REM build.bat - HM 类型推导系统构建脚本（Windows）

echo ═══════════════════════════════════════════════════════════════
echo   Building HM Type Inference System
echo ═══════════════════════════════════════════════════════════════

REM 创建目录
if not exist build mkdir build
if not exist bin mkdir bin

REM 编译选项
set CC=gcc
set CFLAGS=-Wall -Wextra -std=c11 -g -I./include

echo Compiling source files...

REM 编译每个源文件
echo   src/type_utils.c
%CC% %CFLAGS% -c -o build/type_utils.o src/type_utils.c
if errorlevel 1 goto :error

echo   src/env.c
%CC% %CFLAGS% -c -o build/env.o src/env.c
if errorlevel 1 goto :error

echo   src/subst.c
%CC% %CFLAGS% -c -o build/subst.o src/subst.c
if errorlevel 1 goto :error

echo   src/unify.c
%CC% %CFLAGS% -c -o build/unify.o src/unify.c
if errorlevel 1 goto :error

echo   src/infer.c
%CC% %CFLAGS% -c -o build/infer.o src/infer.c
if errorlevel 1 goto :error

echo   src/ast.c
%CC% %CFLAGS% -c -o build/ast.o src/ast.c
if errorlevel 1 goto :error

echo   src/main.c
%CC% %CFLAGS% -c -o build/main.o src/main.c
if errorlevel 1 goto :error

REM 链接
echo Linking...
%CC% %CFLAGS% -o bin/hm_infer.exe build/*.o
if errorlevel 1 goto :error

echo.
echo ═══════════════════════════════════════════════════════════════
echo   Build successful! Executable: bin/hm_infer.exe
echo ═══════════════════════════════════════════════════════════════
echo.
echo Run with: bin\hm_infer.exe

if "%1"=="--run" (
    echo.
    bin\hm_infer.exe
)

goto :end

:error
echo.
echo ═══════════════════════════════════════════════════════════════
echo   Build FAILED!
echo ═══════════════════════════════════════════════════════════════
exit /b 1

:end

