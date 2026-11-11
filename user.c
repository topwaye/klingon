/*
 * user.c
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
 * he is negated. ( placed in a context of choice, it means a negative choice against him. )
 *
 * 'don't' is overlaid onto a subject-predicate unit to express negation, that is, the meaning expressed by the subject-predicate
 * unit is false, and the opposite meaning is true. for example, if 'red' is false, then the opposite meaning 'not red' is true.
 * note that a subject-predicate unit is an atomic, indivisible unit. so you can't just negate a predicate alone. essentially,
 * this is a matter of granularity.
 *
 * in ancient times, there were no subjects, only verb-object phrases. in modern times, when constructing sentences, we need
 * to add a subject to these verb-object phrases, that is, insert a subject to form a subject-predicate unit.
 *
 * the language formula for English is as follows:
 *
 * ^( ^^V ) / O => ^( S^^V ) / O
 *
 *  S  represents a subject.
 *  V  represents a verb, preposition, adjective, or noun that is overlaid with break syllables, like 'do/don't'.
 *  /  represents a division slash in mathematics.
 *  O  represents an object.
 *
 * here are example sentences applying the above formula:
 *
 * 1. who are you ?
 *    ^who => ^( you who )
 *
 * 2. what do you think you play ?
 *    ^think; play / what => ^( you think ); you play / what
 *
 * 3. don't you want me to play with him ?
 *    ^want / me; ^play; with / him => ^( you want ) / me; ^play; with / him
 *
 * 4. my love shall in my verse ever live young.
 *    in / my verse; ever ^live / young; => ^( my love [ in / my verse ] ever live ) / young
 *
 * in summary, how our brains construct English sentences:
 *
 * 1. no subjects, there are only verb-object phrases, where a verb is overlaid with break syllables, like 'do/don't'.
 * 2. insert a subject among the break syllables of the verb.
 *
 * know that the focus of thinking is unconditionally on the subject-predicate unit right next to a break syllable, rather than
 * on the break syllable itself which is usually in the first position.
 *
 * know that all the thinking in our brains is just mathematical permutations and combinations.
 *
 * https://github.com/topwaye/klingon
 */

#include <stdio.h>

#include "kernel.h"
#include "render.h"
#include "dict.h"

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

    struct en_word * segment_1 = new_word ( word_102 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_41 ),               /* verb zone */
        new_word ( word_42 )                /* object zone */
    );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_42, 0, jump );
}

void insert_25 ( void )
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

void insert_26 ( void )
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

void insert_27 ( void )
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
        segment_2                           /* adverbial zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, word_42, 0, jump );
}

void insert_28 ( void )
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

void insert_29 ( void )
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

    struct en_word word_0 [ ] = { { "(tall)" } };

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

void insert_30 ( void )
{
    /* forming verb-object segments */

    struct en_word * segment_1 = new_word_with_negation ( word_104 );
    struct en_word * segment_2 = new_word ( word_43 + 1 );
    struct en_word * segment_3 = new_word ( word_111 );

    link_words
    (
        4,
        segment_1,                          /* break zone */
        new_word ( word_45 ),               /* verb zone */
        new_word ( word_43 ),               /* adverbial zone */
        new_word ( word_46 )                /* adverbial zone */
    );

    link_words
    (
        1,
        segment_2                           /* conjunction zone */
    );

    struct en_word word_0 [ ] = { { "(work)" }, { "(hard)" } };

    link_words
    (
        3,
        segment_3,                          /* break zone */
        word_0,                             /* verb zone */
        word_0 + 1                          /* adverbial zone */
    );

    /* inserting subjects */

    link_words ( 2, segment_1, new_word ( word_b ) );
    link_words_ahead ( 2, segment_3, new_word ( word_b + 1 ) );
    segment_3 = word_b + 1;

    /* forming a sentence */

    link_lines ( 3, segment_1, segment_2, segment_3 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}
