# Exercises

Based on exercises by: Michael Kirkedal Thomsen <kirkedal@acm.org>

There are two classes of exercises today (and more than you have time
for, but this is an important topic, so consider spending some of your
free time on them).

The first exercises are theoretical exercises of a form very similar
to what you will encounter at the exam.

The remaining exercises are practical exercises that are more
reminiscent of what you will do with the rest of your life, and also
the mandatory assignments.

## Theoretical exercises from COD

*Note*: Assume words are 32 bit.

* 5.1
  * *Note for 5.1.4-6*: Matlab uses Column-major order. See [this](https://se.mathworks.com/help/coder/ug/what-are-column-major-and-row-major-representation-1.html) for reference.

* 5.2
  * Assume the list of addresses are **32-bit**.

* 5.5 (The tag bits are only supposed to go up to 31)

## Simple performance measurements

You can use `time(1)` to get a quick measurement of the execution
time. Be aware that this is not very accurate and can be susceptible
to cache effects and what other tasks are running. So run it several
times to get a good estimate. To run use

```
> time ./[program]
```

If you want a better profiling you can look at the Linux tool
`gprof(1)` or Google Performance Tools.

## Summing an array

Consider the two programs from the lecture included in the
`exercise_code` directory.

### Locality

First, recap the two types of locality that we would like to achieve
to in order to get good performance. Why does `sum_array_rows` have
better locality than `sum_array_cols`? Which types of locality does
the programs have?

### Performance

Try to run the programs on increasing sizes until you can see a
difference. See below

Map the execution time for increasing sizes of input. Compare the two
programs. What is the asymptotic behaviour? Calculate the execution
time per element.

How does it compare to the operations per element that we discussed at
the lecture? You need to examine the assembler code to know the exact
number for this.

Hint, I can suggest that you setup a simple test-bench (e.g. using a
script) that makes the above calculations, but don't spend too much
time on it.

## Summing a 3D array

Consider the following program taken from the slides.

```
/* You might want to use different values for L,M,N when performing benchmarks. */
#define L 10
#define M 10
#define N 10

long sum_array_3d(long a[L][M][N])
{
  long sum = 0;
  int i, j, k;
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < L; k++) {
        sum += a[k][i][j];
      }
    }
  }
  return sum;
}
```

There is a good reference for how to use 3d arrays here on
[stackoverflow](https://stackoverflow.com/questions/40845302/passing-three-dimensional-arrays-to-a-function-in-c).


### Locality

Sketch what the structure of a 3D array will be like in the 1D memory
of the computer. What should be the order of the indices be to achieve
spatial locality?

### Performance

Write the above into a C program that you can run. You can base it on
the previous examples.

Test with different ordering of the indices to very verify your
previous result.

Take care to prevent the compiler from completely optimizing away your
computation.

## Visualising the memory mountain

In this task you will be generating a visualisation of the memory
mountain - a visualisation of memory access performance.  This will
help you gain an understanding of the memory hierarchy on your own
machine.  It will also provide an example of how to do (slightly)
refined benchmarking and visualisation.

You will do this by writing scaffolding and timing code around a core
loop similar to the one in the lecture.  Specifically, you should modify
the program [locality.c](mountain_src/locality.c) (and be sure to also grab
[Makefile](mountain_src/Makefile) and
[mountain.gnuplot](mountain_src/mountain.gnuplot) - you'll need them later).

The `test(limit,stride)` function, which you do *not* need to modify,
iterates up to the first `limit` elements of the global array `data`,
with a stride of `stride`.  By modifying `limit` we can investigate
the impact of temporal locality, and by modifying `stride` we can
investigate spatial locality.

### Determining memory traffic

The amount of memory read by a call `test(limit,stride)` depends on
`limit` and `stride`.  Write a function with the following prototype:

```C
double test_MiB(int limit, int stride);
```

The function must return the number of
[MiB](https://en.wikipedia.org/wiki/Mebibyte) accessed by a
corresponding call to `test(limit,stride)`.  Look at the definition of
`test()` and try to figure out how many bytes it accesses, then divide
that by *1048576*.

#### Hints

* Each single read from the `data` array reads four bytes.

* Assume `limit` is divisible by `stride`.  The difference doesn't
  matter at this scale.

### Benchmarking a function call

We wish to measure how many MiB per second (the *bandwidth*) a call
`test(limit,stride)` obtains.  The higher the bandwidth, the more
efficiently we are exploiting the memory hierarchy.  To do this, we
need to divide the amount of memory traffic (computed with
`test_MiB()`) with the time it takes to run the function.

To measure time within a C function, we use the `gettimeofday()`
function (from `<sys/time.h>`), which returns the number of seconds
that have passed since the 1st of January 1970 ([Unix
time](https://en.wikipedia.org/wiki/Unix_time)).  Since
`gettimeofday()` returns its result as a structure, it is common to
write a wrapper function that converts it to a `double` indicating the
number of seconds:

```C
double seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL); // The null is for timezone information.
  return tv.tv_sec + tv.tv_usec/1000000.0;
}
```

To measure how long some operation takes, we store the time before the
operation and the time after the operation.  The difference between
these times is then the duration of the operation.

Write a function with the following prototype:

```C
double test_time(int limit, int stride);
```

That returns, in MiB/s, the bandwidth of a call `test(limit,stride)`.

#### Hints

* Call the `seconds()` function above before and after you call `test()`.

* Use `test_MiB(limit,stride)` to compute the total memory traffic.

* Divide the memory traffic with the time it took to call the function.

* Your measurements may be noisy.  It is a good idea to do a *warmup
  run* of `test()`, that you do not time, to warm up the caches.  You
  may also wish to do *multiple runs* of `test()` and return the
  average time.

### Putting it together

In the `main()` function, call `test_time(limit,stride)` with various
values of `limit` and `stride`.  For each, write to standard output a
line in the following format:

```
stride bytes bandwidth
```

Where `stride` is the, well, stride, `bytes` is the amount of memory
accessed (*not* `limit`), and `bandwidth` is the return value of the
corresponding call to `test_time()`.

For example:

```
1 65536 10613.1
2 65536 10832.4
3 65536 10402.5
1 4194304 10609.8
2 4194304 10514.7
3 4194304 10383.2
1 1073741824 9674.6
2 1073741824 7225.4
3 1073741824 5433.8
```

#### Hints

* You should use two nested `for`-loops to iterate across various
  limits and strides.  For example, I use

  ```C
  for (int i = 13; i < 28; i++) {
    int limit = 2<<i;
    ...
  }
  ```

  to compute `limit`s from 2¹³ to 2²⁸.  Within the body of this loop,
  I then use a second `for`-loop `for (int stride = 1; stride < 12;
  stride++)`.

* Use `printf` like this:

  ```C
  printf("%d %d %.1f\n", stride, bytes, MiB_per_sec);
  ```

### Visualisation

The code handout comes with a small
[Gnuplot](http://www.gnuplot.info/) script for visualising data files
in the format produced by the `locality` program.  If you have Gnuplot
installed, and have implemented the previous tasks correctly, then
simply run

```
$ make mountain.png
```

and you should produce a more-or-less pretty picture of the memory
mountain.  You're welcome to look at the [reference
image](mountain_ref/mountain.png) I produced on my own computer.
Based on the images (either your own or mine), what can you say about
the memory hierarchy of these machines?

#### Installing Gnuplot

Gnuplot is a very widely used program.  On a Debian-like Linux system
(including WSL on Windows), do

```
$ sudo apt-get install gnuplot
```

On macOS with [Homebrew](https://brew.sh/),

```
$ brew install gnuplot
```

### Improve the visualisation (optional)

You may have been taught visualisation in other courses.  Now's the
time to put those skills to the test.  Visualise the memory mountain
in a nicer way and show us!  Perhaps interactively?
