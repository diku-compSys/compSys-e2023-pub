# General advice
Remember that there are many options for the commands, and that it is possible to see them in the man-page. If a command nearly fits your use-case, consider looking up additional options on the man-page, or combine it with another command. Most of the commands will be followed by some examples.

# Special directories/files
- `~`, the home directory
- `.`, the current directory
- `..`, the parent directory
- `/dev/null`, a file that dicards data written to it

# Glob patterns (from: [cheat-sheet](https://github.com/begin/globbing/blob/master/cheatsheet.md))
- `*`, matches any character zero or more times, except for /
- `**`, matches any character zero or more times, including /
- `?`, matches any character except for / one time
-  `[abc]`, matches any characters inside the brackets. For example, [abc] would match the characters a, b or c, and nothing else. Your can also specify a range of characters like `[0-9]`

## Notes:
- `*` typically does not match dotfiles (file names starting with a .) unless explicitly enabled by the user via options
- `?` also typically does not match the leading dot
- More than two stars in a glob path segment are typically interpreted as a single star (e.g. /***/ is the same as /*/)

# Common commands
- `ls`, list the files that are in the current directory. Use the option `-l` for listing in line format. Use the option `-a` to list all files, even hidden files
    - `ls -la`
- `mkdir`, create a new directory
    - `mkdir mydir`
- `mv`, move folders and files, or rename them 
    - `mv mydir anotherdir`
    - `mv mai.c main.c` (renaming the mai.c file to main.c)
    - `mv *.c c_files` (move all files with c extension to the c_files directory)
- `cp`, copy folders and and files. 
    - `cp main.c head.h mydir`
    - `cp -r mydir anotherdir` (copy whole directory recursively)
- `cd`, change directory.
    - `cd ../../mydir`, go to outer directory two times, and then into the `mydir` directory
    - `cd ~`, go to home directory
- `rm`, remove folders and files. **WARNING** only use this command if you are ABSOLUTELY certain you do not need the contents of the files or directories, since it is probably not possible to recover. Useful way to safeguard around this is to use the option `-i`, so that it needs confirmation when you are trying to delete a file. You can use `-r` to remove a folder recursively, but be aware of the potential repercussions
    - `rm -i file.txt`
    - `rm -ir mydir`
- `clear`, clear the terminal.
- `history`, list the commands you have used previously. 
- `man`, a REALLY useful command, that gives you iformation about unix commands, syscalls and c functions. `man 1` is for unix commands, `man 2` is for syscalls and `man 3` is for c-functions
    - `man 1 printf` 
    - `man 2 mmap`
    - `man 3 printf`
- `find`, find a file or directory. 
    - `find . -name "*.c"` find files with the c extension
- `grep`, output lines of a file, that contains the pattern (regex) specified. Use the `-E` option to assure that it is the extended version
    - `grep -E "yes|no" file.txt` (get all lines containing the word yes or no from the `file.txt` file)
- `diff` and `cmp`, use for comparing files
    - `diff file1 file2`
- `$?`, contains the return code for the last command
    - `echo $?`
    

# Input/ouput commands
- `echo`, output line of text to the terminal.
    - `echo 'hello\nworld`
- `printf`, a more advanced version of outputting text to the terminal
    - `printf "%-10s %-10s %-10s\n" "Name" "Age" "City"`
- `>`, redirect output to a file. This will create a new file or overwrite the file if it already exists
    - `echo hello > hello.txt`
    - `find . -name file1 2>/dev/null` (redirect errors (stderr) to /dev/null to not display errors)
- `>>`, append output to a file. This will also create a new file if it does not currently exist
    - `echo 'hello again' > hello.txt`
- `|`, pipe output from one program to the next
   - `history | tail -n 10` (get the last ten commands that you have executed)
   - `man printf | grep -E -B 10 -A 10 "return"` (get 10 lines before and after the lines that contain the word 'return' on the printf manpage)

# Other commands (commands you can install)
- `tree`, gives you a nice visualization of your directories and subdirectories
- `cowsay`, this is a very essential command, combine it with a man-page and you will never need Chat-GPT again
    - `man printf | cowsay`
- `cowthink`, like the above command, just a more thoughtful version