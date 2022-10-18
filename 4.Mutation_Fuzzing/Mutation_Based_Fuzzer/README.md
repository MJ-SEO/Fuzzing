# A Fuzzing Architecture

## Architecture

### src

- ```src/config.c``` is the part that makes the initial setup of the Fuzzing framework. You can find the variables of *test_config_t* in ```include/config.h```

- ```src/create_input.c``` is the part that make input for Fuzzing. it makes a random input or mutated input of given input via configuration.

- ```src/fuzzer.c``` is the main part of Fuzzing framework.
 It consist of <br/> 1. &nbsp; Initialize of Fuzzing framework via configuration. 
<br/> 2. &nbsp; Create random or mutated input for Fuzzing.
<br/> 3. &nbsp; Execute the program with Fuzzed input created above
<br/> 4. &nbsp; Get information from the results of executed program and save information via file into temporary directory.
<br/> 5. &nbsp; Print out the Code Coverage and Fuzzing result. 

- ```src/coverage.c``` is handle the ```gcov``` file. It read the gcov file and get information about line and branch coverage.

- ```src/mutating.c``` is the part of mutation. The mutators that are implemented
<br/> 1. &nbsp; *insert_random_character*
<br/> 2. &nbsp; *insert_known_integer*
<br/> 3. &nbsp; *change_random_bits*
<br/> 4. &nbsp; *change_random_bytes* 
<br/> 5. &nbsp; *change_simple_arith*
<br/> 6. &nbsp; *change_known_integer*
<br/> 7. &nbsp; *delete_random_character*


### lib 


- ```lib/my_troff.c```  

- ```lib/cgi_decoder.c```

- ```lib/http_program.c```

Simple target programs to test fuzzing framework.


### test

- ```test/test_troff.c``` is the simple test driver for Fuzzing senario. 

- ```test/test_cat.c``` is the test driver for Fuzzing Linux command ```cat``` 

- ```test/test_cgi.c``` is the test driver to check for changes in ```Code Coverage```

- ```test/http_program.c``` is the test driver that parsing the given URL and check if it is vaild URL.

---

## Usage

in test directory

> $ make 

Example)

> ./http_test

```
========================================Fuzzing Summary=========================================
                                        ---[Input 0]---
[Source: http_program.c] Line: 26/34 Total: 26 Coverage: 0.764706    Branch: 10/10 Total: 10 Coverage: 1.000000
                                        ---[Input 1]---
[Source: http_program.c] Line: 26/34 Total: 32 Coverage: 0.941176    Branch: 10/10 Total: 10 Coverage: 1.000000
                                        ---[Input 2]---
[Source: http_program.c] Line: 26/34 Total: 32 Coverage: 0.941176    Branch: 10/10 Total: 10 Coverage: 1.000000
                                        ---[Input 3]---
[Source: http_program.c] Line: 26/34 Total: 32 Coverage: 0.941176    Branch: 10/10 Total: 10 Coverage: 1.000000
                                        ---[Input 4]---
[Source: http_program.c] Line: 26/34 Total: 32 Coverage: 0.941176    Branch: 10/10 Total: 10 Coverage: 1.000000
                                        ---[Input 5]---
[Source: http_program.c] Line: 26/34 Total: 32 Coverage: 0.941176    Branch: 10/10 Total: 10 Coverage: 1.000000
                                        ---[Input 6]---
[Source: http_program.c] Line: 26/34 Total: 32 Coverage: 0.941176    Branch: 10/10 Total: 10 Coverage: 1.000000
                                        ---[Input 7]---
[Source: http_program.c] Line: 26/34 Total: 32 Coverage: 0.941176    Branch: 10/10 Total: 10 Coverage: 1.000000
                                        ---[Input 8]---
[Source: http_program.c] Line: 26/34 Total: 32 Coverage: 0.941176    Branch: 10/10 Total: 10 Coverage: 1.000000
                                        ---[Input 9]---
[Source: http_program.c] Line: 26/34 Total: 32 Coverage: 0.941176    Branch: 10/10 Total: 10 Coverage: 1.000000
===================================================================================================
```


