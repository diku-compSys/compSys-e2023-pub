# Test-yourself - Implementation of CSV

In this exercise you will implement a simple CSV (comma-seperated-values) reader.

Implement it following in your favourite programming language. E.g. use C# that you learned in spring. Do not start to learn a new language.

When you make your implementation, always remember to KISS!: "Keep It Simple, Stupid!". 

Throughout the course, when you get an implementation problem, we will see if you can solve the task described and rate you on that. That can be to handle some format encoding (like below), ensure concurrency, or implement a communication protocol.
You should focus on making the solution simple and the code clear to read. And _simple_ does not mean small and fancy. It means that it is easy to understand so everyone can read what is going on.

_Don't_ make fancy optimisations; _don't_ merge loops together with advanced control structures. It is important to learn when we should do fancy optimisations. Most often the compiler can do a much better job optimising the code than you.

On CompSys we will optimize for cache performance later in the course, as compilers can have a hard time with this. This will be very clear from the tasks. Other optimisations will be covered throughout your studies.


## Implementation of CSV reader

Write a program that takes a comma separated string of numbers as command-line input and stores this in an array of Integers.

For example
```
.\read-comma-string "1,5,3,7,9,4"
```
will store this in a format
```
  array = [1,5,3,7,9,4]
```

Remember, you need to handle the conversion from strings to integers. Start by considering what the program needs to do. That is:

1. Consider how this should be implemented.
1. Consider if you can do this simpler. KISS!
1. Consider how you would like to test your implementation.
1. Implement it.
1. Test that your implementation is correct.

### Printing
Extend the above program with printing. That is:

1. Consider what format you want to print in.
1. Consider if you can do this simpler. KISS!
1. Consider how you would like to test your implementation.
1. Implement it.
1. Test that your implementation is correct.

### Space handling
Users are often slacking with spaces after (and perhaps even before) commas. For example, users could expect that
```
.\read-comma-string "1,5, 3,7 , 9, 4"
```
would give the same result as above. Extent your implementation to handle spaces. That is:

1. Consider where you would need to handle spaces in the string.
1. Consider how it is best to extend your previous implementation.
1. Consider if you can do this simpler. KISS!
1. Consider how you would like to test your implementation.
1. Implement it.
1. Test that your implementation is correct.

### Error handling
Users do not always give correct input values. They could add letters in the string or format it using other delimiters (e.g. a semicolon). Extent your implementation to handle errors. That is:

1. Consider what can go wrong.
1. Decide what should happen, when something goes wrong. 
   * Will you print error hints to help the user?
   * Will you accept that they use other delimiters than comma?
   * Will you skip some fields that are wrongly formatted?
1. Consider how to implement this.
1. Consider if you can do this simpler. KISS!
1. Consider how you would like to test your implementation.
1. Implement it.
1. Test that your implementation is correct.

### File input
Extend you implementation to accept inputs in local files. E.g. if the user writes 
```
.\read-comma-string my-file.csv
```
Given that there exists a file called `my-file.csv` containing a string, it will read its contents. That is:

1. Consider what you need to do to implement reading from files.
1. Decide how you would best extend your program.
1. Consider what can go wrong in the new implementation.
1. Decide how to handle these errors
1. Consider if you can do this simpler. KISS!
1. Consider how you would like to test your implementation.
1. Implement it.
1. Test that your implementation is correct.


### Full CSV format - 2D arrays
Extend you full CSV files. A CSV file consists of several lines of comma separated values; hence CSV. Extend you program to handle full CSV-file as file inputs. Such inputs should be read into two-dimensional arrays. That is:

1. Consider how you need to extend your program
1. Decide on an approach
1. Consider what can go wrong
1. Decide how to handle errors
1. Consider if you can do this simpler. KISS!
1. Consider how you would like to test your implementation.
1. Implement it.
1. Test that your implementation is correct.


## Post Scriptum

The overall task was to implement a CSV reader. However, this exercise has on purpose been separated into minor steps that build on the previous one. At the end we have the full implementation.
This strategy simplifies the implementation of the reader. Instead of making one big program, we can make several smaller ones that in the end gives the intended result.

Assignments in CompSys will not be as detailed as this. Some have hints to it, though, but never to this level. Before starting to program, always consider how you can separate the problem into smaller ones. Use it to design you implementation. Write about this design and the choices you made for it in your report.

All good programs starts away from the keyboard!
