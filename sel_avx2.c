#include <stdio.h>
#include <stdlib.h>
// types
#define ATM __attribute((minsize,noinline))
#define T(t,x...) typedef t x;
#define V(t,n) t##n __attribute((vector_size(1<<n),aligned(1)))
T(char,i0,V(g,4),V(g,5),V(g,6))
T(unsigned short,i1)
T(unsigned,i2,V(i,6),V(i,5),V(i,8))
T(unsigned long,U,(*_)(i2,U),V(j,6))
T(float,e2,V(e,6),V(e,5),V(e,7),V(e,8))
T(int,V(s,6))
#undef T
#undef V
#define Ux U x
#define z0 (g6){}
#define g0 (g5){}

#define Tf(t,g,z,x...) static t g(x){return({z;});}
#define U(g,z,x...) Tf(U,g,z,x)
#define g6(g,z,x...) Tf(g6,g,z,x)

#ifdef __AVX512F__
#define O(f) B(ia32_##f##512)
g6(GB,O(selectb_)(x,1|z0,z0),Ux)

#elif __AVX2__
#define Zv(i)  ((g5*)&z)[i]
#define avi  ((g4*)&a)[i]
#define xvi  ((g4*)&x)[i]
#define o1(f)  B(ia32_##f##128)
#define o2(f)  B(ia32_##f##256)


// Convert a 32-bit mask to a 256-bit mask for _mm256_blendv_epi8
__m256i expand_32bit_mask(uint32_t mask) {
    uint8_t mask_bytes[32]; // create 32-byte array where each bit of mask becomes a byte (0xFF or 0x00)
    for (int i = 0; i < 32; i++) { mask_bytes[i] = (mask & (1u << i)) ? 0xFF : 0x00; }
    return _mm256_loadu_si256((__m256i*)mask_bytes); // Load into a 256-bit vector
}

__m256i expand_32bit_mask_opt(uint32_t mask) {
    __m128i mask_vec = _mm_set1_epi32(mask); // Broadcast 32-bit mask to all 4 lanes of a 128-bit vector
    __m256i expanded = _mm256_setzero_si256();
    // Compare each bit with 1 (shifted) to create 0xFF or 0x00 per byte
    for (int i = 0; i < 32; i += 8) {
        // Extract 8 bits at a time
        __m256i bit_mask = _mm256_srai_epi32( _mm256_slli_epi32(_mm256_cvtepu32_epi64(mask_vec), i), 31); // -1 (0xFF per byte) if bit=1, 0 if bit=0
        // Pack into the result
        expanded = _mm256_or_si256( expanded, _mm256_slli_si256(bit_mask, i / 2));
    }
    return expanded;
}


ATM static g6 GB(Ux){
 Gz; i2*c=&x;
 g5 m0=expand_32bit_mask(c[0]),m1=expand_32bit_mask(c[1]);
 Zv(0) = _mm256_blendv_epi8(g0, 1|g0, m0); // get 256b
 Zv(1) = _mm256_blendv_epi8(g0, 1|g0, m1); // get next 256b (or switch first 2 args)
 return z;
}

#elif __arm64
// TODO
#endif

int main(int argc, char**argv) {
  g6 x={0.f,1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f,10.f,11.f,12.f,13.f,14.f,15.f};
  return 0;
}
