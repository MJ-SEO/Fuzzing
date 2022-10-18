# Fuzzing: Breaking Things with Random Inputs


### **A Simple Fuzzer**
<br/>

``` python
def fuzzer(max_length=100, char_start=32, char_range=32):
    """A string of up to `max_length` characters
       in the range [`char_start`, `char_start` + `char_range`]"""
    string_length = random.randrange(0, max_length + 1)
    out = ""
    for i in range(0, string_length):
        out += chr(random.randrange(char_start, char_start + char_range))
    return out	
```

This is the very naive Fuzzer that made a random input. (actually, it is no more than random input generator)

It'll be improved and complicated while this study progress more and more.

By executing ```test/simple_fuzzer.c```, you can get a randomly generated input.

---


### **Fuzzing_External_Programs**

<br/>


This part handle how to "Fuzzing" external program.

I used unnamed Pipes and Fork

When you execute ```test/long_running_fuzzing```, it "Fuzzing" the target program 100 times.

It means that it repeats 100 time the processes that creates random input, executes target program and makes output files.



- Target program : [bc calculator](https://man7.org/linux/man-pages/man1/bc.1p.html)

- Used: dup2, fork()


---

### **Bugs_Fuzzers_Find**

<br/>

```test/bugs_test.c``` contains scenarios that find bugs with Fuzzing.

It is the list of the sort of bugs Fuzzing could find. 

1. Buffer Overflows

2. Missing Error Checks

3. Rogue Numbers



---

### **Catching_Errors**



1. Generic Checkers

	- Checking Memory Accesses
    
    <br/>
    
    ```test/general_memory.c``` is the simple program to practice LLVM memory sanitizer to check out-of-bound momory access.


    > clang -fsanitize=address -g -o program general_memory.c
    > ./program 99; echo $? <br/>
    > ./program 110;

    <br/>
	
	- Information Leaks	

    <br/>

    ```test/general_leaks.c``` is the simple [HeartBleed-Bug](https://heartbleed.com/) test senario with fuzzing



2. Program-Specific Checkers

    ```test/general_leaks.c``` is the simple testing senario for specific program.


---



### [A Fuzzing Architecture](https://github.com/MJ-SEO/Fuzzing/tree/master/2.Fuzzing/A_Fuzzing_Architecture)

<br/>

This is the first Fuzzing framework with whole functions handled by above. 

It contains.

> Simpler fuzzer <br/>
> Executing external program <br/>
> Long-running fuzzer <br/>
> Detect and report bugs (Oracle) <br/>

The detailed description is in the above repository.