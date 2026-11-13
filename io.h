/*
 * io.h
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
 *     ^           ^
 *     V O   =>   S V O
 *
 *  S  represents a subject.
 *  V  represents a verb, preposition, adjective, or noun that is overlaid with break syllables, like 'do/don't'.
 *  O  represents an object.
 *
 * here are example sentences applying the above formula:
 *
 * 1. who are you ?
 *    ^who => ^( you who )
 *
 * 2. what do you think you play ?
 *    ^think; play what => ^( you think ); ( you play ) what
 *
 * 3. don't you want me to play with him ?
 *    ^want me; ^play; with him => ^( you want ) me; ^play; with him
 *
 * 4. my love shall in my verse ever live young.
 *    in my verse; ever ^live young; => ^( my love [ in my verse ] ever live ) young
 *
 * 5. would you have been playing cards ?
 *    ^^^playing cards => ^( you ^^playing ) cards
 *
 * know that all the thinking is anchored on a subject-predicate unit, not on a subject or a predicate alone.
 * know that all the thinking in our brains is just mathematical permutations and combinations.
 *
 * https://github.com/topwaye/klingon
 */

#ifndef IO_H
#define IO_H

extern void print_buffer_flush ( void );
extern int print ( const char * fmt, ... );

#endif
