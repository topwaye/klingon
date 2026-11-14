/*
 * user.c
 *
 * Copyright (C) 1976.12.27 TOP WAYE topwaye@hotmail.com
 *
 * basic human brain language logic shown by a recursive algorithm running on a basic CPU architecture.
 * give a few words to the algorithm, and it gives you an English sentence. this algorithm is called Klingon.
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
 * 'don't' is a predicate that has degenerated into a break syllable, expressing negation, and is overlaid onto a subject. that is,
 * the meaning expressed by the subject-predicate unit is false, and the opposite meaning is true. for example, if 'red' is false,
 * then the opposite meaning 'not red' is true.
 *
 * note: a predicate can express a complete meaning on its own without the help of other words.
 * note: in English, there are only two predicates, 'be' and 'do', which have already degenerated into break syllables, so we
 * no longer use the concept of predicates. instead, we use the concept of complements.
 *
 * in ancient times, there were no subjects, only complement-object phrases. in modern times, when constructing sentences, we need
 * to insert a subject into these complement-object phrases.
 *
 * the language formula for English is as follows:
 *
 *            @
 *     @      S      @
 *     C  =>  C  =>  S  C  O
 *     O      O
 *
 * the language formula extension for English is as follows:
 *
 *            @
 *     @      S
 *     @      @         @
 *     @      @      @  @
 *     C  =>  C  =>  S  C  O
 *     O      O
 *
 *  S: a subject.
 *  C: a complement which can be a verb, preposition, adjective, or noun that is overlaid with break syllables, like 'do/don't'.
 *  O: an object.
 *
 * note: whether a word is a subject, complement, or object is unconditionally determined by its position in the sentence formula.
 * note: the difference between a complement and an object is that a subject and a complement are in the same group, while an object
 * is in another group.
 *
 * here are example sentences applying the above formula:
 *
 * 1. who are you ?
 *    @who => @you who
 *
 * 2. what do you think you play ?
 *    @think; play what => @you think; you play what
 *
 * 3. don't you want me to play with him ?
 *    @want me; @play; with him => @you want me; @play; with him
 *
 * 4. my love shall in my verse ever live young.
 *    in my verse; ever @live young; => @my love [ in my verse ] ever live young
 *
 * 5. would you have been playing cards ?
 *    @@@playing cards => @you @@playing cards
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
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word_with_negation ( word_104 );
    struct en_word * segment_2 = new_word ( word_13 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_11 ),               /* complement zone */
        new_word ( word_12 )                /* object zone */
    );

    link_words
    (
        2,
        segment_2,                          /* complement zone */
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
    /* forming complement-object segment 1 */

    struct en_word * segment_1 = new_word ( word_13 );

    link_words
    (
        2,
        segment_1,                          /* complement zone */
        new_word ( word_14 )                /* object zone */
    );

    /* forming sentence 1 */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, NULL, 0, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming complement-object segment 2 */

    struct en_word * segment_2 = new_word_with_negation ( word_104 );

    link_words
    (
        4,
        segment_2,                          /* break zone */
        word_null,                          /* adverbial zone */
        new_word ( word_11 ),               /* complement zone */
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
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word ( word_107 );
    struct en_word * segment_2 = new_word ( word_13 );

    link_words
    (
        5,
        segment_1,                          /* break zone */
        new_word ( word_108 ),              /* break zone */
        new_word ( word_109 ),              /* break zone */
        new_word ( word_17 ),               /* complement zone */
        new_word ( word_18 )                /* object zone */
    );

    link_words
    (
        2,
        segment_2,                          /* complement zone */
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
    /* forming complement-object segment 1, 2 */

    struct en_word * segment_1 = new_word ( word_11 );
    struct en_word * segment_2 = new_word ( word_13 );

    link_words
    (
        2,
        segment_1,                          /* complement zone */
        new_word ( word_12 )                /* object zone */
    );

    link_words
    (
        2,
        segment_2,                          /* complement zone */
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

    /* forming complement-object segment 3 */

    struct en_word * segment_3 = new_word ( word_104 );

    link_words
    (
        3,
        segment_3,                          /* break zone */
        new_word ( word_15 ),               /* complement zone */
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
    /* forming a complement-object segment */

    struct en_word * segment_1 = new_word_with_negation ( word_100 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_13 ),               /* complement zone */
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
    /* forming a complement-object segment */

    struct en_word * segment_1 = new_word_with_negation ( word_19 );

    link_words
    (
        1,
        segment_1                           /* complement zone */
    );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_7 ( void )
{
    /* forming a complement-object segment */

    struct en_word * segment_1 = new_word_with_negation ( word_104 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_103 ),              /* break zone */
        new_word ( word_19 )                /* complement zone */
    );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_8 ( void )
{
    /* forming complement-object segment 1 */

    struct en_word * segment_1 = new_word ( word_20 );

    link_words
    (
        3,
        segment_1,                          /* complement zone */
        new_word ( word_21 ),               /* object zone */
        new_word ( word_22 )                /* object zone */
    );

    /* forming sentence 1 */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, NULL, 0, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming complement-object segment 2 */

    struct en_word * segment_2 = new_word_with_negation ( word_106 );

    link_words
    (
        5,
        segment_2,                          /* break zone */
        word_null,                          /* adverbial zone */
        new_word ( word_23 ),               /* complement zone */
        new_word ( word_24 ),               /* complement zone */
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
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word ( word_100 );
    struct en_word * segment_2 = new_word ( word_27 );
    struct en_word * segment_3 = new_word ( word_100 + 1 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_26 )                /* complement zone */
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
        new_word ( word_28 )                /* complement zone */
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
    /* forming a complement-object segment */

    struct en_word * segment_1 = new_word ( word_101 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_30 )                /* complement zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_c ) );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_30, 0, jump );
}

void insert_11 ( void )
{
    /* forming a complement-object segment */

    struct en_word * segment_1 = new_word ( word_101 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_19 )                /* complement zone */
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
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_102 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_16 )                /* complement zone */
    );

    link_words
    (
        3,
        segment_2,                          /* break zone */
        new_word ( word_103 ),              /* break zone */
        new_word ( word_30 )                /* complement zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, word_30, 0, jump );
}

void insert_13 ( void )
{
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_102 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_16 )                /* complement zone */
    );

    link_words
    (
        3,
        segment_2,                          /* break zone */
        new_word ( word_31 ),               /* complement zone */
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
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_102 );
    struct en_word * segment_3 = new_word ( word_29 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_16 )                /* complement zone */
    );

    link_words
    (
        2,
        segment_2,                          /* break zone */
        new_word ( word_11 )                /* complement zone */
    );

    link_words
    (
        2,
        segment_3,                          /* complement zone */
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
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word_with_negation ( word_102 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_16 )                /* complement zone */
    );

    link_words
    (
        3,
        segment_2,                          /* break zone */
        new_word ( word_103 ),              /* break zone */
        new_word ( word_33 )                /* complement zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 2, segment_1, segment_2 );

    new_sentence ( sentence, segment_1, NULL, 0, jump );
}

void insert_17 ( void )
{
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_12 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_34 ),               /* complement zone */
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
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_37 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_34 ),               /* complement zone */
        new_word ( word_36 )                /* object zone */
    );

    link_words
    (
        2,
        segment_2,                          /* complement zone */
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
    /* forming complement-object segment 1 */

    struct en_word * segment_1 = new_word ( word_100 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_30 )                /* complement zone */
    );

    /* inserting subject 1 */

    link_words_ahead ( 2, segment_1, new_word ( word_b ) );
    segment_1 = word_b;

    /* forming sentence 1 */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_30, 0, NULL );

    /* filling word_null */

    new_null_word ( word_null, sentence );

    /* forming complement-object segment 2 */

    struct en_word * segment_2 = new_word ( word_100 + 1 );

    link_words
    (
        2,
        segment_2,                          /* break zone */
        word_null                           /* complement zone */
    );

    /* inserting subject 2 */

    link_words ( 2, segment_2, new_word ( word_b + 1 ) );

    /* forming sentence 2 */

    link_lines ( 1, segment_2 );

    new_sentence ( sentence + 1, segment_2, NULL, 0, jump );
}

void insert_20 ( void )
{
    /* forming complement-object segment 1 */

    struct en_word * segment_1 = new_word ( word_39 );

    link_words
    (
        2,
        segment_1,                          /* complement zone */
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

    /* forming complement-object segment 2, 3, 4 */

    struct en_word * segment_2 = new_word ( word_105 );
    struct en_word * segment_3 = new_word ( word_38 );
    struct en_word * segment_4 = word_null;

    link_words
    (
        3,
        segment_2,                          /* break zone */
        new_word ( word_31 ),               /* complement zone */
        new_word ( word_32 )                /* object zone */
    );

    link_words
    (
        2,
        segment_3,                          /* complement zone */
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
    /* forming complement-object segment 1 */

    struct en_word * segment_1 = new_word ( word_39 );

    link_words
    (
        2,
        segment_1,                          /* complement zone */
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

    /* forming complement-object segment 2, 3 */

    struct en_word * segment_2 = new_word ( word_105 );
    struct en_word * segment_3 = new_word ( word_38 );

    link_words
    (
        4,
        segment_2,                          /* break zone */
        new_word ( word_31 ),               /* complement zone */
        new_word ( word_32 ),               /* object zone */
        word_null                           /* object zone */
    );

    link_words
    (
        2,
        segment_3,                          /* complement zone */
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
    /* forming complement-object segment 1, 3 */

    struct en_word * segment_1 = new_word ( word_39 );
    struct en_word * segment_3 = new_word ( word_38 );

    link_words
    (
        2,
        segment_1,                          /* complement zone */
        new_word ( word_32 )                /* object zone */
    );

    link_words
    (
        2,
        segment_3,                          /* complement zone */
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

    /* forming complement-object segment 2 */

    struct en_word * segment_2 = new_word ( word_105 );

    link_words
    (
        4,
        segment_2,                          /* break zone */
        new_word ( word_31 ),               /* complement zone */
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
    /* forming complement-object segment 1, 3 */

    struct en_word * segment_1 = new_word ( word_39 );
    struct en_word * segment_3 = new_word ( word_38 );

    link_words
    (
        2,
        segment_1,                          /* complement zone */
        new_word ( word_12 )                /* object zone */
    );

    link_words
    (
        2,
        segment_3,                          /* complement zone */
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

    /* forming complement-object segment 2 */

    struct en_word * segment_2 = new_word ( word_105 );

    link_words
    (
        3,
        segment_2,                          /* break zone */
        new_word ( word_31 ),               /* complement zone */
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
    /* forming a complement-object segment */

    struct en_word * segment_1 = new_word ( word_102 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_41 ),               /* complement zone */
        new_word ( word_42 )                /* object zone */
    );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_42, 0, jump );
}

void insert_25 ( void )
{
    /* forming a complement-object segment */

    struct en_word * segment_1 = new_word ( word_104 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_41 ),               /* complement zone */
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
    /* forming a complement-object segment */

    struct en_word * segment_1 = new_word ( word_100 );

    link_words
    (
        2,
        segment_1,                          /* break zone */
        new_word ( word_42 )                /* complement zone */
    );

    /* inserting a subject */

    link_words ( 2, segment_1, new_word ( word_b ) );

    /* forming a sentence */

    link_lines ( 1, segment_1 );

    new_sentence ( sentence, segment_1, word_42, 0, jump );
}

void insert_27 ( void )
{
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word ( word_104 );
    struct en_word * segment_2 = new_word ( word_42 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_11 ),               /* complement zone */
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
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word_with_negation ( word_100 );
    struct en_word * segment_3 = new_word ( word_43 + 1 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_43 ),               /* complement zone */
        new_word ( word_44 )                /* complement zone */
    );

    link_words
    (
        2,
        segment_3,                          /* complement zone */
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
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word_with_negation ( word_100 );
    struct en_word * segment_2 = new_word ( word_43 + 1 );
    struct en_word * segment_3 = new_word ( word_101 );

    link_words
    (
        3,
        segment_1,                          /* break zone */
        new_word ( word_43 ),               /* complement zone */
        new_word ( word_44 )                /* complement zone */
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
        word_0                              /* complement zone */
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
    /* forming complement-object segments */

    struct en_word * segment_1 = new_word_with_negation ( word_104 );
    struct en_word * segment_2 = new_word ( word_43 + 1 );
    struct en_word * segment_3 = new_word ( word_111 );

    link_words
    (
        4,
        segment_1,                          /* break zone */
        new_word ( word_45 ),               /* complement zone */
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
        word_0,                             /* complement zone */
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
