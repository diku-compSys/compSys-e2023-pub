# Exercises

## Scalability and speedup

### Amdahl's Law

For this question we use Amdahl's Law to estimate speedup in latency.
Suppose we have a program where 4% of the work is *not*
parallelisable.  Assuming the rest can be fully parallelised without
any overhead:

1. What is the speedup if we run it on a 4-processor machine?
2. What about with 128 processors?
3. What is the smallest number of processors that will give us a speedup of at least 5?
4. What is the smallest number of processors that will give us a speedup of at least 30?

<details>
  <summary>Open this to see the answer</summary>

Since 4% is not parallelisable, *p=0.96*, which gives us *S(N) =
1/(1-0.96+(0.96/N))*.

1. *S(4) = 1 / (1-0.96+(0.96/4)) = 3.57*

2. *S(128) = 1 / (1-0.96+(0.96/128)) = 21.05*

3. *S(N) = 5*.  Solving for *N*, we get *N=6*.

4. Since the limit of *S(N)* is *25* as *N* goes to infinity, we
   cannot ever get a speedup of at least 30 with this program.

</details>

### Gustafson's Law

For this question we use Gustafson's Law to estimate speedup in latency.  Suppose
we have a program where 4% of the work is *not* parallelisable.
Assuming the rest can be fully parallelised without any overhead, and
that the parallel workload is proportional to the amount of
processors/threads we use:

1. What is the speedup if we run it on a 4-processor machine?
2. What about with 128 processors?
3. What is the smallest number of processors that will give us a speedup of at least 5?
4. What is the smallest number of processors that will give us a speedup of at least 30?

<details>
  <summary>Open this to see the answer</summary>

Since 4% is not parallelisable, *s=0.04*, which gives us *S(N) =
N + (1-N) * 0.04*.

1. *S(4) = 3.88*

2. *S(128) = = 122.92*

3. *S(N) = 5*.  Solving for *N*, we get *N=31/6*, and since we cannot
   have a fractional number of processors, we round up to *N=6*.

4. *S(N) = 30*.  Solving for *N*, we get *N=749/24*, which we round up
   to *N=32*.

</details>

### Estimating parallel fraction

Suppose that a program runs in *50s* on one processor (*N=1*) and in
*10s* on sixteen processors (*N=16*) with the same workload.  Assuming
that the parallel part of the program scales linearly with the number
of processors used, what is the parallelisable fraction *p*?

<details>
  <summary>Open this to see the answer</summary>

Since the workload is fixed, we use Amdahl's law.  The speedup is
*50/10=5* for *N=16*, which we plug into the formula and get the
following equation:

*1/((1-p)+(p/16)) = 5*

Solving for *p*, we get *p=64/75*, or *p ~ 0.86*.

</details>

### Performance comparisons

Suppose you wish to parallelise an image processing algorithm.  You
are given an efficient *sequential* implementation *I_s*, and you then
develop a parallel implementation *I_p*.  You have access to two
machines:

1. A machine with a single very fast processor running at 4GHz (i.e. executes 4
   billion instructions per second).

2. A machine with eight slower processors, each running at 2.5GHz
   (i.e. each executes 2.5 billion instructions per second).

Explain how you could perform a fair performance comparison of *I_s*
and *I_p*.

<details>
  <summary>Open this to see the answer</summary>

When we compare the performance of two programs, both must be shown in
their best light.  *I_s* cannot take advantage of more than one
processor, so it would be unfair to use a single one of the slow
processors.  Conversely, parallel programs like *I_p* might not run
optimally on a single processor.  Thus, we need to run *I_s* on system
1 and *I_p* on system 2 and compare their performance.  Since the
systems are different, we cannot use speedup-in-latency.  What we need
to do is compute the *throughput* of the two programs, and then we can
compute the speedup-in-throughput.
</details>

## Parallelisation with POSIX Threads

In the following exercises you will parallelise a program that sums
the bytes of a file.  A sequential (single-threaded) solution is given
in [exercise_code/sumbytes-one.c]([exercise_code/sumbytes-one.c]).  We
will be using the [*fork-join
model*](https://en.wikipedia.org/wiki/Fork%E2%80%93join_model) of
parallelism.  Contrary to its name, it has nothing to do with the
`fork()` function.  Rather it is a model of parallelism where we solve
a big problem by:

1. Conceptually or physically splitting the problem into *chunks*.
2. Launching a thread per chunk that processes just that chunk and
   provides a partial result.  This is the "fork" part.
3. Waiting for these threads to finish.  This is the "join" part.
4. Sequentially combining the per-thread partial results into a
   complete result.

The fork-join model is closely related to the notion of *divide and
conquer* algorithms.  Its great advantage is that when used correctly,
it is easy to avoid race conditions.

First you will need to generate a big file.  The `Makefile` in the
[exercise_code](exercise_code/) contains helpful targets.  For
example, run `make 1000000000_bytes` to create a file containing one
billion random bytes.  You can then compile `sumbytes-one` with `make
sumbytes-one` and benchmark it as follows:

```C
$ time ./sumbytes-one 1000000000_bytes
sum: 127499175667

real    0m0.161s
user    0m0.135s
sys 0m0.027s
```

You should read the source code carefully and make sure you understand
it.  It is not long.  You should check that the result you obtain with
your parallelised versions is identical to the result produced by the
sequential version.

### Parallelising with two worker threads

We will start by parallelising the program using two threads.  Each
thread must sum half of the array into partial sums, which will then
be added to form the final sum.  In principle, this can result in a 2x
speedup.

Use the commented skeleton code found in
[sumbytes-two.c]([exercise_code/sumbytes-two.c]).  The main challenge
is passing information (the *payload*) to each worker thread.  The
actual summation is much like in
[sumbytes-one.c]([exercise_code/sumbytes-one.c]), except that instead
of summing *all* of data, the first thread sums index 0 up to the
midpoint, and the other sums from the midpoint and until the end.

#### Usage examples

```
$ time ./sumbytes-two 1000000000_bytes
Sum: 127499175667

real    0m0.091s
user    0m0.143s
sys     0m0.024s
```

### Parallising with any number of worker threads

In this variant we will parallelise using *n* threads, where *n* is a
value given by the user.  In real programs, we would often determine
*n* by checking how many processors are installed in the machine we
are running on, but here we make it explicit.

Use the commented skeleton code provided in
[sumbytes-many.c](exercise_code/sumbytes-many.c).  As before, the main
design question is which data you pass to each worker thread (i.e. the
contents of `struct worker_payload`).  The overall structure is
largely similar to before, except that computing the start- and end
offsets used in each thread to index `data` are more involved.

#### Usage examples

Note that this program takes an extra initial option, namely the
number of threads.

```
$ time ./sumbytes-many 1 1000000000_bytes
sum: 127499175667

real    0m0.186s
user    0m0.137s
sys     0m0.049s
```

Or with 16 threads:

```
$ time ./sumbytes-many 16 1000000000_bytes
sum: 127499175667

real    0m0.043s
user    0m0.390s
sys     0m0.083s
```

## Exercises from COD

* 6.3

* 6.8
