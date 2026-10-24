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
#include <stdarg.h>
#include <assert.h>

#define EN_CHAR_NUM             16

struct en_content;

struct en_word
{
    int selected;                   /* select or unselect the word */
    int breakpoint;                 /* a breakpoint or not */
    char content [ EN_CHAR_NUM ];
    struct en_content * sen_content;
    struct en_word * prior;
    struct en_word * next;
    struct en_word * down;
};

struct en_content
{
    int outer_starting;
    struct en_word * starting_point;
    struct en_word * starting_line;
    struct en_word * segments;
};

void print_content ( struct en_word * t );
void print_newline ( struct en_word * t );

void print ( struct en_word * t )
{
    t ? print_content ( t ) : print_newline ( t );
}

void jump ( int depth, struct en_content * sentence )
{
    struct en_word * r, * s, * p, * q, * t;

    if ( sentence )
    {
        r = sentence -> segments;
        if ( r )
        {
            q = sentence -> starting_point;
            if ( q )
            {
                if ( ! sentence -> outer_starting )
                {
                    s = sentence -> starting_line;
                    if ( s )
                    {
                        t = q;
                        do
                        {
                            print ( t );
                            jump ( depth + 1, t -> sen_content );
                            t = t -> next;
                        } while ( t != s );
                    }
                }
            }

            p = r;
            do
            {
                t = p;
                do
                {
                    if ( t == q )
                        break;
                    print ( t );
                    jump ( depth + 1, t -> sen_content );
                    t = t -> next;
                } while ( t != p );
                p = p -> down;
            } while ( p != r );
        }
    }

    if ( ! depth )
        print ( NULL );
}

void link_words_ahead ( int len, struct en_word * list, ... )
{
    va_list ap;
    struct en_word * p, * t;

    va_start ( ap, list );

    assert ( len > 0 );
    while ( -- len )
    {
        p = va_arg ( ap, struct en_word * );
        assert ( p );
        assert ( list );
        t = list -> prior;
        t -> next = p;
        list -> prior = p;
        p -> prior = t;
        p -> next = list;
    }

    va_end ( ap );
}

void link_words ( int len, struct en_word * list, ... )
{
    va_list ap;
    struct en_word * p, * t;

    va_start ( ap, list );

    assert ( len > 0 );
    while ( -- len )
    {
        p = va_arg ( ap, struct en_word * );
        assert ( p );
        assert ( list );
        t = list -> next;
        t -> prior = p;
        list -> next = p;
        p -> prior = list;
        p -> next = t;
        list = p;
    }

    va_end ( ap );
}

void link_lines ( int len, struct en_word * list, ... )
{
    va_list ap;
    struct en_word * p, * t;

    va_start ( ap, list );

    assert ( len > 0 );
    while ( -- len )
    {
        p = va_arg ( ap, struct en_word * );
        assert ( p );
        assert ( list );
        t = list -> down;
        list -> down = p;
        p -> down = t;
        list = p;
    }

    va_end ( ap );
}

struct en_word * new_line ( struct en_word * list )
{
    assert ( list );
    list -> prior = list;
    list -> next = list;
    return list;
}

struct en_word * new_multiline ( struct en_word * list )
{
    assert ( list );
    list -> down = list;
    return list;
}

struct en_word word_2 = { 1, 0, "play", NULL };
struct en_word word_3 = { 1, 0, "what", NULL };

struct en_word word_4 = { 1, 0, "at", NULL };
struct en_word word_5 = { 1, 0, "home", NULL };

struct en_word word_6 = { 1, 0, "think", NULL };

struct en_word word_7 = { 1, 0, "want", NULL };

struct en_word word_10 = { 1, 0, "playing", NULL };
struct en_word word_11 = { 1, 0, "cards", NULL };

struct en_word word_12 = { 1, 0, "bad", NULL };

struct en_word word_20 = { 1, 0, "in", NULL };
struct en_word word_21 = { 1, 0, "my", NULL };
struct en_word word_22 = { 1, 0, "verse", NULL };

struct en_word word_23 = { 1, 0, "ever", NULL };
struct en_word word_24 = { 1, 0, "live", NULL };
struct en_word word_25 = { 1, 0, "young", NULL };

struct en_word word_30 = { 1, 0, "singing", NULL };
struct en_word word_31 = { 1, 0, "or", NULL };
struct en_word word_32 = { 1, 0, "dancing", NULL };

struct en_word word_51 = { 1, 0, "with", NULL };
struct en_word word_52 = { 1, 0, "who", NULL };

struct en_word word_53 = { 1, 0, "love", NULL };

struct en_word word_54 = { 1, 0, "loved", NULL };

void insert_1 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_101 = { 1, 2, "do", NULL };
    struct en_word word_a = { 1, 0, "you", NULL };

    /* forming segments */

    struct en_word * segment_1 = new_line ( & word_101 );
    struct en_word * segment_2 = new_line ( & word_4 );

    link_words
    (
        3,
        segment_1,                  /* break zone */
        & word_2,                   /* verb zone */
        & word_3                    /* object zone */
    );

    link_words
    (
        2,
        segment_2,                  /* verb zone */
        & word_5                    /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, & word_a );

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 2, segment_1, segment_2 );
    sentence . starting_point = & word_3;
    sentence . starting_line = segment_1;
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_2 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_107 = { 1, 2, "would", NULL };
    struct en_word word_108 = { 1, 1, "have", NULL };
    struct en_word word_109 = { 1, 1, "been", NULL };
    struct en_word word_a = { 1, 0, "you", NULL };

    /* forming segments */

    struct en_word * segment_1 = new_line ( & word_107 );
    struct en_word * segment_2 = new_line ( & word_4 );

    link_words
    (
        5,
        segment_1,                  /* break zone */
        & word_108,                 /* break zone */
        & word_109,                 /* break zone */
        & word_10,                  /* verb zone */
        & word_11                   /* object zone */
    );

    link_words
    (
        2,
        segment_2,                  /* verb zone */
        & word_5                    /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, & word_a );

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 2, segment_1, segment_2 );
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_3 ( void )
{
    struct en_content sentence_1 = { 0 };
    struct en_content sentence_2 = { 0 };
    struct en_word word_101 = { 1, 2, "do", NULL };
    struct en_word word_a = { 1, 0, "you", NULL };
    struct en_word word_b = { 1, 0, "you", NULL };
    struct en_word word_0 = { 1, 0, "", NULL };

    /* forming segment 1, 2 */

    struct en_word * segment_1 = new_line ( & word_2 );
    struct en_word * segment_2 = new_line ( & word_4 );

    link_words
    (
        2,
        segment_1,                  /* verb zone */
        & word_3                    /* object zone */
    );

    link_words
    (
        2,
        segment_2,                  /* verb zone */
        & word_5                    /* object zone */
    );

    /* inserting subject 1 */

    link_words_ahead ( 2, segment_1, & word_a );
    segment_1 = & word_a;

    /* forming sentence 1 */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 2, segment_1, segment_2 );
    sentence_1 . outer_starting = 1;
    sentence_1 . starting_point = & word_3;
    sentence_1 . starting_line = segment_1;
    sentence_1 . segments = segment_1;

    /* filling word 0 */

    word_0 . sen_content = & sentence_1;

    /* forming segment 3 */

    struct en_word * segment_3 = new_line ( & word_101 );

    link_words
    (
        3,
        segment_3,                  /* break zone */
        & word_6,                   /* verb zone */
        & word_0                    /* object zone */
    );

    /* inserting subject 2 */

    link_words ( 2, segment_3, & word_b );

    /* forming sentence 2 */

    segment_3 = new_multiline ( segment_3 );
    link_lines ( 1, segment_3 );
    sentence_2 . starting_point = & word_3;
    sentence_2 . starting_line = segment_1;
    sentence_2 . segments = segment_3;

    /* outputting sentence 2 */

    jump ( 0, & sentence_2 );
}

void insert_4 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_100 = { 0, 2, "are", NULL };
    struct en_word word_a = { 1, 0, "you", NULL };

    /* forming a segment */

    struct en_word * segment_1 = new_line ( & word_100 );

    link_words
    (
        3,
        segment_1,                  /* break zone */
        & word_4,                   /* verb zone */
        & word_5                    /* object zone */
    );

    /* inserting a subject */

    link_words_ahead ( 2, segment_1, & word_a );
    segment_1 = & word_a;

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 1, segment_1 );
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_5 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_12 = { 0, 0, "bad", NULL };

    /* forming segments */

    struct en_word * segment_1 = new_line ( & word_12 );

    link_words
    (
        1,
        segment_1                   /* verb zone */
    );

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 1, segment_1 );
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_6 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_101 = { 0, 2, "do", NULL };
    struct en_word word_100 = { 1, 1, "be", NULL };

    /* forming a segment */

    struct en_word * segment_1 = new_line ( & word_101 );

    link_words
    (
        3,
        segment_1,                  /* break zone */
        & word_100,                 /* break zone */
        & word_12                   /* verb zone */
    );

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 1, segment_1 );
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_7 ( void )
{
    struct en_content sentence_1 = { 0 };
    struct en_content sentence_2 = { 0 };
    struct en_word word_110 = { 0, 5, "shall", NULL };
    struct en_word word_a = { 1, 0, "my", NULL };
    struct en_word word_b = { 1, 0, "love", NULL };
    struct en_word word_0 = { 1, 0, "", NULL };

    /* forming segment 1 */

    struct en_word * segment_1 = new_line ( & word_20 );

    link_words
    (
        3,
        segment_1,                  /* verb zone */
        & word_21,                  /* object zone */
        & word_22                   /* object zone */
    );

    /* forming sentence 1 */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 1, segment_1 );
    sentence_1 . segments = segment_1;

    /* filling word 0 */

    word_0 . sen_content = & sentence_1;

    /* forming segment 2 */

    struct en_word * segment_2 = new_line ( & word_110 );

    link_words
    (
        5,
        segment_2,                  /* break zone */
        & word_0,                   /* verb zone */
        & word_23,                  /* verb zone */
        & word_24,                  /* verb zone */
        & word_25                   /* object zone */
    );

    /* inserting subject 1 */

    link_words_ahead ( 3, segment_2, & word_a, & word_b );
    segment_2 = & word_a;

    /* forming sentence 2 */

    segment_2 = new_multiline ( segment_2 );
    link_lines ( 1, segment_2 );
    sentence_2 . segments = segment_2;

    /* outputting sentence 2 */

    jump ( 0, & sentence_2 );
}

void insert_8 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_100 = { 1, 2, "are", NULL };
    struct en_word word_101 = { 1, 2, "are", NULL };
    struct en_word word_a = { 1, 0, "you", NULL };
    struct en_word word_b = { 1, 0, "you", NULL };

    /* forming segments */

    struct en_word * segment_1 = new_line ( & word_100 );
    struct en_word * segment_2 = new_line ( & word_31 );
    struct en_word * segment_3 = new_line ( & word_101 );

    link_words
    (
        2,
        segment_1,                  /* break zone */
        & word_30                   /* verb zone */
    );

    link_words
    (
        1,
        segment_2                   /* conjunction zone */
    );

    link_words
    (
        2,
        segment_3,                  /* break zone */
        & word_32                   /* verb zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, & word_a );
    link_words ( 2, segment_3, & word_b );

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 3, segment_1, segment_2, segment_3 );
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_9 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_100 = { 1, 2, "is", NULL };
    struct en_word word_a = { 1, 0, "he", NULL };

    /* forming a segment */

    struct en_word * segment_1 = new_line ( & word_100 );

    link_words
    (
        2,
        segment_1,                  /* break zone */
        & word_52                   /* verb zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, & word_a );

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 1, segment_1 );
    sentence . starting_point = & word_52;
    sentence . starting_line = segment_1;
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_10 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_100 = { 1, 2, "is", NULL };

    /* forming a segment */

    struct en_word * segment_1 = new_line ( & word_100 );

    link_words
    (
        2,
        segment_1,                  /* break zone */
        & word_12                   /* verb zone */
    );

    /* inserting a subject */

    link_words_ahead ( 2, segment_1, & word_52 );
    segment_1 = & word_52;

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 1, segment_1 );
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_11 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_101 = { 1, 2, "do", NULL };
    struct en_word word_102 = { 1, 1, "to", NULL };
    struct en_word word_100 = { 1, 1, "be", NULL };
    struct en_word word_a = { 1, 0, "you", NULL };

    /* forming segments */

    struct en_word * segment_1 = new_line ( & word_101 );
    struct en_word * segment_2 = new_line ( & word_102 );

    link_words
    (
        2,
        segment_1,                  /* break zone */
        & word_7                    /* verb zone */
    );

    link_words
    (
        3,
        segment_2,                  /* break zone */
        & word_100,                 /* break zone */
        & word_52                   /* verb zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, & word_a );

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 2, segment_1, segment_2 );
    sentence . starting_point = & word_52;
    sentence . starting_line = segment_2;
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_12 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_101 = { 1, 2, "do", NULL };
    struct en_word word_102 = { 1, 1, "to", NULL };
    struct en_word word_a = { 1, 0, "you", NULL };

    /* forming segments */

    struct en_word * segment_1 = new_line ( & word_101 );
    struct en_word * segment_2 = new_line ( & word_102 );

    link_words
    (
        2,
        segment_1,                  /* break zone */
        & word_7                    /* verb zone */
    );

    link_words
    (
        3,
        segment_2,                  /* break zone */
        & word_53,                  /* verb zone */
        & word_52                   /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, & word_a );

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 2, segment_1, segment_2 );
    sentence . starting_point = & word_52;
    sentence . starting_line = segment_2;
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_with_starting_point ( struct en_word * starting_point )
{
    struct en_content sentence = { 0 };
    struct en_word word_101 = { 1, 2, "do", NULL };
    struct en_word word_102 = { 1, 1, "to", NULL };
    struct en_word word_a = { 1, 0, "you", NULL };

    /* forming segments */

    struct en_word * segment_1 = new_line ( & word_101 );
    struct en_word * segment_2 = new_line ( & word_102 );
    struct en_word * segment_3 = new_line ( & word_51 );

    link_words
    (
        2,
        segment_1,                  /* break zone */
        & word_7                    /* verb zone */
    );

    link_words
    (
        2,
        segment_2,                  /* break zone */
        & word_2                    /* verb zone */
    );

    link_words
    (
        2,
        segment_3,                  /* verb zone */
        & word_52                   /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, & word_a );

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 3, segment_1, segment_2, segment_3 );
    sentence . starting_point = starting_point;
    sentence . starting_line = segment_3;
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

void insert_13 ( void )
{
    insert_with_starting_point ( & word_52 );
}

void insert_14 ( void )
{
    insert_with_starting_point ( & word_51 );
}

void insert_15 ( void )
{
    struct en_content sentence = { 0 };
    struct en_word word_101 = { 1, 2, "do", NULL };
    struct en_word word_102 = { 0, 1, "to", NULL };
    struct en_word word_100 = { 1, 1, "be", NULL };
    struct en_word word_a = { 1, 0, "you", NULL };

    /* forming segments */

    struct en_word * segment_1 = new_line ( & word_101 );
    struct en_word * segment_2 = new_line ( & word_102 );

    link_words
    (
        2,
        segment_1,                  /* break zone */
        & word_7                    /* verb zone */
    );

    link_words
    (
        3,
        segment_2,                  /* break zone */
        & word_100,                 /* break zone */
        & word_54                   /* verb zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, & word_a );

    /* forming a sentence */

    segment_1 = new_multiline ( segment_1 );
    link_lines ( 2, segment_1, segment_2 );
    sentence . segments = segment_1;

    /* outputting a sentence */

    jump ( 0, & sentence );
}

typedef void ( * insert_t ) ( void );

void run ( void )
{
    int i, n;

    insert_t func [ ] =
    {
        insert_1,
        insert_2,
        insert_3,
        insert_4,
        insert_5,
        insert_6,
        insert_7,
        insert_8,
        insert_9,
        insert_10,
        insert_11,
        insert_12,
        insert_13,
        insert_14,
        insert_15
    };

    n = sizeof ( func ) / sizeof ( func [ 0 ] );

    for ( i = 0; i < n; i ++ )
        func [ i ] ( );
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

    run ( );

    return 0;
}

const char * FMT_NEWLINE    = "\n";
const char * FMT_STR_SPACE  = "%s ";
const char * FMT_STR_NT     = "%sn't ";
const char * FMT_AI_NT      = "ain't ";
const char * FMT_WO_NT      = "won't ";
const char * FMT_SHA_NT     = "shan't ";
const char * FMT_NOT_S      = "not %s ";
const char * FMT_NOT        = "not ";

void print_content ( struct en_word * t )
{
    assert ( t );
    if ( * t -> content )
    {
        if ( ! t -> selected )
            switch ( t -> breakpoint )
            {
                case 2 : printf ( FMT_STR_NT, t -> content ); break;
                case 3 : printf ( FMT_AI_NT ); break;
                case 4 : printf ( FMT_WO_NT ); break;
                case 5 : printf ( FMT_SHA_NT ); break;
                default : printf ( FMT_NOT_S, t -> content );
            }
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
