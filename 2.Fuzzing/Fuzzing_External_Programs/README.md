# Fuzzing External Programs

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

## Objectives

Fuzzing External Programs(bc calculator) with Fork and Pipes

- Learned

	Used Unnamed Pipe

	Execute Extenal Program with Fuzzer 	 
