#!/bin/bash

# Взять строки вывода утилиты с 
# третьей по десятую, отрезать вторую колонку и 
# посчитать сколько раз во вторых колонках встречается слово hello - на баше

echo "Today is " `date`

echo "\n enter the path to directory"
read the_path

echo "\n you path has the following and folders: "
ls $the_path