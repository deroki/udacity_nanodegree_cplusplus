# gdb use

```bash
carlos@Navi:~/Desktop/openmap/CppND-Route-Planning-Project/Memory_tutorial$ gdb gdb_tutorial 
GNU gdb (Ubuntu 9.1-0ubuntu1) 9.1
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from gdb_tutorial...
(gdb) list
1       #include <stdio.h>
2
3       int main()
4       {
5           char str1[]= "UDACITY";
6           printf("%s",str1);
7
8           return 0;
9       }
(gdb) break 8
Breakpoint 1 at 0x11aa: file main.cpp, line 8.
(gdb) run
Starting program: /home/carlos/Desktop/openmap/CppND-Route-Planning-Project/Memory_tutorial/gdb_tutorial 

Breakpoint 1, main () at main.cpp:8
8           return 0;
(gdb) p srt1
No symbol "srt1" in current context.
(gdb) p str1
$1 = "UDACITY"
(gdb) p & str1
$2 = (char (*)[8]) 0x7fffffffdb90
(gdb) x/10xb Quit
(gdb) x/10xb 0x7fffffffdb90
0x7fffffffdb90: 0x55    0x44    0x41    0x43    0x49    0x54    0x59    0x00
0x7fffffffdb98: 0x00    0x86
(gdb) 
```