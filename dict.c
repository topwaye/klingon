/*
 * dict.c
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

#include "kernel.h"

/* verb-object phrases */

struct en_word word_11 [ ] = { { "play" } };
struct en_word word_12 [ ] = { { "what" }, { "what" } };

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

struct en_word word_47 [ ] = { { "gonna" } };

struct en_word word_48 [ ] = { { "going" } };
struct en_word word_49 [ ] = { { "off" } };

struct en_word word_50 [ ] = { { "feel" } };
struct en_word word_51 [ ] = { { "how" } };

struct en_word word_52 [ ] = { { "eat" } };
struct en_word word_53 [ ] = { { "a" } };
struct en_word word_54 [ ] = { { "piece" } };
struct en_word word_55 [ ] = { { "of" } };
struct en_word word_56 [ ] = { { "cake" } };

struct en_word word_57 [ ] = { { "the" } };
struct en_word word_58 [ ] = { { "enemy" }, { "enemy" } };

struct en_word word_59 [ ] = { { "friend" } };

struct en_word word_60 [ ] = { { "often" } };

struct en_word word_61 [ ] = { { "since" } };
struct en_word word_62 [ ] = { { "when" } };

struct en_word word_63 [ ] = { { "have" } };

struct en_word word_64 [ ] = { { "there" } };

struct en_word word_65 [ ] = { { "about" } };

struct en_word word_66 [ ] = { { "plus" } };

struct en_word word_67 [ ] = { { "equals" } };
struct en_word word_68 [ ] = { { "two" } };

struct en_word word_69 [ ] = { { "let" } };

struct en_word word_70 [ ] = { { "look" } };

struct en_word word_71 [ ] = { { "like" } };

struct en_word word_72 [ ] = { { "neither" } };

struct en_word word_73 [ ] = { { "only" } };
struct en_word word_74 [ ] = { { "if" } };

/* break syllables */

struct en_word word_100 [ ] = { { "are", 2 }, { "are", 2 } };
struct en_word word_101 [ ] = { { "is", 2 } };
struct en_word word_102 [ ] = { { "to", 1 }, { "to", 1 } };
struct en_word word_103 [ ] = { { "be", 1 }, { "be", 1 } };

struct en_word word_104 [ ] = { { "do", 2 } };
struct en_word word_105 [ ] = { { "does", 2 } };

struct en_word word_106 [ ] = { { "shall", 5 } };

struct en_word word_107 [ ] = { { "would", 2 } };
struct en_word word_108 [ ] = { { "have", 1 } };
struct en_word word_109 [ ] = { { "been", 1 } };

struct en_word word_110 [ ] = { { "have", 2 } };

struct en_word word_111 [ ] = { { "can", 6 } };

/* subjects */

struct en_word word_b [ ] = { { "you" }, { "you" } };
struct en_word word_c [ ] = { { "he" } };

/* word_null: the only entry point where a sentence is nested */

struct en_word word_null [ ] = { { 0 } };

/* sentences */

struct en_content sentence [ ] = { { 0 }, { 0 } };
