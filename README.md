# Word Frequency Counter

Several C programs to process text documents. The programs will count the frequency of every distinct word in a text document and print out the top 3 most frequent words for each provided text document. User can input more than one file at a time to be processed.

## Build

Compile with:

``` sh
$ gcc rvw.c
```

## Usage

Run with:

``` sh
$ ./a.out 'filename' 'filename' 
```
## Notes
dataset1.txt dataset2.txt dataset3.txt are given for your reference. To check accuracy, you may use the following Unix commands:<br/>
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
