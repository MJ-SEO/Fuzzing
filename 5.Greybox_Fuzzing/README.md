# Greybox Fuzzing

## Greybox Fuzzer

The algorithms in this chapter stem from the popular [American Fuzzy Lop(AFL)](https://lcamtuf.coredump.cx/afl/) fuzzer.

AFL is also a greybox fuzzer (not blackbox nor whitebox). Meaning, AFL leverages coverage-feedback to learn how to reach deeper into the program. It is not entirely blackbox because AFL leverages at least some program analysis. It is not entirely whitebox either because AFL does not build on heavyweight program analysis or constraint solving. Instead, AFL uses lightweight program instrumentation to glean some information about the (branch) coverage of a generated input. If a generated input increases coverage, it is added to the seed corpus for further fuzzing.

Basic idea is that if a input increase the code coverage, add the input in the seed corpus.


---

## [A Fuzzing Architecture with Greybox Mutation](https://github.com/MJ-SEO/Fuzzing/tree/master/4.Mutation_Fuzzing/Mutation_Based_Fuzzer)

The detailed description and usage is in the above repository.

