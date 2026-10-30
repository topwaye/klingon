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
 * being able to be clearly spoken and clearly heard was the top priority when English was invented in ancient times. that's
 * why it was necessary to change the pronunciation of certain words by adding break syllables. for example, 'play' is changed
 * to 'to play', and 'be' is changed to 'to be', that is, insert a break syllable as a breakpoint to make the target word sound
 * clearer in the middle of multiple words.
 *
 * another example: 'do' is overlaid onto a subject to change pronunciation, helping to clearly locate the subject in a sentence.
 *
 * 'not' is a judgment concept in logic. it's a matter of 'true' or 'false'. for example, 'not him' means he is false, that is,
 * he is negated. ( placed in a context of choice, it means a negative choice against him. ) 'don't' is overlaid onto a subject
 * to express negation, that is, the meaning expressed by the subject-predicate unit is false, and the opposite meaning is true.
 * for example, if 'red' is false, then the opposite meaning 'not red' is true.
 *
 * note that a subject-predicate unit is an atomic, indivisible unit. so you can't just negate a predicate alone. essentially,
 * this is a matter of granularity.
 *
 * in ancient times, there were no subjects, only verb-object phrases. in modern times, when constructing sentences, we need
 * to add a subject to these verb-object phrases.
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

/* data structure area */


#define PRINT_STRING_LENGTH     31
#define EN_CHAR_NUM             16

struct en_content;

struct en_word
{
    char content [ EN_CHAR_NUM ];
    int breakpoint;                         /* a breakpoint or not */
    int negative;                           /* negate a granularity */
    struct en_content * sen_content;
    struct en_word * prior;
    struct en_word * next;
    struct en_word * down;
};

struct en_content
{
    struct en_word * segments;
    struct en_word * starting_point;
    int outer_starting;
};

/* kernel function area */

void print ( struct en_word * t );

void jump ( int depth, struct en_content * sen )
{
    struct en_word * r, * p, * q, * t;

    if ( sen )
    {
        r = sen -> segments;
        if ( r )
        {
            q = sen -> starting_point;
            if ( q )
            {
                if ( ! sen -> outer_starting )
                {
                    t = q;
                    do
                    {
                        print ( t );
                        jump ( depth + 1, t -> sen_content );
                        t = t -> next;
                    } while ( t );
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
                } while ( t );
                p = p -> down;
            } while ( p );
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
        if ( t )
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
        if ( t )
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

struct en_word * init_word ( struct en_word * t, int no_sel, struct en_content * sen )
{
    assert ( t );
    t -> negative = no_sel;
    t -> sen_content = sen;
    t -> prior = NULL;
    t -> next = NULL;
    t -> down = NULL;
    return t;
}

struct en_word * new_word ( struct en_word * t )
{
    return init_word ( t, 0, NULL );
}

struct en_word * new_word_with_negation ( struct en_word * t )
{
    return init_word ( t, 1, NULL );
}

struct en_word * new_null_word ( struct en_word * t, struct en_content * sen )
{
    return init_word ( t, 0, sen );
}

typedef void ( * jump_t ) ( int, struct en_content * );

void new_sentence ( struct en_content * sen, struct en_word * segs, struct en_word * starting, int outer_starting, jump_t jmp_func )
{
    assert ( sen );
    sen -> segments = segs;
    sen -> starting_point = starting;
    sen -> outer_starting = outer_starting;

    if ( jmp_func )
        jmp_func ( 0, sen );
}

/* verb-object phrases */

struct en_word word_0 [ ] = { { "(...)" }, { "(...)" } };

struct en_word word_11 [ ] = { { "play" } };
struct en_word word_12 [ ] = { { "what" } };

struct en_word word_13 [ ] = { { "at" } };
struct en_word word_14 [ ] = { { "home" } };

struct en_word word_15 [ ] = { { "think" } };

struct en_word word_16 [ ] = { { "want" } };

struct en_word word_17 [ ] = { { "playing" } };
struct en_word word_18 [ ] = { { "cards" } };

struct en_word word_19 [ ] = { { "bad" } };

struct en_word word_20 [ ] = { { "in" } };
struct en_word word_21 [ ] = { { "my" }, { "my" } };
struct en_word word_22 [ ] = { { "verse" } };

struct en_word word_23 [ ] = { { "ever" } };
struct en_word word_24 [ ] = { { "live" } };
struct en_word word_25 [ ] = { { "young" } };

struct en_word word_26 [ ] = { { "singing" } };
struct en_word word_27 [ ] = { { "or" } };
struct en_word word_28 [ ] = { { "dancing" } };

struct en_word word_29 [ ] = { { "with" } };
struct en_word word_30 [ ] = { { "who" } };

struct en_word word_31 [ ] = { { "love" } };
struct en_word word_32 [ ] = { { "everything" } };

struct en_word word_33 [ ] = { { "loved" } };

struct en_word word_34 [ ] = { { "give" } };
struct en_word word_35 [ ] = { { "him" } };

struct en_word word_36 [ ] = { { "money" } };

struct en_word word_37 [ ] = { { "to" } };

struct en_word word_38 [ ] = { { "for" } };

struct en_word word_39 [ ] = { { "do" } };
struct en_word word_40 [ ] = { { "that" } };

struct en_word word_41 [ ] = { { "go" } };
struct en_word word_42 [ ] = { { "where" } };

struct en_word word_43 [ ] = { { "as" }, { "as" } };
struct en_word word_44 [ ] = { { "tall" } };

struct en_word word_45 [ ] = { { "work" } };
struct en_word word_46 [ ] = { { "hard" } };

/* break syllables */

struct en_word word_100 [ ] = { { "are", 2 }, { "are", 2 } };
struct en_word word_101 [ ] = { { "is", 2 } };
struct en_word word_102 [ ] = { { "to", 1 } };
struct en_word word_103 [ ] = { { "be", 1 } };

struct en_word word_104 [ ] = { { "do", 2 } };
struct en_word word_105 [ ] = { { "does", 2 } };

struct en_word word_106 [ ] = { { "shall", 5 } };

struct en_word word_107 [ ] = { { "would", 2 } };
struct en_word word_108 [ ] = { { "have", 1 } };
struct en_word word_109 [ ] = { { "been", 1 } };

struct en_word word_110 [ ] = { { "can", 6 } };

/* subjects */

struct en_word word_b [ ] = { { "you" }, { "you" } };
struct en_word word_c [ ] = { { "he" } };

/* word_null: the only entry point where a sentence is nested */

struct en_word word_null [ ] = { { 0 } };

/* sentences */

struct en_content sentence [ ] = { { 0 }, { 0 } };

/* test function area */

void insert_1 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word_with_negation ( word_104 );
    struct en_word * segment_2 = new_word ( word_13 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_11 ),               /* verb zone */
        new_word ( word_12 )                /* object zone */
    );

    link_words
    (
        2,
        segment_2,                          /* verb zone */
        new_word ( word_14 )                /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, word_12, 0, jump );
}

void insert_2 ( void )
{
    /* forming verb-object segment 1 */

    struct en_word * segment_1 = new_word ( word_13 );

    link_words
    (
        2,
        segment_1,                          /* verb zone */
        new_word ( word_14 )                /* object zone */
    );

    /* forming sentence 1 */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, NULL, 0, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming verb-object segment 2 */

    struct en_word * segment_2 = new_word_with_negation ( word_104 );

    link_words
    (
        4,
        segment_2,                          /* break zone */
        word_null,                          /* adverbial zone */
        new_word ( word_11 ),               /* verb zone */
        new_word ( word_12 )                /* object zone */
    );

    /* inserting subject 1 */

    link_words ( 2, segment_2, new_word ( word_b ) );

    /* forming sentence 2 */

    link_lines ( 1, segment_2 );

    new_sentence ( sentence + 1, segment_2, word_12, 0, jump );
}

void insert_3 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word ( word_107 );
    struct en_word * segment_2 = new_word ( word_13 );

    link_words
    (
        5,
        segment_1,                          /* break zone */
        new_word ( word_108 ),              /* break zone */
        new_word ( word_109 ),              /* break zone */
        new_word ( word_17 ),               /* verb zone */
        new_word ( word_18 )                /* object zone */
    );

    link_words
    (
        2,
        segment_2,                          /* verb zone */
        new_word ( word_14 )                /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_4 ( void )
{
    /* forming verb-object segment 1, 2 */

    struct en_word * segment_1 = new_word ( word_11 );
    struct en_word * segment_2 = new_word ( word_13 );

    link_words
    (
        2,
        segment_1,                          /* verb zone */
        new_word ( word_12 )                /* object zone */
    );

    link_words
    (
        2,
        segment_2,                          /* verb zone */
        new_word ( word_14 )                /* object zone */
    );

    /* inserting subject 1 */

    link_words_ahead ( 2, segment_1, new_word ( word_b ) );
    segment_1 = word_b;

    /* forming sentence 1 */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, word_12, 1, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming verb-object segment 3 */

    struct en_word * segment_3 = new_word ( word_104 );

    link_words
    (
        3,
        segment_3,                          /* break zone */
        new_word ( word_15 ),               /* verb zone */
        word_null                           /* object zone */
    );

    /* inserting subject 2 */

    link_words ( 2, segment_3, new_word ( word_b + 1 ) );

    /* forming sentence 2 */

    link_lines ( 1, segment_3 );

    new_sentence ( sentence + 1, segment_3, word_12, 0, jump );
}

void insert_5 ( void )
{
    /* forming a verb-object segment */

    struct en_word * segment_1 = new_word_with_negation ( word_100 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_13 ),               /* verb zone */
        new_word ( word_14 )                /* object zone */
    );

    /* inserting a subject */

    link_words_ahead ( 2, segment_1, new_word ( word_b ) );
    segment_1 = word_b;

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_6 ( void )
{
    /* forming a verb-object segment */

    struct en_word * segment_1 = new_word_with_negation ( word_19 );

    link_words
    (
        1,
        segment_1                           /* verb zone */
    );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_7 ( void )
{
    /* forming a verb-object segment */

    struct en_word * segment_1 = new_word_with_negation ( word_104 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_103 ),              /* break zone */
        new_word ( word_19 )                /* verb zone */
    );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_8 ( void )
{
    /* forming verb-object segment 1 */

    struct en_word * segment_1 = new_word ( word_20 );

    link_words
    (
        3,
        segment_1,                          /* verb zone */
        new_word ( word_21 ),               /* object zone */
        new_word ( word_22 )                /* object zone */
    );

    /* forming sentence 1 */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, NULL, 0, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming verb-object segment 2 */

    struct en_word * segment_2 = new_word_with_negation ( word_106 );

    link_words
    (
        5,
        segment_2,                          /* break zone */
        word_null,                          /* adverbial zone */
        new_word ( word_23 ),               /* verb zone */
        new_word ( word_24 ),               /* verb zone */
        new_word ( word_25 )                /* object zone */
    );

    /* inserting subject 1 */

    link_words_ahead ( 3, segment_2, new_word ( word_21 + 1 ), new_word ( word_31 ) );
    segment_2 = word_21 + 1;

    /* forming sentence 2 */

    link_lines ( 1, segment_2 );

    new_sentence ( sentence + 1, segment_2, NULL, 0, jump );
}

void insert_9 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word ( word_100 );
    struct en_word * segment_2 = new_word ( word_27 );
    struct en_word * segment_3 = new_word ( word_100 + 1 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_26 )                /* verb zone */
    );

    link_words
    (
        1,
        segment_2                           /* conjunction zone */
    );

    link_words
    (
        2,
        segment_3,                          /* break zone */
        new_word ( word_28 )                /* verb zone */
    );

    /* inserting subjects */

    link_words ( 2, segment_1, new_word ( word_b ) );
    link_words ( 2, segment_3, new_word ( word_b + 1 ) );

    /* forming a sentence */

    link_lines ( 3, segment_1, segment_2, segment_3 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_10 ( void )
{
    /* forming a verb-object segment */

    struct en_word * segment_1 = new_word ( word_101 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_30 )                /* verb zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_c ) );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_30, 0, jump );
}

void insert_11 ( void )
{
    /* forming a verb-object segment */

    struct en_word * segment_1 = new_word ( word_101 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_19 )                /* verb zone */
    );

    /* inserting a subject */

    link_words_ahead ( 2, segment_1, new_word ( word_30 ) );
    segment_1 = word_30;

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_12 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_102 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_16 )                /* verb zone */
    );

    link_words
    (
        3,
        segment_2,                          /* break zone */
        new_word ( word_103 ),              /* break zone */
        new_word ( word_30 )                /* verb zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, word_30, 0, jump );
}

void insert_13 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_102 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_16 )                /* verb zone */
    );

    link_words
    (
        3,
        segment_2,                          /* break zone */
        new_word ( word_31 ),               /* verb zone */
        new_word ( word_30 )                /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, word_30, 0, jump );
}

void insert_with_starting_point ( struct en_word * starting )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_102 );
    struct en_word * segment_3 = new_word ( word_29 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_16 )                /* verb zone */
    );

    link_words
    (
        2,
        segment_2,                          /* break zone */
        new_word ( word_11 )                /* verb zone */
    );

    link_words
    (
        2,
        segment_3,                          /* verb zone */
        new_word ( word_30 )                /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 3, segment_1, segment_2, segment_3 );

    new_sentence ( sentence, segment_1, starting, 0, jump );
}

void insert_14 ( void )
{
    insert_with_starting_point ( word_30 );
}

void insert_15 ( void )
{
    insert_with_starting_point ( word_29 );
}

void insert_16 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word_with_negation ( word_102 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_16 )                /* verb zone */
    );

    link_words
    (
        3,
        segment_2,                          /* break zone */
        new_word ( word_103 ),              /* break zone */
        new_word ( word_33 )                /* verb zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_17 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_12 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_34 ),               /* verb zone */
        new_word ( word_35 )                /* object zone */
    );

    link_words
    (
        1,
        segment_2                           /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, word_12, 0, jump );
}

void insert_18 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_37 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_34 ),               /* verb zone */
        new_word ( word_36 )                /* object zone */
    );

    link_words
    (
        2,
        segment_2,                          /* verb zone */
        new_word ( word_30 )                /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, word_30, 0, jump );
}

void insert_19 ( void )
{
    /* forming verb-object segment 1 */

    struct en_word * segment_1 = new_word ( word_100 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_30 )                /* verb zone */
    );

    /* inserting subject 1 */

    link_words_ahead ( 2, segment_1, new_word ( word_b ) );
    segment_1 = word_b;

    /* forming sentence 1 */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_30, 0, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming verb-object segment 2 */

    struct en_word * segment_2 = new_word ( word_100 + 1 );

    link_words
    (
        2,
        segment_2,                          /* break zone */
        word_null                           /* verb zone */
    );

    /* inserting subject 2 */

    link_words ( 2, segment_2, new_word ( word_b + 1 ) );

    /* forming sentence 2 */

    link_lines ( 1, segment_2 );

    new_sentence ( sentence + 1, segment_2, NULL, 0, jump );
}

void insert_20 ( void )
{
    /* forming verb-object segment 1 */

    struct en_word * segment_1 = new_word ( word_39 );

    link_words
    (
        2,
        segment_1,                          /* verb zone */
        new_word ( word_40 )                /* object zone */
    );

    /* inserting subject 1 */

    link_words_ahead ( 2, segment_1, new_word ( word_b ) );
    segment_1 = word_b;

    /* forming sentence 1 */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_40, 0, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming verb-object segment 2, 3, 4 */

    struct en_word * segment_2 = new_word ( word_105 );
    struct en_word * segment_3 = new_word ( word_38 );
    struct en_word * segment_4 = word_null;

    link_words
    (
        3,
        segment_2,                          /* break zone */
        new_word ( word_31 ),               /* verb zone */
        new_word ( word_32 )                /* object zone */
    );

    link_words
    (
        2,
        segment_3,                          /* verb zone */
        new_word ( word_35 )                /* object zone */
    );

    link_words
    (
        1,
        segment_4                           /* object zone */
    );

    /* inserting subject 2 */

    link_words ( 2, segment_2, new_word ( word_c ) );

    /* forming sentence 2 */

    link_lines ( 3, segment_2, segment_3, segment_4 );

    new_sentence ( sentence + 1, segment_2, NULL, 0, jump );
}

void insert_21 ( void )
{
    /* forming verb-object segment 1 */

    struct en_word * segment_1 = new_word ( word_39 );

    link_words
    (
        2,
        segment_1,                          /* verb zone */
        new_word ( word_40 )                /* object zone */
    );

    /* inserting subject 1 */

    link_words_ahead ( 2, segment_1, new_word ( word_b ) );
    segment_1 = word_b;

    /* forming sentence 1 */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_40, 0, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming verb-object segment 2, 3 */

    struct en_word * segment_2 = new_word ( word_105 );
    struct en_word * segment_3 = new_word ( word_38 );

    link_words
    (
        4,
        segment_2,                          /* break zone */
        new_word ( word_31 ),               /* verb zone */
        new_word ( word_32 ),               /* object zone */
        word_null                           /* object zone */
    );

    link_words
    (
        2,
        segment_3,                          /* verb zone */
        new_word ( word_35 )                /* object zone */
    );

    /* inserting subject 2 */

    link_words ( 2, segment_2, new_word ( word_c ) );

    /* forming sentence 2 */

    link_lines ( 2, segment_2, segment_3 );

    new_sentence ( sentence + 1, segment_2, NULL, 0, jump );
}

void insert_22 ( void )
{
    /* forming verb-object segment 1, 3 */

    struct en_word * segment_1 = new_word ( word_39 );
    struct en_word * segment_3 = new_word ( word_38 );

    link_words
    (
        2,
        segment_1,                          /* verb zone */
        new_word ( word_32 )                /* object zone */
    );

    link_words
    (
        2,
        segment_3,                          /* verb zone */
        new_word ( word_35 )                /* object zone */
    );

    /* inserting subject 1 */

    link_words_ahead ( 2, segment_1, new_word ( word_b ) );
    segment_1 = word_b;

    /* forming sentence 1 */

    link_lines ( 2, segment_1, segment_3 );

    new_sentence ( sentence, segment_1, NULL, 0, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming verb-object segment 2 */

    struct en_word * segment_2 = new_word ( word_105 );

    link_words
    (
        4,
        segment_2,                          /* break zone */
        new_word ( word_31 ),               /* verb zone */
        new_word ( word_40 ),               /* object zone */
        word_null                           /* object zone */
    );

    /* inserting subject 2 */

    link_words ( 2, segment_2, new_word ( word_c ) );

    /* forming sentence 2 */

    link_lines ( 1, segment_2 );

    new_sentence ( sentence + 1, segment_2, NULL, 0, jump );
}

void insert_23 ( void )
{
    /* forming verb-object segment 1, 3 */

    struct en_word * segment_1 = new_word ( word_39 );
    struct en_word * segment_3 = new_word ( word_38 );

    link_words
    (
        2,
        segment_1,                          /* verb zone */
        new_word ( word_12 )                /* object zone */
    );

    link_words
    (
        2,
        segment_3,                          /* verb zone */
        new_word ( word_35 )                /* object zone */
    );

    /* inserting subject 1 */

    link_words_ahead ( 2, segment_1, new_word ( word_b ) );
    segment_1 = word_b;

    /* forming sentence 1 */

    link_lines ( 2, segment_1, segment_3 );

    new_sentence ( sentence, segment_1, word_12, 0, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming verb-object segment 2 */

    struct en_word * segment_2 = new_word ( word_105 );

    link_words
    (
        3,
        segment_2,                          /* break zone */
        new_word ( word_31 ),               /* verb zone */
        word_null                           /* object zone */
    );

    /* inserting subject 2 */

    link_words ( 2, segment_2, new_word ( word_c ) );

    /* forming sentence 2 */

    link_lines ( 1, segment_2 );

    new_sentence ( sentence + 1, segment_2, NULL, 0, jump );
}

void insert_24 ( void )
{
    /* forming a verb-object segment */

    struct en_word * segment_1 = new_word ( word_104 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_41 ),               /* verb zone */
        new_word ( word_42 )                /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_42, 0, jump );
}

void insert_25 ( void )
{
    /* forming a verb-object segment */

    struct en_word * segment_1 = new_word ( word_100 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_42 )                /* verb zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_42, 0, jump );
}

void insert_26 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_42 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_11 ),               /* verb zone */
        new_word ( word_18 )                /* object zone */
    );

    link_words
    (
        1,
        segment_2                           /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, word_42, 0, jump );
}

void insert_27 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word_with_negation ( word_100 );
    struct en_word * segment_3 = new_word ( word_43 + 1 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_43 ),               /* verb zone */
        new_word ( word_44 )                /* verb zone */
    );

    link_words
    (
        2,
        segment_3,                          /* verb zone */
        new_word ( word_35 )                /* object zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_3 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_28 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word_with_negation ( word_100 );
    struct en_word * segment_2 = new_word ( word_43 + 1 );
    struct en_word * segment_3 = new_word ( word_101 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_43 ),               /* verb zone */
        new_word ( word_44 )                /* verb zone */
    );

    link_words
    (
        1,
        segment_2                           /* conjunction zone */
    );

    * word_0 = { "(tall)" };

    link_words
    (
        2,
        segment_3,                          /* break zone */
        word_0                              /* verb zone */
    );

    /* inserting subjects */

    link_words ( 2, segment_1, new_word ( word_b ) );
    link_words_ahead ( 2, segment_3, new_word ( word_c ) );
    segment_3 = word_c;

    /* forming a sentence */

    link_lines ( 3, segment_1, segment_2, segment_3 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_29 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word_with_negation ( word_104 );
    struct en_word * segment_2 = new_word ( word_43 + 1 );
    struct en_word * segment_3 = new_word ( word_110 );

    link_words
    (
        4,
        segment_1,                          /* break zone */
        new_word ( word_45 ),               /* verb zone */
        new_word ( word_43 ),               /* object zone */
        new_word ( word_46 )                /* object zone */
    );

    link_words
    (
        1,
        segment_2                           /* conjunction zone */
    );

    * word_0 = { "(work)" };
    * ( word_0 + 1 ) = { "(hard)" };

    link_words
    (
        3,
        segment_3,                          /* break zone */
        word_0,                             /* verb zone */
        word_0 + 1                          /* object zone */
    );

    /* inserting subjects */

    link_words ( 2, segment_1, new_word ( word_b ) );
    link_words_ahead ( 2, segment_3, new_word ( word_b + 1 ) );
    segment_3 = word_b + 1;

    /* forming a sentence */

    link_lines ( 3, segment_1, segment_2, segment_3 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

/* interface function area */

typedef void ( * insert_t ) ( void );

const insert_t insert_func [ ] =
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
    insert_15,
    insert_16,
    insert_17,
    insert_18,
    insert_19,
    insert_20,
    insert_21,
    insert_22,
    insert_23,
    insert_24,
    insert_25,
    insert_26,
    insert_27,
    insert_28,
    insert_29
};

const int insert_count = sizeof ( insert_func ) / sizeof ( insert_func [ 0 ] );

void run ( void )
{
    int i;

    for ( i = 0; i < insert_count; i ++ )
        insert_func [ i ] ( );
}

int main ( void )
{
    printf ( "***********************************************************************************************************************\n" );
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
    printf ( "# no subjects, there are only verb-object phrases, where a verb is overlaid with break syllables, like 'do/don't';\n" );
    printf ( "# insert a subject among the break syllables of the verb:\n" );
    printf ( "# \n" );
    printf ( "# don't eat    don't you eat\n" );
    printf ( "# --------- => -------------\n" );
    printf ( "#   bread          bread\n" );
    printf ( "#\n" );
    printf ( "# don't eat    you don't eat\n" );
    printf ( "# --------- => -------------\n" );
    printf ( "#   bread          bread\n" );
    printf ( "\n" );
    printf ( "copyright (C) 2026.10.30 TOP WAYE topwaye@hotmail.com\n" );
    printf ( "***********************************************************************************************************************\n" );

    run ( );

    return 0;
}

/* I/O function area */

char print_buffer [ PRINT_STRING_LENGTH + 1 ] = { 0 };

int print_position = 0;

int grow_print_string ( char c )
{
    if ( print_position < PRINT_STRING_LENGTH )
    {
        print_buffer [ print_position ++ ] = c;
        return 1;
    }
    return 0;
}

void print_buffer_flush ( void )
{
    print_buffer [ print_position ] = '\0';
    print_position = 0;

    printf ( "%s", print_buffer );
}

void print_buffer_putchar ( char c )
{
    if ( ! grow_print_string ( c ) )
    {
        print_buffer_flush ( );
        grow_print_string ( c );
    }
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
                print_buffer_putchar ( '%' );
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
                    print_buffer_putchar ( * s );
                    n ++;
                    s ++;
                }
                p ++;
            }
            else
            {
                /* unsupported specifier: klingon_print percent and the specifier literally */
                print_buffer_putchar ( '%' );
                n ++;
                if ( * p )
                {
                    print_buffer_putchar ( * p );
                    n ++;
                    p ++;
                }
            }
        }
        else
        {
            print_buffer_putchar ( * p );
            n ++;
            p ++;
        }
    }

    va_end ( ap );

    return n;
}

const char * FMT_NEWLINE    = "\n";
const char * FMT_STR_SPACE  = "%s ";
const char * FMT_STR_NT     = "%sn't ";
const char * FMT_AI_NT      = "ain't ";
const char * FMT_WO_NT      = "won't ";
const char * FMT_SHA_NT     = "shan't ";
const char * FMT_CA_NT      = "can't ";
const char * FMT_NOT_S      = "not %s ";
const char * FMT_NOT        = "not ";

void print_content ( struct en_word * t )
{
    assert ( t );
    if ( * t -> content )
    {
        if ( t -> negative )
            switch ( t -> breakpoint )
            {
                case 2 : print ( FMT_STR_NT, t -> content ); break;
                case 3 : print ( FMT_AI_NT ); break;
                case 4 : print ( FMT_WO_NT ); break;
                case 5 : print ( FMT_SHA_NT ); break;
                case 6 : print ( FMT_CA_NT ); break;
                default : print ( FMT_NOT_S, t -> content );
            }
        else
            print ( FMT_STR_SPACE, t -> content );
    }
    else
    {
        if ( t -> negative )
            print ( FMT_NOT );
    }
}

void print_newline ( struct en_word * t )
{
    assert ( ! t );
    print ( FMT_NEWLINE );

    print_buffer_flush ( );
}

void print ( struct en_word * t )
{
    t ? print_content ( t ) : print_newline ( t );
}
