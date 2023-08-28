# Exercises

Solve the exercises from the end of the [reading material on condition
variables](http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf).  The
files you need are in the `exercise_code/` directory.

## And a fun one

Modify the futures implementation used by `fibs-futures.c` to also use
a thread pool or task queue to avoid having to launch a thread for
every future.  Combine this with `fibs-threadpool.c` to efficiently
exploit all degrees of parallelism.
