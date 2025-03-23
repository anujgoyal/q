#include <stdio.h>
#define V_(n) __attribute((vector_size(1<<n),aligned(1)))
typedef char     i0,g4 V_(4),g5 V_(5),g6 V_(6); //8b
typedef unsigned i2,         i5 V_(5),i6 V_(6); //32b
typedef float    e2,         e5 V_(5),e6 V_(6); //32b
typedef unsigned long U,              j6 V_(6); //64b
#define i(b,z) {i2 $=b;i2 i=0;while(i<$){z;++i;}}
#define Va g6 a
#define Vb g6 b
#define Vx g6 x
#define Vz g6 z
#define Ez e6 z
#define bu(o) __builtin_##o
#define o1(o) bu(ia32_##o##128)
#define o2(o) bu(ia32_##o##256)

#define Av(i) ((e5*)&a)[i] 
#define Bv(i) ((e5*)&b)[i] 
#define Xv(i) ((e5*)&x)[i] 
#define Zev(i) ((e5*)&z)[i] 
#define Ziv(i) ((i5*)&z)[i] 

//print utils
void pg6(g6 v){i(64,printf("%d ",v[i]))putchar('\n');}
void pj6(j6 v){i(8,printf("%d ",v[i]))putchar('\n');}
void pi6(i6 v){i(16,printf("%d ",v[i]))putchar('\n');}
void pe6(e6 v){i(16,printf("%3.2f ",v[i]))putchar('\n');}
void pe5(e5 v){i(8,printf("%3.2f ",v[i]))putchar('\n');}

// Insight: vfmaddsubps512_mask3 operates on a 512b vector, but AVX2 can only support 256b vectors
// https://grok.com/share/bGVnYWN5_6d7ca3ed-0620-40bb-951d-6e33d37dffe5

//_V(bm,o(vfmaddsubps512_mask3)(a,b,x,-1,9),Va,Vb,Vx)
static e5 MALT={1,-1,1,-1,1,-1,1,-1};
static g6 bm(Va,Vb,Vx){ Ez;
 Zev(0)=o2(vfmaddps)(Av(0),Bv(0),Xv(0)*MALT); //printf("z0:");pe5(Zev(0));
 Zev(1)=o2(vfmaddps)(Av(1),Bv(1),Xv(1)*MALT); //printf("z1:");pe5(Zev(1));
 return z;
}

// Ef(IE,o(cvtps2dq512_mask)(x,x,-1,4))
// https://grok.com/share/bGVnYWN5_8e96d3cd-749d-4c30-b2e7-3baa91133a55
// https://grok.com/share/bGVnYWN5_cf9ff7f3-753f-426d-b661-78865d00f178
static g6 IE(Vx){
 i6 z;
 Ziv(0)=o2(cvtps2dq)(Xv(0));
 Ziv(1)=o2(cvtps2dq)(Xv(1));
 return z;
}

#include <stdlib.h>
int main() {
 // mmap 4096 bytes (1024 x 32b floats)
 float*fa=(float*)malloc(1024*sizeof(float));
 i(1024,fa[i]=(float)rand()/RAND_MAX);

 // FMA
 e6 *a=fa, *b=fa+64, *x=fa+128;
 printf("a:");pe6(*a);
 printf("b:");pe6(*b);
 printf("x:");pe6(*x);
 e6 tf=bm(*a,*b,*x);
 printf("tf:");pe6(tf);

 // IE (int from float)
 e6 xx={15.6f, 14.2f, 13.9f, 12.0f, 11.5f, 10.1f, 9.7f, 8.3f, 7.8f, 6.4f, 5.9f, 4.5f, 3.2f, 2.7f, 1.3f, 0.9f};
 printf("xx:");pe6(xx);
 i6 z=IE(xx);
 printf(" z:");pi6(z);

 return 0;
}

