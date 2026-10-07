/*
 * main.c
 *
 * Copyright (C) 1976.12.27 TOP WAYE topwaye@hotmail.com
 *
 * basic human brain language logic shown by a recursive algorithm running on a basic CPU architecture.
 * give a few words to the algorithm, and it gives you an English sentence. this algorithm is called Klingon.
 *
 * two steps to speak English:
 * 
 * step one: spell out words that have meaning.
 * step two: add words that don't have meaning to change the pronunciation of certain words.
 *
 * the current algorithm shows how we construct English sentences in our brains. it combines the first and
 * second steps above: an arrangement of meaningful words, overlaid with meaningless words to change
 * the pronunciation of certain words. for example, 'play' is changed to 'to play', and 'be' is changed to 'to be',
 * i.e., insert a weak syllable to make the target word sound clearer in the middle of multiple words.
 *
 * another example: the subject and predicate naturally form a unit, and 'do' is overlaid onto this subject-predicate
 * unit to change the pronunciation, helping to clearly locate the subject-predicate unit in an English sentence.
 *
 * as for the word 'not', it represents a choice logic in our brain, meaning: not choosing. for instance, 'not him'
 * means not choosing him. and 'don't' is overlaid on a subject-predicate unit to express the opposite meaning,
 * that is, not choosing the meaning expressed by the current subject-predicate unit.
 *
 * be careful of how much scope 'do/don't' can cover in a sentence.
 *
 * the two steps of speaking English mentioned above are processed in our brains as follows:
 *
 * verb -> t'verb                                           // to verb
 * noun + verb -> d'( noun + verb ) -> d'noun + d'verb      // do ( noun + verb )
 * noun + adj -> b'( noun + adj ) -> b'noun + b'adj         // be ( noun + adj )
 * 
 * the following example sentences represent how our brain thinks:
 * 
 * you play what -> d'you play what                         // what do you play
 * you nice -> b'you nice                                   // are you nice
 * you nice -> can'you b'nice                               // can you be nice
 * nice -> can'b'nice                                       // can be nice
 * you work -> would'you have'been'working                  // would you have been working
 * you want love -> you want t'love                         // you want to love
 * you want loved -> you want t'b'loved                     // you want to be loved
 * you want him loved -> you want him t'b'loved             // you want him to be loved
 * 
 * know that all the thinking in our brains is just mathematical permutations and combinations.
 *
 * https://github.com/topwaye/klingon
 */

#include <stdio.h>

#define KLINGON_WORD_NUM            16
#define KLINGON_SEG_NUM              4
#define KLINGON_DIACRITIC_NUM        4

struct klingon_content;

struct klingon_word
{
    int c_selected; /* select or unselect this word */
    int d_selected; /* select or unselect the granularity */
    int d_forward; /* where diacritics are */
    char diacritic [ KLINGON_DIACRITIC_NUM ] [ KLINGON_WORD_NUM ]; /* step 2: add words that don't have meaning */
    char content [ KLINGON_WORD_NUM ]; /* step 1: spell out words that have meaning*/
    struct klingon_content * kcontent;
};

struct klingon_content
{
    int outer_start;
    struct klingon_word * start_point;
    struct klingon_word * segments [ KLINGON_SEG_NUM ];
    int start_len;
    int segment_lens [ KLINGON_SEG_NUM ];
};

static void print_word ( struct klingon_word * t )
{
    int i;

    if ( t -> d_forward )
    {
        if ( * t -> diacritic [ 0 ] )
                t -> d_selected ? printf ( "%s ", t -> diacritic [ 0 ] ) : printf( "%sn't ", t -> diacritic [ 0 ] );

        if ( * t -> diacritic [ 1 ] )
                t -> d_selected ? printf ( "%s ", t -> diacritic [ 1 ] ) : printf( "not %s ", t -> diacritic [ 1 ] );

        for ( i = 2; i < KLINGON_DIACRITIC_NUM; i ++ )
            if ( * t -> diacritic [ i ] )
                printf ( "%s ", t -> diacritic [ i ] );
    }

    if ( * t -> content )
        t -> c_selected ? printf ( "%s ", t -> content ) : printf ( "not %s ", t -> content );
    else
        t -> c_selected ? printf ( "" ) : printf ( "not " );

    if ( ! t -> d_forward )
    {
        if ( * t -> diacritic [ 0 ] )
                t -> d_selected ? printf ( "%s ", t -> diacritic [ 0 ] ) : printf( "%sn't ", t -> diacritic [ 0 ] );

        if ( * t -> diacritic [ 1 ] )
                t -> d_selected ? printf ( "%s ", t -> diacritic [ 1 ] ) : printf( "not %s ", t -> diacritic [ 1 ] );

        for ( i = 2; i < KLINGON_DIACRITIC_NUM; i ++ )
            if ( * t -> diacritic [ i ] )
                printf ( "%s ", t -> diacritic [ i ] );
    }
}

void conditioned_jump ( struct klingon_content * sentence )
{
    int i, j, m, n;
    struct klingon_word * p, * q, * t;

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

    for ( j = 0; j < KLINGON_SEG_NUM ; j ++ )
    {
        p = sentence -> segments [ j ];
        if ( p )
        {
            n = sentence -> segment_lens [ j ];
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
}

int klingon ( void )
{
    /* forming segments */

    struct klingon_word segment_0 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "you", NULL },
        { 1, 1, 1, "", "", "", "", "play", NULL },
        { 1, 1, 1, "", "", "", "", "what", NULL }
    };

    struct klingon_word segment_1 [ ] =
    {
        { 1, 0, 1, "do", "", "", "", "you", NULL },
        { 1, 1, 1, "", "", "", "", "play", NULL },
        { 1, 1, 1, "", "", "", "", "what", NULL }
    };

    struct klingon_word segment_2 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "at", NULL },
        { 1, 1, 1, "", "", "", "", "home", NULL }
    };

    struct klingon_word segment_3 [ ] =
    {
        { 1, 1, 1, "would", "", "", "", "you", NULL },
        { 1, 1, 1, "", "have", "been", "", "playing", NULL },
        { 1, 1, 1, "", "", "", "", "cards", NULL }
    };

    struct klingon_word segment_5 [ ] =
    {
        { 1, 1, 1, "do", "", "", "", "you", NULL },
        { 1, 1, 1, "", "", "", "", "want", NULL },
        { 1, 0, 1, "", "to", "be", "", "loved", NULL }
    };
    
    struct klingon_word segment_6 [ ] =
    {
        { 1, 0, 0, "are", "", "", "", "you", NULL },
        { 1, 1, 1, "", "", "", "", "nice", NULL }
    };

    struct klingon_word segment_7 [ ] =
    {
        { 1, 0, 1, "are", "", "", "", "you", NULL },
        { 1, 1, 1, "", "", "", "", "nice", NULL }
    };

    struct klingon_word segment_8 [ ] =
    {
        { 0, 1, 1, "", "", "", "", "bad", NULL }
    };

    struct klingon_word segment_9 [ ] =
    {
        { 1, 0, 1, "do", "", "be", "", "bad", NULL }
    };

    /* forming sentence 0 */

    struct klingon_word * start_point_0 = segment_1 + 2;
    
    struct klingon_content sentence_0 =
    {
        0,
        start_point_0,
        segment_1,
        segment_2,
        NULL,
        NULL,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 1 */

    struct klingon_content sentence_1 =
    {
        0,
        NULL,
        segment_3,
        segment_2,
        NULL,
        NULL,
        0,
        sizeof ( segment_3 ) / sizeof ( segment_3 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 3 */

    struct klingon_word * start_point_2 = segment_0 + 2;

    struct klingon_content sentence_2 =
    {
        1,
        start_point_2,
        segment_0,
        segment_2,
        NULL,
        NULL,
        1,
        sizeof ( segment_0 ) / sizeof ( segment_0 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0,
        0
    };

    struct klingon_word segment_4 [ ] =
    {
        { 1, 1, 1, "do", "", "", "", "you", NULL },
        { 1, 1, 1, "", "", "", "", "think", & sentence_2 },
    };

    struct klingon_content sentence_3 =
    {
        0,
        start_point_2,
        segment_4,
        NULL,
        NULL,
        NULL,
        1,
        sizeof ( segment_4 ) / sizeof ( segment_4 [ 0 ] ),
        0,
        0,
        0
    };

    /* forming sentence 4 */
    
    struct klingon_content sentence_4 =
    {
        0,
        NULL,
        segment_5,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( segment_5 ) / sizeof ( segment_5 [ 0 ] ),
        0,
        0,
        0
    };

    /* forming sentence 5 */
    
    struct klingon_content sentence_5 =
    {
        0,
        NULL,
        segment_6,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        0,
        0,
        0
    };

    /* forming sentence 6 */
    
    struct klingon_content sentence_6 =
    {
        0,
        NULL,
        segment_7,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( segment_7 ) / sizeof ( segment_7 [ 0 ] ),
        0,
        0,
        0
    };

    /* forming sentence 7 */
    
    struct klingon_content sentence_7 =
    {
        0,
        NULL,
        segment_8,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( segment_8 ) / sizeof ( segment_8 [ 0 ] ),
        0,
        0,
        0
    };

    /* forming sentence 8 */
    
    struct klingon_content sentence_8 =
    {
        0,
        NULL,
        segment_9,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( segment_9 ) / sizeof ( segment_9 [ 0 ] ),
        0,
        0,
        0
    };

    /* jump triggered by software with jmp-like instruction */

    conditioned_jump ( & sentence_0 ); printf ( "\n" );
    conditioned_jump ( & sentence_1 ); printf ( "\n" );
    conditioned_jump ( & sentence_3 ); printf ( "\n" );
    conditioned_jump ( & sentence_4 ); printf ( "\n" );
    conditioned_jump ( & sentence_5 ); printf ( "\n" );
    conditioned_jump ( & sentence_6 ); printf ( "\n" );
    conditioned_jump ( & sentence_7 ); printf ( "\n" );
    conditioned_jump ( & sentence_8 ); printf ( "\n" );

    return 1;
}

/* sequential execution with CPU head */

int main ( void )
{
    printf ( "************************************************************************************\n" );
    printf ( "KLINGON: This is how our brains construct English sentences\n" );
    printf ( "copyright (C) 2026.10.7 TOP WAYE topwaye@hotmail.com\n" );
    printf ( "\n" );
    printf ( "          O                         O          O\n" );
    printf ( "\n" );
    printf ( " --------------------        \\                        /        --------------------\n" );
    printf ( " |                            \\                      /         |                  |\n" );
    printf ( " |                             \\                    /          |                  |\n" );
    printf ( " |                              \\                  /           |                  |\n" );
    printf ( " |                               \\                /            |                  |\n" );
    printf ( " |                                \\              /             |                  |\n" );
    printf ( " --------------------              \\            /              |                  |\n" );
    printf ( "                    |               \\          /               |                  |\n" );
    printf ( "                    |                \\        /                |                  |\n" );
    printf ( "                    |                 \\      /                 |                  |\n" );
    printf ( "                    |                  \\    /                  |                  |\n" );
    printf ( "                    |                   \\  /                   |                  |\n" );
    printf ( " --------------------                    \\/                    --------------------\n" );
    printf ( "\n" );
    printf ( "************************************************************************************\n" );

    return klingon ( );
}
