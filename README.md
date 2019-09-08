# Auto_make


Auto_make it's easiest way to create your own Makefile.

### How to install

1) Clone repository to root directory
```
https://github.com/kagestonedragon/auto_make.git ~/auto_make
```

2) Compile
```
make -C ~/auto_make
```

3) Copy Auto_make to your project directory
```
cp ~/auto_make/auto_make <path to the project directory>
```


### How to use

```
./auto_make <output file> -S <dir1> <dir2> ... -I <dir1> ...
```
Run auto_make with parameters:
* `<output file>` — name of the output file (% = EXECUTABLE, %.a = LIBRARY)
* `-S` — recursive search in directrories (only %.c files)
* `-I` — search header files in directories (only %.h files)

<b>Example</b>

