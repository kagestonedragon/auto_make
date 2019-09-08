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
./auto_make <output file> -S <sd1> <sd2> ... -I <id1> ...
```
Run auto_make with parameters:
* `<output file>` — name of the output file (`% = EXECUTABLE`, `%.a = LIBRARY`)
* `-S` — recursive search in directrories (only `%.c` files)
* `-I` — search header files in directories (only `%.h` files)

<b>Example</b>
```
./auto_make auto_make -S sources -I includes
```

<p align="center">
  <img src="/pics/console.png" width="1000%" alt="auto_make information"/>
</p>


### Generated Makefile

<p align="center">
  <img src="/pics/makefile.png" width="85%" alt="generated Makefile"/>
</p>

```ruby
require 'redcarpet'
markdown = Redcarpet.new("Hello World!")
puts markdown.to_html
```
