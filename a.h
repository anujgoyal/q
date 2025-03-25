#include"_.h" //x86(avx2/512)arm(neon/sve(graviton/ampere))

#ifdef __AVX512F__
#define o(o) bu(ia32_##o)
_V(g0,o(gathersiv16si)(z0,s,x,-1,1),ss,Vx)
_V(g2,o(gathersiv16si)(z0,s,x,-1,4),ss,Vx)
_V(g3,o(gathersiv8di)(z0,s,x,-1,8),ss,Yx)
Ef(ie,o(cvtps2dq512_mask)(x,z0,-1,4))
Ef(_q,o(sqrtps512)(x,4))
VF(p0,o(permvarqi512)(a,x))
VF(p2,o(permvarsi512)(a,x))
Vg(r0,p0(x,i?I0%4|15-I2<<2:63-I0))
_V(P2,o(vpermi2varps512)(a,b,x),Va,Vb,Vx)
IF(_P,P2(a,2*I2,x))IF(P_,P2(a,1|2*I2,x))
Vg(s0,4>i?o(vpermi2varqi512)(x,I0-(i0)i,z0):P2(x,I2-i/4,z0))
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
#define Ziv(i)       ((i5*)&z)[i] 
#define Aev(i)       ((e5*)&a)[i] 
#define Xev(i)       ((e5*)&x)[i] 
#define Zev(i)       ((e5*)&z)[i] 
#define o1(o)    bu(ia32_##o##128)
#define o2(o)    bu(ia32_##o##256)
static g4 M15={15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},M31={31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},M47={47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47};
static g4 v4u(g6 a,g4 x){g4 z,i=x&M15;z=o1(pblendvb)(o1(pshufb)(av(0),i),o1(pshufb)(av(1),i),x>M15);z=o1(pblendvb)(z,o1(pshufb)(av(2),i),x>M31);z=o1(pblendvb)(z,o1(pshufb)(av(3),i),x>M47);return z;} //v4u~vqtbl4
//static g4 s4u(ss,g4 x){g4 z,i=x&M15;z=o1(pblendvb)(o1(pshufb)(sv(0),i),o1(pshufb)(sv(16),i),x>M15);z=o1(pblendvb)(z,o1(pshufb)(sv(32),i),x>M31);z=o1(pblendvb)(z,o1(pshufb)(sv(48),i),x>M47);return z;} 
//static g4 MiB={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3},MiF={0,0,0,0,4,4,4,4,8,8,8,8,12,12,12,12};
//static g4 v1u(g4 x){g4 z=MiB+o1(pshufb)(x*4,MiF);return z;} //v1u~vqtbl1
//static g4 MjB={0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7},MjF={0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,8};
//static g4 j1u(g4 x){g4 z=MjB+o1(pshufb)(x*4,MjF);return z;} */
_V(g0,Iz;i(16,zi=*(i2*)(s+x[i]))z,ss,Vx)
_V(g2,Iz;i(16,zi=*(i2*)(s+x[i]*4))z,ss,Vx)
_V(g3,Ez;i(8,zi=*(e2*)(s+x[i]*8))z,ss,Yx)
Ef(ie,Iz;Ziv(0)=o2(cvtps2dq)(Xiv(0));Ziv(1)=o2(cvtps2dq)(Xiv(1));z)
Ef(_q,Ez;Zev(0)=o2(sqrtps)(Xev(0));Zev(1)=o2(sqrtps)(Xev(1));z) // Xiv or Xev?
VF(p0,L(v4u(a,xv(i))))
VF(p2,Iz;Ziv(0)=o2(pblendvb)(o2(permvarsi)(Aiv(0),Xiv(0)),o2(permvarsi)(Aiv(1),Xiv(0)),Xiv(0)>=8);  // Need more testing, 4 or 8
         Ziv(1)=o2(pblendvb)(o2(permvarsi)(Aiv(0),Xiv(1)),o2(permvarsi)(Aiv(1),Xiv(1)),Xiv(1)>=8);z)
Vg(r0,p0(x,i?I0%4|15-I2<<2:63-I0))
ZV P2(Va,Vb,Vx){Ez;
 e5 ra=o2(pblendvb)(o2(permvarsf)(Aev(0),Biv(0)),   o2(permvarsf)(Aev(1),Biv(0)),Biv(0)>=8);
 e5 rb=o2(pblendvb)(o2(permvarsf)(Xev(0),Biv(0)-16),o2(permvarsf)(Xev(1),Biv(0)-16),(Biv(0)-16)>=8);
 Zev(0)=o2(pblendvb)(ra,rb,Biv(0)>=16);
 ra=o2(pblendvb)(o2(permvarsf)(Aev(0),Biv(1)),   o2(permvarsf)(Aev(1),Biv(1)),Biv(1)>=8);
 rb=o2(pblendvb)(o2(permvarsf)(Xev(0),Biv(1)-16),o2(permvarsf)(Xev(1),Biv(1)-16),(Biv(1)-16)>=8);
 Zev(1)=o2(pblendvb)(ra,rb,Biv(1)>=16);
 return z;}
IF(_P,P2(a,2*I2,x))IF(P_,P2(a,1|2*I2,x))
ZV s0(ii,Vx){Vz,a=x,b=z0;x=I0-(i0)i;if(4<i){i(4,zv(i)=o1(pblendvb)(v4u(a,xv(i)),v4u(b,xv(i)-64),xv(i)>=64))}else{z=P2(a,I2-i/4,b);}return z;}
#endif

Ef(_l,Sz=ie(x-.5);x-=C(e6,z);(e6)(z+127<<23)*p6(.99999994,.69315308,.24015361,.055826318,.0089893397,.0018775767))
Ef(l_,Sz=x;x=E1|b(23)&z;C(e6,(z>>23)-127)+(x-1)*p6(3.1157899,-3.324199,2.5988452,-1.2315303,.31821337,-.034436006))
Z2 b[]={3,0,2,2,3,0,0,3},o,W,Z[1<<18];ZU M=1l<<32,a[30],O[1<<17];_g(_M,W-=1<<i;*(U*)x=ai;ai=x)Ui(M_,Ux=ai;P(x,ai=*(U*)x;W+=1<<i;x)OO(i>28)_M(i,M_(i+1))+(64L<<i))_f(qm,1l<<36>(U)sx-M)
g_(ku,x?$4(i,_r(x),r_(x),(U)sx,ux):ti(W))_F(u_,Ox|=a<<47;Mx|x)_f(_u,Ox&=b(47);~Mx&x)_g(p,cc=Nx%64;if(c)$(i,xV[Nx>>6]|=I0>=c)xV[Nx>>6]&=I0<c;x)inx(ln,R(tx,n,M6(Nr,sr,sx+((int)i<<bx))))
_G(o_,Ub=o;o=O[o];O[b]=a;t(8+i,b<<38|x))_f(_o,qm(x)?_M(hx,(U)sx):_m((U)sx,nx);Ox=o;o=ox;x)_f(_r,P(ax,x)P(63&Ox,--Ox;x)if(!tx)i(nx,_r(xj))_o(x))_f(r_,P(ax,x)OO(!(63&++Ox))x)
_g(hn,lu(m(64,x<<b[i]))-6)_g(dz,hn(tx,i)>hx?_R(tx,i,M6(Nx,sr,sx)):x+i-nx)ZJ A={-1},B={0xc6a4a7935bd1e995};_V(JJ,B=RJ(37,RJ(55,A^=B)^B^B<<14);A+B)_f(uz,!qm(x)|63&Ox?_R(tx,nx,):x)
Z_(k_,m_(0,0);i(30,ai=M+(64L<<i))i(1<<17,O[i]=i+1)i(8,if(i)Ai=Bi=i)i(1e4,JJ()))g_(tn,Ua=hn(i,x);a<<55|o_(i,M_(a),x))_f(ms,x&=b(60);Ua=m_(&x,&x);Qz(x>>30)o_(1,a,x))
g(_i,mx?ln(i*vx,vx,x):tx?t(tx,$b(xg,xi,xj)):r_(xj))g(i_,0)//ij=i;Ua;VX=sx;I(Nx,$(2>tx,P(a=B0((i0)j==X_),l(nx,64*i|iu(a))))P(a=B2(j==Ix),l(nx,16*i|iu(a))))nx)
_f(_v,_x(_i(0,x)))f(v,R(tx,1,*(U*)sr=b(60)&x))_f(_n,_x(ti(ux)))g(n_,RV(tx,i,$b((i0)ix-z0,ix-z2,jx-z3)))
_Z(m6,$(tx,cc=63&(U)d;VA=d-c;Va=*A;M6(c+(n<<bx),A,sx-c);*A=I0<c&a|I0>=c&*A)i(n,r_(Ud=xj);d+=8),in,sd,Ux)g(nt,i>nx?r(dz(i,x),W(i<nr)(m6(l(i,nr-i),sr+(i<<bx),r),i*=2)):x+i-nx)
g(T,i>tx?T(i,_x(RV(tx+1,nx,$3(tx-1,C(i6,XX),C(e6,(s6)XZ),C(j6,XY))))):x)f(_T,_R(tx-1,nx,VX=sx;I(Nx,$3(tx-2,RX=C(g4,Ix);0,RZ=ie(Ex);0,RY=C(i5,Jx);0))))G(dD,7>x?T(4,x):ms(x))
G(cC,P(!a,ax?v(x):!tx|mx?R(0,1,*(U*)sr=x):u_(1,x))Qz(ta-tx|mx|(ma&&va-nx))a=aa?v(a):a;x=ax?v(x):x;x=_x(r(dz(na+nx,a),m6(nx,sr+Na,x)));ma?(1L<<32)+x:x)
G(L3,in=iz(a);Qr(!aa)P(ax,n_(n,x))P(15<i,u_(n,x))i&=1;P(i^n>>31,Qz(!tx|mx)n+=!i*ux;_x(ln(n,nx-n,x)))n+=!!i*ux;tx?mx?u_(n,nt(n*vx,x)):nt(n,x):RU(n,_i(i%nx,x)))
#define z(K) h(8/K,ik=K;j(k,ii=2*h*k+j;zi=_P(zi,r(zk,zk=P_(zi,r)))))
_f(ff,Qr(!mx)Qz(2-bx)in=vx;Qn(16-ux|16-n)u_(n,_X(V,Ez[16];i(16,zi=XZ)z(1)z(2)z(4)z(8)i(16,Ri=zi))))_f(rr,Qr(mx)_X(V,VX=sx+Nx;I(Nx,R_=r0(bx,*--X))))

