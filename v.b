#include"v.a"
e6(JJ,ZJ A={-1};ZJ B={0xc6a4a7935bd1e995};Z2 a;if(!a){i(a=8,if(i)Ai=Bi=i)i(1e4,JJ())}A^=B;B^=B<<14^(A<<55|A>>9);B=B<<37|B>>27;(e6)(127<<23|b(23)&(i6)(A+B))-1)
e6(EI,o(convertvector)(x,e6),s6 x)j6(JI,o(convertvector)(x,j6),i5 x)i6(IG,o(convertvector)(x,i6),g4 x)g6(GI,1&o(convertvector)(x,g6),i8 x)

#ifdef __AVX512F__
#define O(f) o(ia32_##f##512)
Ef(q,O(sqrtps)(x,4))
Ef(IE,o(ia32_cvtps2dq512_mask)(x,z0,-1,9))
EF(d8,EI(O(vpdpbusd)(z2,a,x)))
U(b2,O(cvtd2mask)(x),Vx)
i6(G2,o(ia32_gathersiv16si)(z0,s,x,-1,4),ss,Vx)
GF(MG,O(pmaxub)(a,x))
IF(LI,O(pminsd)(a,x))
IF(MI,O(pmaxsd)(a,x))
If(A2,O(permvarsi)(x,15-I2))
G3(P2,O(vpermi2varps)(a,b,x))
Gg(S0,O(vpermi2varqi)(x,I0-(i0)(1<<i),z0))

#elif __arm64
#undef V
#define V(t,n) t##n __attribute((vector_size(1<<n),aligned(1)))
typedef char V(g,3); typedef unsigned short V(h,3),V(h,4); typedef unsigned V(ii,4);
#undef V
#undef o
#define B(f) __builtin_neon_##f
#define o(f) __builtin_neon_v##f##q_v
#define Vz g6 z
#define Va g6 a
#define Ib i6 b
#define Ia i6 a
#undef L
#define L(e)  Vz;i(4,((g4*)&z)[i]=e)z
#define av(i)        ((g4*)&a)[i]
#define bv(i)        ((g4*)&b)[i]
#define cv(i)        ((g4*)&c)[i]
#define xv(i)        ((g4*)&x)[i]
#define zv(i)        ((g4*)&z)[i]
#define avi          ((g3*)&a)[i]
#define xvi          ((g3*)&x)[i]
#define s0           ((h3*)&r)[0]
#define s1           ((h3*)&r)[1]
static g4 M0,MC={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
MiB={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3},MiF={0,0,0,0,4,4,4,4,8,8,8,8,12,12,12,12};
#define vlu(e,t) o(qtbl4)(e##v(0),e##v(1),e##v(2),e##v(3),t,48)
#define ilu(e)   MiB+o(qtbl1)(e##v(i)*4,MiF,48)
Ef(q,L(o(sqrt)(xv(i),41)))
Ef(IE,L(B(vcvtq_s32_v)(xv(i),34)))
EF(d8,i6 z;i(8,h4 r=B(vmull_v)(avi,xvi,33);z[i*2]=B(vaddv_s16)(s0);z[i*2+1]=B(vaddv_s16)(s1);)z)
//U(b2,Uf=0;i(4,f|=B(vaddvq_u32)(o(shl)(B(vshrq_n_v)(xv(i),31,50),(ii4){0,1,2,3},50))<<(i*4))f,Vx)
static g4 MSEQ={0,0,0,0, 0,0,0,1, 0,0,0,2, 0,0,0,3};
U(b2,Uf=0;i(4,f|=B(vaddvq_u32)(o(shl)(B(vshrq_n_v)(xv(i),31,50),MSEQ,50))<<(i*4))f,Vx)
i6(G2,Iz;Ib=x;i(16,zi=*(i2*)(s+b[i]*4))z,ss,Vx)
GF(MG,L(o(max)(av(i),xv(i),48)))
IF(LI,L(o(min)(av(i),xv(i),34)))
IF(MI,L(o(max)(av(i),xv(i),34)))
If(A2,Ia=15-I2;L(vlu(x,ilu(a))))
G3(P2,Vz;i(4,ii4 p=ilu(b);zv(i)=vlu(a,p)+vlu(x,o(bsl)(p>=16,p,MC,48)-16))z)
Gg(S0,Vz;Va=I0-(i0)(1<<i);i(4,zv(i)=vlu(x,av(i))+M0)z)
#undef o
#undef L
#undef av 
#undef bv
#undef cv
#undef xv
#undef zv
#undef avi
#undef xvi
#undef s0
#undef s1
#endif

Gg(S2,P2(x,I2-(1<<i),z0))EF(_P,P2(a,2*I2,x))EF(P_,P2(a,1|2*I2,x))
#define p6(z,a,b,c,d,e,f) _(e6 $=z;(e2)(a)+$*((e2)b+$*((e2)c+$*((e2)d+$*((e2)e+$*(e2)f)))))
Ef(L,i6 z=x;.69314575f*(EI((z>>23)-127)+p6(127<<23|b(23)&z,-1,3.1157899,-3.324199,2.5988452,-1.2315303,.31821337)))IF(SI,a+x)EF(SE,a+x)
Ef(E,x*=1.442695f;s6 z=IE(x-.5);p6(x-EI(z),.99999994,.69315308,.24015361,.055826318,.0089893397,.0018775767)*(z+127<<23))EF(AZ,q(a*a+x*x))Ef(Se,i(4,x+=S2(i,x))x)
