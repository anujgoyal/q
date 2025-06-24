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
#define B(e) __builtin_##e
#define O(e) B(neon_##e)
#define o(e) O(v##e##q_v)
static g4 M0,MC={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
MiB={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3}, MiF={0,0,0,0,4,4,4,4,8,8,8,8,12,12,12,12};
#define vlu(e,t)  o(qtbl4)(e##v(0),e##v(1),e##v(2),e##v(3),t,48)

#define xv(i) ((g4*)&x)[i] 
#define zv(i) ((g4*)&z)[i] 
#define ziv(i) ((i4*)&z)[i] 
#define P printf
void pi6(i6 z){i(16,P("%d ",zi))putchar('\n');}
void pi4(i4 z){i(4,P("%d ",zi))putchar('\n');}
void pg6(g6 z){i(64,P("%d ",zi))putchar('\n');}
void pg4(g4 z){i(16,P("%d%s",zi,((i+1)%4)?",":", "))putchar('\n');}

// popcntd (ARM)
static g4 
Mf={0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf, 0xf,0xf,0xf,0xf},
Mb={0xf,0,0,0, 0xf,0,0,0, 0xf,0,0,0, 0xf,0,0,0},
M1={1,3,5,7,9,11,13,15,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
M2={2,6,10,14,0xff,0xff,0xff,0xff,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
ML={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};

static i4
Miff={0x0000ffff, 0x0000ffff,0x0000ffff,0x0000ffff},
 Mif={0x000000ff, 0x000000ff,0x000000ff,0x000000ff};

ATI static g4 p42(g4 x){
 // lookup # of 1's per nibble(4b)
 g4 a = o(qtbl1)(ML,x&Mf,48);// P("a:");pg4(a);
 g4 b = o(qtbl1)(ML,O(vshrq_n_v)(x,4,48)&Mf,48); //P("b:");pg4(b);
 g4 v = a+b; //P("v:");pg4(v);

 // add 4 bytes within vector
 g4 b0 = v & Mif;
 g4 b1 = O(vshrq_n_v)(v,8,50) & Mif;
 g4 b2 = O(vshrq_n_v)(v,16,50) & Mif;
 g4 b3 = O(vshrq_n_v)(v,24,50) & Mif;
 return b0+b1+b2+b3;
}

// popcount using 4 loops of 128b vec, ~144 bytes (inner loop: 80 bytes) => 4*80 = 320 cycles  + (144-80) = ~380
ATM static g6 pop42(Vx){Vz; i(4,zv(i)=p42(xv(i))) return z; }

// popcount using 16 loops on 32b ints, ~92 bytes (inner loop: 52 bytes) => 16*52 = 832 cycles
ATM static i6 pop(Vx){Iz; iR=&x; i(16,zi=B(popcount)(Ri)) return z;}

// popcount using 4 loops repeated, ~252 bytes (inner loop 200 bytes) => 4*200 = 800 cycles
ATM static i6 popx(Vx){Iz;iR=&x;i(4,z[i*4]=B(popcount)(R[i*4]); z[i*4+1]=B(popcount)(R[i*4+1]);z[i*4+2]=B(popcount)(R[i*4+2]);z[i*4+3]=B(popcount)(R[i*4+3])) return z;}

int main() {
 i6 d={0xd4c3b2a1, 0x32323232, 0xf0f0f0f0, 0x00000707,0x000000ff, 0x00000fff, 0x0000ffff, 0x000fffff,
       0x0000000F, 0xFFFF0000, 0x00000000, 0xFFFFFFFF,0x55555555, 0xAAAAAAAA, 0x12345678, 0xF0F0F0F0};
 //P("d:");pi6(d);

 /* testing g4
 g4*p = &d;
 g4 r = p4(p[0]); 
 P("R:");pi4(r);*/

 //z = pop4(d);
 //P("pop4:");pi6(z);
 Iz = pop42(d);
 P("pop42:");pi6(z);
 z = pop(d);
 P(" pop:");pi6(z);
 z = popx(d);
 P("popx:");pi6(z);
 return 0;
}

