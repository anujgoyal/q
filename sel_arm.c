#include <stdio.h>
// clang -osel sel.c -funsigned-char -fno-unwind-tables -w -Os -Ofast
// started Jun 14, 2025

// defines
#define v(n) __attribute((vector_size(1<<n),aligned(1)))
typedef unsigned long(*_)(),U,J v(6);
typedef char    G v(6),_G v(6-2), g3 v(6-3);
typedef int     I v(6),I_ v(6+2);
typedef float e,E v(6),E_ v(6+2);
#undef v
#define i(b,e) {unsigned $=b;unsigned i=0;while(i<$){e;++i;}}
#define D(t,g,x,a...) static t g(a){return({x;});}
#define Uz U z
#define Gz G z
#define Gy G y
#define GU(g,x) D(G,g,x,Uz)
#define ZG static G
#define ss char*s
ZG Z0;

// printing
#define ATM __attribute((minsize,noinline)) 
//ATM void pg4(_G v) { for(int i=0;i<16;i++) { printf("%u,%s", v[i], (i+1)%8?"":" ");} putchar('\n');}
//ATM void pi6(I v) { for(int i=0;i<16;i++) { printf("%u ", v[i]);} putchar('\n');}
//ATM void pu(Uz) {int i;for(i=63;i>=0;i--){putchar((- & (1ULL<<i))?'1':'0'); if(0==(i)%8) putchar(' ');} putchar('b'); putchar('\n');}
ATM void pG(Gz) {int i;for(i=0;i<64;i++) {printf("%d,%s", z[i], (i+1)%8?"":" ");} putchar('\n');}

#ifdef __AVX512F__
GU(Gb,O(selectb_)(z,1|Z0,Z0))

#elif __arm64
#define B(f) __builtin_neon_##f
#define O(f) B(v##f##q_v)
#define xvi ((_G*)&x)[i]
#define yvi ((_G*)&y)[i]
#define zvi ((_G*)&z)[i]


// 80 bytes code, 0 bytes text, 64 loops
ATM static G Gb(Uz){Gy;i(64,y[i]=1&z>>i) return y;}


//static char bit_unpack_table[256][8] = {
static g3 bit_unpack_table[256] = {
 #define ROW(b) {(b>>0)&1,(b>>1)&1,(b>>2)&1,(b>>3)&1,(b>>4)&1,(b>>5)&1,(b>>6)&1,(b>>7)&1}
 ROW(0x00), ROW(0x01), ROW(0x02), ROW(0x03), ROW(0x04), ROW(0x05), ROW(0x06), ROW(0x07),
 ROW(0x08), ROW(0x09), ROW(0x0A), ROW(0x0B), ROW(0x0C), ROW(0x0D), ROW(0x0E), ROW(0x0F),
 ROW(0x10), ROW(0x11), ROW(0x12), ROW(0x13), ROW(0x14), ROW(0x15), ROW(0x16), ROW(0x17),
 ROW(0x18), ROW(0x19), ROW(0x1A), ROW(0x1B), ROW(0x1C), ROW(0x1D), ROW(0x1E), ROW(0x1F),
 ROW(0x20), ROW(0x21), ROW(0x22), ROW(0x23), ROW(0x24), ROW(0x25), ROW(0x26), ROW(0x27),
 ROW(0x28), ROW(0x29), ROW(0x2A), ROW(0x2B), ROW(0x2C), ROW(0x2D), ROW(0x2E), ROW(0x2F),
 ROW(0x30), ROW(0x31), ROW(0x32), ROW(0x33), ROW(0x34), ROW(0x35), ROW(0x36), ROW(0x37),
 ROW(0x38), ROW(0x39), ROW(0x3A), ROW(0x3B), ROW(0x3C), ROW(0x3D), ROW(0x3E), ROW(0x3F),
 ROW(0x40), ROW(0x41), ROW(0x42), ROW(0x43), ROW(0x44), ROW(0x45), ROW(0x46), ROW(0x47),
 ROW(0x48), ROW(0x49), ROW(0x4A), ROW(0x4B), ROW(0x4C), ROW(0x4D), ROW(0x4E), ROW(0x4F),
 ROW(0x50), ROW(0x51), ROW(0x52), ROW(0x53), ROW(0x54), ROW(0x55), ROW(0x56), ROW(0x57),
 ROW(0x58), ROW(0x59), ROW(0x5A), ROW(0x5B), ROW(0x5C), ROW(0x5D), ROW(0x5E), ROW(0x5F),
 ROW(0x60), ROW(0x61), ROW(0x62), ROW(0x63), ROW(0x64), ROW(0x65), ROW(0x66), ROW(0x67),
 ROW(0x68), ROW(0x69), ROW(0x6A), ROW(0x6B), ROW(0x6C), ROW(0x6D), ROW(0x6E), ROW(0x6F),
 ROW(0x70), ROW(0x71), ROW(0x72), ROW(0x73), ROW(0x74), ROW(0x75), ROW(0x76), ROW(0x77),
 ROW(0x78), ROW(0x79), ROW(0x7A), ROW(0x7B), ROW(0x7C), ROW(0x7D), ROW(0x7E), ROW(0x7F),
 ROW(0x80), ROW(0x81), ROW(0x82), ROW(0x83), ROW(0x84), ROW(0x85), ROW(0x86), ROW(0x87),
 ROW(0x88), ROW(0x89), ROW(0x8A), ROW(0x8B), ROW(0x8C), ROW(0x8D), ROW(0x8E), ROW(0x8F),
 ROW(0x90), ROW(0x91), ROW(0x92), ROW(0x93), ROW(0x94), ROW(0x95), ROW(0x96), ROW(0x97),
 ROW(0x98), ROW(0x99), ROW(0x9A), ROW(0x9B), ROW(0x9C), ROW(0x9D), ROW(0x9E), ROW(0x9F),
 ROW(0xA0), ROW(0xA1), ROW(0xA2), ROW(0xA3), ROW(0xA4), ROW(0xA5), ROW(0xA6), ROW(0xA7),
 ROW(0xA8), ROW(0xA9), ROW(0xAA), ROW(0xAB), ROW(0xAC), ROW(0xAD), ROW(0xAE), ROW(0xAF),
 ROW(0xB0), ROW(0xB1), ROW(0xB2), ROW(0xB3), ROW(0xB4), ROW(0xB5), ROW(0xB6), ROW(0xB7),
 ROW(0xB8), ROW(0xB9), ROW(0xBA), ROW(0xBB), ROW(0xBC), ROW(0xBD), ROW(0xBE), ROW(0xBF),
 ROW(0xC0), ROW(0xC1), ROW(0xC2), ROW(0xC3), ROW(0xC4), ROW(0xC5), ROW(0xC6), ROW(0xC7),
 ROW(0xC8), ROW(0xC9), ROW(0xCA), ROW(0xCB), ROW(0xCC), ROW(0xCD), ROW(0xCE), ROW(0xCF),
 ROW(0xD0), ROW(0xD1), ROW(0xD2), ROW(0xD3), ROW(0xD4), ROW(0xD5), ROW(0xD6), ROW(0xD7),
 ROW(0xD8), ROW(0xD9), ROW(0xDA), ROW(0xDB), ROW(0xDC), ROW(0xDD), ROW(0xDE), ROW(0xDF),
 ROW(0xE0), ROW(0xE1), ROW(0xE2), ROW(0xE3), ROW(0xE4), ROW(0xE5), ROW(0xE6), ROW(0xE7),
 ROW(0xE8), ROW(0xE9), ROW(0xEA), ROW(0xEB), ROW(0xEC), ROW(0xED), ROW(0xEE), ROW(0xEF),
 ROW(0xF0), ROW(0xF1), ROW(0xF2), ROW(0xF3), ROW(0xF4), ROW(0xF5), ROW(0xF6), ROW(0xF7),
 ROW(0xF8), ROW(0xF9), ROW(0xFA), ROW(0xFB), ROW(0xFC), ROW(0xFD), ROW(0xFE), ROW(0xFF)
};

/*#include <arm_neon.h>
ATM static G Gbb(uint64_t z) { Gy;
 _G b0= { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15 }; _G b1 = vaddq_u8(b0, vdupq_n_u8(16)); _G b2 = vaddq_u8(b0, vdupq_n_u8(32)); _G b3 = vaddq_u8(b0, vdupq_n_u8(48));
 uint64x2_t zz = vdupq_n_u64(z); y[0] = vandq_u8(vshrq_u8((uint8x16_t)zz, b0), vdupq_n_u8(1));
 y[1] = vandq_u8(vshrq_u8((uint8x16_t)zz, b1), vdupq_n_u8(1));
 y[2] = vandq_u8(vshrq_u8((uint8x16_t)zz, b2), vdupq_n_u8(1));
 y[3] = vandq_u8(vshrq_u8((uint8x16_t)zz, b3), vdupq_n_u8(1)); return y; }*/


// 120 bytes code, 16384 bytes text, 8 loops
ATM static G Gbb(U z) 
 Gy; ss=(char*)&z;
 i(8,((g3*)&y)[i]=(g3)bit_unpack_table[s[i]])
 return y;
}

#endif

int main(int argc, char *argv[]) {
 U a=7;
 G r=Gb(a);
 printf("r:");pG(r);
 G s=Gbb(a);
 printf("s:");pG(s);
 return 0;
}



/*
#include <arm_sve.h>
#include <stdint.h>

void Gb_sve(uint64_t z, uint8_t out[64]) {
    // Create a vector of bit positions: 0, 1, 2, ..., 63
    svuint8_t bit_indices = svindex_u8(0, 1);  // [0, 1, 2, ..., 63]
    
    // Broadcast the scalar z into each lane of a 64-bit vector
    svuint64_t z_vec = svdup_u64(z);
    
    // Shift right: each lane gets z >> i
    svuint64_t shifted = svlsr_u64_z(svptrue_b8(), z_vec, svreinterpret_u64(bit_indices));
    
    // Mask to extract only LSB
    svuint8_t bits = svand_z(svptrue_b8(), svreinterpret_u8(shifted), svdup_u8(1));
    
    // Store result into memory
    svst1_u8(svptrue_b8(), out, bits);
}

//svindex_u8(0, 1) creates a vector [0, 1, ..., 63]
//svdup_u64(z) duplicates z into every 64-bit lane
//svlsr_u64_z(..., z_vec, bit_indices) shifts z by the bit index in each lane
//svand_z(..., ..., 1) masks to get LSB
//svst1_u8 stores the result into memory

*/
