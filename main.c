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
 * the current algorithm shows how we construct English sentences in our brains. it combines the first and second steps above:
 * an arrangement of meaningful words, overlaid with meaningless words to change the pronunciation of certain words. for example,
 * 'play' is changed to 'to play', and 'be' is changed to 'to be', i.e., insert a weak syllable to make the target word sound clearer
 * in the middle of multiple words.
 *
 * another example: the subject and predicate naturally form a unit, and 'do' is overlaid onto this subject-predicate unit to change
 * the pronunciation, helping to clearly locate the subject-predicate unit in an English sentence.
 *
 * as for the word 'not', it represents a choice logic in our brain, meaning: not choosing. for instance, 'not him' means not choosing
 * him. and 'don't' is overlaid on a subject-predicate unit to express the opposite meaning, that is, not choosing the meaning expressed
 * by the current subject-predicate unit.
 *
 * be careful of how much scope 'do/don't' can cover in a sentence: one unit.
 *
 * being able to be clearly spoken and clearly heard was the top priority when English was invented in ancient times. that's why it was
 * necessary to change the pronunciation of certain words by adding meaningless syllables.
 *
 * in ancient times, there were no subjects, only verb-object phrases. in modern times, when constructing sentences, we need to assign
 * a subject to these verb-object phrases, that is, bind a subject to the verb to form a subject-verb unit.
 *
 * the language formula for English is as follows:
 *
 * V + O --> '(SV) + O
 *
 *  S  represents a subject.
 * '() represents a unit that is overlaid with meaningless syllables.
 *  V  represents a verb, preposition, adjective, or noun.
 *  O  represents an object.
 *
 * because the scope of 'do/don't' always covers a subject-verb unit, the distributive law of syllables is as follows:
 *
 * (S'V) == ('SV) == ('S'V) == '(S'V) == '(SV)
 *
 * here are example sentences applying the above formula:
 *
 * 1. who are you ?
 *
 *    who --> '( you who )
 *
 * 2. what do you think you play ?
 *
 *    think; play + what --> '( you think ); '( you play ) + what
 *
 * 3. don't you want me to play with him ?
 *
 *    want + me; play; with + him --> '( you want ) + me; 'play; with + him
 *
 * 4. don't be bad.
 *
 *    bad --> ''bad
 *
 * 5. my love shall in my verse ever live young.
 *
 *    in + my verse; ever live + young; --> '( my love [ in + my verse ] ever live ) + young
 *
 * know that all the thinking in our brains is just mathematical permutations and combinations.
 *
 * https://github.com/topwaye/klingon
 */

#include <stdio.h>
#include <stdarg.h>

#define KLINGON_WORD_NUM            16
#define KLINGON_SEG_NUM              4
#define KLINGON_DIACRITIC_NUM        4

struct klingon_content;

struct klingon_word
{
    int d_selected;                                                 /* select or unselect the unit */
    int d_in_front;                                                 /* where diacritics are */
    int c_selected;                                                 /* select or unselect the word */
    char diacritic [ KLINGON_DIACRITIC_NUM ] [ KLINGON_WORD_NUM ];  /* step 2: add words that don't have meaning */
    char content [ KLINGON_WORD_NUM ];                              /* step 1: spell out words that have meaning */
    struct klingon_content * k_content;
};

struct klingon_content                                              /* bind a subject using the distributive law of syllables */
{
    int outer_object;
    struct klingon_word * object;
    struct klingon_word * segments [ KLINGON_SEG_NUM ];
    int object_len;
    int segment_lens [ KLINGON_SEG_NUM ];
};

const char * fmt [ ] = { "\n", "%s ", "", "%sn't ", "not %s ", "not " };

int print ( const char * fmt, ... );

void klingon_print ( struct klingon_word * t )
{
    int i;

    if ( ! t )
    {
        print ( fmt [ 0 ] );
        return;
    }

    if ( t -> d_in_front )
    {
        if ( * t -> diacritic [ 0 ] )
                t -> d_selected ? print ( fmt [ 1 ], t -> diacritic [ 0 ] ) : print ( fmt [ 3 ], t -> diacritic [ 0 ] );

        if ( * t -> diacritic [ 1 ] )
                t -> d_selected ? print ( fmt [ 1 ], t -> diacritic [ 1 ] ) : print ( fmt [ 4 ], t -> diacritic [ 1 ] );

        for ( i = 2; i < KLINGON_DIACRITIC_NUM; i ++ )
            if ( * t -> diacritic [ i ] )
                print ( fmt [ 1 ], t -> diacritic [ i ] );
    }

    if ( * t -> content )
        t -> c_selected ? print ( fmt [ 1 ], t -> content ) : print ( fmt [ 4 ], t -> content );
    else
        t -> c_selected ? print ( fmt [ 2 ] ) : print ( fmt [ 5 ] );

    if ( ! t -> d_in_front )
    {
        if ( * t -> diacritic [ 0 ] )
                t -> d_selected ? print ( fmt [ 1 ], t -> diacritic [ 0 ] ) : print ( fmt [ 3 ], t -> diacritic [ 0 ] );

        if ( * t -> diacritic [ 1 ] )
                t -> d_selected ? print ( fmt [ 1 ], t -> diacritic [ 1 ] ) : print ( fmt [ 4 ], t -> diacritic [ 1 ] );

        for ( i = 2; i < KLINGON_DIACRITIC_NUM; i ++ )
            if ( * t -> diacritic [ i ] )
                print ( fmt [ 1 ], t -> diacritic [ i ] );
    }
}

void klingon_jump ( int depth, struct klingon_content * sentence )
{
    int i, j, m, n;
    struct klingon_word * p, * q, * t;

    if ( sentence )
    {
        q = sentence -> object;
        if ( q )
        {
            m = sentence -> object_len;
            if ( ! sentence -> outer_object )
            {
                i = 0;
                while ( i < m )
                {
                    t = q + i;
                    klingon_print ( t );
                    klingon_jump ( depth + 1, t -> k_content );
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
                    klingon_print ( t );
                    klingon_jump ( depth + 1, t -> k_content );
                    i ++;
                }
            }
        }

        if ( ! depth )
            klingon_print ( NULL );
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
        { 0, 0, 1, "are", "", "", "", "you", NULL }
    };

    struct klingon_word subject_3 [ ] =
    {
        { 1, 1, 1, "do", "", "", "", "you", NULL }
    };

    struct klingon_word subject_4 [ ] =
    {
        { 1, 1, 1, "would", "", "", "", "you", NULL }
    };

    struct klingon_word segment_1 [ ] =
    {
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
        { 1, 1, 1, "", "have", "been", "", "playing", NULL },
        { 1, 1, 1, "", "", "", "", "cards", NULL }
    };

    struct klingon_word segment_5 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "want", NULL },
        { 0, 1, 1, "", "to", "be", "", "loved", NULL }
    };

    struct klingon_word segment_6 [ ] =
    {
        { 1, 1, 0, "", "", "", "", "bad", NULL }
    };

    struct klingon_word segment_7 [ ] =
    {
        { 0, 1, 1, "do", "", "be", "", "bad", NULL }
    };

    /* forming sentence 1 */

    struct klingon_word * object_1 = segment_1 + 1;

    struct klingon_content sentence_1 =
    {
        0,
        object_1,
        subject_3,
        segment_1,
        segment_2,
        NULL,
        1,
        sizeof ( subject_3 ) / sizeof ( subject_3 [ 0 ] ),
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0
    };

    /* forming sentence 2 */

    struct klingon_content sentence_2 =
    {
        0,
        NULL,
        subject_4,
        segment_3,
        segment_2,
        NULL,
        0,
        sizeof ( subject_4 ) / sizeof ( subject_4 [ 0 ] ),
        sizeof ( segment_3 ) / sizeof ( segment_3 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0
    };

    /* forming sentence 4 */

    struct klingon_word * object_3 = segment_1 + 1;

    struct klingon_content sentence_3 =
    {
        1,
        object_3,
        subject_1,
        segment_1,
        segment_2,
        NULL,
        1,
        sizeof ( subject_1 ) / sizeof ( subject_1 [ 0 ] ),
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0
    };

    struct klingon_word segment_4 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "think", & sentence_3 }
    };

    struct klingon_content sentence_4 =
    {
        0,
        object_3,
        subject_3,
        segment_4,
        NULL,
        NULL,
        1,
        sizeof ( subject_3 ) / sizeof ( subject_3 [ 0 ] ),
        sizeof ( segment_4 ) / sizeof ( segment_4 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 5 */
    
    struct klingon_content sentence_5 =
    {
        0,
        NULL,
        subject_3,
        segment_5,
        NULL,
        NULL,
        0,
        sizeof ( subject_3 ) / sizeof ( subject_3 [ 0 ] ),
        sizeof ( segment_5 ) / sizeof ( segment_5 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 6 */
    
    struct klingon_content sentence_6 =
    {
        0,
        NULL,
        subject_2,
        segment_2,
        NULL,
        NULL,
        0,
        sizeof ( subject_2 ) / sizeof ( subject_2 [ 0 ] ),
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 7 */
    
    struct klingon_content sentence_7 =
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

    /* forming sentence 8 */
    
    struct klingon_content sentence_8 =
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

    klingon_jump ( 0, & sentence_1 );
    klingon_jump ( 0, & sentence_2 );
    klingon_jump ( 0, & sentence_4 );
    klingon_jump ( 0, & sentence_5 );
    klingon_jump ( 0, & sentence_6 );
    klingon_jump ( 0, & sentence_7 );
    klingon_jump ( 0, & sentence_8 );

    return 1;
}

int main ( void )
{
    print ( "********************************************************************************************\n" );
    print ( "An English formula about how our brains construct sentences, called Klingon, is shown below:\n" );
    print ( "\n" );
    print ( "V + O --> '(SV) + O\n" );
    print ( "\n" );
    print ( " S  represents a subject.\n" );
    print ( "'() represents a unit that is overlaid with meaningless syllables.\n" );
    print ( " V  represents a verb, preposition, adjective, or noun.\n" );
    print ( " O  represents an object.\n" );
    print ( "\n" );
    print ( "Copyright (C) 2026.10.12 TOP WAYE topwaye@hotmail.com\n" );
    print ( "********************************************************************************************\n" );

    return klingon ( );
}

/*
 * simple replacement for C's print supporting only %s and %%.
 * outputs directly using putchar without building a large intermediate buffer.
 * limitations: only %s (string) and %% (literal percent) are specially handled.
 */
int print ( const char * fmt, ... )
{
    va_list ap;
    int n;
    const char * p;

    if ( ! fmt )
        return 0;

    va_start ( ap, fmt );

    n = 0;
    p = fmt;
    while ( * p )
    {
        if ( * p == '%' )
        {
            p ++;
            if ( * p == '%' )
            {
                putchar ( '%' );
                n ++;
                p ++;
            }
            else if ( * p == 's' )
            {
                const char * s = va_arg ( ap, const char * );
                if ( ! s )
                    s = "(null)";
                while ( * s )
                {
                    putchar ( * s );
                    n ++;
                    s ++;
                }
                p ++;
            }
            else
            {
                /* unsupported specifier: klingon_print percent and the specifier literally */
                putchar ( '%' );
                n ++;
                if ( * p )
                {
                    putchar ( * p );
                    n ++;
                    p ++;
                }
            }
        }
        else
        {
            putchar ( * p );
            n ++;
            p ++;
        }
    }

    va_end ( ap );

    return n;
}
