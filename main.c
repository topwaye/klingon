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
 * 1. spell out words that have meaning.
 * 2. add words that don't have meaning to change the pronunciation of certain words.
 *
 * the current algorithm shows how we construct English sentences in our brains. it combines the first and second steps above:
 * an arrangement of meaningful words, overlaid with meaningless words to change the pronunciation of certain words. for example,
 * 'play' is changed to 'to play', and 'be' is changed to 'to be', i.e., insert a break syllable as a breakpoint to make the target word
 * sound clearer in the middle of multiple words.
 *
 * another example: the subject and predicate naturally form a unit, and 'do' is overlaid onto this subject-predicate unit to change
 * the pronunciation, helping to clearly locate the subject-predicate unit in an English sentence.
 *
 * as for the word 'not', it represents a choice logic in our brain, meaning: not choosing. for instance, 'not him' means not choosing
 * him. and 'don't' is overlaid on a subject-predicate unit to express the opposite meaning, that is, not choosing the meaning expressed
 * by the current subject-predicate unit.
 *
 * be careful of how much scope 'do/don't' can cover in a sentence: one unit, or even one sentence, not just one subject alone.
 *
 * being able to be clearly spoken and clearly heard was the top priority when English was invented in ancient times. that's why it was
 * necessary to change the pronunciation of certain words by adding break syllables.
 *
 * in ancient times, there were no subjects, only verb-object phrases. in modern times, when constructing sentences, we need to assign
 * a subject to these verb-object phrases, i.e., bind a subject to the verb to form a subject-verb unit.
 *
 * the language formula for English is as follows:
 *
 * V / O => '(SV) / O
 *
 *  S  represents a subject.
 * '() represents a unit that is overlaid with break syllables.
 *  V  represents a verb, preposition, adjective, or noun.
 *  /  represents a semicolon in mathematics.
 *  O  represents an object.
 *
 * because the scope of 'do/don't' always covers a subject-verb unit, the distributive law of break syllables is as follows:
 *
 * (S'V) == ('SV) == ('S'V) == '(S'V) == '(SV)
 *
 * the distributive law of break syllables reveals a truth: always merge a subject and a verb first, then merge break syllables.
 * note that the distributive law of break syllables is applicable in cases where a subject is a logical subject.
 *
 * here are example sentences applying the above formula:
 *
 * 1. who are you ?
 *    who => '( you who )
 *
 * 2. what do you think you play ?
 *    think; play / what => '( you think ); '( you play ) / what
 *
 * 3. don't you want me to play with him ?
 *    want / me; play; with / him => '( you want ) / me; 'play; with / him
 *
 * 4. don't be bad.
 *    bad => ''bad
 *
 * 5. my love shall in my verse ever live young.
 *    in / my verse; ever live / young; => '( my love [ in / my verse ] ever live ) / young
 *
 * in summary, how our brains construct English sentences:
 *
 * 0. no subjects, only verb-object phrases.
 * 1. bind a subject to a verb to form a subject-verb unit.
 * 2. add a break syllable whose scope always covers a subject-verb unit.
 *
 * know that your thinking should always start with a declarative sentence and end with an interrogative sentence.
 * know that your thinking should always focus on the subject-verb unit behind a break syllable, not on the break syllable itself.
 * know that all the thinking in our brains is just mathematical permutations and combinations.
 *
 * https://github.com/topwaye/klingon
 */

#include <stdio.h>
#include <assert.h>

#define EN_WORD_NUM             16
#define EN_SEG_NUM              4
#define EN_BREAKPOINT_NUM       4

struct en_content;

struct en_word
{
    int b_selected; /* select or unselect the unit */
    int b_in_front; /* where breakpoints are */
    int c_selected; /* select or unselect the word */
    char breakpoint [ EN_BREAKPOINT_NUM ] [ EN_WORD_NUM ];
    char content [ EN_WORD_NUM ];
    struct en_content * sen_content;
};

struct en_content
{
    int outer_object;
    struct en_word * object;
    struct en_word * segments [ EN_SEG_NUM ];
    int object_len;
    int segment_lens [ EN_SEG_NUM ];
};

void print_breakpoint ( int in_front, struct en_word * t );
void print_content ( struct en_word * t );
void print_newline ( struct en_word * t );

void print ( struct en_word * t )
{
    if ( ! t )
    {
        print_newline ( t );
        return;
    }

    print_breakpoint ( 1, t );
    print_content ( t );
    print_breakpoint ( 0, t );
}

void jump ( int depth, struct en_content * sentence )
{
    int i, j, m, n;
    struct en_word * p, * q, * t;

    if ( sentence )
    {
        q = sentence -> object;
        if ( q )
        {
            assert ( sentence -> object_len > 0 );
            m = sentence -> object_len;
            if ( ! sentence -> outer_object )
            {
                i = 0;
                while ( i < m )
                {
                    t = q + i;
                    print ( t );
                    jump ( depth + 1, t -> sen_content );
                    i ++;
                }
            }
        }

        for ( j = 0; j < EN_SEG_NUM ; j ++ )
        {
            p = sentence -> segments [ j ];
            if ( p )
            {
                assert ( sentence -> segment_lens [ j ] > 0 );
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
                    print ( t );
                    jump ( depth + 1, t -> sen_content );
                    i ++;
                }
            }
        }

        if ( ! depth )
            print ( NULL );
    }
}

int bind ( void )
{
    /* forming segments */

    struct en_word segment_1 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "play", NULL },
        { 1, 1, 1, "", "", "", "", "what", NULL }
    };

    struct en_word segment_2 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "at", NULL },
        { 1, 1, 1, "", "", "", "", "home", NULL }
    };

    struct en_word segment_3 [ ] =
    {
        { 1, 1, 1, "", "have", "been", "", "playing", NULL },
        { 1, 1, 1, "", "", "", "", "cards", NULL }
    };

    struct en_word segment_5 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "want", NULL },
        { 0, 1, 1, "", "to", "be", "", "loved", NULL }
    };

    struct en_word segment_6 [ ] =
    {
        { 1, 1, 0, "", "", "", "", "bad", NULL }
    };

    struct en_word segment_7 [ ] =
    {
        { 0, 1, 1, "do", "", "be", "", "bad", NULL }
    };

    /* forming subjects */

    struct en_word subject_1 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "you", NULL }
    };

    struct en_word subject_2 [ ] =
    {
        { 0, 0, 1, "are", "", "", "", "you", NULL }
    };

    struct en_word subject_3 [ ] =
    {
        { 1, 1, 1, "do", "", "", "", "you", NULL }
    };

    struct en_word subject_4 [ ] =
    {
        { 1, 1, 1, "would", "", "", "", "you", NULL }
    };

    /* forming sentence 1 */

    struct en_word * object_1 = segment_1 + 1;

    struct en_content sentence_1 =
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

    struct en_content sentence_2 =
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

    struct en_word * object_3 = segment_1 + 1;

    struct en_content sentence_3 =
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

    struct en_word segment_4 [ ] =
    {
        { 1, 1, 1, "", "", "", "", "think", & sentence_3 }
    };

    struct en_content sentence_4 =
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
    
    struct en_content sentence_5 =
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
    
    struct en_content sentence_6 =
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
    
    struct en_content sentence_7 =
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
    
    struct en_content sentence_8 =
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

    jump ( 0, & sentence_1 );
    jump ( 0, & sentence_2 );
    jump ( 0, & sentence_4 );
    jump ( 0, & sentence_5 );
    jump ( 0, & sentence_6 );
    jump ( 0, & sentence_7 );
    jump ( 0, & sentence_8 );

    return 0;
}

int main ( void )
{
    printf ( "************************************************************************************************************************\n" );
    printf ( "an English formula about how our brains construct sentences, called Klingon, is shown below:\n" );
    printf ( "\n" );
    printf ( " V      '(SV)\n" );
    printf ( "--- => -------\n" );
    printf ( " O        O\n" );
    printf ( "\n" );
    printf ( " S  represents a subject.\n" );
    printf ( "'() represents a unit that is overlaid with break syllables.\n" );
    printf ( " V  represents a verb, preposition, adjective, or noun.\n" );
    printf ( " /  represents a semicolon in mathematics.\n" );
    printf ( " O  represents an object.\n" );
    printf ( "\n" );
    printf ( "# no subjects, only verb-object segments.\n" );
    printf ( "# bind a subject to a verb to form a subject-verb unit.\n" );
    printf ( "# add a break syllable whose scope always covers a subject-verb unit.\n" );
    printf ( "\n" );
    printf ( "# your thinking should always start with a declarative sentence and end with an interrogative sentence.\n" );
    printf ( "# your thinking should always focus on the subject-verb unit behind a break syllable, not on the break syllable itself.\n" );
    printf ( "\n" );
    printf ( "copyright (C) 2026.10.16 TOP WAYE topwaye@hotmail.com\n" );
    printf ( "************************************************************************************************************************\n" );

    return bind ( );
}

const char * FMT_NEWLINE    = "\n";
const char * FMT_STR_SPACE  = "%s ";
const char * FMT_STR_NT     = "%sn't ";
const char * FMT_NOT_S      = "not %s ";
const char * FMT_NOT        = "not ";

void print_breakpoint ( int in_front, struct en_word * t )
{
    int i;

    assert ( t );
    if ( t -> b_in_front != in_front )
        return;

    for ( i = 0; i < EN_BREAKPOINT_NUM; i ++ )
    {
        if ( ! * t -> breakpoint [ i ] )
            continue;

        if ( ! t -> b_selected )
        {
            switch ( i )
            {
            case 0 : printf ( FMT_STR_NT, t -> breakpoint [ i ] ); continue;
            case 1 : printf ( FMT_NOT_S, t -> breakpoint [ i ] ); continue;
            }
        }
        printf ( FMT_STR_SPACE, t -> breakpoint [ i ] );
    }
}

void print_content ( struct en_word * t )
{
    assert ( t );
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
}

void print_newline ( struct en_word * t )
{
    assert ( ! t );
    printf ( FMT_NEWLINE );
}
