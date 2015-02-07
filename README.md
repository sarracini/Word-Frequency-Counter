# Word Frequency Counter

Several C programs to process text documents. The programs will count the frequency of every distinct word in a text document and print out the top 3 most frequent words for each provided text document. User can input more than one file at a time to be processed. 

- ```rvw.c``` does word counting sequentially in the main process, printing results one after the other for each data set.
- ```process.c``` does word counting concurrently using multiple processes, creating a new child process per data set. 
- ```thread.c``` does word counting concurrently using multiple threads, creating one new pthread per data set. 

## Build

Compile with:

``` sh
$ gcc rvw.c
```

``` sh
$ gcc process.c
```

``` sh
$ gcc thread.c -lpthread
```

## Usage

Run with:

``` sh
$ ./a.out 'filename1' 'filename2' ...
```
## Notes
dataset1.txt dataset2.txt dataset3.txt are given for your reference. To check accuracy, you may use the following Unix commands:

To show how many distinct words in file ‘dataset1.txt’:
``` sh
$ cat dataset1.txt | tr -s ' \t' '\n\n' | tr -d '\t' | grep -v '^$'| sort | uniq -c  | wc -l
```
To show the top 3 most frequent words in ‘dataset1.txt’ and their frequencies:
``` sh
$ cat dataset1.txt | tr -s ' \t' '\n\n' | sort | uniq -c | sort -r -n -k1 | head -n 3
```


## License

MIT &copy; Ursula Sarracini
