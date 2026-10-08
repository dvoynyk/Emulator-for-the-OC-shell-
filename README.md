# Emulator-for-the-OC-shell
Разработка эмулятора для языка оболочки OC

# Эмулятор командной оболочки ОС (GUI) — Этап 3: Виртуальная файловая система (VFS)

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Interface](https://img.shields.io/badge/UI-GUI-green.svg)
![Stage](https://img.shields.io/badge/Stage-3%20(VFS)-red.svg)

Графический эмулятор командной строки UNIX-подобной операционной системы с полноценной виртуальной файловой системой (VFS). Все операции выполняются в памяти без распаковки архивов.

---

## 📋 Обзор Этапа 3

На текущем этапе реализована виртуальная файловая система:

- **VFS на основе XML** с кодированием двоичных данных в base64
- **Загрузка VFS в память** при запуске приложения
- **Полная реализация команд:**
  - `ls` - список файлов и папок с размерами
  - `cd` - навигация по папкам
  - `pwd` - отображение текущего пути
  - `cat` - вывод содержимого текстовых файлов
- **Обработка ошибок:**
  - Файл VFS не найден
  - Неверный формат XML
  - Попытка доступа к несуществующим путям
  - Попытка чтения папки как файла
- **Работа в памяти** - без распаковки или модификации VFS
- **Навигация между уровнями** - поддержка `.` и `..`

---

## 🖼 Демонстрация работы

### 1. Запуск с минимальной VFS
```text
$ shell-emulator.exe --vfs "vfs/vfs_minimal.xml"

=== Конфигурация эмулятора ===
VFS: vfs/vfs_minimal.xml
Стартовый скрипт: не указан
VFS загружена успешно!
Текущий путь: /
```

### 2. Просмотр содержимого
```text
user@host:~$ ls
Содержимое директории (/):
[FILE] readme.txt (51 bytes)
[DIR] folder1

user@host:~$ cat readme.txt
Содержимое файла 'readme.txt':
Hello World! This is a minimal VFS filesystem.

user@host:~$ pwd
Текущий путь: /
```

### 3. Навигация по папкам
```text
user@host:~$ cd folder1
Переход в директорию: folder1

user@host:~$ pwd
Текущий путь: /folder1

user@host:~$ cd ..
Переход в директорию: ..

user@host:~$ pwd
Текущий путь: /
```

### 4. Обработка ошибок
```text
user@host:~$ cd nonexistent
Ошибка: директория не найдена: nonexistent

user@host:~$ cat nonexistent.txt
Ошибка: файл не найден: nonexistent.txt

user@host:~$ ls nonexistent
Ошибка: директория не найдена
```

---

## 💻 Параметры командной строки

| Параметр | Короткий | Описание | Пример |
| :--- | :--- | :--- | :--- |
| `--vfs <путь>` | `-v <путь>` | Путь к XML файлу VFS | `--vfs "vfs/filesystem.xml"` |
| `--script <путь>` | `-s <путь>` | Путь к стартовому скрипту | `--script "scripts/test.txt"` |
| `--help` | `-h` | Показать справку | `--help` |

---

## 📝 Формат VFS (XML)

```xml
<?xml version="1.0" encoding="UTF-8"?>
<filesystem>
  <file name="readme.txt">
    SGVsbG8gV29ybGQh
  </file>
  <directory name="folder1">
  </directory>
</filesystem>
```

Особенности:

- Двоичные данные кодируются в base64
- Папки представлены тегами `<directory>`
- Файлы представлены тегами `<file>`
- Содержимое файла находится между открывающим и закрывающим тегами

## 📋 Поддерживаемые команды на Этапе 3

| Команда | Описание | Пример | Результат |
| :--- | :--- | :--- | :--- |
| `ls` | Список файлов текущей папки | `ls` | Показывает все файлы и папки |
| `ls <путь>` | Список файлов в директории | `ls /documents` | Показывает файлы в `/documents` |
| `cd <путь>` | Переход в директорию | `cd /home` | Переходит в `/home` |
| `cd ..` | Переход на уровень выше | `cd ..` | Переходит в родительскую папку |
| `pwd` | Текущий путь | `pwd` | Показывает `/current/path` |
| `cat <файл>` | Содержимое файла | `cat readme.txt` | Выводит содержимое файла |
| `exit` | Выход | `exit` | Закрывает приложение |

## 🛠 Сборка и запуск

### Требования

- Компилятор с поддержкой C++17
- CMake 3.16+
- Qt6 Widgets
- MinGW 11.2.0

### Сборка

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Запуск

Без VFS (режим заглушек):

```bash
shell-emulator.exe
```

С VFS:

```bash
shell-emulator.exe --vfs "../vfs/vfs_minimal.xml"
```

С VFS и стартовым скриптом:

```bash
shell-emulator.exe --vfs "../vfs/vfs_minimal.xml" --script "../scripts/comprehensive_test.txt"
```

## 🧪 Тестирование

### Включённые тестовые VFS файлы

- `vfs_minimal.xml` - минимальная структура
  - 1 файл и 1 папка в корне
  - Для быстрой проверки базовой функциональности
- `vfs_multiple.xml` - средняя сложность
  - Несколько файлов и папок
  - 2 уровня вложенности
- `vfs_complex.xml` - сложная структура
  - 20+ элементов
  - 3+ уровня вложенности
  - Тестирование глубокой навигации

### Запуск тестов

Используйте `bat`/`sh` файлы в папке `launch_scripts/`:

```bash
# Windows
../launch_scripts/test_vfs_minimal.bat
../launch_scripts/test_vfs_multiple.bat
../launch_scripts/test_vfs_complex.bat

# Linux/Mac
../launch_scripts/test_vfs_minimal.sh
../launch_scripts/test_vfs_multiple.sh
../launch_scripts/test_vfs_complex.sh
```

### Комплексный тест

Запуск со всеми компонентами:

```bash
shell-emulator.exe --vfs "vfs/vfs_minimal.xml" --script "scripts/comprehensive_test.txt"
```
## 📂 Структура проекта

```text
shell-emulator/
├── Header Files/
│   ├── MainWindow.h
│   ├── SystemInfo.h
│   ├── Parser.h
│   ├── Executor.h
│   ├── ConfigParser.h
│   ├── ScriptExecutor.h
│   ├── VFSManager.h
│   └── Base64Decoder.h
│
├── Source Files/
│   ├── main.cpp
│   ├── MainWindow.cpp
│   ├── SystemInfo.cpp
│   ├── Parser.cpp
│   ├── Executor.cpp
│   ├── ConfigParser.cpp
│   ├── ScriptExecutor.cpp
│   ├── VFSManager.cpp
│   └── Base64Decoder.cpp
│
├── vfs/
│   ├── vfs_minimal.xml
│   ├── vfs_multiple.xml
│   └── vfs_complex.xml
│
├── scripts/
│   ├── test_basic.txt
│   ├── test_errors.txt
│   ├── test_all.txt
│   ├── demo.txt
│   └── comprehensive_test.txt
│
├── launch_scripts/
│   ├── test_vfs_minimal.bat
│   ├── test_vfs_multiple.bat
│   ├── test_vfs_complex.bat
│   ├── test_vfs_minimal.sh
│   ├── test_vfs_multiple.sh
│   └── test_vfs_complex.sh
│
├── CMakeLists.txt
├── README.md
└── .gitignore
