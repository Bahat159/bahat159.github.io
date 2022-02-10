# To Assemble and link all file in this folder

  - To Assemble and link
  - as -o cpuid.o cpuid.s
  - ld -o cpuid cpuid.o

# To Assemble Using GCC Compiler to compile and link

- gcc -o cpuid cpuid.s

# Using GDB to debug application
 -In order to debug the assembly language program, you must first reassemble the source code using the `-gstabs` parameter
  - as `-gstabs` -o cpuid.o cpuid.s
  - ld -o cpuid cpuid.o
