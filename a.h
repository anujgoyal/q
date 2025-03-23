#include"_.h"//arm(neon128 sve256) x86(avx2/16 avx512)

#ifdef __AVX512F__
#define O(f) o(f##512)
VF(p0,O(permvarqi)(a,x))
VF(p2,O(permvarsi)(a,x))
VF(p3,O(permvardi)(a,x))
_V(P2,O(vpermi2varps)(a,b,x),Va,Vb,Vx)
IF(_P,P2(a,2*I2,x))
IF(P_,P2(a,1|2*I2,x))
Vg(R0,P2(x,I2-i,z0))
Vg(R1,P2(x,I2-i,~z0))
Ef(_q,O(sqrtps)(x,4))
UV(b0,O(cvtb2mask)(x))
UV(b2,O(cvtd2mask)(x))
_V(bm,o(vfmaddsubps512_mask3)(a,b,x,-1,9),Va,Vb,Vx)
Ef(IE,o(cvtps2dq512_mask)(x,x,-1,4))
_V(g2,o(gathersiv16si)(z0,s,x,-1,1),ss,Vx)
_V(G2,o(gathersiv16si)(z0,s,x,-1,4),ss,Vx)
_V(g3,o(gathersiv8di)(z0,s,x,-1,1),ss,Yx)
_V(G3,o(gathersiv8di)(z0,s,x,-1,8),ss,Yx)

#elif __AVX2__

#define L(e)  Vz;i(4,((g4*)&z)[i]=e)z
#define av(i)        ((g4*)&a)[i] // 128b
#define bv(i)        ((g4*)&b)[i]
#define cv(i)        ((g4*)&c)[i]
#define xv(i)        ((g4*)&x)[i]
#define zv(i)        ((g4*)&z)[i]
#define sv(e)        *(g4*)(s+e)
#define Av(i)        ((g5*)&a)[i] // 256b
#define Xv(i)        ((g5*)&x)[i]
#define Zv(i)        ((g5*)&z)[i]
#define Aiv(i)       ((i5*)&a)[i] 
#define Biv(i)       ((i5*)&b)[i] 
#define Xiv(i)       ((i5*)&x)[i] 
#define Zev(i)       ((e5*)&z)[i] 
#define o1(o)    bu(ia32_##o##128)
#define o2(o)    bu(ia32_##o##256)
static g4 M15={15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},M31={31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},M47={47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47};
static g4 v4u(g6 a,g4 x){g4 z,i=x&M15;z=o1(pblendvb)(o1(pshufb)(av(0),i),o1(pshufb)(av(1),i),x>M15);z=o1(pblendvb)(z,o1(pshufb)(av(2),i),x>M31);z=o1(pblendvb)(z,o1(pshufb)(av(3),i),x>M47);return z;} //v4u~vqtbl4
static g4 s4u(ss,g4 x){g4 z,i=x&M15;z=o1(pblendvb)(o1(pshufb)(sv(0),i),o1(pshufb)(sv(16),i),x>M15);z=o1(pblendvb)(z,o1(pshufb)(sv(32),i),x>M31);z=o1(pblendvb)(z,o1(pshufb)(sv(48),i),x>M47);return z;} 
static g4 MiB={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3},MiF={0,0,0,0,4,4,4,4,8,8,8,8,12,12,12,12};
static g4 v1u(g4 x){g4 z=MiB+o1(pshufb)(x*4,MiF);return z;} //v1u~vqtbl1
static g4 MjB={0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7},MjF={0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,8};
static g4 j1u(g4 x){g4 z=MjB+o1(pshufb)(x*4,MjF);return z;} 
VF(p0,L(v4u(a,xv(i))))
VF(p2,Vz;Zv(0)=o2(pblendvb)(o2(permvarsi)(Av(0),Xv(0)),o2(permvarsi)(Av(1),Xv(0)),Xv(0)>7);Zv(1)=o2(pblendvb)(o2(permvarsi)(Av(0),Xv(1)),o2(permvarsi)(Av(1),Xv(1)),Xv(1)>7);z)
VF(p3,Jz;i(8,Uu=((j6*)&x)[i];zi=((j6*)&a)[u])z) // try L(v4u(a,vju(xv(i))))
static g6 P2(Va,Vb,Vx){Vz;
 Zv(0)=o2(pblendvb)(o2(pblendvb)(o2(permvarsf)(Aiv(0),Biv(0)),o2(permvarsf)(Aiv(1),Biv(0)),Biv(0)>=8),o2(pblendvb)(o2(permvarsf)(Xiv(0),Biv(0)-16),o2(permvarsf)(Xiv(1),Biv(0)-16),(Biv(0)-16)>=8),Biv(0)>=16);
 Zv(1)=o2(pblendvb)(o2(pblendvb)(o2(permvarsf)(Aiv(0),Biv(1)),o2(permvarsf)(Aiv(1),Biv(1)),Biv(1)>=8),o2(pblendvb)(o2(permvarsf)(Xiv(0),Biv(1)-16),o2(permvarsf)(Xiv(1),Biv(1)-16),(Biv(1)-16)>=8),Biv(1)>=16);
 return z;}
IF(_P,P2(a,2*I2,x))
IF(P_,P2(a,1|2*I2,x))
Vg(R0,P2(x,I2-i,z0))
Vg(R1,P2(x,I2-i,~z0))
Ef(_q,Vz;Zv(0)=o2(sqrtps)(Xv(0));Zv(1)=o2(sqrtps)(Xv(1));z)
UV(b0,i2 a=o2(pmovmskb)(Xv(0)),b=o2(pmovmskb)(Xv(1));((U)b<<32)|(U)a)
static g1 m1={8,9,10,11,0,1,2,3,4,5,6,7,12,13,14,15};
UV(b2,g5 a=o2(psradi)(Xv(0),31),b=o2(psradi)(Xv(1),31);a=o2(packssdw)(a,b);a=o2(packsswb)(a,a,);g4 c=o1(pblendd)(av(0),av(1),(int)0b1001);c=o1(pshufb)(c,m1);Uu=o1(pmovmskb)(c);u)
static e5 MALT={1,-1,1,-1,1,-1,1,-1};
_V(bm,Ez;Zev(0)=o2(vfmaddps)(Av(0),Bv(0),Xv(0)*MALT);Zev(1)=o2(vfmaddps)(Av(1),Bv(1),Xv(1)*MALT);z)
Ef(IE,Iz;Ziv(0)=o2(cvtps2dq)(Xv(0));Ziv(1)=o2(cvtps2dq)(Xv(1));z)
_V(g2,L(s4u(s,xv(i))),ss,Vx) //Is(g0,bu(ia32_gathersiv16si)(z0,s,x,-1,1))
_V(G2,L(s4u(s,v1u(xv(i)),ss,Vx))) //Is(g2,bu(ia32_gathersiv16si)(z0,s,x,-1,4))
_V(g3,Jz;i(8,zi=*(U*)=s+x[i])z,ss,Vx)
_V(G3,Jz;i(8,zi=*(U*)(s+(x[i]*8)))z,ss,Vx)

#endif

