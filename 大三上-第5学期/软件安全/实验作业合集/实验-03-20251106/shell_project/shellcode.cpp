#include<windows.h>  
int main()  
{  
    HINSTANCE LibHandle;  
    char dllbuf[13] = "kernel32.dll";  
    LibHandle = LoadLibrary(dllbuf);  
    _asm{  
        sub sp,0x440  
        xor ebx,ebx  
        push ebx  
        push 0x74  
        push 0x78742E65  
        push 0x646F636C  
        push 0x6C656873  
        push 0x20657865  
        push 0x2E646170  
        push 0x65746F6E  
  
        mov eax,esp 
        push 0x5  
        push eax
  
        mov eax,0x77E78601  //WinExec  入口地址  
        call eax  
        push ebx  
        mov eax,0x77E7BB0B  //ExitProcess  入口地址  
        call eax  
    }  
    return 0;  
}  
