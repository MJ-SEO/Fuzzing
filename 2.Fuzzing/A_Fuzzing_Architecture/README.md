# A Fuzzing Architecture

## Architecture

### src

- ```src/config.c``` is the part that makes the initial setup of the Fuzzing framework. You can find the variables of *test_config_t* in ```include/config.h```

- ```src/create_input.c``` is the part that make input for Fuzzing. In this stage, it only makes a random input via configuration.

- ```src/fuzzer.c``` is the main part of Fuzzing. It consist of <br/> 1. &nbsp; Initialize of Fuzzing framework via configuration. 
<br/> 2. &nbsp; Create input for Fuzzing.
<br/> 3. &nbsp; Execute the program with Fuzzed input created above
<br/> 4. &nbsp; Get information from the results of executed program and save information via file into temporary directory.
<br/> 5. &nbsp; Print out the Fuzzing result. 

### lib

- ```lib/my_troff```


### test

- ```test/test_troff.c``` is the simple test driver for Fuzzing senario. 

- ```test/test_cat.c``` is the test driver for Fuzzing Linux command ```cat``` 


---

## Usage

in test directory

> $ make 

Example)

with configuration in ```test_cat.c```

> ./cat_test

> [Random Input] ggUWOrpo[ge1;olkf^
> <br/> [Random Input] u]pUo_n_ugjXr^\hb_gj
> <br/>[Random Input] ]qbWr[f
> <br/>[Random Input] e\ddoXfi_mY
> <br/>[Random Input] Uj^jlW[i\adic^mu
> <br/>[Random Input] \[sistYe^pisZgorgsel_r
> <br/>[Random Input] uhiYmd
> <br/>[Random Input] jcpWjhj_cr_pfijo
> <br/>[Random Input] pnrbsgoiYZa\krnt`Vph*
> <br/>[Random Input] dWb^q\ilnc]s
> <br/>
> <br/>==========Fuzzer Summary===========
> <br/>Number of Tests: 10
> <br/>No_dat_Failures: 0
> <br/>No_8bit_Failures: 0
> <br/>No_backslash_d_Failures: 0
> <br/>Normal cases: 10
> <br/>===================================


