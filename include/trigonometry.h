
typedef struct {
    long x,y;
} vector_t;

long sinus(long x);
long expand(long i);
long cosinus(long x);
void printFix(long i);
long degConversion(long x);
long multiply(long a, long b);
void initVector(vector_t *vector_p);
void rotate(vector_t *vector_p, long x);
