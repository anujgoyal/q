#include"_.h"//abcdlm[<=] %REXYZ

#ifdef __AVX512F__
#define O(f) B(ia32_##f##512)//VF(LG,B(elementwise_min)(a,x))VF(MG,B(elementwise_max)(a,x))IF(LI,B(elementwise_min)(a,x))IF(MI,B(elementwise_max)(a,x))EF(LE,B(elementwise_min)(a,x))EF(ME,B(elementwise_max)(a,x))
VF(LG,O(pminub)(a,x))VF(MG,O(pmaxub)(a,x))VF(LI,O(pminud)(a,x))VF(MI,O(pmaxud)(a,x))VF(LE,O(minps)(a,x,4))VF(ME,O(maxps)(a,x,4))
VF(p2,O(permvarsi)(a,x))
VH(P2,O(vpermi2varps)(a,b,x))
Vg(s0,2>i?O(vpermi2varqi)(x,I0-(i0)(1<<i),z0):P2(x,I2-(1<<i-2),z0))
Vg(r0,2>i?O(permvarqi)(x,63-I0):p2(x,15-I2))
VH(bc,o(vfmaddsubps512_mask3)(a,b,x,-1,9))
Vf(ba,p2(x,BA))
Vf(_q,O(sqrtps)(x,4))
Vf(ie,o(cvtps2dq512_mask)(x,z0,-1,4))
V(G0,o(gathersiv16si)(z0,s,x,-1,1),ss,Vx)
V(G2,o(gathersiv16si)(z0,s,x,-1,4),ss,Vx)
V(G3,o(gathersiv8di)(z0,s,y,-1,8),ss,Yy)
#elif __AVX2__
VF(LG,B(elementwise_min)(a,x))VF(MG,B(elementwise_max)(a,x))IF(LI,B(elementwise_min)(a,x))IF(MI,B(elementwise_max)(a,x))EF(LE,B(elementwise_min)(a,x))EF(ME,B(elementwise_max)(a,x))
#define av(i)  ((g4*)&a)[i] // 128b
#define bv(i)  ((g4*)&b)[i]
#define cv(i)  ((g4*)&c)[i]
#define xv(i)  ((g4*)&x)[i]
#define zv(i)  ((g4*)&z)[i]
#define sv(e)  *(g4*)(s+e)
#define Av(i)  ((g5*)&a)[i] // 256b
#define Xv(i)  ((g5*)&x)[i]
#define Zv(i)  ((g5*)&z)[i]
#define Aiv(i) ((i5*)&a)[i] 
#define Biv(i) ((i5*)&b)[i] 
#define Xiv(i) ((i5*)&x)[i] 
#define Ziv(i) ((i5*)&z)[i] 
#define Aev(i) ((e5*)&a)[i] 
#define Bev(i) ((e5*)&b)[i] 
#define Xev(i) ((e5*)&x)[i] 
#define Zev(i) ((e5*)&z)[i] 
#define o1(o)  B(ia32_##o##128)
#define o2(o)  B(ia32_##o##256)
#define M0 ((g4){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
static g4 M15=M0+15,M31=M0+31,M47=M0+47;static e5 MALT5={1,-1,1,-1,1,-1,1,-1};
static g4 v4u(Va,g4 x){g4 z,i=x&M15;z=o1(pblendvb)(o1(pshufb)(av(0),i),o1(pshufb)(av(1),i),x>M15);z=o1(pblendvb)(z,o1(pshufb)(av(2),i),x>M31);z=o1(pblendvb)(z,o1(pshufb)(av(3),i),x>M47);return z;} //v4u~arm:vqtbl4
#define BL o2(pblendvb) 
#define Pmi o2(permvarsi) // permute i
#define Pme o2(permvarsf) // permute e
#define BPI(a,b,c) BL(Pmi(a##iv(0),b),Pmi(a##iv(1),b),b>=c) 
VF(p2,Iz;Ziv(0)=BPI(A,Xiv(0),8);Ziv(0)=BPI(A,Xiv(1),8);z)
#define BPE(a,b,c) BL(Pme(a##ev(0),b),Pme(a##ev(1),b),b>=c) 
VH(P2,Ez;Zev(0)=BL(BPE(A,Biv(0),8),BPE(X,Biv(0)-16,8),Biv(0)>=16);Zev(1)=BL(BPE(A,Biv(1),8),BPE(X,Biv(1)-16,8),Biv(1)>=16);z)
Vg(s0,Vz;Va=I0-(i0)(1<<i);$(2>i,i(4,zv(i)=o1(pblendvb)(v4u(x,av(i)),M0,av(i)>=64)))z=P2(x,I2-(1<<i-2),z0);z)
//ZZ s0(ii,Vx){Vz,a=I0-(i0)(1<<i);if(2>i){i(4,zv(i)=o1(pblendvb)(v4u(x,av(i)),M0,av(i)>=64))}else{z=P2(x,I2-(1<<i-2),z0);}return z;} 
Vg(r0,Vz;Va=63-I0;$(2>i,i(4,zv(i)=v4u(x,av(i))))z=p2(x,15-I2);z)
//ZZ r0(ii,Vx){Vz,a=63-I0;if(2>i){i(4,zv(i)=v4u(x,av(i)))}else{z=p2(x,15-I2);}return z;}
VH(bc,Ez;Zev(0)=o2(vfmaddps)(Aev(0),Bev(0),Xev(0)*MALT5);Zev(1)=o2(vfmaddps)(Aev(1),Bev(1),Xev(1)*MALT5);z)
Vf(ba,p2(x,BA))
Vf(_q,Ez;Zev(0)=o2(sqrtps)(Xev(0));Zev(1)=o2(sqrtps)(Xev(1));z)
Vf(ie,Iz;Ziv(0)=o2(cvtps2dq)(Xiv(0));Ziv(1)=o2(cvtps2dq)(Xiv(1));z)
V(G0,Iz;Ib=x;i(16,zi=*(i2*)(s+b[i]))z,ss,Vx)
V(G2,Iz;Ib=x;i(16,zi=*(i2*)(s+b[i]*4))z,ss,Vx)
V(G3,Ez;i(8,zi=*(e2*)(s+y[i]*8))z,ss,Yy)
#elif __arm64
#undef o
#define o(o)  B(neon_v##o##q_v)
#define L(e)  Vz;i(4,((g4*)&z)[i]=e)z
#define av(i)        ((g4*)&a)[i]
#define bv(i)        ((g4*)&b)[i]
#define xv(i)        ((g4*)&x)[i]
#define zv(i)        ((g4*)&z)[i]
static e4 MALT={1,-1,1,-1};
static g4 M0,MC={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
MiB={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3}, MiF={0,0,0,0,4,4,4,4,8,8,8,8,12,12,12,12};
#define vlu(e,t)  o(qtbl4)(e##v(0),e##v(1),e##v(2),e##v(3),t,48)
#define ilu(e)    MiB+o(qtbl1)(e##v(i)*4,MiF,48)
VF(LG,L(o(min)(av(i),xv(i),48))) //__builtin_neon_vminq_v 8b
VF(MG,L(o(max)(av(i),xv(i),48)))
VF(LI,L(o(min)(av(i),xv(i),50))) //__builtin_neon_vminq_v 32b i
VF(MI,L(o(max)(av(i),xv(i),50)))
EF(LE,L(o(min)(av(i),xv(i),41))) // __builtin_neon_vminq_v 32b e
EF(ME,L(o(max)(av(i),xv(i),41)))
VF(p2,L(vlu(a,ilu(x)))) // permvarsi: 32b ints (16 elements per 512b vec)
Vg(r0,Vz;Va=63-I0;$(2>i,i(4,zv(i)=vlu(x,av(i))))z=p2(x,15-I2);z) // permvarqi: 8b ints (64 elements per 512b vec)
VH(P2,Vz;i(4,i4 p=ilu(b);zv(i)=vlu(a,p)+vlu(x,o(bsl)(p>=16,p,MC,48)-16))z) // vpermi2varps: 16x32b floats
Vg(s0,Vz;Va=I0-(i0)(1<<i);$(2>i,i(4,zv(i)=vlu(x,av(i))+M0))z=P2(x,I2-(1<<i-2),z0);z) // vpermi2varqi 64x8 ints
//Vg(s0,Vz;Va=I0-(i0)(1<<i);$(2>i,i(4,zv(i)=vlu(a,bv(i))+vlu(x,o(bsl)(bv(i)>=64,bv(i),MC,48)-64)))z=P2(x,I2-(1<<i-2),z0);z) // vpermi2varqi 
//VH(bc,Vz;i(4,zv(i)=o(fma)(av(i),bv(i),xv(i)*MALT,41))z)
VH(bc,L(o(fma)(av(i),bv(i),xv(i)*MALT,41)))
Vf(ba,p2(x,BA))
Vf(_q,L(o(sqrt)(xv(i),41)))
Vf(ie,L(B(neon_vcvtq_s32_v)(xv(i),34)))
V(G0,Iz;Ib=x;i(16,zi=*(i2*)(s+b[i]))z,ss,Vx)
V(G2,Iz;Ib=x;i(16,zi=*(i2*)(s+b[i]*4))z,ss,Vx)
V(G3,Ez;i(8,zi=*(e2*)(s+y[i]*8))z,ss,Yy)
#undef o
#undef L
#undef av 
#undef bv
#undef xv
#undef zv
#endif

EF(c,bc(p2(a,I2/2*2),x,(e6)p2(a,1|I2/2*2)*ba(x)))IF(_P,B(shufflevector)(a,x,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30))IF(P_,B(shufflevector)(a,x,1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31))
Ef(_l,Sz=ie(x-.5);x-=C(e6,z);(e6)(z+127<<23)*p6(.99999994,.69315308,.24015361,.055826318,.0089893397,.0018775767))VF(SG,a+x)IF(SI,a+x)EF(SE,a+x)
Ef(l_,Sz=x;x=E1|b(23)&z;C(e6,(z>>23)-127)+(x-1)*p6(3.1157899,-3.324199,2.5988452,-1.2315303,.31821337,-.034436006))ZJ A={-1},B={0xc6a4a7935bd1e995};V(JJ,B=RJ(37,RJ(55,A^=B)^B^B<<14);A+B)
e2 const X=.92387953,Y=.38268343,Q=.70710678;ZE xy[]={{1,0,Q,-Q,0,-1,-Q,-Q,-1,0,-Q,Q,0,1,Q,Q},{1,0,X,-Y,Q,-Q,Y,-X,0,-1,-Y,-X,-Q,-Q,-X,-Y},{
1,0,.98078528,-.19509032,X,-Y,.83146961,-.55557023,Q,-Q,.55557023,-.83146961,Y,-X,.19509032,-.98078528},{0,-1,-.19509032,-.98078528,-Y,-X,-.55557023,-.83146961,-Q,-Q,-.83146961,-.55557023,-X,-Y,-.98078528,-.19509032},{
1,0,.99518473,-.09801714,.98078528,-.19509032,.95694034,-.29028468,X,-Y,.88192126,-.47139674,.83146961,-.55557023,.77301045,-.63439328},{Q,-Q,.63439328,-.77301045,.55557023,-.83146961,.47139674,-.88192126,Y,-X,.29028468,-.95694034,.19509032,-.98078528,.09801714,-.99518473},{
0,-1,-.09801714,-.99518473,-.19509032,-.98078528,-.29028468,-.95694034,-Y,-X,-.47139674,-.88192126,-.55557023,-.83146961,-.63439328,-.77301045},{-Q,-Q,-.77301045,-.63439328,-.83146961,-.55557023,-.88192126,-.47139674,-X,-Y,-.95694034,-.29028468,-.98078528,-.19509032,-.99518473,-.09801714}};
ZE g[]={{1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1},{1,-1,0,0,1,-1,1,-1,1,-1,0,0,1,-1,1,-1},{1,1,1,-1,1,-1,1,1, 1,1,1,-1,1,1,1,1},{1,-1,Q,-Q,0,0,Q,-Q,-1,-1,-Q,Q,0,0,-Q,Q}};
ZI h[]={{0,0,4,4,2,2,6,6,1,1,5,5,3,3,7,7},{0,0,1,3,4,4,5,5,8,8,9,11,12,12,13,13},{0,0,2,3,1,5,2,3,0,0,2,3,1,5,2,3},{4,0,7,6,4,0,7,6,4,0,7,6,4,0,7,6}};
