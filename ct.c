#include <stdio.h>
#include <stdlib.h>
// clang -Ofast -oct ct.c -funsigned-char -fno-unwind-tables -w

#define ATM  __attribute((minsize,noinline)) 
#define AT(z...) __attribute((z))
#define _(n) AT(vector_size(1<<n),aligned(1))
typedef unsigned long U,i3,j4 _(4),j6 _(6),(*UF)();
typedef char i0,g4 _(4),g5 _(5),g6 _(6);
typedef unsigned short i1;
typedef unsigned i2,i4 _(4),i5 _(5),i6 _(6);
typedef float e2,e5 _(5),e6 _(6);
typedef int s6 _(6);
#undef _

#define ii i2 i
#define ij i2 i
#define i(b,z) {i2 $=b;ii=0;while(i<$){z;++i;}} 
#define X_ *X++; // easier traversal

ATM static void pe(e6 v) { i(16,printf("%.1f %s",v[i],(i+1)%8?"":" ")) putchar('\n');}
ATM static void pen(i2 n,e2 *v) { i(n,printf("%.1f %s",v[i],(i+1)%8?"":" ")) putchar('\n');}

// Cooley-Tukey FFT algo
// i(n,a=X_;R_=Y(0,a,b=X_);R_=Y(1,a,b)) // part 1
// a,b => a,b
// a,b,c => a,c,b
// a,b,c,d => a,c,b,d
// a,b,c,d,e => a,c,e,b,d
// https://groups.google.com/g/shaktidb/c/32jCeqJxP_c

ATM static float* ct(unsigned n,float *x) {
  // allocate new vector 
  float *z=(float*)malloc(n*sizeof(float));

  // calculate midpoint
  int mid=(n/2)+(n%2);

  // loop through each element
  // if index even, add onto 1st half of vector
  // if index odd, add onto 2nd half of vector (mid+...)
  for(int i=0;i<n;i++) {
    int j = i/2+(i%2?mid:0); // i%2 ? odd : even
    z[j] = *x++;
  } 
  //i(n,ij=i%2?m+i/2:i/2;z[j]=X_);
  return z;
}

int main(int argc, char**argv) {
  e6 x={0.f,1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f,10.f,11.f,12.f,13.f,14.f,15.f};
  pe(x);
  i2 n = 7;
  e2*a=ct(n,&x); 
  pen(n,a);
  free(a);
  return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

void in_place_even_odd_split(complex double *x, int n) {
    if (n <= 1) return; // Base case for recursion

    // In-place bit-reversal-style even-odd split
    complex double temp[n];
    for (int i = 0; i < n / 2; i++) {
        temp[i] = x[2 * i];       // Even indices
        temp[i + n / 2] = x[2 * i + 1]; // Odd indices
    }
    for (int i = 0; i < n; i++) {
        x[i] = temp[i]; // Copy back to the original array
    }
}

void fft(complex double *x, int n) {
    if (n <= 1) return;

    // Perform in-place even-odd split
    in_place_even_odd_split(x, n);

    // Recursively compute FFT on even and odd parts
    fft(x, n / 2);
    fft(x + n / 2, n / 2);

    // Combine results using the FFT butterfly operations
    for (int k = 0; k < n / 2; k++) {
        complex double t = cexp(-2.0 * I * PI * k / n) * x[k + n / 2];
        x[k + n / 2] = x[k] - t;
        x[k] = x[k] + t;
    }
}

void print_fft(complex double *x, int n) {
    for (int i = 0; i < n; i++) {
        printf("(%lf, %lf)\n", creal(x[i]), cimag(x[i]));
    }
}

int main() {
    int n = 8; // Must be a power of 2
    complex double x[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    printf("Input:\n");
    print_fft(x, n);

    fft(x, n);

    printf("\nFFT Output:\n");
    print_fft(x, n);

    return 0;
}
*/
