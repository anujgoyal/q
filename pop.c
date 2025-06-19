#include <stdio.h>
#define ATM __attribute((minsize,noinline)) 
#define ATI __attribute((minsize,always_inline))
#define V(t,n) t##n __attribute((vector_size(1<<n),aligned(1)))
//typedef int V(s,6);
//typedef float e2,V(e,6);
typedef char i0,V(g,4),V(g,6),V(g,5);
typedef unsigned i2,V(i,5),V(i,6),V(i,8);
//typedef unsigned long U,(*_U)(i2,U),V(j,6);
#undef V
#define Vx g6 x
#define Vz g6 z
#define Iz i6 z
#define iR i2*R
#define Ri R[i] 
#define zi z[i] 

#define i(b,z) {i2 $=b;i2 i=0;while(i<$){z;++i;}}

#define B(o) __builtin_##o
#define o1(o) B(ia32_##o##128)
#define o2(o) B(ia32_##o##256)
#define Xv(i) ((g5*)&x)[i] 
#define Zv(i) ((g5*)&z)[i] 

void pi6(i6 v){for(int i=0;i<16;++i){printf("%d ",v[i]);}putchar('\n');}

// popcntd (avx2)
static g5 MB={{0x0F}}, MZ={{0x00}}, MLU={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
#define MSHUFFLE(z, y, x, w) (((z) << 6) | ((y) << 4) | ((x) << 2) | (w))

ATI static g5 pop5(g5 a){
 // count bits in each byte
 g5 lo = a & MB;
 g5 hi = o2(psrldi)(a,4) & MB;
 g5 plo = o2(pshufb)(MLU,lo);
 g5 phi = o2(pshufb)(MLU,hi);
 g5 pby = plo + phi;
 // sum bytes within each int
 g5 s1 = o2(psadbw)(pby,MZ);
 g5 s2 = o2(pshufd)(s1,MSHUFFLE(3,3,1,1));
 g5 s3 = s1 + s2; 
 g5 s4 = o2(pshufd)(s3,MSHUFFLE(2,2,0,0));
 return s4;
}

ATM static g6 pop(Vx){ Vz;
 Zv(0)=pop5(Xv(0));
 Zv(1)=pop5(Xv(1));
 return z;
}

ATM static i6 pop2(Vx){ Iz;
 iR=&x;
 i(16,zi=B(popcount)(Ri))
 return z;
}

int main() {
 int data[16] = {0x0000000F, 0xFFFF0000, 0x00000000, 0xFFFFFFFF,0x55555555, 0xAAAAAAAA, 0x12345678, 0xF0F0F0F0,
                 0x00000001, 0x00000002, 0x00000004, 0x00000008,0x00000010, 0x00000020, 0x00000040, 0x00000080};

 Iz = pop2(*(g6*)&data);
 pi6(z);

 z = pop(*(g6*)&data);
 pi6(z);
 return 0;
}

