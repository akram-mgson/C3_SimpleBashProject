# UNIX Core Utilities Implementation

Реализация базовых UNIX утилит `cat` и `grep` на языке C. / Implementation of core UNIX utilities `cat` and `grep` in C.

О проекте / About the Project

Russian:

Этот проект включает полную реализацию двух фундаментальных UNIX утилит:
- s21_cat - аналог `cat` с поддержкой всех основных флагов
- s21_grep - аналог `grep` с регулярными выражениями и расширенными функциями

Проект демонстрирует глубокое понимание системного программирования, работы с файлами и аргументами командной строки.

English:

This project features complete implementations of two fundamental UNIX utilities:
- s21_cat - `cat` analog with all major flags support
- s21_grep - `grep` analog with regex and advanced features

The project demonstrates deep understanding of system programming, file handling, and command-line arguments parsing.

Технические особенности / Technical Features

s21_cat Supported Flags:

bash

-b, --number-nonblank    # Нумерует только непустые строки / Number nonempty lines
-e                       # Показывает символы $ в конце строк / Display $ at end of each line
-n, --number             # Нумерует все строки / Number all output lines
-s, --squeeze-blank      # Сжимает несколько пустых строк / Suppress repeated empty lines
-t                       # Отображает табы как ^I / Display tabs as ^I
-v                       # Отображает непечатаемые символы / Display nonprinting characters
-E                       # Показывает символы $ в конце строк / Display $ at end of each line
-T                       # Отображает табы как ^I / Display tabs as ^I  



-e pattern               # Шаблон для поиска / Pattern to search
-i                       # Игнорирует регистр / Ignore case distinctions
-v                       # Инвертирует поиск / Invert match
-c                       # Подсчет совпадений / Count matching lines
-l                       # Только имена файлов / Print only file names
-n                       # Номера строк / Print line numbers
-h                       # Без имен файлов / Suppress file names
-s                       # Подавляет ошибки / Suppress error messages
-f file                  # Берет шаблоны