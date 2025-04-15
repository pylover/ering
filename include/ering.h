#ifndef  ERING_TYPENAME
#define ERING_TYPENAME ring
#endif

#ifndef ERING_COMMON_H_
#define ERING_COMMON_H_


/* Generic stuff */
#define ERING_PASTER2(x, y) x ## y
#define ERING_PASTER3(x, y, z) x ## y ## z
#define ERING_EVALUATOR2(x, y)  ERING_PASTER2(x, y)
#define ERING_EVALUATOR3(x, y, z)  ERING_PASTER3(x, y, z)
#define ERING_NAME() ERING_EVALUATOR2(ERING_PREFIX, ERING_TYPENAME)
#define ERING_NAME1(n) ERING_EVALUATOR3(ERING_PREFIX, ERING_TYPENAME, n)
#define ERING_BUFFTYPE() ERING_EVALUATOR2(ERING_PREFIX, _t)


/* ringbuffer utils */
#define ERING_BYTES(n) ((n) * sizeof(ERING_BUFFTYPE()))
#define ERING_CALC(b, n) ((n) & (b)->mask)
#define ERING_USED(b) ERING_CALC(b, (b)->head - (b)->tail)
#define ERING_AVAIL(b) ERING_CALC(b, (b)->tail - ((b)->head + 1))
#define ERING_INCRHEAD(b) (b)->head = ERING_CALC(b, (b)->head + 1)
#define ERING_DECRHEAD(b) (b)->head = ERING_CALC(b, (b)->head - 1)
#define ERING_INCRTAIL(b) (b)->tail = ERING_CALC(b, (b)->tail + 1)
#define ERING_DECRTAIL(b) (b)->tail = ERING_CALC(b, (b)->tail - 1)
#define ERING_TAILPTR(b) ((b)->buffer + (b)->tail)
#define ERING_HEADPTR(b) ((b)->buffer + (b)->head)
#define ERING_HEADPTROFF(b, off) \
    ((b)->buffer + (((b)->head - (off)) & (b)->mask))
#define ERING_TAIL(b) ((b)->buffer[(b)->tail])
#define ERING_TAILOFF(b, off) ((b)->buffer[((b)->tail + (off)) & (b)->mask])
#define ERING_ISEMPTY(b) (ERING_USED(b) == 0)
#define ERING_ISFULL(b) (ERING_AVAIL(b) == 0)
#define ERING_USED_TOEND(b) \
    ({int end = ((b)->mask + 1) - (b)->tail; \
      int n = ((b)->head + end) & (b)->mask; \
      n < end ? n : end;})
#define ERING_SKIP(b, n) (b)->tail = ERING_CALC((b), (b)->tail + (n))
#define ERING_POP(b) \
    (b)->buffer[(b)->tail]; \
    (b)->tail = ERING_CALC(b, (b)->tail + 1)


#endif  // ERING_COMMON_H_


typedef struct ERING_NAME() {
    int mask;

    /* Read/Tail*/
    int tail;

    /* Write/Head */
    int head;

    ERING_BUFFTYPE() *buffer;
} ERING_NAME1(_t);


int
ERING_NAME1(_init) (struct ERING_NAME() *ring, uint8_t maskbits);


int
ERING_NAME1(_deinit) (struct ERING_NAME() *ring);


int
ERING_NAME1(_popwrite) (struct ERING_NAME() *ring, int fd, size_t count);
