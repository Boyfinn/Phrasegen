# TODO:
## Flag driven pipeline:
Instead of processing all conditions through a stack of if-statements, do a bitmask for each process, and iterate through a function pointer table handling each situation.
Example:
```
typedef void (*func)(char*str);  //Process type template

void Delimiter(cjar*s);          //Prototypes
void Uppercase(char*s);

enum{
  DELIM = 1 <<0,
  UPPER = 1 <<1
  //etc...
};

func processors[] ={
  Delimiter,
  Uppercase
  //etc...
}

void Delimiter(char *s){
  //Modify delimiter
}

void Uppercase(char *s){
  //Capitalize words
}

void ProcessWord(char *str, unsigned procMask){
  for(size_t i=0; i<sizeof(processors)/sizeof(processors[0]);i++)
    if(procMask &(1<<i))
      processors[bit](str);
}
```
## The whole GUI app
