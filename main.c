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
 * be careful of how much scope 'do/don't' can cover in a sentence. furthermore, in our brain, there exists
 * a mathematical equivalence substitution that helps us understand the meaning of a sentence. a sentence is naturally
 * like a ping-pong paddle-shaped container, with the subject at the handle and the verb-object at the paddle.
 *
 * 'don't' is applied to the whole paddle, which is equivalent to 'don't' being applied to the handle, which is equivalent
 * to 'don't' being applied to the paddle. it expresses 'not on the paddle side'.
 *
 * 'not' is applied to a single point on the paddle, expressing 'not at this point'.
 *
 * the main idea for understanding the meaning of a sentence is separating the subject and the predicate.
 * note: the starting point of thinking is always unconditionally on the subject.
 * note: everything other than the subject is called the predicate.
 *
 * being able to be clearly spoken and clearly heard was the top priority when English was invented in ancient times.
 * that's why it was necessary to change the pronunciation of certain words by adding meaningless syllables.
 *
 * the language formula for English is as follows:
 *
 * { 'S | 'V O } J
 *
 * 'S represents the subject that is overlaid with meaningless syllables.
 * 'V represents the verb, preposition, or adjective that is overlaid with meaningless syllables.
 *  O represents an object.
 *  | represents a separator.
 * {} represents a container.
 *  J represents a hook that can take the object out of the container.
 *
 * note: rather than thinking of the formula as a ping-pong paddle, think of it as a fish that's being hooked.
 *
 * here are example sentences applying the above formula:
 *
 * 1. who are you ?
 *
 * { 'you |   }
 *          J
 *
 * 2. who do you think you are ?
 *
 * { 'you | think { 'you |   } } 
 *                         J
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
    int outer_bait;
    struct klingon_word * bait;
    struct klingon_word * segments [ KLINGON_SEG_NUM ];
    int bait_len;
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

    q = sentence -> bait;
    if ( q )
    {
        m = sentence -> bait_len;
        if ( ! sentence -> outer_bait )
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

    struct klingon_word subject_1 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "you", NULL }
    };

    struct klingon_word subject_2 [ ] =
    {
        { 1, 0, 0, "are", "", "", "", "you", NULL }
    };

    struct klingon_word subject_3 [ ] =
    {
        { 1, 1, 1, "do", "", "", "", "you", NULL }
    };

    struct klingon_word subject_4 [ ] =
    {
        { 1, 1, 1, "would", "", "", "", "you", NULL }
    };

    struct klingon_word predicate_1 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "play", NULL },
        { 1, 1, 1, "", "", "", "", "what", NULL }
    };

    struct klingon_word predicate_2 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "at", NULL },
        { 1, 1, 1, "", "", "", "", "home", NULL }
    };

    struct klingon_word predicate_3 [ ] =
    {
        { 1, 1, 1, "", "have", "been", "", "playing", NULL },
        { 1, 1, 1, "", "", "", "", "cards", NULL }
    };

    struct klingon_word predicate_5 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "want", NULL },
        { 1, 0, 1, "", "to", "be", "", "loved", NULL }
    };

    struct klingon_word predicate_6 [ ] =
    {
        { 0, 1, 1, "", "", "", "", "bad", NULL }
    };

    struct klingon_word predicate_7 [ ] =
    {
        { 1, 0, 1, "do", "", "be", "", "bad", NULL }
    };

    /* forming sentence 1 */

    struct klingon_word * bait_1 = predicate_1 + 1;
    
    struct klingon_content sentence_1 =
    {
        0,
        bait_1,
        subject_3,
        predicate_1,
        predicate_2,
        NULL,
        1,
        sizeof ( subject_3 ) / sizeof ( subject_3 [ 0 ] ),
        sizeof ( predicate_1 ) / sizeof ( predicate_1 [ 0 ] ),
        sizeof ( predicate_2 ) / sizeof ( predicate_2 [ 0 ] ),
        0
    };

    /* forming sentence 2 */

    struct klingon_content sentence_2 =
    {
        0,
        NULL,
        subject_4,
        predicate_3,
        predicate_2,
        NULL,
        0,
        sizeof ( subject_4 ) / sizeof ( subject_4 [ 0 ] ),
        sizeof ( predicate_3 ) / sizeof ( predicate_3 [ 0 ] ),
        sizeof ( predicate_2 ) / sizeof ( predicate_2 [ 0 ] ),
        0
    };

    /* forming sentence 4 */

    struct klingon_word * bait_3 = predicate_1 + 1;

    struct klingon_content sentence_3 =
    {
        1,
        bait_3,
        subject_1,
        predicate_1,
        predicate_2,
        NULL,
        1,
        sizeof ( subject_1 ) / sizeof ( subject_1 [ 0 ] ),
        sizeof ( predicate_1 ) / sizeof ( predicate_1 [ 0 ] ),
        sizeof ( predicate_2 ) / sizeof ( predicate_2 [ 0 ] ),
        0
    };

    struct klingon_word predicate_4 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "think", & sentence_3 }
    };

    struct klingon_content sentence_4 =
    {
        0,
        bait_3,
        subject_3,
        predicate_4,
        NULL,
        NULL,
        1,
        sizeof ( subject_3 ) / sizeof ( subject_3 [ 0 ] ),
        sizeof ( predicate_4 ) / sizeof ( predicate_4 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 5 */
    
    struct klingon_content sentence_5 =
    {
        0,
        NULL,
        subject_3,
        predicate_5,
        NULL,
        NULL,
        0,
        sizeof ( subject_3 ) / sizeof ( subject_3 [ 0 ] ),
        sizeof ( predicate_5 ) / sizeof ( predicate_5 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 6 */
    
    struct klingon_content sentence_6 =
    {
        0,
        NULL,
        subject_2,
        predicate_2,
        NULL,
        NULL,
        0,
        sizeof ( subject_2 ) / sizeof ( subject_2 [ 0 ] ),
        sizeof ( predicate_2 ) / sizeof ( predicate_2 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 7 */
    
    struct klingon_content sentence_7 =
    {
        0,
        NULL,
        predicate_6,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( predicate_6 ) / sizeof ( predicate_6 [ 0 ] ),
        0,
        0,
        0
    };

    /* forming sentence 8 */
    
    struct klingon_content sentence_8 =
    {
        0,
        NULL,
        predicate_7,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( predicate_7 ) / sizeof ( predicate_7 [ 0 ] ),
        0,
        0,
        0
    };

    /* jump triggered by software with jmp-like instruction */

    conditioned_jump ( & sentence_1 ); printf ( "\n" );
    conditioned_jump ( & sentence_2 ); printf ( "\n" );
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
    printf ( "{ 'S | 'V O } J\n" );
    printf ( "\n" );
    printf ( "************************************************************************************\n" );

    return klingon ( );
}
