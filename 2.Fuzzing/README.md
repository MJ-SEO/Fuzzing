# Fuzzing: Breaking Things with Random Inputs

[Reference Site](https://www.fuzzingbook.org/html/Fuzzer.html)

## [A Simple Fuzzer (Copy in C)](https://github.com/MJ-SEO/Fuzzing/blob/master/2.Fuzzing/fuzzer.c)

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
---

## [Fuzzing_External_Programs](https://github.com/MJ-SEO/Fuzzing/tree/master/2.Fuzzing/Fuzzing_External_Programs)

``` python
program = "bc"
with open(FILE, "w") as f:
    f.write("2 + 2\n")
result = subprocess.run([program, FILE],
                        stdin=subprocess.DEVNULL,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                        universal_newlines=True)
```

- Reference : [bc calculator](https://man7.org/linux/man-pages/man1/bc.1p.html)

---

## [Bugs_Fuzzers_Find](https://github.com/MJ-SEO/Fuzzing/tree/master/2.Fuzzing/Bugs_Fuzzers_Find)

1. Buffer Overflows

2. Missing Error Checks

3. Rogue Numbers

---

## [Catching_Errors](https://github.com/MJ-SEO/Fuzzing/tree/master/2.Fuzzing/Catching_Errors)

1. Generic Checkers

	Checking Memory Accesses
	
	Information Leaks	

2. Program-Specific Checkers


---

## [A Fuzzing Architecture](https://github.com/MJ-SEO/Fuzzing/tree/master/2.Fuzzing/A_Fuzzing_Architecture)

