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
    int selected;
    char content [ KLINGON_WORD_LENGTH ];
    struct klingon_content * kcontent;
};

struct klingon_granularity
{
    int selected;
    char acontent [ KLINGON_WORD_LENGTH ];
    char bcontent [ KLINGON_WORD_LENGTH ];
    char ccontent [ KLINGON_WORD_LENGTH ];
    char dcontent [ KLINGON_WORD_LENGTH ];
    struct klingon_content * kcontent;
    struct klingon_word * start_point;
    struct klingon_word * subject;
    struct klingon_word * predicate;
    int subject_len;
    int predicate_len;
};

struct klingon_content
{
    struct klingon_word * start_point;
    struct klingon_granularity * ring;
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
        i = 0;
        while ( i < m )
        {
            t = q + i;
            if ( * t -> content )
                t -> selected ? printf ( "%s ", t -> content )
                              : printf ( "not %s ", t -> content );
            conditioned_jump ( t -> kcontent );
            i ++;
        }
    }
    
    r = sentence -> ring;
    if ( r )
    {
        p = r -> subject;
        n = r -> subject_len;
        if ( r -> start_point != r -> subject )
        {
            if ( * r -> acontent )
                r -> selected ? printf ( "%s ", r -> acontent )
                              : printf ( "%sn't ", r -> acontent );
            conditioned_jump ( r -> kcontent );

            if ( p )
            {
                i = 0;
                while ( i < n )
                {
                    t = p + i;
                    if ( * t -> content )
                        t -> selected ? printf ( "%s ", t -> content )
                                      : printf ( "not %s ", t -> content );
                    conditioned_jump ( t -> kcontent );
                    i ++;
                }
            }

            if ( * r -> acontent && * r -> bcontent )
                printf ( "%s ", r -> bcontent );
            if ( * r -> acontent && * r -> ccontent )
                printf ( "%s ", r -> ccontent );
            if ( * r -> acontent && * r -> dcontent )
                printf ( "%s ", r -> dcontent );
        }
        else
        {
            if ( p )
            {
                i = 0;
                while ( i < n )
                {
                    t = p + i;
                    if ( * t -> content )
                        t -> selected ? printf ( "%s ", t -> content )
                                      : printf ( "not %s ", t -> content );
                    conditioned_jump ( t -> kcontent );
                    i ++;
                }
            }

            if ( * r -> acontent )
                r -> selected ? printf ( "%s ", r -> acontent )
                              : printf ( "%sn't ", r -> acontent );
            conditioned_jump ( r -> kcontent );

            if ( * r -> acontent && * r -> bcontent )
                printf ( "%s ", r -> bcontent );
            if ( * r -> acontent && * r -> ccontent )
                printf ( "%s ", r -> ccontent );
            if ( * r -> acontent && * r -> dcontent )
                printf ( "%s ", r -> dcontent );
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
            if ( * t -> content )
                t -> selected ? printf ( "%s ", t -> content )
                              : printf ( "not %s ", t -> content );
            conditioned_jump ( t -> kcontent );
            i ++;
        }
    }

    p = sentence -> primary_segment;
    if ( r ) /* NOT p */
    {
        n = sentence -> primary_len;
        /* NOT i = 0 */
        while ( i < n )
        {
            t = p + i;
            if ( t == q )
            {
                i += m;
                continue;
            }
            if ( * t -> content )
                t -> selected ? printf ( "%s ", t -> content )
                              : printf ( "not %s ", t -> content );
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
            if ( * t -> content )
                t -> selected ? printf ( "%s ", t -> content )
                              : printf ( "not %s ", t -> content );
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

    struct klingon_word subject_1 [ ] =
    {
        { 1, "you", NULL }
    };

    /* forming sentence 1 */

    struct klingon_granularity ring_1 = { 0, "do", "", "", "", NULL, NULL, subject_1, segment_1, 1, 1 };

    struct klingon_word * start_point_1 = segment_1 + 1;

    struct klingon_content sentence_1 =
    {
        start_point_1,
        & ring_1,
        segment_1,
        segment_2,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 2 */
    
    struct klingon_granularity ring_2 = { 0, "are", "", "", "", NULL, NULL, subject_1, segment_2, 1, 1 };
    
    struct klingon_word * start_point_2 = segment_3;

    struct klingon_content sentence_2 =
    {
        start_point_2,
        & ring_2,
        segment_2,
        segment_3,
        1,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        sizeof ( segment_3 ) / sizeof ( segment_3 [ 0 ] )
    };

    /* forming sentence 3 */

    struct klingon_granularity ring_3 = { 1, "are", "", "", "", NULL, subject_1, subject_1, segment_2, 1, 1 };

    struct klingon_content sentence_3 =
    {
        NULL,
        & ring_3,
        segment_2,
        NULL,
        0,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0
    };

    /* forming sentence 5 */

    struct klingon_granularity ring_4 = { 0, "do", "", "", "", NULL, NULL, subject_1, segment_4, 1, 1 };

    struct klingon_content sentence_4 =
    {
        NULL,
        & ring_4,
        segment_4,
        NULL,
        0,
        sizeof ( segment_4 ) / sizeof ( segment_4 [ 0 ] ),
        0
    };

    struct klingon_granularity ring_5 = { 1, "", "", "", "", & sentence_4, NULL, subject_1, segment_1, 1, 1 };

    struct klingon_word * start_point_5 = segment_1 + 1;

    struct klingon_content sentence_5 =
    {
        start_point_5,
        & ring_5,
        segment_1,
        NULL,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        0
    };

    /* forming sentence 7 */

    struct klingon_granularity ring_6 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_1, 1, 1 };

    struct klingon_word * start_point_6 = segment_1 + 1;

    struct klingon_content sentence_6 =
    {
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

    struct klingon_granularity ring_7 = { 1, "is", "", "", "", NULL, subject_7, subject_7, segment_5, 1, 1 };
 
    struct klingon_content sentence_7 =
    {
        NULL,
        & ring_7,
        segment_5,
        NULL,
        0,
        sizeof ( segment_5 ) / sizeof ( segment_5 [ 0 ] ),
        0
    };

    /* forming sentence 8 */

    struct klingon_granularity ring_8 = { 1, "do", "", "", "", NULL, NULL, subject_1, segment_6, 1, 1 };

    struct klingon_content sentence_8 =
    {
        NULL,
        & ring_8,
        segment_6,
        segment_2,
        0,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 9 */

    struct klingon_granularity ring_9 = { 1, "do", "", "", "", NULL, subject_1, subject_1, segment_6, 1, 1 };
    
    struct klingon_content sentence_9 =
    {
        NULL,
        & ring_9,
        segment_6,
        segment_2,
        0,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 10 */

    struct klingon_granularity ring_10 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_6, 1, 1 };
   
    struct klingon_content sentence_10 =
    {
        NULL,
        & ring_10,
        segment_6,
        segment_2,
        0,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 12 */

    struct klingon_granularity ring_11 = { 0, "did", "", "", "", NULL, subject_1, subject_1, segment_1, 1, 1 };

    struct klingon_word * start_point_11 = segment_1 + 1;

    struct klingon_content sentence_11 =
    {
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

    struct klingon_granularity ring_12 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_7, 1, 1 };
    
    struct klingon_content sentence_12 =
    {
        NULL,
        & ring_12,
        segment_7,
        NULL,
        0,
        sizeof ( segment_7 ) / sizeof ( segment_7 [ 0 ] ),
        0
    };

    /* forming sentence 13 */

    struct klingon_granularity ring_13 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_6, 1, 1 };

    struct klingon_word * start_point_13 = segment_6 + 1;

    struct klingon_content sentence_13 =
    {
        start_point_13,
        & ring_13,
        segment_6,
        NULL,
        1,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        0
    };

    /* forming sentence 15 */

    struct klingon_granularity ring_14 = { 1, "", "", "", "", NULL, subject_1, subject_1, segment_8, 1, 1 };

    struct klingon_word * start_point_14 = segment_8 + 1;

    struct klingon_content sentence_14 =
    {
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
        NULL,
        NULL,
        NULL,
        segment_9,
        0,
        0,
        sizeof ( segment_9 ) / sizeof ( segment_9 [ 0 ] ),
    };

    /* forming sentence 16 */

    struct klingon_granularity ring_16 = { 1, "do", "", "", "", NULL, NULL, subject_1, segment_6, 1, 1 };

    struct klingon_word * start_point_16 = segment_10;

    struct klingon_content sentence_16 =
    {
        start_point_16,
        & ring_16,
        segment_6,
        segment_10,
        3,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_10 ) / sizeof ( segment_10 [ 0 ] )
    };

    /* forming sentence 17 */

    struct klingon_granularity ring_17 = { 1, "are", "", "", "", NULL, NULL, subject_1, segment_10, 1, 3 };
        
    struct klingon_word * start_point_17 = segment_10;
    
    struct klingon_content sentence_17 =
    {
        start_point_17,
        & ring_17,
        segment_10,
        NULL,
        3,
        sizeof ( segment_10 ) / sizeof ( segment_10 [ 0 ] ),
        0
    };

    /* forming sentence 18 */

    struct klingon_granularity ring_18 = { 1, "are", "", "", "", NULL, NULL, subject_1, segment_10, 1, 1 };
        
    struct klingon_word * start_point_18 = segment_10 + 1;
    
    struct klingon_content sentence_18 =
    {
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

    struct klingon_granularity ring_19 = { 1, "do", "", "", "", NULL, NULL, subject_19, segment_1, 3, 1 };

    struct klingon_word * start_point_19 = segment_1 + 1;

    struct klingon_content sentence_19 =
    {
        start_point_19,
        & ring_19,
        segment_1,
        segment_2,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 20 */

    struct klingon_granularity ring_20 = { 0, "do", "", "", "", NULL, NULL, NULL, segment_6, 1, 1 };

    struct klingon_content sentence_20 =
    {
        NULL,
        & ring_20,
        segment_6,
        segment_2,
        0,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 21 */

    struct klingon_granularity ring_21 = { 1, "would", "have", "", "", NULL, NULL, subject_1, segment_11, 1, 1 };

    struct klingon_content sentence_21 =
    {
        NULL,
        & ring_21,
        segment_11,
        NULL,
        0,
        sizeof ( segment_11 ) / sizeof ( segment_11 [ 0 ] ),
        0
    };

    /* forming sentence 22 */

    struct klingon_granularity ring_22 = { 1, "were", "", "", "", NULL, subject_1, subject_1, segment_2, 1, 1 };

    struct klingon_word * start_point_22 = segment_12;

    struct klingon_content sentence_22 =
    {
        start_point_22,
        & ring_22,
        segment_2,
        segment_12,
        1,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        sizeof ( segment_12 ) / sizeof ( segment_12 [ 0 ] )
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

    return 0;
}
