`liboverlay.so` - динамическая библиотека для скрытия файлов от приложения

# Установка

```
make
make install PREFIX=/директория/для/установки
```

# Использование

```
export LD_PRELOAD=/путь/к/liboverlay.so

# Если хотим видеть отладочные сообщения
export OVERLAY_DEBUG=1

# Файлы, которые требуется скрыть
export OVERLAY_DENY='первый_файл:второй_файл:'

some_program
```

`some_program` - должна быть динамически связанной программой