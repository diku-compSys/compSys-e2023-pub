# Exercise 1 (unix commands): 
Mess around with the unix commands of `mkdir`, `cp -`, `ls -la`, clear, move, rm. For around ~5 min suggestions include:
- Making a folder
- Moving a file from a folder to another, not necessarily only 1 step at a time.
- Copying a file
- Copying a whole folder or folder within folder etc. recursively
- Clearing the terminal with `clear`
- Deleting a file or an empty folder. Careful with deleting with `-r` (recursively). 

# Exercise 2:
## Task 1:
```c
void print_example(int importantNumber) {
  if (fprintf("Output.txt", "The chosen number is (%d)\n",
    importantNumber) <= 0) {
  exit(EXIT_FAILURE);
  }
}
```
With the help of the manual command `man` in the terminal do the following:
In your own words, describe what this function does.
Hints:
- Consider the difference between `fprintf` and `printf`
- Consider what the if statement does/when the condition is true.

## Task 2 (Optional, but very relevant):

With the help of the manual command `man` in the terminal do the following:
Either show via psuedocode, or explain in your own words:
How would you, check that a file given as argument to `fopen` was a successfully opened using said function?

Hints:
- A file is not successfully opened, if the filename given as an argument does not exist
- Look at the return section of the manual page of `fopen`
- Consider that if the file is indeed opened correctly, it should be able to be used afterwards. 
- If writing psuedocode, please do not worry about the correctness of the code, at all.

# Exercise 3
**NOTE: All tasks should be done only from the terminal.**

## Task 1
Create the file `n.txt` that contains the line `Numbers` (remove it with `rm` first if it already exists).

## Task 2
Overwrite the file `n.txt` so that it only contains the line `Numbers:`.

## Task 3
Append the lines: `123`., `456` and `789` to the `n.txt` file.

## Task 4
- Use grep to get all lines from `n.txt` that contains one of theses numbers: `4`, `5`, `6`, `89`. (Hint: use the option `-E` and then `|` in the grep pattern)
- Pipe the output into `wc -l`. Is this the expected result?

## Task 5
What is the return code of `grep -E "0" n.txt`? Explain why.

## Task 6 (optional)
Create a script called `deathstar.sh` that takes a filename as an argument, and removes all the lines that contains the word `world` or `planet`, and outputs the result to the terminal.
Hints: 
- You can get the first argument in the script with `$1`
- Use `-Ev` as an option to grep
- Use `chmod +x` to make the script able to execute

# Extra resources
If you want to read more about what you can do in the command-line:
[Unix-Like Data Processing 2017](https://github.com/diku-summer-programming/DSoP21/blob/main/uldp17-2018-08-16.pdf)
If you want to practice (and learn more):
[The Bandit wargame](https://overthewire.org/wargames/bandit/)

