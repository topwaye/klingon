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

struct klingon_word
{
    int selected;
    char content [ KLINGON_WORD_LENGTH ];
};

struct klingon_bind
{
    int selected;
    char content [ KLINGON_WORD_LENGTH ];
    struct klingon_word * subject;
    struct klingon_word * predicate;
};

/* jump from main, triggered either by sofeware with jmp instruction, or by hardware without jmp instruction */

void conditioned_jump ( struct klingon_word * start_point,
                        struct klingon_bind * ring,
                        struct klingon_word * primary_segment, int primary_len,
                        struct klingon_word * secondary_segment, int secondary_len )
{
    int i;

    if ( start_point )
        printf ( "%s ", start_point -> content );

    if ( ring )
    {
        ring -> selected ? printf ( "%s ", ring -> content ) : printf ( "%sn't ", ring -> content );
        printf ( "%s ", ring -> subject -> content );
        printf ( "%s ", ring -> predicate -> content );
    }

    if ( primary_segment )
        for ( i = 1; i < primary_len; i ++ )
            if ( & primary_segment [ i ] != start_point )
                primary_segment [ i ] . selected ? printf ( "%s ", primary_segment [ i ] . content )
                                                 : printf ( "not %s ", primary_segment [ i ] . content );
    if ( secondary_segment )
        for ( i = 0; i < secondary_len; i ++ )
            secondary_segment [ i ] . selected ? printf ( "%s ", secondary_segment [ i ] . content )
                                               : printf ( "not %s ", secondary_segment [ i ] . content );

    printf ( "?\n" );
}

/* sequential execution with CPU head */

int main ( void )
{
    /* forming segments */

    struct klingon_word segment_1 [ ] =
    {
        { 1, "play" },
        { 1, "what" }
    };

    struct klingon_word segment_2 [ ] =
    {
        { 1, "at" },
        { 1, "home" }
    };

    struct klingon_word subject = { 1, "you" };

    /* forming sentence 1 */

    struct klingon_bind ring_1 = { 0, "do", & subject, & segment_1 [ 0 ] };

    struct klingon_word * start_point = & segment_1 [ 1 ];

    /* forming sentence 2 */

    struct klingon_bind ring_2 = { 0, "are", & subject, & segment_2 [ 0 ] };

    /* jump triggered by software with jmp-like instruction */

    conditioned_jump ( start_point,
                       & ring_1,
                       segment_1, sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
                       segment_2, sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ) );

    conditioned_jump ( NULL,
                       & ring_2,
                       segment_2, sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
                       NULL, 0 );

    return 0;
}
