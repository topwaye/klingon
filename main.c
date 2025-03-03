/*
 * main.c
 *
 * Copyright (C) 2025.3.1 TOP WAYE topwaye@hotmail.com
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

struct klingon_bind
{
    int selected;
    char content [ KLINGON_WORD_LENGTH ];
    struct klingon_content * kcontent;
    struct klingon_word * start_point;
    struct klingon_word * subject;
    struct klingon_word * predicate;
};

struct klingon_content
{
    struct klingon_word * start_point;
    struct klingon_bind * ring;
    struct klingon_word * primary_segment;
    struct klingon_word * secondary_segment;
    int primary_len;
    int secondary_len;
};

/* 
 * jump from main
 * triggered either by sofeware with jmp instruction, or by hardware without jmp instruction
 */

void conditioned_jump ( struct klingon_content * sentence )
{
    int i, n;
    struct klingon_word * p, * q, * t;
    struct klingon_bind * r;

    if ( ! sentence ) /* patch!!! */
        return;

    q = sentence -> start_point;
    if ( q )
        q -> selected ? printf( "%s ", q -> content )
                      : printf( "not %s ", q -> content );
    
    r = sentence -> ring;
    if ( r )
    {
        p = r -> subject;
        if ( r -> start_point != r -> subject )
        {
            if ( * r -> content )
                r -> selected ? printf ( "%s ", r -> content )
                              : printf ( "%sn't ", r -> content );
            conditioned_jump ( r -> kcontent );

            if ( * p -> content )
                p -> selected ? printf ( "%s ", p -> content )
                              : printf ( "not %s ", p -> content );
            conditioned_jump ( p -> kcontent );
        }
        else
        {
            if ( * p -> content )
                p -> selected ? printf ( "%s ", p -> content )
                              : printf ( "not %s ", p -> content );
            conditioned_jump ( p -> kcontent );
            
            if ( * r -> content )
                r -> selected ? printf ( "%s ", r -> content )
                              : printf ( "%sn't ", r -> content );
            conditioned_jump ( r -> kcontent );
        }

        p = r -> predicate;
        if ( * p -> content )
            p -> selected ? printf ( "%s ", p -> content )
                          : printf ( "not %s ", p -> content );
    }

    p = sentence -> primary_segment;
    if ( p )
    {
        n = sentence -> primary_len;
        for ( i = 1; i < n; i ++ ) /* NOT = 0 */
        {
            t = p + i;
            if ( t != q )
            {
                if ( * t -> content )
                    t -> selected ? printf ( "%s ", t -> content )
                                  : printf ( "not %s ", t -> content );
                conditioned_jump ( t -> kcontent );
            }
        }
    }

    p = sentence -> secondary_segment;
    if ( p )
    {
        n = sentence -> secondary_len;
        for ( i = 0; i < n; i ++ )
        {
            t = p + i;
            if ( t != q )
            {
                if ( * t -> content )
                    t -> selected ? printf ( "%s ", t -> content )
                                  : printf ( "not %s ", t -> content );
                conditioned_jump ( t -> kcontent );
            }
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

    struct klingon_word subject_1 = { 1, "you", NULL };

    /* forming sentence 1 */

    struct klingon_bind ring_1 = { 0, "do", NULL, NULL, & subject_1, & segment_1 [ 0 ] };

    struct klingon_word * start_point_1 = & segment_1 [ 1 ];

    struct klingon_content sentence_1 =
    {
        start_point_1,
        & ring_1,
        segment_1,
        segment_2,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 2 */
    
    struct klingon_bind ring_2 = { 0, "are", NULL, NULL, & subject_1, & segment_2 [ 0 ] };
    
    struct klingon_word * start_point_2 = & segment_3 [ 0 ];

    struct klingon_content sentence_2 =
    {
        start_point_2,
        & ring_2,
        segment_2,
        segment_3,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        sizeof ( segment_3 ) / sizeof ( segment_3 [ 0 ] )
    };

    /* forming sentence 3 */

    struct klingon_bind ring_3 = { 1, "are", NULL, & subject_1, & subject_1, & segment_2 [ 0 ] };

    struct klingon_content sentence_3 =
    {
        NULL,
        & ring_3,
        segment_2,
        NULL,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0
    };

    /* forming sentence 5 */

    struct klingon_bind ring_4 = { 0, "do", NULL, NULL, & subject_1, & segment_4 [ 0 ] };

    struct klingon_content sentence_4 =
    {
        NULL,
        & ring_4,
        segment_4,
        NULL,
        sizeof ( segment_4 ) / sizeof ( segment_4 [ 0 ] ),
        0
    };

    struct klingon_bind ring_5 = { 1, "", & sentence_4, NULL, & subject_1, & segment_1 [ 0 ] };

    struct klingon_word * start_point_5 = & segment_1 [ 1 ];

    struct klingon_content sentence_5 =
    {
        start_point_5,
        & ring_5,
        segment_1,
        NULL,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        0
    };

    /* forming sentence 7 */

    struct klingon_bind ring_6 = { 1, "", NULL, & subject_1, & subject_1, & segment_1 [ 0 ] };

    struct klingon_word * start_point_6 = & segment_1 [ 1 ];

    struct klingon_content sentence_6 =
    {
        start_point_6,
        & ring_6,
        segment_1,
        NULL,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        0
    };

    struct klingon_word subject_7 = { 1, "", & sentence_6 };

    struct klingon_bind ring_7 = { 1, "is", NULL, & subject_7, & subject_7, & segment_5 [ 0 ] };
 
    struct klingon_content sentence_7 =
    {
        NULL,
        & ring_7,
        segment_5,
        NULL,
        sizeof ( segment_5 ) / sizeof ( segment_5 [ 0 ] ),
        0
    };

    /* forming sentence 8 */

    struct klingon_bind ring_8 = { 1, "do", NULL, NULL, & subject_1, & segment_6 [ 0 ] };

    struct klingon_content sentence_8 =
    {
        NULL,
        & ring_8,
        segment_6,
        segment_2,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 9 */

    struct klingon_bind ring_9 = { 1, "do", NULL, & subject_1, & subject_1, & segment_6 [ 0 ] };
    
    struct klingon_content sentence_9 =
    {
        NULL,
        & ring_9,
        segment_6,
        segment_2,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 10 */

    struct klingon_bind ring_10 = { 1, "", NULL, & subject_1, & subject_1, & segment_6 [ 0 ] };
   
    struct klingon_content sentence_10 =
    {
        NULL,
        & ring_10,
        segment_6,
        segment_2,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] )
    };

    /* forming sentence 12 */

    struct klingon_bind ring_11 = { 0, "did", NULL, & subject_1, & subject_1, & segment_1 [ 0 ] };

    struct klingon_word * start_point_11 = & segment_1 [ 1 ];

    struct klingon_content sentence_11 =
    {
        start_point_11,
        & ring_11,
        segment_1,
        NULL,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        0
    };

    struct klingon_word segment_7 [ ] =
    {
        { 1, "play", NULL },
        { 1, "", & sentence_11 }
    };

    struct klingon_bind ring_12 = { 1, "", NULL, & subject_1, & subject_1, & segment_7 [ 0 ] };
    
    struct klingon_content sentence_12 =
    {
        NULL,
        & ring_12,
        segment_7,
        NULL,
        sizeof ( segment_7 ) / sizeof ( segment_7 [ 0 ] ),
        0
    };

    /* forming sentence 13 */

    struct klingon_bind ring_13 = { 1, "", NULL, & subject_1, & subject_1, & segment_6 [ 0 ] };

    struct klingon_word * start_point_13 = & segment_6 [ 1 ];

    struct klingon_content sentence_13 =
    {
        start_point_13,
        & ring_13,
        segment_6,
        NULL,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        0
    };

    /* forming sentence 15 */

    struct klingon_bind ring_14 = { 1, "", NULL, & subject_1, & subject_1, & segment_8 [ 0 ] };

    struct klingon_word * start_point_14 = & segment_8 [ 1 ];

    struct klingon_content sentence_14 =
    {
        start_point_14,
        & ring_14,
        segment_8,
        NULL,
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
        sizeof ( segment_9 ) / sizeof ( segment_9 [ 0 ] ),
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

    return 0;
}
