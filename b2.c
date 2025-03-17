#include "../../_.h"
#include <stdio.h>
#define ATM AT(minsize,noinline)
ATM static void pj(j6 v) { i(8,printf("%lu ",v[i])) putchar('\n');}
ATM static void pV(g6 v) { i(64,printf("%d%s",v[i],(i+1)%16?"":" ")) putchar('\n');}
ATM static void pg5(g5 v) { i(32,printf("%d ",v[i])) putchar('\n');}
ATM static void pg4(g4 v) { i(16,printf("%d ",v[i])) putchar('\n');}
ATM static void pe6(e6 v) { i(16,printf("%3.1f ",v[i])) putchar('\n');}
ATM static void pe5(e5 v) { i(8,printf("%3.1f ",v[i])) putchar('\n');}
ATM static void pi6(i6 v) { i(16,printf("%u ",v[i])) putchar('\n');}
ATM static void pi5(i5 v) { i(8,printf("%u ",v[i])) putchar('\n');}
ATM static void ps6(s6 v) { i(16,printf("%d ",v[i])) putchar('\n');}
ATM static void ps5(s5 v) { i(8,printf("%d ",v[i])) putchar('\n');}
ATM static void ph5(h5 v) { i(16,printf("%d ",v[i])) putchar('\n');}
ATM static void pU(Uu){ printf("%llu",u); putchar('\n');}
ATM static void pu(Uu){ i(64,printf("%d",(u>>(63-i))&1,(i+1)%8?"":" ")) putchar('\n');}
//i(64,printf("%d",(u>>i)&1)) putchar('\n');}
ATM static void ph(hh){ //i(16,printf("%d%s",(h>>i&1),i+1%8?"":" ")); putchar('\n');}
for(int i=15;i>=0;i--){printf("%d%s",h&(1<<i)?1:0,i!=8?"":" "); } putchar('\n');}

#if __AVX2__ 
#define L(e)  Vz;i(4,((g4*)&z)[i]=e)z
#define av(i)        ((g4*)&a)[i] // 128b
#define bv(i)        ((g4*)&b)[i]
#define cv(i)        ((g4*)&c)[i]
#define xv(i)        ((g4*)&x)[i]
#define zv(i)        ((g4*)&z)[i]
#define xj(i)        ((j4*)&x)[i]
#define sv(e)        *(g4*)(s+e)
#define Av(i)        ((g5*)&a)[i] // 256b
#define Xv(i)        ((g5*)&x)[i]
#define Zv(i)        ((g5*)&z)[i]
#define Aev(i)       ((e5*)&a)[i] // 256b
#define Bev(i)       ((e5*)&b)[i]
#define Xiv(i)       ((i5*)&x)[i]
#define o1(o)    bu(ia32_##o##128)
#define o2(o)    bu(ia32_##o##256)

// [v4u] utility fn similar to ARM:vqtbl4 
static g4 M15={15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},M31={31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31};
static g4 M47={47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47};
//static g4 v4u(g4 v0,g4 v1,g4 v2,g4 v3,g4 x) { g4 r,i=x&M15; r=o1(pblendvb)(o1(pshufb)(v0,i),o1(pshufb)(v1,i),x>M15);
// r=o1(pblendvb)(r,o1(pshufb)(v2,i),x>M31); r=o1(pblendvb)(r,o1(pshufb)(v3,i),x>M47); return r; }
// ATM static g6 p0(g6 a,g6 x) { return ({L(v4u(av(0),av(1),av(2),av(3),xv(i)));}); } 
static g4 v4u(g6 a,g4 x) { g4 r,i=x&M15; r=o1(pblendvb)(o1(pshufb)(av(0),i),o1(pshufb)(av(1),i),x>M15);
 r=o1(pblendvb)(r,o1(pshufb)(av(2),i),x>M31); r=o1(pblendvb)(r,o1(pshufb)(av(3),i),x>M47); return r;
}
static g4 s4u(ss,g4 x) { g4 r,i=x&M15; 
 r=o1(pblendvb)(o1(pshufb)(sv(0),i),o1(pshufb)(sv(16),i),x>M15);
 r=o1(pblendvb)(r,o1(pshufb)(sv(32),i),x>M31); 
 r=o1(pblendvb)(r,o1(pshufb)(sv(48),i),x>M47); return r;
}
static g4 MiF={0,0,0,0,4,4,4,4,8,8,8,8,12,12,12,12},MiB={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
static g4 v1u(g4 x){g4 z=MiB+o1(pshufb)(x*4,MiF); return z;}

// [p0] a:data, x:index (permute 64 x 8b)
// NB: builtin exists to permute in a 256 vector, but it only permutes 
// within each 128b lane, it can't permute across both lanes :( 
ATM static g6 p0(g6 a,g6 x){return _(L(v4u(a,xv(i))));} 
// [p2] a:data, x:index (permute 16 x 32b)
ATM static g6 p2(g6 a,g6 x) { 
 g6 z;//for(ii=0;i<2;++i){Zv(i)=o2(pblendvb)(o2(permvarsi)(Av(0),Xv(i)),o2(permvarsi)(Av(1),Xv(i)),Xv(i)>7);}return z;
 Zv(0)=o2(pblendvb)(o2(permvarsi)(Av(0),Xv(0)),o2(permvarsi)(Av(1),Xv(0)),Xv(0)>7);
 Zv(1)=o2(pblendvb)(o2(permvarsi)(Av(0),Xv(1)),o2(permvarsi)(Av(1),Xv(1)),Xv(1)>7);
 return z;
/* i5 a0 = (i5)Av(0); //printf("a0:");pi5(a0);
 i5 a1 = (i5)Av(1); //printf("a1:");pi5(a1);
 i5 x0 = (i5)Xv(0); printf("x0:");pi5(x0);
 i5 x1 = (i5)Xv(1); printf("x1:");pi5(x1);
 // get first set of 8 elements
 i5 b = o2(permvarsi)(Av(0),Xv(0)); // avx2intrin.h(3284) __builtin_ia32_permvarsi26
 i5 c = o2(permvarsi)(Av(1),Xv(0));
// printf("b:");pi5(b); printf("c:");pi5(c);
 // given two vectors, select bytes based on whether idx >7; careful it's 7, not 8
 Zv(0) = __builtin_ia32_pblendvb256(b,c,Xv(0)>7);
 printf("d:");pi5(Zv(0)); 
 Zv(1) = __builtin_ia32_pblendvb256(o(permvarsi)(Av(0),Xv(1)),o(permvarsi)(Av(1),Xv(1)),Xv(1)>7);
 printf("e:");pi5(Zv(1)); */
}

// [P0] vec a,b; index x: 0..63 (pick from a), 64..127 (pick from b)
// AVX512: V3(P0,o(vpermi2varqi)(a,b,c))
//    ARM: V3(P0,L(vlu(a,bv(i))+vlu(c,o(bsl)(bv(i)>=64,bv(i),MC,48)-64)))
static g4 MC={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};//MALT={1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1},
ATM static g6 P0(g6 a,g6 x,g6 b) {
 return _(L(o1(pblendvb)(v4u(a,xv(i)),v4u(b,xv(i)-64),xv(i)>=64)));
 //Vz;for(ii=0;i<4;++i){ // DEBUG
   //printf("\nxv(%d):",i);pg4(xv(i));
   //g4 d = v4u(a,xv(i));   printf("d:");pg4(d);
   //g4 e = v4u(b,xv(i)-64);printf("e:");pg4(e);
   //zv(i)=o1(pblendvb)(d,e,xv(i)>=64);
 //} 
}

//static g5 v2u(g6 a,g5 x){ return o2(pblendvb)(o2(permvarsf)(Aev(0),x),o2(permvarsf)(Aev(1),x),x>=8); }
//ra=v2u(a,Xiv(0));rb=v2u(b,Xiv(0)-16);
//ra=v2u(a,Xiv(1));rb=v2u(b,Xiv(1)-16);
//Zv(0)=o2(pblendvb)(v2u(a,Xiv(0)),v2u(b,Xiv(0)-16),Xiv(0)>=16);
//Zv(1)=o2(pblendvb)(v2u(a,Xiv(1)),v2u(b,Xiv(1)-16),Xiv(1)>=16);
// [P2] vec a,b (32b x 16); x: 0..15 (pick from a), 16..31 (pick from b)
// AVX512: V3(P2,o(vpermi2varps)(a,b,c))
//    ARM: V3(P2,Vz;i(4,i4 p=ilu(b);zv(i)=vlu(a,p)+vlu(c,o(bsl)(p>=16,p,MC,48)-16))z)
//ATM static g6 P2(g6 a,g6 x,g6 b) { e6 z; e5 ra = o2(pblendvb)(v2u(Aev(0),Xiv(0)), o2(pblendvb)(v2u(Aev(1),Xiv(0)>=8); return (g6)z; }
ATM static g6 P2(g6 a,g6 x,g6 b) { Vz;
 // get elments from a,b => blend 
 e5 ra = o2(pblendvb)(o2(permvarsf)(Aev(0),Xiv(0)),   o2(permvarsf)(Aev(1),Xiv(0)),Xiv(0)>=8);
 e5 rb = o2(pblendvb)(o2(permvarsf)(Bev(0),Xiv(0)-16),o2(permvarsf)(Bev(1),Xiv(0)-16),(Xiv(0)-16)>=8);
 Zv(0) = o2(pblendvb)(ra,rb,Xiv(0)>=16);
 ra = o2(pblendvb)(o2(permvarsf)(Aev(0),Xiv(1)),   o2(permvarsf)(Aev(1),Xiv(1)),Xiv(1)>=8);
 rb = o2(pblendvb)(o2(permvarsf)(Bev(0),Xiv(1)-16),o2(permvarsf)(Bev(1),Xiv(1)-16),(Xiv(1)-16)>=8);
 Zv(1) = o2(pblendvb)(ra,rb,Xiv(1)>=16);
 return z;
}

// [P2b] loop 16 times
ATM static g6 P2b(g6 a,g6 x,g6 b) {
 e6 z,c=(e6)a,d=(e6)b;i6 y=(i6)x;ij; //printf("fc:");pe6(c); printf("fd:");pe6(d);
 i(16,j=y[i];zi=j<16?c[j]:d[j-16]); return (g6)z;
 //for(ii=0;i<16;++i) {j=y[i];zi=j<16?c[j]:d[j-16]; } // DEBUG
 //i(16,j=y[i];((e6*)&z)[i]=j<16?((e6*)&a)[j]:((e6*)&b)[j-16]); // BAD
}

// [g0] gather 8b
ATM static i6 g0(ss,g6 x){return _(L(s4u(s,xv(i))));}
// [g2] gather 32b
ATM static i6 g2(ss,g6 x){return _(L(s4u(s,v1u(xv(i)))));}

// [b0] 
ATM static U b0(g6 x){ 
 //return ((U)o2(pmovmskb)(Xv(1))<<32)|(U)o2(pmovmskb)(Xv(0)); // BAD
 //return ((U)o2(pmovmskb)(Xv(0)))|((U)o2(pmovmskb)(Xv(1))<<32);// BAD
 //avx2intrin.h:1311:_mm256_movemask_epi8(__m256i __a)
 i2 a=o2(pmovmskb)(Xv(0)),b=o2(pmovmskb)(Xv(1));
 return ((U)b<<32)|(U)a;
}

// [b2] 
// ATM static U b2(g6 x){ i6 e=(i6)x;Uu=0;i(16,u|=(((e[i]>>31)&1)<<i));return u;} // works, but loops 16 times
ATM static U b2(g6 x){
 //uint32_t avx2_cvtdword2mask(__m256i src) {
 // Shift right by 31 to move sign bit to LSB of each 32-bit lane
 //__m256i sign_bits = _mm256_srai_epi32(src, 31); // 0xFFFFFFFF if negative, 0x00000000 if non-negative
 s5 a=o2(psradi)(Xv(0),31); //printf("a:");ps5(a);
 s5 b=o2(psradi)(Xv(1),31); //printf("b:");ps5(b);
 // Pack 32-bit lanes into 8-bit lanes (only LSB of each 32-bit lane matters)
 //__m256i packed = _mm256_packs_epi32(sign_bits, _mm256_setzero_si256()); // Pack to 16-bit
 //packed = _mm256_packs_epi16(packed, _mm256_setzero_si256()); // Pack to 8-bit
 //g5 p=o2(packssdw)(s,(g5){0}); //__builtin_ia32_packssdw256
 //g5 p=o2(packssdw)(a,(g5){0}); //__builtin_ia32_packssdw256
 //h5 c=o2(packssdw)(a,a); //__builtin_ia32_packssdw256
 //g5 p = (g5)c;//h5 c=(h5)p;
 //printf("c:");ph5(c);
 h5 c=o2(packssdw)(a,(g5){0}); //printf("c[a,0]: ");ph5(c);
 h5 d=o2(packssdw)(b,(g5){0}); //printf("c[a,0]: ");ph5(c);
 //c=o2(packssdw)((g5){0},a);
 //printf("c:");ph5(c);
 //printf("p:");pg5(p);
 //h5 d=o2(packsswb)(p,(g5){0}); //__builtin_ia32_packsswb256
 //putchar('\n');
 g5 e=o2(packsswb)(c,(g5){0}); //printf("d[c,0]: ");pg5(d);
 g5 f=o2(packsswb)(d,(g5){0}); //printf("d[c,0]: ");pg5(d);
 //d=o2(packsswb)((g5){0},c); 
 //printf("d[0,c]:");pg5(d);
 //d=o2(packsswb)(c,c);
 //printf("d[c,c]:");pg5(d);
 //printf("p:");pg5(p);
 // Extract MSB of each byte (only first 8 bytes matter)
 //return (uint32_t)_mm256_movemask_epi8(packed) & 0xFF; // Mask to first 8 bits
 U u=o2(pmovmskb)(e); // have to get full 64 bits
 U v=o2(pmovmskb)(f); // have to get full 64 bits
 //printf("u:");pu(u);
 i1 h=u;
 h |= (u&0xff0000)>>12;
 //printf("h:");ph(h);
 i1 j=v;
 //printf("j:");ph(j);
 j |= (v&0xff0000)>>12;
 //printf("j:");ph(j);
 return (j<<8)|h;
}
#endif // av2

int main(int argc, char**argv) {
  //j6 a = {0,1,22,333,4444,55555,666666,7777777},x = {3,4,4,2,6,7,1,0};
  // test p0
  g6 a=I0; // 0..63
  g6 x={4,5,6,7,0,1,2,3,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
        32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,63,62,61,60};
  g6 z=p0(a,x);
  //printf("a:");pg(a); printf("x:");pg(x); printf("z:");pg(z);

  // test p2 
  // I: 0..15
  i6 y={15,14,0,1,2,3,4,5,6,7,8,9,10,11,12,13};
  //i6 y={7,7,7,7,7,7,7,7, 8,8,8,8,8,8,8,8};
  i6 zz=p2(I,y); 
  //printf("z:");pi6(zz);

  // P0: testing.. output should be 0,7,1,8,...
  // I0: 0..63
  g6 b={7,8,9,1,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  g6 i={0,64,1,65,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  //printf("a:");pg(a); printf("b:");pg(b); printf("i:");pg(i); z=P0(a,i,b); printf("\nz:");pg(z);

  // P2: testing
  //e6 f1={1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f, 1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f}; printf("f1:");pe6(f1);
  //e6 c = I*1.0f;//,d=I+16.f; // 0-15,16-31 // compiler doesn't like this... probably can't gen 512b vectors * single value
  e6 c = {0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.};
  e6 d = {16.,17.,18.,19.,20.,21.,22.,23.,24.,25.,26.,27.,28.,29.,30.,31.};
  i6 idx = {0,16,1,17,2,18,3,19, 4,20,5,21,6,24,7,26};
  //printf("c:");pe6(c); printf("d:");pe6(d); printf("idx:");pi6(idx); 
  // e6 r = P2(c,idx,d);
  //e6 r = P2b(c,idx,d);
  //printf("r:");pe6(r);

  // test b0
  g6 e={0,0,0,128,128,128,128,128, 128,128,128,128,128,128,128,128,
        128,128,128,128,128,128,128,128, 128,128,128,128,128,128,128,128,
        000,128,128,128,128,128,128,128, 128,128,128,128,128,128,128,128,
        128,000,128,128,128,128,128,128, 128,128,128,128,128,128,128,128};
  Uu=b0(e); //pu(u);

  // test b2
  //s6 f={-1, 0, -100, 42, 1, -5, 0, 100, -1,-1,-1,-1,1,-1,1,-1};
  //s6 f={-1, 0, -100, 42, 1, -5, 0, 100, 0,0,0,0,0,0,0,0};
  s6 f={-1,0,-1,0, -1,-5,-7,-8, 0,0,0,0,-1,-1,-1,-1};
  //s6 f={0,0,0,0,0,0,0,0, 0,0,0,0,-1,-1,-1,-1};
  printf("f:");ps6(f);
  hh=b2(f); ph(h);
  return 0;
}

