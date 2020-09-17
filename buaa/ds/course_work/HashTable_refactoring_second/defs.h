#define DICBUCKETBITSIZE 21
#define DICBUCKETSIZE (1u << DICBUCKETBITSIZE)
#define MISSBUCKETBITSIZE 17
#define MISSBUCKETSIZE (1u << MISSBUCKETBITSIZE)

#define MISSWORDNUM 30000
#define MISSWORDTOTAL 500000

#define DICCHARTOTAL 5000000
#define ARTCHARTOTAL 30000000
#define MISSCHARTOTAL 8000000

#define WORDSIZE 50

#define INLINE __attribute__((__gnu_inline__, __always_inline__, __artificial__))
#define O3  __attribute__((optimize("O2")))

#define DEBUG
#define SEED 13131
#define STEP 12
#define EXTRASIZE 1024
