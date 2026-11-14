/*
 * user.h
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

#ifndef USER_H
#define USER_H

extern void insert_1 ( void );
extern void insert_2 ( void );
extern void insert_3 ( void );
extern void insert_4 ( void );
extern void insert_5 ( void );

extern void insert_6 ( void );
extern void insert_7 ( void );
extern void insert_8 ( void );
extern void insert_9 ( void );
extern void insert_10 ( void );

extern void insert_11 ( void );
extern void insert_12 ( void );
extern void insert_13 ( void );
extern void insert_14 ( void );
extern void insert_15 ( void );

extern void insert_16 ( void );
extern void insert_17 ( void );
extern void insert_18 ( void );
extern void insert_19 ( void );
extern void insert_20 ( void );

extern void insert_21 ( void );
extern void insert_22 ( void );
extern void insert_23 ( void );
extern void insert_24 ( void );
extern void insert_25 ( void );

extern void insert_26 ( void );
extern void insert_27 ( void );
extern void insert_28 ( void );
extern void insert_29 ( void );
extern void insert_30 ( void );

extern void insert_31 ( void );
extern void insert_32 ( void );
extern void insert_33 ( void );
extern void insert_34 ( void );
extern void insert_35 ( void );

extern void insert_36 ( void );
extern void insert_37 ( void );
extern void insert_38 ( void );
extern void insert_39 ( void );
extern void insert_40 ( void );

extern void insert_41 ( void );
extern void insert_42 ( void );
extern void insert_43 ( void );
extern void insert_44 ( void );
extern void insert_45 ( void );

extern void insert_46 ( void );
extern void insert_47 ( void );
extern void insert_48 ( void );
extern void insert_49 ( void );
extern void insert_50 ( void );

extern void insert_51 ( void );
extern void insert_52 ( void );
extern void insert_53 ( void );
extern void insert_54 ( void );
extern void insert_55 ( void );

extern void insert_56 ( void );
extern void insert_57 ( void );
extern void insert_58 ( void );
extern void insert_59 ( void );
extern void insert_60 ( void );

extern void insert_61 ( void );

#endif
