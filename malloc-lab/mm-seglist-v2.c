/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memlib.h"
#include "mm.h"
/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "bk",
    /* First member's email address */
    "bknote71@gmai.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

static void *find_fit(size_t);
static void place(void *, size_t);
static void *coalesce(void *);
static void *extend_heap(size_t);
static void insert(void *);
static void erase(void *);

#ifdef NULL
#undef NULL
#define NULL ((void *)0)
#endif

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8 // 할당 배수

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t))) // 64비트? 8

#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1 << 7)
#define LIMIT 15

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HDRP(bp) ((char *)(bp)-WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp)-WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp)-GET_SIZE(((char *)(bp)-DSIZE)))

#define PREV(bp) (*(void **)(bp))
#define SUCC(bp) (*(void **)(bp + WSIZE))
#define INDEX(x) ((x) > (1 << (LIMIT - 2)) ? (LIMIT - 1) : (int)log2((x)-1) + 1)

static inline int getIndex(int x)
{
    int idx = 0;
    x -= 1;
    while ((idx++ < LIMIT) && x > 0)
    {
        x >>= 1;
    }
    return idx > LIMIT ? LIMIT - 1 : idx - 1;
}

static char *seg_array[LIMIT];

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    // mem_init();
    // 배열 NULL 로 초기화
    char *heap_list;
    if ((heap_list = mem_sbrk(6 * WSIZE)) == (void *)-1)
        return -1;
    PUT(heap_list, 0);                                // unuse
    PUT(heap_list + (1 * WSIZE), PACK(2 * DSIZE, 1)); // prolog header
    PUT(heap_list + (2 * WSIZE), NULL);               // sentinel next pointer
    PUT(heap_list + (3 * WSIZE), NULL);               // sentinel pointer pointer
    PUT(heap_list + (4 * WSIZE), PACK(2 * DSIZE, 1)); // prolog header
    PUT(heap_list + (5 * WSIZE), PACK(0, 1));         // epilogue header
    // 나중에 여기를 활용해볼까...?
    for (int index = 0; index < LIMIT; ++index)
        seg_array[index] = heap_list + 2 * WSIZE;
    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
        return -1;
    return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    /* Ignore spurious requests */
    if (size == 0)
        return NULL;
    size_t newsize = ALIGN(size + SIZE_T_SIZE);
    char *bp;
    if ((bp = find_fit(newsize)) != NULL)
    {
        place(bp, newsize);
        return bp;
    }
    int extendsize = MAX(newsize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize / WSIZE)) == NULL)
        return NULL;
    place(bp, newsize);
    return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    if (ptr == NULL)
        return;
    size_t size = GET_SIZE(HDRP(ptr));
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    if (size <= 0)
    {
        mm_free(ptr);
        return NULL;
    }
    size_t org_size = GET_SIZE(HDRP(ptr));
    size_t new_size = size + (2 * WSIZE); // prev, next
    if (new_size <= org_size)
        return ptr;
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(ptr)));
    size_t bsize;
    if (!next_alloc && ((bsize = org_size + GET_SIZE(HDRP(NEXT_BLKP(ptr))))) >= new_size)
    {
        erase(NEXT_BLKP(ptr));
        PUT(HDRP(ptr), PACK(bsize, 1));
        PUT(FTRP(ptr), PACK(bsize, 1));
        return ptr;
    }
    void *newptr = mm_malloc(new_size);
    if (newptr == NULL)
        return NULL;
    place(newptr, new_size);
    memcpy(newptr, ptr, new_size);
    mm_free(ptr);
    return newptr;
}

static void *find_fit(size_t size)
{
    for (int index = getIndex(size); index < LIMIT; ++index)
    {
        for (void *p = seg_array[index]; p != NULL && GET_ALLOC(HDRP(p)) == 0; p = SUCC(p))
        {
            if (GET_SIZE(HDRP(p)) >= size)
                return p;
        }
    }
    return NULL;
}

static void place(void *bp, size_t asize)
{
    int orgsize = GET_SIZE(HDRP(bp));
    int bsize = orgsize - asize;

    // 일단 무조건 erase bp 는 호출해야 한다.
    erase(bp);
    if (bsize >= 2 * DSIZE)
    {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(bsize, 0));
        PUT(FTRP(bp), PACK(bsize, 0));
        insert(bp);
    }
    else
    {
        PUT(HDRP(bp), PACK(orgsize, 1));
        PUT(FTRP(bp), PACK(orgsize, 1));
    }
}

static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc)
        ;
    else if (prev_alloc && !next_alloc)
    {
        erase(NEXT_BLKP(bp));
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }
    else if (!prev_alloc && next_alloc)
    {
        erase(PREV_BLKP(bp));
        size += GET_SIZE(FTRP(PREV_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP((bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    else
    {
        erase(PREV_BLKP(bp));
        erase(NEXT_BLKP(bp));
        size += GET_SIZE(FTRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    // free 영역: bp hdr ~ bp의 ftr 까지
    // 해당 블록 SIZE 에 해당하는 index 에 insert
    insert(bp);
    return bp;
}

static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;
    // printf("extend heap\n");
    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words + 1) : words;
    size *= WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;
    /* Initailize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); // setting epilogue
    return coalesce(bp);
}

static void insert(void *bp)
{
    int size = GET_SIZE(HDRP(bp));
    int index = getIndex(size);
    void *p = NULL;
    void *q = seg_array[index];
    // 작은 순으로 삽입
    while (q != NULL && !GET_ALLOC(HDRP(q)) && (size > GET_SIZE(HDRP(q))))
    {
        p = q;
        q = SUCC(q);
    }
    // q's size >= size && size > p's size
    SUCC(bp) = q;
    PREV(bp) = p;
    PREV(q) = bp;
    // if p is not null
    if (p != NULL)
        SUCC(p) = bp;
    else // bp 가 새로운 루트
        seg_array[index] = bp;
}

static void erase(void *bp)
{
    // assert seg_array[index] != NULL ??
    int index = getIndex(GET_SIZE(HDRP(bp)));
    // printf("erase %d size this index %d\n", GET_SIZE(HDRP(bp)), index);
    if (PREV(bp) == NULL)
        seg_array[index] = SUCC(bp);
    else
        SUCC(PREV(bp)) = SUCC(bp);
    PREV(SUCC(bp)) = PREV(bp);
}