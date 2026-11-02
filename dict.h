/*
 * dict.h
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

#ifndef DICT_H
#define DICT_H

/* verb-object phrases */

extern struct en_word word_11 [ ];
extern struct en_word word_12 [ ];

extern struct en_word word_13 [ ];
extern struct en_word word_14 [ ];

extern struct en_word word_15 [ ];

extern struct en_word word_16 [ ];

extern struct en_word word_17 [ ];
extern struct en_word word_18 [ ];

extern struct en_word word_19 [ ];

extern struct en_word word_20 [ ];
extern struct en_word word_21 [ ];
extern struct en_word word_22 [ ];

extern struct en_word word_23 [ ];
extern struct en_word word_24 [ ];
extern struct en_word word_25 [ ];

extern struct en_word word_26 [ ];
extern struct en_word word_27 [ ];
extern struct en_word word_28 [ ];

extern struct en_word word_29 [ ];
extern struct en_word word_30 [ ];

extern struct en_word word_31 [ ];
extern struct en_word word_32 [ ];

extern struct en_word word_33 [ ];

extern struct en_word word_34 [ ];
extern struct en_word word_35 [ ];

extern struct en_word word_36 [ ];

extern struct en_word word_37 [ ];

extern struct en_word word_38 [ ];

extern struct en_word word_39 [ ];
extern struct en_word word_40 [ ];

extern struct en_word word_41 [ ];
extern struct en_word word_42 [ ];

extern struct en_word word_43 [ ];
extern struct en_word word_44 [ ];

extern struct en_word word_45 [ ];
extern struct en_word word_46 [ ];

/* break syllables */

extern struct en_word word_100 [ ];
extern struct en_word word_101 [ ];
extern struct en_word word_102 [ ];
extern struct en_word word_103 [ ];

extern struct en_word word_104 [ ];
extern struct en_word word_105 [ ];

extern struct en_word word_106 [ ];

extern struct en_word word_107 [ ];
extern struct en_word word_108 [ ];
extern struct en_word word_109 [ ];

extern struct en_word word_110 [ ];

/* subjects */

extern struct en_word word_b [ ];
extern struct en_word word_c [ ];

/* word_null: the only entry point where a sentence is nested */

extern struct en_word word_null [ ];

/* sentences */

extern struct en_content sentence [ ];

#endif
