//#include <immintrin.h>
#include <stdio.h>
#define V_(n) __attribute((vector_size(1<<n),aligned(1)))
typedef char     i0,g4 V_(4),g5 V_(5),g6 V_(6); //8b
typedef unsigned i2,         i5 V_(5),i6 V_(6); //32b
typedef unsigned long U,              j6 V_(6); //64b
#define ZV static g6
ZV z0; // init 64 elements to zero
#define i(b,z) {i2 $=b;i2 i=0;while(i<$){z;++i;}}
#define ss i0*s
#define Yx i5 x   // 256b, 32b x 8
#define Jz j6 z   // 512b, 64b x 8
#define Us *(U*)s
#define zi z[i]

#define bu(o) __builtin_##o
#define o1(o) bu(ia32_##o##128)
#define o2(o) bu(ia32_##o##256)

// Insight: __builtin_ia32_gathersiv8di corresponds to AVX-512 gather instruction (e.g., VPGATHERQQ), 
// collects 8 x 64b ints (di = double-word integer, v8 = vector of 8) into a 512-bit vector (__m512i). It uses:
//  src: Source vector (values for inactive mask lanes).
//  base: Base memory address pointer.
//  indices: Vector of 8x 64-bit indices (__m512i) specifying offsets.
//  mask: Vector of 8x 64-bit mask elements (__m512i), where non-zero enables gathering.
//  scale: A compile-time constant (1, 2, 4, or 8) that scales the indices.
// In both cases the input is 'i5' or a 256b vector of 32b * 8 elements
// The output will be a 512b vector of 64b * 8 elements

//_V(g3,o(gathersiv8di)(z0,s,x,-1,1),ss,Yx)
static g6 g3(ss,Yx){Jz;i(8,U*u=s+x[i];zi=*u;)return z;}
/*static g6 g3(ss,Yx){ j6 z; U*u;
 for(int i=0;i<8;i++) {
  printf("\ns: %p\n",s);
  printf("x[%d]: %d\n",i,x[i]);
  u=s+x[i];
  printf("s+x: %p\n",s+x[i]);
  printf("u: %p\n",u);
  printf("*u: %d\n",*u);
  zi=*u;
  printf("z[%d]: %d\n",i,zi);
 }
return z;}*/

//_V(G3,o(gathersiv8di)(z0,s,x,-1,8),ss,Yx)
static g6 G3(ss,Yx){Jz;i(8,zi=*(U*)(s+(x[i]*8)))return z;}

//print utils
void pg6(g6 v){i(64,printf("%d ",v[i]))putchar('\n');}
void pj6(j6 v){i(8,printf("%d ",v[i]))putchar('\n');}

int main() {
 // WRONG: array with 32 x 8b = 256b //char data[] = {32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63};
 // RIGHT: array of 64b values, but it could be sparse data eg. over 1024 bytes
 U d[]={77,10000,20000,30000, 40000,50000,60000,70000};

 printf("&(data[0]:%p \n", &(d[0]));
 printf("&(data[1]:%p \n", &(d[1]));

 U db[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
           32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63};
 // Indices to gather (8b in a 256-bit vector)
 //i5 y = {0,1,2,3,4,5,6,7}; //32b*8
 //i5 x = {7,6,5,4,3,2,1,0}; //32b*8  Note that small byte offsets don't work
 i5 x = {7*8,6*8,5*8,4*8,3*8,2*8,1*8,0}; //32b*8
 //i5 x = {0,8,16,0,0,0,0,0};

 // Perform the gather operation
 //__m512i result = __builtin_ia32_gathersiv8di(TBD, data, x, -1, 8);
 // NB: Assumption that all the data is closeby... probably not a correct assumption
 //g6 r= bu(ia32_gathersiv8di)(z0, data, x, -1, 1);
 //g6 s= bu(gathersiv8di)(z0, data, y, -1, 8);
 printf("\n");
 printf("d:");pj6(*(j6*)&d);
 printf("g3:");pj6(g3(d,x));
 printf("\n");
 printf("db:");pj6(*(j6*)&db);
 printf("G3:");pj6(G3(db,x));
 printf("\n");

 return 0;
}

/* AVX2 utils
#define L(e)  Vz;i(4,((g4*)&z)[i]=e)z
#define zv(i)        ((g4*)&z)[i]
#define av(i)        ((g4*)&a)[i]
#define bv(i)        ((g4*)&b)[i]
#define sv(e)        *(g4*)(s+e)
static g4 M15={15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},M31={31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},M47={47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47};
static g4 v4u(g6 a,g4 x){g4 z,i=x&M15;z=o1(pblendvb)(o1(pshufb)(av(0),i),o1(pshufb)(av(1),i),x>M15);z=o1(pblendvb)(z,o1(pshufb)(av(2),i),x>M31);z=o1(pblendvb)(z,o1(pshufb)(av(3),i),x>M47);return z;} //v4u~vqtbl4
static g4 s4u(ss,g4 x){g4 z,i=x&M15;z=o1(pblendvb)(o1(pshufb)(sv(0),i),o1(pshufb)(sv(16),i),x>M15);z=o1(pblendvb)(z,o1(pshufb)(sv(32),i),x>M31);z=o1(pblendvb)(z,o1(pshufb)(sv(48),i),x>M47);return z;} 
static g4 MiB={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3},MiF={0,0,0,0,4,4,4,4,8,8,8,8,12,12,12,12};
static g4 v1u(g4 x){g4 z=MiB+o1(pshufb)(x*4,MiF);return z;} //v1u~vqtbl1
static g4 MjB={0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7},MjF={0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,8};
static g4 j1u(g4 x){g4 z=MjB+o1(pshufb)(x*8,MjF);return z;} 
*/

