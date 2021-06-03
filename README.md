# HPrint

## A small Tool designed to highlight strings inside of a text file based on the given input

### Install:
```
make

sudo make install
```

### Run:
```
hprint -p [STRING] FILE

Optional Switches:
     -m     Match Case
```


Example:

##### No Case Matching:
```hprint -p "Frodo" lotr.exe```

![](imgs/no_match.png)


##### Case Matching:
```hprint -mp "Frodo" lotr.exe```

![](imgs/match.png)


### Contributing:
Pull Requests are Welcomed