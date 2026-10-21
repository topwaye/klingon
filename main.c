/*
 * main.c
 *
 * Copyright (C) 1976.12.27 TOP WAYE topwaye@hotmail.com
 *
 * basic human brain language logic shown by a recursive algorithm running on a basic CPU architecture.
 * give a few words to the algorithm, and it gives you an English sentence. this algorithm is called Klingon.
 *
 * the fish bubbling language model for English is as follows:
 *
 * a verb is a fish blowing bubbles. a bubble is a break syllable. a subject is inserted among bubbles.
 *
 * being able to be clearly spoken and clearly heard was the top priority when English was invented in ancient times. that's why
 * it was necessary to change the pronunciation of certain words by adding break syllables. for example, 'play' is changed to 'to play',
 * and 'be' is changed to 'to be', that is, insert a break syllable as a breakpoint to make the target word sound clearer in the middle
 * of multiple words.
 *
 * another example: 'do' is overlaid onto a subject to change pronunciation, helping to clearly locate the subject in a sentence.
 *
 * as for the word 'not', it represents a choice logic in our brain, meaning: not choosing. for instance, 'not him' means not choosing
 * him. and 'don't' is overlaid onto a subject to express the opposite meaning, that is, the subject does not choose the meaning
 * expressed by the predicate.
 *
 * in ancient times, there were no subjects, only verb-object phrases. in modern times, when constructing sentences, we need to add
 * a subject to these verb-object phrases.
 *
 * the language formula for English is as follows:
 *
 * '''V / O => 'S''V / O
 *
 *  S  represents a subject.
 *  V  represents a verb, preposition, adjective, or noun that is overlaid with break syllables, like 'do/don't'.
 *  /  represents a division slash in mathematics.
 *  O  represents an object.
 *
 * here are example sentences applying the above formula:
 *
 * 1. who are you ?
 *    'who => 'you who
 *
 * 2. what do you think you play ?
 *    'think; play / what => 'you think; you play / what
 *
 * 3. don't you want me to play with him ?
 *    'want / me; 'play; with / him => 'you want / me; 'play; with / him
 *
 * 4. my love shall in my verse ever live young.
 *    in / my verse; ever 'live / young; => 'my love [ in / my verse ] ever live / young
 *
 * in summary, how our brains construct English sentences:
 *
 * 1. no subjects, there are only verb-object phrases, where a verb is overlaid with break syllables, like 'do/don't'.
 * 2. insert a subject among the break syllables of the verb.
 *
 * know that all the thinking in our brains is just mathematical permutations and combinations.
 *
 * https://github.com/topwaye/klingon
 */

#include <stdio.h>
#include <assert.h>

#define EN_CHAR_NUM             16
#define EN_SEG_NUM              4

struct en_content;

struct en_word
{
    int selected;   /* select or unselect the word */
    int breakpoint; /* a breakpoint or not */
    char content [ EN_CHAR_NUM ];
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

void print_content ( struct en_word * t );
void print_newline ( struct en_word * t );

void print ( struct en_word * t )
{
    t ? print_content ( t ) : print_newline ( t );
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

int insert ( void )
{
    /* forming segments */

    struct en_word segment_1 [ ] =
    {
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "play", NULL },
        { 1, 0, "what", NULL }
    };

    struct en_word segment_2 [ ] =
    {
        { 1, 0, "", NULL },
        { 1, 1, "do", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "play", NULL },
        { 1, 0, "what", NULL }
    };

    struct en_word segment_3 [ ] =
    {
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "at", NULL },
        { 1, 0, "home", NULL }
    };

    struct en_word segment_4 [ ] =
    {
        { 1, 0, "", NULL },
        { 0, 1, "are", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "at", NULL },
        { 1, 0, "home", NULL }
    };

    struct en_word segment_5 [ ] =
    {
        { 1, 0, "", NULL },
        { 1, 1, "would", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "have", NULL },
        { 1, 1, "been", NULL },
        { 1, 0, "playing", NULL },
        { 1, 0, "cards", NULL }
    };

    struct en_word segment_7 [ ] =
    {
        { 1, 0, "", NULL },
        { 1, 1, "do", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "want", NULL },
        { 1, 0, "", NULL }
    };

    struct en_word segment_8 [ ] =
    {
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "", NULL },
        { 0, 0, "to", NULL },
        { 1, 1, "be", NULL },
        { 1, 0, "loved", NULL },
        { 1, 0, "", NULL }
    };

    struct en_word segment_9 [ ] =
    {
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 1, "", NULL },
        { 0, 0, "bad", NULL },
        { 1, 0, "", NULL }
    };

    struct en_word segment_10 [ ] =
    {
        { 1, 0, "", NULL },
        { 0, 1, "do", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 1, "be", NULL },
        { 1, 0, "bad", NULL },
        { 1, 0, "", NULL }
    };

    /* inserting subjects */

    segment_1 [ 0 ] = { 1, 0, "you", NULL };
    segment_2 [ 2 ] = { 1, 0, "you", NULL };
    segment_4 [ 0 ] = { 1, 0, "you", NULL };
    segment_5 [ 2 ] = { 1, 0, "you", NULL };
    segment_7 [ 2 ] = { 1, 0, "you", NULL };

    /* forming sentence 1 */

    struct en_word * object_1 = segment_2 + 6;

    struct en_content sentence_1 =
    {
        0,
        object_1,
        segment_2,
        segment_3,
        NULL,
        NULL,
        1,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        sizeof ( segment_3 ) / sizeof ( segment_3 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 2 */

    struct en_content sentence_2 =
    {
        0,
        NULL,
        segment_5,
        segment_3,
        NULL,
        NULL,
        0,
        sizeof ( segment_5 ) / sizeof ( segment_5 [ 0 ] ),
        sizeof ( segment_3 ) / sizeof ( segment_3 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 4 */

    struct en_word * object_3 = segment_1 + 6;

    struct en_content sentence_3 =
    {
        1,
        object_3,
        segment_1,
        segment_3,
        NULL,
        NULL,
        1,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        sizeof ( segment_3 ) / sizeof ( segment_3 [ 0 ] ),
        0,
        0
    };

    struct en_word segment_6 [ ] =
    {
        { 1, 0, "", NULL },
        { 1, 1, "do", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "think", NULL },
        { 1, 0, "", & sentence_3 }
    };

    segment_6 [ 2 ] = { 1, 0, "you", NULL };

    struct en_content sentence_4 =
    {
        0,
        object_3,
        segment_6,
        NULL,
        NULL,
        NULL,
        1,
        sizeof ( segment_6 ) / sizeof ( segment_6 [ 0 ] ),
        0,
        0,
        0
    };

    /* forming sentence 5 */
    
    struct en_content sentence_5 =
    {
        0,
        NULL,
        segment_7,
        segment_8,
        NULL,
        NULL,
        0,
        sizeof ( segment_7 ) / sizeof ( segment_7 [ 0 ] ),
        sizeof ( segment_8 ) / sizeof ( segment_8 [ 0 ] ),
        0,
        0
    };

    /* forming sentence 6 */
    
    struct en_content sentence_6 =
    {
        0,
        NULL,
        segment_4,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( segment_4 ) / sizeof ( segment_4 [ 0 ] ),
        0,
        0,
        0
    };

    /* forming sentence 7 */
    
    struct en_content sentence_7 =
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

    /* forming sentence 8 */
    
    struct en_content sentence_8 =
    {
        0,
        NULL,
        segment_10,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( segment_10 ) / sizeof ( segment_10 [ 0 ] ),
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

    return 1;
}

int insert_ex ( void )
{
    /* forming segment 1 */

    struct en_word segment_1 [ ] =
    {
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "in", NULL },
        { 1, 0, "my", NULL },
        { 1, 0, "verse", NULL }
    };

    /* forming sentence 2 */

    struct en_content sentence_1 =
    {
        0,
        NULL,
        segment_1,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( segment_1 ) / sizeof ( segment_1 [ 0 ] ),
        0,
        0,
        0
    };

    struct en_word segment_2 [ ] =
    {
        { 1, 0, "", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "shall", NULL },
        { 1, 0, "", NULL },
        { 1, 0, "", NULL },
        { 1, 1, "", NULL },
        { 1, 1, "", NULL },
        { 1, 0, "", & sentence_1 },
        { 1, 0, "ever", NULL },
        { 1, 0, "live", NULL },
        { 1, 0, "young", NULL }
    };

    segment_2 [ 0 ] = { 1, 0, "my", NULL };
    segment_2 [ 1 ] = { 1, 0, "love", NULL };

    struct en_content sentence_2 =
    {
        0,
        NULL,
        segment_2,
        NULL,
        NULL,
        NULL,
        0,
        sizeof ( segment_2 ) / sizeof ( segment_2 [ 0 ] ),
        0,
        0,
        0
    };

    /* outputting sentence 2 */

    jump ( 0, & sentence_2 );

    return 1;
}

int run ( void )
{
    return insert ( ) && insert_ex ( );
}

int main ( void )
{
    printf ( "************************************************************************************************************************\n" );
    printf ( "an English formula about how our brains construct sentences, called Klingon, is shown below:\n" );
    printf ( "\n" );
    printf ( " '''V      'S''V\n" );
    printf ( "------ => -------\n" );
    printf ( "   O         O\n" );
    printf ( "\n" );
    printf ( " S  represents a subject.\n" );
    printf ( " V  represents a verb, preposition, adjective, or noun that is overlaid with break syllables, like 'do/don't'.\n" );
    printf ( " /  represents a division slash in mathematics.\n" );
    printf ( " O  represents an object.\n" );
    printf ( "\n" );
    printf ( "# no subjects, there are only verb-object phrases, where a verb is overlaid with break syllables, like 'do/don't'.\n" );
    printf ( "# insert a subject among the break syllables of the verb.\n" );
    printf ( "\n" );
    printf ( "copyright (C) 2026.10.19 TOP WAYE topwaye@hotmail.com\n" );
    printf ( "************************************************************************************************************************\n" );

    return run ( );
}

const char * FMT_NEWLINE    = "\n";
const char * FMT_STR_SPACE  = "%s ";
const char * FMT_STR_NT     = "%sn't ";
const char * FMT_NOT_S      = "not %s ";
const char * FMT_NOT        = "not ";

void print_content ( struct en_word * t )
{
    assert ( t );
    if ( * t -> content )
    {
        if ( ! t -> selected )
            t -> breakpoint ? printf ( FMT_STR_NT, t -> content ) : printf ( FMT_NOT_S, t -> content );
        else
            printf ( FMT_STR_SPACE, t -> content );
    }
    else
    {
        if ( ! t -> selected )
            printf ( FMT_NOT );
    }
}

void print_newline ( struct en_word * t )
{
    assert ( ! t );
    printf ( FMT_NEWLINE );
}
