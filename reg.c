/*
 * reg.c
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
 * know that the focus of thinking is unconditionally on the subject-predicate unit right next to a break syllable, rather than
 * on the break syllable itself which is usually in the first position.
 *
 * know that all the thinking in our brains is just mathematical permutations and combinations.
 *
 * https://github.com/topwaye/klingon
 */

#include <assert.h>

#include "user.h"

#define FUNCS_PER_ROW           32

typedef void ( * insert_t ) ( void );

const insert_t insert_func [ ] [ FUNCS_PER_ROW ] =
{
    {
        insert_1, insert_2, insert_3, insert_4, insert_5, insert_6, insert_7, insert_8, insert_9, insert_10,
        insert_11, insert_12, insert_13, insert_14, insert_15, insert_16, insert_17, insert_18, insert_19, insert_20,
        insert_21, insert_22, insert_23, insert_24, insert_25, insert_26, insert_27, insert_28, insert_29, insert_30
    },
    {
        insert_31, insert_32, insert_33, insert_34, insert_35, insert_36, insert_37, insert_38, insert_39, insert_40
    },
    {
        insert_41, insert_42, insert_43, insert_44, insert_45, insert_46, insert_47, insert_48, insert_49, insert_50
    },
    {
        insert_51, insert_52, insert_53, insert_54, insert_55, insert_56, insert_57, insert_58, insert_59, insert_60
    }
};

const int row_count = sizeof ( insert_func ) / sizeof ( insert_func [ 0 ] );

int get_func_group_count ( void )
{
    return row_count;
}

void run ( int group )
{
    const insert_t * pp;

    assert ( group < row_count );
    pp = * ( insert_func + group );
    while ( * pp )
        ( * pp ++ ) ( );
}
