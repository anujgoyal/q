#include"v.a"
Ig(S2,$4(i,
 p(x,z2,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),
 p(x,z2,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17),
 p(x,z2,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19),
 p(x,z2,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23)))

Gg(S0,$3(i,
 p(x,z0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64),
 p(x,z0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65),
 S2(i-2,x)))

EF(_P,p(a,x,0,16,2,18,4,20,6,22,8,24,10,26,12,28,14,30))
EF(P_,p(a,x,1,17,3,19,5,21,7,24,9,25,11,27,13,29,15,31))
IF(SI,a+x)
EF(SE,a+x)
GF(SG,a|x)
If(R2,p(x,15-I2))
e6(EI,c(x,e6),s6 x)

#ifdef __AVX512F__
#define O(f) o(ia32_##f##512)//GF(MG,o(elementwise_max)(a,x))IF(LI,o(elementwise_min)(a,x))IF(MI,o(elementwise_max)(a,x))
Ef(IE,o(ia32_cvtps2dq512_mask)(x,z2,-1,9))
i6(G2,o(ia32_gathersiv16si)(z2,s,x,-1,4),ss,Vx)
EF(d8,EI(O(vpdpbusd)(z2,a,x)))
U(b2,O(cvtd2mask)(x),Vx)
Ef(q,O(sqrtps)(x,4))
GF(MG,O(pmaxub)(a,x))
IF(LI,O(pminsd)(a,x))
IF(MI,O(pmaxsd)(a,x))

#elif __AVX2__
#define o2(f)  o(ia32_##f##256)
#define o1(f)  o(ia32_##f##128)
#define av(i)  ((g4*)&a)[i] // 128b
#define xv(i)  ((g4*)&x)[i]
#define zv(i)  ((g4*)&z)[i]
#define agv(i) ((g5*)&a)[i]
#define xgv(i) ((g5*)&x)[i]
#define zgv(i) ((g5*)&z)[i]
#define Aiv(i) ((i5*)&a)[i] 
#define Biv(i) ((i5*)&b)[i] 
#define Xiv(i) ((i5*)&x)[i] 
#define Ziv(i) ((i5*)&z)[i] 
#define Aev(i) ((e5*)&a)[i] 
#define Bev(i) ((e5*)&b)[i] 
#define Xev(i) ((e5*)&x)[i] 
#define Zev(i) ((e5*)&z)[i] 
If(IE,Iz;Ziv(0)=o2(cvtps2dq)(Xiv(0));Ziv(1)=o2(cvtps2dq)(Xiv(1));z)
i6(G2,Iz;i6 b=x;i(16,zi=*(i2*)(s+b[i]*4))z,ss,Vx)
#define ATM __attribute((minsize,noinline))
ATM e6 d8(e6 a,e6 x) { g6 z;
 typedef unsigned i3 __attribute((vector_size(1<<3),aligned(1)));
 // add adjacent shorts for each 256b vector
 g5 c=o2(pmaddubsw)(agv(0),xgv(0)), d=o2(pmaddubsw)(agv(1),xgv(1));
 // munge results of above into 128b vectors (8 x 16b)
 h4 r0=((h4*)&c)[0],r1=((h4*)&c)[1], r2=((h4*)&d)[0], r3=((h4*)&d)[1];
 // convert 128b to 256b to avoid losing precision
 i5 v0=c(r0,i5), v1=c(r1,i5), v2=c(r2,i5), v3=c(r3,i5);
 // add adjacent ints
 i5 a0=o2(phaddd)(v0,v0), a1=o2(phaddd)(v1,v1), a2=o2(phaddd)(v2,v2), a3=o2(phaddd)(v3,v3);
 // get proper bytes
 ((i3*)&z)[0] = ((h3*)&a0)[0]; 
 ((i3*)&z)[1] = ((h3*)&a0)[2]; 
 ((i3*)&z)[2] = ((h3*)&a1)[0]; 
 ((i3*)&z)[3] = ((h3*)&a1)[2]; 
 ((i3*)&z)[4] = ((h3*)&a2)[0]; 
 ((i3*)&z)[5] = ((h3*)&a2)[2]; 
 ((i3*)&z)[6] = ((h3*)&a3)[0]; 
 ((i3*)&z)[7] = ((h3*)&a3)[2]; 
 // convert from int to float
 return EI(z);
}
static g4 m1={8,9,10,11,0,1,2,3,4,5,6,7,12,13,14,15};
U(b2,g5 a=o2(psradi)(xgv(0),31);g5 b=o2(psradi)(xgv(1),31);a=o2(packssdw)(a,b);a=o2(packsswb)(a,a);g4 c=o1(pblendd)(av(0),av(1),(int)0b1001);c=o1(pshufb)(c,m1);Uf=o1(pmovmskb)(c);f,Vx)
Ef(q,Ez;Zev(0)=o2(sqrtps)(Xev(0));Zev(1)=o2(sqrtps)(Xev(1));z)
GF(MG,o(elementwise_max)(a,x))
IF(LI,o(elementwise_min)(a,x))
IF(MI,o(elementwise_max)(a,x))

#elif __arm64

#endif

#define p6(z,a,b,c,d,e,f) _(e6 $=z;(e2)(a)+$*((e2)b+$*((e2)c+$*((e2)d+$*((e2)e+$*(e2)f)))))
Ef(E,x*=1.442695f;s6 z=IE(x-.5);p6(x-EI(z),.99999994,.69315308,.24015361,.055826318,.0089893397,.0018775767)*(z+127<<23))
i6(IG,c(x,i6),g4 x)
g6(GI,1&c(x,g6),i8 x)
EF(AZ,q(a*a+x*x))
e6(JJ,ZJ A={-1};ZJ B={0xc6a4a7935bd1e995};Z2 a;if(!a){i(a=8,if(i)Ai=Bi=i)i(1e4,JJ())}A^=B;B^=B<<14^(A<<55|A>>9);B=B<<37|B>>27;(e6)(127<<23|b(23)&(i6)(A+B))-1)
Ef(Se,i(4,x+=S2(i,x))x)

