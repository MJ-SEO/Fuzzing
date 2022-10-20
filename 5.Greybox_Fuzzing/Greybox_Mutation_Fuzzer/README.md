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

- ```src/coverage.c``` is handle the ```gcov``` file. It read the gcov file and get information about line and branch ```coverage```.

- ```src/mutating.c``` is the part of mutation. The mutators that are implemented
<br/> 1. &nbsp; *insert_random_character*
<br/> 2. &nbsp; *insert_known_integer*
<br/> 3. &nbsp; *change_random_bits*
<br/> 4. &nbsp; *change_random_bytes* 
<br/> 5. &nbsp; *change_simple_arith*
<br/> 6. &nbsp; *change_known_integer*
<br/> 7. &nbsp; *delete_random_character*

- ```src/sched.c``` is part of ```Greybox Fuzzing```. Meanings, it uses the information of executions and coverage then makes better input for better testing. 

### lib 


- ```lib/my_troff.c```  

- ```lib/cgi_decoder.c```

- ```lib/http_program.c```

- ```lib/crashme.c```

Simple target programs to test fuzzing framework.


### test

- ```test/test_troff.c``` is the simple test driver for Fuzzing senario. 

- ```test/test_cat.c``` is the test driver for Fuzzing Linux command ```cat``` 

- ```test/test_cgi.c``` is the test driver to check for changes in ```Code Coverage```

- ```test/http_program.c``` is the test driver that parsing the given URL and check if it is vaild URL.

- ```test/crach.c``` is the simple test driver for observing the evolutionary algorithm of fuzzing via coverage.

---

## Usage

in test directory

> $ make crash


- crahme.c

``` C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(){
	char* inp = (char*)malloc(sizeof(char)*100);
	scanf("%s", inp);

	if(strlen(inp) > 0 && inp[0] == 'b'){
		if(strlen(inp) > 1 && inp[1] == 'a'){
			if(strlen(inp) > 2 && inp[2] == 'd'){
				if(strlen(inp) > 3 && inp[3] == '!'){
					assert(0);
				}
			}
		}
	}
	return 0;
}
```

Example)

> ./crash_test

```

[Trial 1] Input: good

...

[Trial 82] Input: bagoE!apd
[Trial 83] Input: bTgoodj
[Trial 84] Input: bTg
[Trial 85] Input: bagiood
[Trial 87] Input: badSf[good

...


                                       ---[Input 89]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000
                                        ---[Input 90]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000
                                        ---[Input 91]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000
                                        ---[Input 92]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000
                                        ---[Input 93]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000
                                        ---[Input 94]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000
                                        ---[Input 95]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000
                                        ---[Input 96]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000
                                        ---[Input 97]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000
                                        ---[Input 98]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000
                                        ---[Input 99]---
[Source: crashme.c] Line: 5/9 Union: 5 Coverage: 0.555556    Branch: 4/16 Union: 4 Coverage: 0.250000

=====================================================================================================
It took the fuzzer 0.045911 seconds to generate and execute 100 inputs.

```

You can see a input close to ```bad!``` even the start seed(input) was a ```good```.
