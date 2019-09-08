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

Run auto_make with parameters:
* `1 parameter` — output file name
* `-S` — recursive read files from directrories (.c)
* `-I` — read header files from directories (.c)

# Example
```
./auto_make auto_make -S sources -I includes
```
