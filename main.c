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
 * a subject to these verb-object phrases, that is, bind a subject to the verb to form a subject-verb unit, also known as an instance
 * of that verb.
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
#include <assert.h>

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

struct klingon_content          /* bind a subject to instantiate a verb, using the distributive law of syllables */
{
    int outer_object;
    struct klingon_word * object;
    struct klingon_word * segments [ KLINGON_SEG_NUM ];
    int object_len;
    int segment_lens [ KLINGON_SEG_NUM ];
};

const char * FMT_NEWLINE     = "\n";
const char * FMT_STR_SPACE   = "%s ";                               /* print a word followed by a space */
const char * FMT_STR_NT      = "%sn't ";                            /* print word + n't + space */
const char * FMT_NOT_S       = "not %s ";                           /* print 'not ' before word */
const char * FMT_NOT         = "not ";                              /* literal 'not ' (no format args) */

void klingon_print_diacritics ( struct klingon_word * t )
{
    int i;

    assert ( t );
    for ( i = 0; i < KLINGON_DIACRITIC_NUM; i ++ )
    {
        if ( ! * t -> diacritic [ i ] )
            continue;

        if ( ! t -> d_selected )
        {
            switch ( i )
            {
            case 0 : printf ( FMT_STR_NT, t -> diacritic [ i ] ); continue;
            case 1 : printf ( FMT_NOT_S, t -> diacritic [ i ] ); continue;
            }
        }
        printf ( FMT_STR_SPACE, t -> diacritic [ i ] );
    }
}

void klingon_print ( struct klingon_word * t )
{
    if ( ! t )
    {
        printf ( FMT_NEWLINE );
        return;
    }

    if ( t -> d_in_front )
        klingon_print_diacritics ( t );

        if ( * t -> content )
        {
            if ( ! t -> c_selected )
                printf ( FMT_NOT_S, t -> content );
            else
                printf ( FMT_STR_SPACE, t -> content );
        }
        else
        {
            if ( ! t -> c_selected )
                printf ( FMT_NOT );
        }

    if ( ! t -> d_in_front )
        klingon_print_diacritics ( t );
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
            assert ( m > 0 );
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
                        assert ( q );
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

int klingon_instantiate ( void )
{
    /* forming subjects */

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

    /* forming segments */

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

    /* outputting sentences */

    klingon_jump ( 0, & sentence_1 );
    klingon_jump ( 0, & sentence_2 );
    klingon_jump ( 0, & sentence_4 );
    klingon_jump ( 0, & sentence_5 );
    klingon_jump ( 0, & sentence_6 );
    klingon_jump ( 0, & sentence_7 );
    klingon_jump ( 0, & sentence_8 );

    return 0;
}

int main ( void )
{
    printf ( "********************************************************************************************\n" );
    printf ( "An English formula about how our brains construct sentences, called Klingon, is shown below:\n" );
    printf ( "\n" );
    printf ( "V + O --> '(SV) + O   # bind a subject to instantiate a verb\n" );
    printf ( "                      # using the distributive law of syllables\n" );
    printf ( "\n" );
    printf ( " S  represents a subject.\n" );
    printf ( "'() represents a unit that is overlaid with meaningless syllables.\n" );
    printf ( " V  represents a verb, preposition, adjective, or noun.\n" );
    printf ( " O  represents an object.\n" );
    printf ( "\n" );
    printf ( "Copyright (C) 2026.10.12 TOP WAYE topwaye@hotmail.com\n" );
    printf ( "********************************************************************************************\n" );

    return klingon_instantiate ( );
}
