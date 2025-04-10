#include"_.h"//13<clang VF(MG,B(elementwise_max)(a,x))IF(MI,B(elementwise_max)(a,x))VF(ME,B(elementwise_max)((e6)a,(e6)x))

#ifdef __AVX512F__
#define O(f) B(ia32_##f##512) 
UV(b2,O(cvtd2mask)(x)) // (16x32b) vec to 16b mask
VF(LI,O(pminsd)(a,x))
VF(MI,O(pmaxsd)(a,x))
VF(LE,O(minps)(a,x,4))
VF(ME,O(maxps)(a,x,4))
VF(MG,O(pmaxub)(a,x))
VF(p2,O(permvarsi)(a,x))
V3(P2,O(vpermi2varps)(a,b,c))
Vg(s0,2>i?O(vpermi2varqi)(x,I0-(i0)(1<<i),z0):P2(x,I2-(1<<i-2),z0))
Vg(r0,2>i?O(permvarqi)(x,63-I0):p2(x,15-I2))
If(IE,o(cvtps2dq512_mask)(x,z0,-1,4)) 
If(ab,O(pabsd)(x))
Ef(_q,O(sqrtps)(x,4))
V3(bc,o(vfmaddsubps512_mask3)(a,b,c,-1,9))
V(G2,o(gathersiv16si)(z0,s,x,-1,4),ss,Vx)

#elif __AVX2__
#define av(i)  ((g4*)&a)[i] // 128b
#define bv(i)  ((g4*)&b)[i]
#define cv(i)  ((g4*)&c)[i]
#define xv(i)  ((g4*)&x)[i]
#define zv(i)  ((g4*)&z)[i]
#define Av(i)  ((g5*)&a)[i] // 256b
#define Xv(i)  ((g5*)&x)[i]
#define Zv(i)  ((g5*)&z)[i]
#define Aiv(i) ((i5*)&a)[i] 
#define Biv(i) ((i5*)&b)[i] 
#define Xiv(i) ((i5*)&x)[i] 
#define Ziv(i) ((i5*)&z)[i] 
#define Xsv(i) ((s5*)&x)[i] 
#define Aev(i) ((e5*)&a)[i] 
#define Bev(i) ((e5*)&b)[i] 
#define Cev(i) ((e5*)&c)[i] 
#define Xev(i) ((e5*)&x)[i] 
#define Zev(i) ((e5*)&z)[i] 
#define o1(o)  B(ia32_##o##128)
#define o2(o)  B(ia32_##o##256)
#define M0 ((g4){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
static g4 M15=M0+15,M31=M0+31,M47=M0+47;static e5 MALT5={1,-1,1,-1,1,-1,1,-1};
static g4 v4u(Va,Xx){g4 z,i=x&M15;z=o1(pblendvb)(o1(pshufb)(av(0),i),o1(pshufb)(av(1),i),x>M15);z=o1(pblendvb)(z,o1(pshufb)(av(2),i),x>M31);z=o1(pblendvb)(z,o1(pshufb)(av(3),i),x>M47);return z;}
static g4 m1={8,9,10,11,0,1,2,3,4,5,6,7,12,13,14,15};
UV(b2,g5 a=o2(psradi)(Xv(0),31);g5 b=o2(psradi)(Xv(1),31);a=o2(packssdw)(a,b);a=o2(packsswb)(a,a);g4 c=o1(pblendd)(av(0),av(1),(int)0b1001);c=o1(pshufb)(c,m1);Uu=o1(pmovmskb)(c);u)
VF(LI,B(elementwise_min)(a,x))
VF(MI,B(elementwise_max)(a,x))
EF(LE,B(elementwise_min)(a,x))
EF(ME,B(elementwise_max)(a,x))
VF(MG,B(elementwise_max)(a,x))
#define BL o2(pblendvb) 
#define Pmi o2(permvarsi) // permute i
#define Pme o2(permvarsf) // permute e
#define BPI(a,b,c) BL(Pmi(a##iv(0),b),Pmi(a##iv(1),b),b>=c) 
#define BPE(a,b,c) BL(Pme(a##ev(0),b),Pme(a##ev(1),b),b>=c) 
VF(p2,Iz;Ziv(0)=BPI(A,Xiv(0),8);Ziv(0)=BPI(A,Xiv(1),8);z)
V3(P2,Ez;Zev(0)=BL(BPE(A,Biv(0),8),BPE(C,Biv(0)-16,8),Biv(0)>=16);Zev(1)=BL(BPE(A,Biv(1),8),BPE(C,Biv(1)-16,8),Biv(1)>=16);z)
Vg(s0,Vz;Va=I0-(i0)(1<<i);$(2>i,i(4,zv(i)=o1(pblendvb)(v4u(x,av(i)),M0,av(i)>=64)))z=P2(x,I2-(1<<i-2),z0);z)
Vg(r0,Vz;Va=63-I0;$(2>i,i(4,zv(i)=v4u(x,av(i))))z=p2(x,15-I2);z)
If(IE,Iz;Ziv(0)=o2(cvtps2dq)(Xiv(0));Ziv(1)=o2(cvtps2dq)(Xiv(1));z)
If(ab,Iz;Ziv(0)=B(elementwise_abs)(Xsv(0));Ziv(1)=B(elementwise_abs)(Xsv(1));z)
Ef(_q,Ez;Zev(0)=o2(sqrtps)(Xev(0));Zev(1)=o2(sqrtps)(Xev(1));z)
V3(bc,Ez;Zev(0)=o2(vfmaddps)(Aev(0),Bev(0),Cev(0)*MALT5);Zev(1)=o2(vfmaddps)(Aev(1),Bev(1),Cev(1)*MALT5);z)
V(G2,Iz;Ib=x;i(16,zi=*(i2*)(s+b[i]*4))z,ss,Vx)

#elif __arm64
#undef o
#define o(o)  B(neon_v##o##q_v)
#define L(e)  Vz;i(4,((g4*)&z)[i]=e)z
#define av(i)        ((g4*)&a)[i]
#define bv(i)        ((g4*)&b)[i]
#define cv(i)        ((g4*)&c)[i]
#define xv(i)        ((g4*)&x)[i]
#define zv(i)        ((g4*)&z)[i]
static e4 MALT={1,-1,1,-1};
static g4 M0,MC={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
MiB={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3}, MiF={0,0,0,0,4,4,4,4,8,8,8,8,12,12,12,12};
#define vlu(e,t)  o(qtbl4)(e##v(0),e##v(1),e##v(2),e##v(3),t,48)
#define ilu(e)    MiB+o(qtbl1)(e##v(i)*4,MiF,48)
UV(b2,Uu=0;i(4,u|=B(neon_vaddvq_u32)(o(shl)(B(neon_vshrq_n_v)(xv(i),31,50),(i4){0,1,2,3},50))<<(i*4))u)
VF(LI,L(o(min)(av(i),xv(i),34))) // 32b si vminq_s32(a,x) => __builtin_neon_vminq_v(a,x,34)
VF(MI,L(o(max)(av(i),xv(i),34))) //       vmaxq_s32(a,x) => __builtin_neon_vmaxq_v(a,x,34)
//Z(frni_,ii;__asm__ volatile("mrs %0, fpcr":"=r"(i));i&=~(0b11<<22);i|=(0b10<<22);i&=~(0x9F<<8);__asm__ volatile("msr fpcr, %0" : : "r"(i));)
VF(LE,L(o(min)(av(i),xv(i),41))) // 32b e __builtin_neon_vminq_v 
VF(ME,L(o(max)(av(i),xv(i),41))) //       __builtin_neon_vmaxq_v 
VF(MG,L(o(max)(av(i),xv(i),48))) // 8b 
VF(p2,L(vlu(a,ilu(x))))
V3(P2,Vz;i(4,i4 p=ilu(b);zv(i)=vlu(a,p)+vlu(c,o(bsl)(p>=16,p,MC,48)-16))z)
Vg(s0,Vz;Va=I0-(i0)(1<<i);$(2>i,i(4,zv(i)=vlu(x,av(i))+M0))z=P2(x,I2-(1<<i-2),z0);z)
Vg(r0,Vz;Va=63-I0;$(2>i,i(4,zv(i)=vlu(x,av(i))))z=p2(x,15-I2);z)
If(IE,L(B(neon_vcvtq_s32_v)(xv(i),34)))
If(ab,L(o(abs)(xv(i),34))) // 32b si, vabsq_s32 => __builtin_neon_vabsq_v(x,34)
Ef(_q,L(o(sqrt)(xv(i),41)))
V3(bc,L(o(fma)(av(i),bv(i),cv(i)*MALT,41)))
V(G2,Iz;Ib=x;i(16,zi=*(i2*)(s+b[i]*4))z,ss,Vx)
#undef o
#undef L
#undef av 
#undef bv
#undef cv
#undef xv
#undef zv
#endif

j6 A={-1},B={0xc6a4a7935bd1e995};V(JJ,B=RJ(37,RJ(55,A^=B)^B^B<<14);A+B)Vf(ba,p2(x,BA))
VF(c,bc(p2(a,I2/2*2),x,(e6)p2(a,1|I2/2*2)*ba(x))) //Vf(lm,AB&LI(x,ba(x))|~AB&MI(x,ba(x)))
IF(_P,B(shufflevector)(a,x,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30))
Ef(_l,Sa=IE(x-.5);p6(x-C(e6,a),.99999994,.69315308,.24015361,.055826318,.0089893397,.0018775767)*(a+127<<23))
IF(P_,B(shufflevector)(a,x,1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31))
If(l_,C(e6,x-E1>>23)+p6(E1|b(23)&x,-1,3.1157899,-3.324199,2.5988452,-1.2315303,.31821337))static i6 Z[1<<14];

