#include <stdio.h>
#define ATM __attribute((minsize,noinline)) 
#define ATI __attribute((minsize,always_inline))
#define v(t,n) t##n __attribute((vector_size(1<<n),aligned(1)))
typedef char     i0,v(g,4),v(g,5),v(g,6);
typedef unsigned i2,v(i,4),v(i,5),v(i,6);
typedef float    e2,v(e,6);
typedef unsigned long U,(*_U)(i2,U),v(j,6);
#undef v
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
#define SR __builtin_ia32_psrldqi128_byteshift
#define xv(i) ((g4*)&x)[i] 
#define zv(i) ((g4*)&z)[i] 
#define ziv(i) ((i4*)&z)[i] 
#define Xv(i) ((g5*)&x)[i] 
#define Zv(i) ((g5*)&z)[i] 
#define P printf
void pi6(i6 z){i(16,P("%d ",zi))putchar('\n');}
void pi5(i5 z){i(8,P("%d ",zi))putchar('\n');}
void pi4(i4 z){i(4,P("%d ",zi))putchar('\n');}
void pg6(g6 z){i(64,P("%d ",zi))putchar('\n');}
void pg5(g5 z){i(32,P("%d%s",zi,((i+1)%4)?",":", "))putchar('\n');}
void pg4(g4 z){i(16,P("%d%s",zi,((i+1)%4)?",":", "))putchar('\n');}

// popcntd (avx2)
static g5 MZ, 
MB={0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf},
MLU={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
#define MSHUFFLE(z, y, x, w) (((z) << 6) | ((y) << 4) | ((x) << 2) | (w))
static g4 
Mf={0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf},
Mb={0xf,0,0,0, 0xf,0,0,0, 0xf,0,0,0, 0xf,0,0,0},
M1={1,3,5,7,9,11,13,15,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
M2={2,6,10,14,0xff,0xff,0xff,0xff,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
ML={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};

static i4
Miff={0x0000ffff, 0x0000ffff,0x0000ffff,0x0000ffff},
 Mif={0x000000ff, 0x000000ff,0x000000ff,0x000000ff};

ATI static g4 p4(g4 x){
 // get nibbles
 g4 a=x&Mf; 
 //P("a: ");pg4(a);
 g4 b=o1(psrldi)(x,4)&Mf; 
 //P("b: ");pg4(b);
 // lookup # of 1's per nibble
 a = o1(pshufb)(ML,a); 
 //P("a: ");pg4(a);
 b = o1(pshufb)(ML,b); 
 //P("b: ");pg4(b);
 g4 nv = a+b; 
 P("\nnv: ");pg4(nv);// nv: nib values

 // sum up 4 bytes per int
 g4 lo16 = Miff & nv;
 g4 hi16 = Miff & o1(psrldi)(nv,16); 
 g4 sum16 = lo16 + hi16;
 g4 lo8 = Mif & sum16;
 g4 hi8 = Mif & o1(psrldi)(sum16,8);
 g4 z = lo8 + hi8;
 P("z:");pg4(z);
 return z;
}

/*ATM static g4 p4(g4 x){
 g4 p = z + SR(z,1); // p:pairs
 P("p:");pg4(p);
 g4 ep = o1(pshufb)(p,M1); // ep: extracted pairs
 g4 final_sums = ep + SR(ep,2);
 z = o1(pshufb)(final_sums,M2); 
 return z;
}*/

/*ATM static g4 pp4(g4 x) {
 g4 a = o1(pshufb)(ML,Mf & x);
 g4 b = o1(pshufb)(ML,Mf & o1(psrldi)(x,4));
 g4 c = o1(pshufb)(ML,Mf & o1(psrldi)(x,8));
 g4 d = o1(pshufb)(ML,Mf & o1(psrldi)(x,12));
 g4 e = o1(pshufb)(ML,Mf & o1(psrldi)(x,16));
 g4 f = o1(pshufb)(ML,Mf & o1(psrldi)(x,20));
 g4 g = o1(pshufb)(ML,Mf & o1(psrldi)(x,24));
 g4 h = o1(pshufb)(ML,Mf & o1(psrldi)(x,28)); 
 return (a+b+c+d+e+f+g+h) & Mb;
}

ATI static g5 pop5(g5 a){
 // count bits in each byte
 g5 lo = a & MB; 
 P("lo:");pg5(lo); 
 g5 hi = o2(psrldi)(a,4) & MB; 
 P("hi:");pg5(hi);
 g5 plo = o2(pshufb)(MLU,lo); //P("pl:");pg5(plo);
 g5 phi = o2(pshufb)(MLU,hi);
 g5 pby = plo + phi;
 // sum bytes within each int
 g5 s1 = o2(psadbw)(pby,MZ);
 g5 s2 = o2(pshufd)(s1,MSHUFFLE(3,3,1,1));
 g5 s3 = s1 + s2; 
 g5 s4 = o2(pshufd)(s3,MSHUFFLE(2,2,0,0));
 return s4;
}*/

/* not quite working
ATM static g6 pop(Vx){ Vz; Zv(0)=pop5(Xv(0)); Zv(1)=pop5(Xv(1)); return z;
}*/

// get counts for each 128b vector
ATM static g6 pop(Vx){ Iz; i(4,ziv(i)=p4(xv(i))) return z; }


// works
ATM static i6 pop2(Vx){ Iz; iR=&x; i(16,zi=B(popcount)(Ri)) return z;}

int main() {
 i6 d={0xd4c3b2a1, 0x32323232, 0xf0f0f0f0, 0x00000707,0x000000ff, 0x00000fff, 0x0000ffff, 0x000fffff,
       0x0000000F, 0xFFFF0000, 0x00000000, 0xFFFFFFFF,0x55555555, 0xAAAAAAAA, 0x12345678, 0xF0F0F0F0};
 P("d:");pi6(d);

 // testing g4
 g4*p = &d;
 g4 r = p4(p[0]); 
 P("R:");pi4(r);

 //Iz = pop(d);
 /*Iz = pop(d);
 P("pop:");pi6(z);
 z = pop2(d);
 P("pop2:");pi6(z);*/
 return 0;
}

