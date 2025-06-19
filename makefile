# 2025.03.08
# clang --print-targets
# clang -target x86_64-apple-macos -o my_x86_binary my_source.c
# arch -x86_64 ./my_x86_binary

p0:p0.c makefile
	clang -Ofast -op0 p0.c -funsigned-char -fno-unwind-tables -w -target x86_64-apple-macos -mavx2
p256:p256.c makefile
	clang -Ofast -op256 p256.c -funsigned-char -fno-unwind-tables -w -target x86_64-apple-macos -mavx2

# 2025.03.16
blend:blend.c makefile
	clang -Ofast -oblend blend.c -funsigned-char -fno-unwind-tables -w -mavx2 -target x86_64-apple-macos 

# 2025.03.22
gather:gather.c makefile
	#clang -Ofast -ogather gather.c -funsigned-char -fno-unwind-tables -w -mavx512f -target x86_64-apple-macos 
	#clang -Ofast -ogather gather.c -funsigned-char -fno-unwind-tables -w -mavx2 -target x86_64-apple-macos 
	clang -Ofast -ogather gather.c -funsigned-char -fno-unwind-tables -w 

fma:fma.c makefile
	clang -Ofast -ofma fma.c -funsigned-char -fno-unwind-tables -w -mavx2 -mavxvnni -mfma -target x86_64-apple-macos

#2025.03.23
ie:ie.c makefile
	clang -Ofast -oie ie.c -funsigned-char -fno-unwind-tables -w -mavx2 -target x86_64-apple-macos

#2025.03.28
p2:p2.c makefile
	clang -Ofast -op2 p2.c -funsigned-char -fno-unwind-tables -w -mavx2 -target x86_64-apple-macos

#2025.05.23
pop:pop.c makefile
	clang -Ofast -opop pop.c -funsigned-char -fno-unwind-tables -w -mavx2 -target x86_64-apple-macos
