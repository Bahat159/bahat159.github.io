# To Assemble and link (Building the executables) in this Repo
  ***Basic method to assmeble abd link asm files without stress***

  - `as -o cpuid.o cpuid.s`
  - `ld -o cpuid cpuid.o`
#
- ***when in doubt or encountered error you should use the below technique to successfully assemble and link your executable***
#
***Another way to Assemble and Link some files with Printf function calls in this Repo***
  - **update you linux download manager**
  - `sudo apt-get update`
  - **Install the required packages**
  - `sudo apt-get install libc6:i386`
  - `sudo apt-get install libc6-dev-i386`
  - **Assemble the program source**
  - `as --32 -o movtest.o movtest.s`
  - **Link the object file to create an executable**
  - `ld -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -o movtest -lc movtest.o`

# To Assemble Using `GCC` Compiler to compile and link
- `gcc -o cpuid cpuid.s`

# Using `GDB` to debug application
**In order to debug the assembly language program, you must first reassemble the source code using the `-gstabs` parameter**
  - `as -gstabs -o cpuid.o cpuid.s`
  - `ld -o cpuid cpuid.o`
