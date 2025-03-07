/*
 * main.c
 *
 * Copyright (C) 1976.12.27 TOP WAYE topwaye@hotmail.com
 *
 * basic klingon language logic shown by basic CPU framework logic
 *
 * https://github.com/topwaye/klingon
 */

#include <stdio.h>

#define KLINGON_WORD_LENGTH     16

struct klingon_content;

struct klingon_word
{
    int selected; /* select or unselect this word */
    char content [ KLINGON_WORD_LENGTH ];
    struct klingon_content * kcontent;
};

struct klingon_granularity
{
    int selected; /* select or unselect this granularity */
    char acontent [ KLINGON_WORD_LENGTH ];
    char bcontent [ KLINGON_WORD_LENGTH ];
    char ccontent [ KLINGON_WORD_LENGTH ];
    char dcontent [ KLINGON_WORD_LENGTH ];
    struct klingon_content * kcontent;
    struct klingon_word * start_point;
    struct klingon_word * subject;
    struct klingon_word * predicate;
    struct klingon_word * breaker; /* break this granularity */
    int subject_len;
    int predicate_len;
    int breaker_len;
};

struct klingon_content
{
    int outer_start;
    struct klingon_word * start_point;
    struct klingon_granularity * primary_ring;
    struct klingon_word * primary_segment;
    struct klingon_word * secondary_segment;
    int start_len;
    int primary_len;
    int secondary_len;
};

/* 
 * jump from main
 * triggered either by sofeware with jmp instruction, or by hardware without jmp instruction
 */

static void print_word ( struct klingon_word * t )
{
    if ( * t -> content )
        t -> selected ? printf ( "%s ", t -> content ) : printf ( "not %s ", t -> content );
    else
        t -> selected ? printf ( "" ) : printf ( "not " );
}

static void print_granularity_binder_1 ( struct klingon_granularity * r )
{
    if ( * r -> acontent )
        r -> selected ? printf ( "%s ", r -> acontent ) : printf ( "%sn't ", r -> acontent );
    else
        r -> selected ? printf ( "" ) : printf ( "not " );
}

static void print_granularity_binder_2 ( struct klingon_granularity * r )
{
    if ( * r -> bcontent )
        printf ( "%s ", r -> bcontent );
}

static void print_granularity_binder_3 ( struct klingon_granularity * r )
{
    if ( * r -> ccontent )
        printf ( "%s ", r -> ccontent );
}

static void print_granularity_binder_4 ( struct klingon_granularity * r )
{
    if ( * r -> dcontent )
        printf ( "%s ", r -> dcontent );
}

void conditioned_jump ( struct klingon_content * sentence )
{
    int i, m, n;
    struct klingon_word * p, * q, * t;
    struct klingon_granularity * r;

    if ( ! sentence ) /* patch!!! */
        return;

    q = sentence -> start_point;
    if ( q )
    {
        m = sentence -> start_len;
        if ( ! sentence -> outer_start )
        {
            i = 0;
            while ( i < m )
            {
                t = q + i;
                print_word ( t );
                conditioned_jump ( t -> kcontent );
                i ++;
            }
        }
    }
    
    r = sentence -> primary_ring;
    if ( r )
    {
        p = r -> subject;
        n = r -> subject_len;
        if ( r -> start_point != r -> subject )
        {
            print_granularity_binder_1 ( r );
            conditioned_jump ( r -> kcontent );

            if ( p )
            {
                i = 0;
                while ( i < n )
                {
                    t = p + i;
                    print_word ( t );
                    conditioned_jump ( t -> kcontent );
                    i ++;
                }
            }

            print_granularity_binder_2 ( r );
            print_granularity_binder_3 ( r );
            print_granularity_binder_4 ( r );
        }
        else
        {
            if ( p )
            {
                i = 0;
                while ( i < n )
                {
                    t = p + i;
                    print_word ( t );
                    conditioned_jump ( t -> kcontent );
                    i ++;
                }
            }

            print_granularity_binder_1 ( r );
            conditioned_jump ( r -> kcontent );

            print_granularity_binder_2 ( r );
            print_granularity_binder_3 ( r );
            print_granularity_binder_4 ( r );
        }

        p = r -> breaker;
        n = r -> breaker_len;
        i = 0;
        while ( i < n )
        {
            t = p + i;
            if ( t == q )
            {
                i += m;
                continue;
            }
            print_word ( t );
            conditioned_jump ( t -> kcontent );
            i ++;
        }

        p = r -> predicate;
        n = r -> predicate_len;
        i = 0;
        while ( i < n )
        {
            t = p + i;
            if ( t == q )
            {
                i += m;
                continue;
            }
            print_word ( t );
            conditioned_jump ( t -> kcontent );
            i ++;
        }
    }

    p = sentence -> primary_segment;
    if ( p )
    {
        n = sentence -> primary_len;
        if ( ! r ) /* patch!!! */
            i = 0;
        while ( i < n )
        {
            t = p + i;
            if ( t == q )
            {
                i += m;
                continue;
            }
            print_word ( t );
            conditioned_jump ( t -> kcontent );
            i ++;
        }
    }

    p = sentence -> secondary_segment;
    if ( p )
    {
        n = sentence -> secondary_len;    
        i = 0;
        while ( i < n )
        {
            t = p + i;
            if ( t == q )
            {
                i += m;
                continue;
            }
            print_word ( t );
            conditioned_jump ( t -> kcontent );
            i ++;
        }
    }
}

/* sequential execution with CPU head */

int main ( void )
{
    /* forming segments */

    struct klingon_word segment_1 [ ] =
    {
        { 1, "play", NULL },
        { 1, "what", NULL }
    };

    struct klingon_word segment_2 [ ] =
    {
        { 1, "at", NULL },
        { 1, "home", NULL }
    };

    struct klingon_word segment_3 [ ] =
    {
        { 1, "why", NULL }
    };

    struct klingon_word segment_4 [ ] =
    {
        { 1, "think", NULL }
    };
    
    struct klingon_word segment_5 [ ] =
    {
        { 0, "cards", NULL }
    };

    struct klingon_word segment_6 [ ] =
    {
        { 1, "play", NULL },
        { 1, "cards", NULL }
    };

    struct klingon_word segment_8 [ ] =
    {
        { 1, "play", NULL },
        { 1, "that", NULL }
    };

    struct klingon_word segment_10 [ ] =
    {
        { 1, "at", NULL },
        { 1, "which", NULL },
        { 1, "place", NULL },
        { 1, "-", NULL },
        { 1, "school", NULL },
        { 1, "or", NULL },
        { 1, "home", NULL }
    };

    struct klingon_word segment_11 [ ] =
    {
        { 1, "played", NULL },
        { 1, "cards", NULL }
    };

    struct klingon_word segment_12 [ ] =
    {
        { 1, "if", NULL }
    };

    struct klingon_word segment_13 [ ] =
    {
        { 1, "want", NULL },
        { 1, "to", NULL },
        { 1, "play", NULL },
        { 1, "what", NULL }
    };

    struct klingon_word segment_15 [ ] =
    {
        { 1, "home", NULL }
    };

    struct klingon_word segment_16 [ ] =
    {
        { 1, "where", NULL }
    };

    struct klingon_word segment_19 [ ] =
    {
        { 1, "fun", NULL }
    };

    struct klingon_word segment_21 [ ] =
    {
        { 1, "to", NULL },
        { 1, "play", NULL },
        { 1, "cards", NULL }
    };

    struct klingon_word subject_1 [ ] =
    {
        { 1, "you", NULL }
    };

    struct klingon_word subject_38 [ ] =
    {
        { 1, "it", NULL }
    };

    /* forming sentence 1 */

    struct klingon_granularity ring_1 = { 0, "do", "", "", "", NULL, NULL, subject_1, segment_1, NULL, 1, 1, 0 };

    struct klingon_word * start_point_1 = segment_1 + 1;

    struct klingon_content sentence_1 =
    {
        0,
        start_point_1,
        & ring_1,
        segment_1,
        segment_2,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 2 */
    
    struct klingon_granularity ring_2 = { 0, "are", "", "", "", NULL, NULL, subject_1, segment_2, NULL, 1, 1, 0 };
    
    struct klingon_word * start_point_2 = segment_3;

    struct klingon_content sentence_2 =
    {
        0,
        start_point_2,
        & ring_2,
        segment_2,
        segment_3,
        1,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        sizeof ( segment_3 ) / sizeof ( segment_3 [ 0 ] )
    };

    /* forming sentence 3 */

    struct klingon_granularity ring_3 = { 1, "are", "", "", "", NULL, subject_1, subject_1, segment_2, NULL, 1, 1, 0 };

    struct klingon_content sentence_3 =
    {
        0,
        NULL,
        & ring_3,
        segment_2,
        NULL,
        0,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0
    };

    /* forming sentence 5 */

    struct klingon_granularity ring_4 = { 0, "do", "", "", "", NULL, NULL, subject_1, segment_4, NULL, 1, 1, 0 };

    struct klingon_content sentence_4 =
    {
        0,
        NULL,
        & ring_4,
        segment_4,
        NULL,
        0,
        sizeof ( segment_4 ) / sizeof ( segment_4 [ 0 ] ),
        0
    };

    struct klingon_granularity ring_5 = { 1, "", "", "", "", & sentence_4, NULL, subject_1, segment_1, NULL, 1, 1, 0 };

    struct klingon_word * start_point_5 = segment_1 + 1;

    struct klingon_content sentence_5 =
    {
        0,
        start_point_5,
        & ring_5,
        segment_1,
        NULL,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        0
    };

    /* forming sentence 7 */

    struct klingon_granularity ring_6 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_1, NULL, 1, 1, 0 };

    struct klingon_word * start_point_6 = segment_1 + 1;

    struct klingon_content sentence_6 =
    {
        0,
        start_point_6,
        & ring_6,
        segment_1,
        NULL,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        0
    };

    struct klingon_word subject_7 [ ] =
    {
        { 1, "", & sentence_6 }
    };

    struct klingon_granularity ring_7 = { 1, "is", "", "", "", NULL, subject_7, subject_7, segment_5, NULL, 1, 1, 0 };
 
    struct klingon_content sentence_7 =
    {
        0,
        NULL,
        & ring_7,
        segment_5,
        NULL,
        0,
        sizeof ( segment_5 ) / sizeof ( segment_5 [ 0 ] ),
        0
    };

    /* forming sentence 8 */

    struct klingon_granularity ring_8 = { 1, "do", "", "", "", NULL, NULL, subject_1, segment_6, NULL, 1, 1, 0 };

    struct klingon_content sentence_8 =
    {
        0,
        NULL,
        & ring_8,
        segment_6,
        segment_2,
        0,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 9 */

    struct klingon_granularity ring_9 = { 1, "do", "", "", "", NULL, subject_1, subject_1, segment_6, NULL, 1, 1, 0 };
    
    struct klingon_content sentence_9 =
    {
        0,
        NULL,
        & ring_9,
        segment_6,
        segment_2,
        0,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 10 */

    struct klingon_granularity ring_10 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_6, NULL, 1, 1, 0 };
   
    struct klingon_content sentence_10 =
    {
        0,
        NULL,
        & ring_10,
        segment_6,
        segment_2,
        0,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 12 */

    struct klingon_granularity ring_11 = { 0, "did", "", "", "", NULL, subject_1, subject_1, segment_1, NULL, 1, 1, 0 };

    struct klingon_word * start_point_11 = segment_1 + 1;

    struct klingon_content sentence_11 =
    {
        0,
        start_point_11,
        & ring_11,
        segment_1,
        NULL,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        0
    };

    struct klingon_word segment_7 [ ] =
    {
        { 1, "play", NULL },
        { 1, "", & sentence_11 }
    };

    struct klingon_granularity ring_12 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_7, NULL, 1, 1, 0 };
    
    struct klingon_content sentence_12 =
    {
        0,
        NULL,
        & ring_12,
        segment_7,
        NULL,
        0,
        sizeof ( segment_7 ) / sizeof ( segment_7 [ 0 ] ),
        0
    };

    /* forming sentence 13 */

    struct klingon_granularity ring_13 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_6, NULL, 1, 1, 0 };

    struct klingon_word * start_point_13 = segment_6 + 1;

    struct klingon_content sentence_13 =
    {
        0,
        start_point_13,
        & ring_13,
        segment_6,
        NULL,
        1,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        0
    };

    /* forming sentence 15 */

    struct klingon_granularity ring_14 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_8, NULL, 1, 1, 0 };

    struct klingon_word * start_point_14 = segment_8 + 1;

    struct klingon_content sentence_14 =
    {
        0,
        start_point_14,
        & ring_14,
        segment_8,
        NULL,
        1,
        sizeof ( segment_8 ) / sizeof ( segment_8 [ 0 ] ),
        0
    };

    struct klingon_word segment_9 [ ] =
    {
        { 1, "cards", & sentence_14 }
    };

    struct klingon_content sentence_15 =
    {
        0,
        NULL,
        NULL,
        NULL,
        segment_9,
        0,
        0,
        sizeof ( segment_9 ) / sizeof ( segment_9 [ 0 ] ),
    };

    /* forming sentence 16 */

    struct klingon_granularity ring_16 = { 1, "do", "", "", "", NULL, NULL, subject_1, segment_6, NULL, 1, 1, 0 };

    struct klingon_word * start_point_16 = segment_10;

    struct klingon_content sentence_16 =
    {
        0,
        start_point_16,
        & ring_16,
        segment_6,
        segment_10,
        3,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_10 ) / sizeof ( segment_10 [ 0 ] )
    };

    /* forming sentence 17 */

    struct klingon_granularity ring_17 = { 1, "are", "", "", "", NULL, NULL, subject_1, segment_10, NULL, 1, 3, 0 };
        
    struct klingon_word * start_point_17 = segment_10;
    
    struct klingon_content sentence_17 =
    {
        0,
        start_point_17,
        & ring_17,
        segment_10,
        NULL,
        3,
        sizeof ( segment_10 ) / sizeof ( segment_10 [ 0 ] ),
        0
    };

    /* forming sentence 18 */

    struct klingon_granularity ring_18 = { 1, "are", "", "", "", NULL, NULL, subject_1, segment_10, NULL, 1, 1, 0 };
        
    struct klingon_word * start_point_18 = segment_10 + 1;
    
    struct klingon_content sentence_18 =
    {
        0,
        start_point_18,
        & ring_18,
        segment_10,
        NULL,
        2,
        sizeof ( segment_10 ) / sizeof ( segment_10 [ 0 ] ),
        0
    };

    /* forming sentence 19 */

    struct klingon_word subject_19 [ ] =
    {
        { 1, "tom", NULL },
        { 1, "and", NULL },
        { 1, "jerry", NULL }
    };

    struct klingon_granularity ring_19 = { 1, "do", "", "", "", NULL, NULL, subject_19, segment_1, NULL, 3, 1, 0 };

    struct klingon_word * start_point_19 = segment_1 + 1;

    struct klingon_content sentence_19 =
    {
        0,
        start_point_19,
        & ring_19,
        segment_1,
        segment_2,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 20 */

    struct klingon_granularity ring_20 = { 0, "do", "", "", "", NULL, NULL, NULL, segment_6, NULL, 1, 1, 0 };

    struct klingon_content sentence_20 =
    {
        0,
        NULL,
        & ring_20,
        segment_6,
        segment_2,
        0,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 21 */

    struct klingon_granularity ring_21 = { 1, "would", "have", "", "", NULL, NULL, subject_1, segment_11, NULL, 1, 1, 0 };

    struct klingon_content sentence_21 =
    {
        0,
        NULL,
        & ring_21,
        segment_11,
        NULL,
        0,
        sizeof ( segment_11 ) / sizeof ( segment_11 [ 0 ] ),
        0
    };

    /* forming sentence 22 */

    struct klingon_granularity ring_22 = { 1, "were", "", "", "", NULL, subject_1, subject_1, segment_2, NULL, 1, 1, 0 };

    struct klingon_word * start_point_22 = segment_12;

    struct klingon_content sentence_22 =
    {
        0,
        start_point_22,
        & ring_22,
        segment_2,
        segment_12,
        1,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        sizeof ( segment_12 ) / sizeof ( segment_12 [ 0 ] )
    };

    /* forming sentence 23 */

    struct klingon_granularity ring_23 = { 0, "do", "", "", "", NULL, NULL, subject_1, segment_1, segment_2, 1, 1, 2 };

    struct klingon_word* start_point_23 = segment_1 + 1;

    struct klingon_content sentence_23 =
    {
        0,
        start_point_23,
        & ring_23,
        segment_1,
        NULL,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        0
    };

    /* forming sentence 24 */

    struct klingon_granularity ring_24 = { 0, "do", "", "", "", NULL, NULL, subject_1, segment_13, NULL, 1, 1, 0 };

    struct klingon_word * start_point_24 = segment_13 + 3;

    struct klingon_content sentence_24 =
    {
        0,
        start_point_24,
        & ring_24,
        segment_13,
        segment_2,
        1,
        sizeof ( segment_13 ) / sizeof ( segment_13 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 30 */
    
    struct klingon_granularity ring_29 = { 1, "", "to", "be", "", NULL, NULL, NULL, segment_16, NULL, 1, 1, 0 };

    struct klingon_word * start_point_29 = segment_16;

    struct klingon_content sentence_29 =
    {
        1,
        start_point_29,
        & ring_29,
        segment_16,
        NULL,
        1,
        sizeof ( segment_16 ) / sizeof ( segment_16 [ 0 ] ),
        0
    };

    struct klingon_word segment_17 [ ] =
    {
        { 1, "want", NULL },
        { 1, "", & sentence_29 }
    };

    struct klingon_granularity ring_30 = { 1, "do", "", "", "", NULL, NULL, subject_1, segment_17, NULL, 1, 1, 0 };

    struct klingon_word * start_point_30 = segment_16;

    struct klingon_content sentence_30 =
    {
        0,
        start_point_30,
        & ring_30,
        segment_17,
        NULL,
        1,
        sizeof ( segment_17 ) / sizeof ( segment_17 [ 0 ] ),
        0
    };

    /* forming sentence 32 */
    
    struct klingon_granularity ring_31 = { 1, "", "to", "be", "", NULL, NULL, NULL, segment_15, NULL, 1, 1, 0 };

    struct klingon_content sentence_31 =
    {
        0,
        NULL,
        & ring_31,
        segment_15,
        NULL,
        0,
        sizeof ( segment_15 ) / sizeof ( segment_15 [ 0 ] ),
        0
    };

    struct klingon_word segment_18 [ ] =
    {
        { 1, "want", NULL },
        { 1, "", & sentence_31 }
    };

    struct klingon_granularity ring_32 = { 1, "do", "", "", "", NULL, NULL, subject_1, segment_18, NULL, 1, 1, 0 };

    struct klingon_content sentence_32 =
    {
        0,
        NULL,
        & ring_32,
        segment_18,
        NULL,
        0,
        sizeof ( segment_18 ) / sizeof ( segment_18 [ 0 ] ),
        0
    };
    
    /* forming sentence 33 */

    struct klingon_granularity ring_33 = { 1, "are", "going", "to", "be", NULL, NULL, subject_1, segment_15, NULL, 1, 1, 0 };

    struct klingon_content sentence_33 =
    {
        0,
        NULL,
        & ring_33,
        segment_15,
        NULL,
        0,
        sizeof ( segment_15 ) / sizeof ( segment_15 [ 0 ] ),
        0
    };

    /* forming sentence 35 */
    
    struct klingon_granularity ring_34 = { 0, "", "being", "", "", NULL, NULL, NULL, segment_15, NULL, 1, 1, 0 };

    struct klingon_content sentence_34 =
    {
        0,
        NULL,
        & ring_34,
        segment_15,
        NULL,
        0,
        sizeof ( segment_15 ) / sizeof ( segment_15 [ 0 ] ),
        0
    };

    struct klingon_word subject_35 [ ] =
    {
        { 0, "", & sentence_34 }
    };

    struct klingon_granularity ring_35 = { 1, "is", "", "", "", NULL, subject_35, subject_35, segment_2, NULL, 1, 1, 0 };

    struct klingon_content sentence_35 =
    {
        0,
        NULL,
        & ring_35,
        segment_2,
        NULL,
        0,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0
    };

    /* forming sentence 37 */

    struct klingon_granularity ring_36 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_6, NULL, 1, 1, 0 };

    struct klingon_content sentence_36 =
    {
        0,
        NULL,
        & ring_36,
        segment_6,
        segment_2,
        0,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    struct klingon_word subject_37 [ ] =
    {
        { 1, "that", & sentence_36 }
    };

    struct klingon_granularity ring_37 = { 1, "is", "", "", "", NULL, subject_37, subject_37, segment_19, NULL, 1, 1, 0 };

    struct klingon_content sentence_37 =
    {
        0,
        NULL,
        & ring_37,
        segment_19,
        NULL,
        0,
        sizeof ( segment_19 ) / sizeof ( segment_19 [ 0 ] ),
        0
    };

    /* forming sentence 38 */
    
    struct klingon_word segment_20 [ ] =
    {
        { 1, "that", & sentence_36 }
    };

    struct klingon_granularity ring_38 = { 1, "is", "", "", "", NULL, subject_38, subject_38, segment_19, NULL, 1, 1, 0 };

    struct klingon_content sentence_38 =
    {
        0,
        NULL,
        & ring_38,
        segment_19,
        segment_20,
        0,
        sizeof ( segment_19 ) / sizeof ( segment_19 [ 0 ] ),
        sizeof ( segment_20 ) / sizeof ( segment_20 [ 0 ] )
    };

    /* forming sentence 40 */

    struct klingon_content sentence_39 =
    {
        0,
        NULL,
        NULL,
        segment_21,
        segment_2,
        0,
        sizeof ( segment_21 ) / sizeof ( segment_21 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    struct klingon_word segment_22 [ ] =
    {
        { 1, "", & sentence_39 }
    };

    struct klingon_granularity ring_40 = { 1, "is", "", "", "", NULL, subject_38, subject_38, segment_19, NULL, 1, 1, 0 };

    struct klingon_content sentence_40 =
    {
        0,
        NULL,
        & ring_40,
        segment_19,
        segment_22,
        0,
        sizeof ( segment_19 ) / sizeof ( segment_19 [ 0 ] ),
        sizeof ( segment_22 ) / sizeof ( segment_22 [ 0 ] )
    };

    /* jump triggered by software with jmp-like instruction */

    conditioned_jump ( & sentence_1 ); printf ( "\n" );
    conditioned_jump ( & sentence_2 ); printf ( "\n" );
    conditioned_jump ( & sentence_3 ); printf ( "\n" );
    conditioned_jump ( & sentence_5 ); printf ( "\n" );
    conditioned_jump ( & sentence_7 ); printf ( "\n" );
    conditioned_jump ( & sentence_8 ); printf ( "\n" );
    conditioned_jump ( & sentence_9 ); printf ( "\n" );
    conditioned_jump ( & sentence_10 ); printf ( "\n" );
    conditioned_jump ( & sentence_12 ); printf ( "\n" );
    conditioned_jump ( & sentence_13 ); printf ( "\n" );
    conditioned_jump ( & sentence_15 ); printf ( "\n" );
    conditioned_jump ( & sentence_16 ); printf ( "\n" );
    conditioned_jump ( & sentence_17 ); printf ( "\n" );
    conditioned_jump ( & sentence_18 ); printf ( "\n" );
    conditioned_jump ( & sentence_19 ); printf ( "\n" );
    conditioned_jump ( & sentence_20 ); printf ( "\n" );
    conditioned_jump ( & sentence_21 );
    conditioned_jump ( & sentence_22 ); printf ( "\n" );
    conditioned_jump ( & sentence_23 ); printf ( "\n" );
    conditioned_jump ( & sentence_24 ); printf ( "\n" );
    conditioned_jump ( & sentence_30 ); printf ( "\n" );
    conditioned_jump ( & sentence_32 ); printf ( "\n" );
    conditioned_jump ( & sentence_33 ); printf ( "\n" );
    conditioned_jump ( & sentence_35 ); printf ( "\n" );
    conditioned_jump ( & sentence_37 ); printf ( "\n" );
    conditioned_jump ( & sentence_38 ); printf ( "\n" );
    conditioned_jump ( & sentence_40 ); printf ( "\n" );

    return 0;
}
