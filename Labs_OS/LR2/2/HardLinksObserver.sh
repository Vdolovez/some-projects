#!/bin/bash

inode=$(ls -i $1 | cut -d' ' -f1)	# Взятие индексного дескриптора у основного файла
ls -l -i -R / 2>/dev/null | grep $inode	# Вывод всех жестких ссылок файла