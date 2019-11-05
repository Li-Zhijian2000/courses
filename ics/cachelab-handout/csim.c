#include "cachelab.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct CacheLine {
    unsigned valid_bit;
    // unsigned dirty_bit;
    unsigned long tag_bit;
    unsigned time;
    char *block;
};
struct CacheSet {
    struct CacheLine *lines;
};
struct Cache {
    struct CacheSet *sets;
    unsigned num_of_set;
    unsigned num_of_line;
    unsigned block_size;
    unsigned hits;
    unsigned misses;
    unsigned evictions;
};

void Usage();
void initial(struct Cache *cache, unsigned s, unsigned E, unsigned b);
void check(struct Cache *cache, unsigned long addr, char *msg);
int main(int argc, char * argv[])
{
    int kDisplayTraceInfo = 0;
    unsigned s;
    unsigned E;
    unsigned b;
    char file_name[128];

    char opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (opt) {
            case 'h':
                Usage();
                break;
            case 'v':
                kDisplayTraceInfo = 1;
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                strcpy(file_name, optarg);
                break;
        }
    }

    struct Cache *cache = malloc(sizeof(struct Cache));
    initial(cache, s, E, b);
    if (kDisplayTraceInfo);
    FILE *in_fp = fopen(file_name, "r");
    if (in_fp == NULL) {
        printf("%s\n", "failed to open file");
        return 0;
    }
    
    char op;
    unsigned long addr;
    unsigned size;
    char message[30];
    while (fscanf(in_fp, " %c%lx,%u", &op, &addr, &size) != EOF) {
        if (op == 'I') continue;
        
        memset(message, 0, sizeof(message));
        switch (op) {
            case 'L': case 'S':
                check(cache, addr, message);
                break;
            case 'M':
                check(cache, addr, message);
                check(cache, addr, message);
                break;
        }
        if (kDisplayTraceInfo) {
            printf("%c %lx,%u %s\n", op, addr, size, message);
        }
    }
    printSummary(cache->hits, cache->misses, cache->evictions);
    return 0;
}

void Usage()
{
    printf("%s\n", "Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>");
    printf("  %s\n", "-h: Optional help flag that prints usage info");
    printf("  %s\n", "-v: Optional verbose flag that displays trace info");
    printf("  %s\n", "-s <s>: Number of set index bits (S = 2^s is the number of sets)");
    printf("  %s\n", "-E <E>: Associativity (number of lines per set)");
    printf("  %s\n", "-b <b>: Number of block bits (B = 2^b is the block size)");
    printf("  %s\n", "-t <tracefile>: Name of the valgrind trace to replay");
}

void initial(struct Cache *cache, unsigned s, unsigned E, unsigned b)
{
    cache->num_of_set = 1 << s;
    cache->num_of_line = E;
    cache->block_size = 1 << b;
    cache->sets = malloc(cache->num_of_set * sizeof(struct CacheSet));
    cache->hits = cache->misses = cache->evictions = 0;

    for (int i = 0; i < cache->num_of_set; i++) {
        cache->sets[i].lines = malloc(cache->num_of_line * sizeof(struct CacheLine));
        for (int j = 0; j < cache->num_of_line; j++) {
            struct CacheLine *cache_line = &cache->sets[i].lines[j];
            // cache_line->block = malloc(cache->block_size);
            cache_line->time = cache_line->tag_bit = cache_line->valid_bit = 0;
            
        }
    }
}
void check(struct Cache *cache, unsigned long addr, char *msg)
{
    unsigned set_index = (addr / cache->block_size) & (cache->num_of_set - 1);
    // unsigned offset = addr & (cache->block_size - 1);
    unsigned long tag = addr / cache->block_size / cache->num_of_set; 
    
    struct CacheSet *cache_set = &cache->sets[set_index];
    int e;
    for (e = 0; e < cache->num_of_line; e++) {
        cache_set->lines[e].time++;
        if (cache_set->lines[e].valid_bit && cache_set->lines[e].tag_bit == tag) {
            strcat(msg, "hit ");
            cache->hits++;
            cache_set->lines[e].time = 0;
            break;
        }
    }
    if (e == cache->num_of_line) {
        strcat(msg, "miss ");
        cache->misses++;

        int max = 0;
        for (e = 0; e < cache->num_of_line; e++) {
            if (!cache_set->lines[e].valid_bit) {
                cache_set->lines[e].valid_bit = 1;
                cache_set->lines[e].tag_bit = tag;
                cache_set->lines[e].time = 0;
                break;
            }

            if (cache_set->lines[e].time > cache_set->lines[max].time) max = e;
        }
        if (e == cache->num_of_line) {
            strcat(msg, "eviction ");
            cache->evictions++;
            cache_set->lines[max].tag_bit = tag;
            cache_set->lines[max].time = 0;
        }
    }
}

