# google-code-jam
My solutions to [Google Code Jam] (https://code.google.com/codejam/).

### Build

CMake.

### Run

It is preferred to run each program with: `program.exe <input_a.txt >output_b.txt 2>error_b.txt`
In this way, **std::cin** is dedicated to read the **input_a.txt**, **std::cout** for **output_b.txt** and **std::cerr** for **error_b.txt**. You can then check the **error_b.txt** each time you call the program to make sure no unexpected error is produced. You do not need to hardcoded anything in the source code. If you do not like the commandline argument input. You can do it inside the source code by:
`freopen ("input_a.txt","r",stdin);`
`freopen ("output_a.txt","w",stdout);`
`freopen ("error_a.txt","w",stderr);`

### Test

Later:)
