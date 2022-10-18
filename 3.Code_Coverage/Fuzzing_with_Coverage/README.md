# A Fuzzing Architecture

## Architecture

### src

- ```src/config.c``` is the part that makes the initial setup of the Fuzzing framework. You can find the variables of *test_config_t* in ```include/config.h```

- ```src/create_input.c``` is the part that make input for Fuzzing. In this stage, it only makes a random input via configuration.

- ```src/fuzzer.c``` is the main part of Fuzzing. It consist of <br/> 1. &nbsp; Initialize of Fuzzing framework via configuration. 
<br/> 2. &nbsp; Create input for Fuzzing.
<br/> 3. &nbsp; Execute the program with Fuzzed input created above
<br/> 4. &nbsp; Get information from the results of executed program and save information via file into temporary directory.
<br/> 5. &nbsp; Print out the Code Coverage and Fuzzing result. 

- ```src/coverage.c``` is handle the ```gcov``` file. It read the gcov file and get information about line and branch coverage.

### lib 


- ```lib/my_troff.c```  

- ```lib/cgi_decoder.c```

Simple target programs to test fuzzing framework.


### test

- ```test/test_troff.c``` is the simple test driver for Fuzzing senario. 

- ```test/test_cat.c``` is the test driver for Fuzzing Linux command ```cat``` 

- ```test/test_cgi.c``` is the test driver to check for changes in ```Code Coverage```


---

## Usage

in test directory

> $ make 

Example)

> ./test_cgi

```
==========================================Trial==========================================
[Input 1] Line: 28/36 Total: 28 Latio:0.777778   Branch: 10/16 Total: 10 Latio:0.625000
[Input 2] Line: 29/36 Total: 29 Latio:0.805556   Branch: 10/16 Total: 10 Latio:0.625000
[Input 3] Line: 28/36 Total: 29 Latio:0.805556   Branch: 10/16 Total: 10 Latio:0.625000
[Input 4] Line: 28/36 Total: 29 Latio:0.805556   Branch: 10/16 Total: 10 Latio:0.625000
[Input 5] Line: 29/36 Total: 29 Latio:0.805556   Branch: 10/16 Total: 10 Latio:0.625000
[Input 6] Line: 28/36 Total: 29 Latio:0.805556   Branch: 10/16 Total: 10 Latio:0.625000
[Input 7] Line: 30/36 Total: 33 Latio:0.916667   Branch: 14/16 Total: 14 Latio:0.875000
[Input 8] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 9] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 10] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 11] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 12] Line: 30/36 Total: 33 Latio:0.916667   Branch: 14/16 Total: 14 Latio:0.875000
[Input 13] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 14] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 15] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 16] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 17] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 18] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 19] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
[Input 20] Line: 28/36 Total: 33 Latio:0.916667   Branch: 10/16 Total: 14 Latio:0.875000
=========================================================================================

===========================Fuzzing Summary===========================
* Trial : 20
* Pass  : 18
* Fail  : 2
* Line Coverage : (33/36) 0.916667
* Branch Coverage : (14/16) 0.875000
=====================================================================
```
