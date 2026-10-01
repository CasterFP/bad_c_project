# Исправление CI

Исходный коммит: `dfb0d9efab42841a5932c9332ea396ab8ce21d0b`.
Изучены README, конфигурация CMake, исходники, тесты и
[логи исходного CI](https://github.com/WoWaster/bad_c_project/actions/runs/36236088354).

## Причины ошибок

- `build` проходил успешно.
- `test`: 8 из 24 тестов падали, потому что `multiply_by_two` возвращала
  `value + 2` вместо `value * 2`.
- `format-check`: файлы `.c` и `.h` в `src/` и `tests/` не соответствовали
  стилю WebKit из `.clang-format`. Проверка охватывает также старые файлы,
  которые не участвуют в сборке.

## Выполненные действия

1. Склонирован исходный проект, создана ветка `fix/ci-and-format-on-save`.
2. На Ubuntu 24.04 подготовлены CMake, cmocka и clang-format 18.
   В рабочей среде зависимости размещены локально; для CMake задан
   `CMAKE_PREFIX_PATH`, для инструментов — `PATH` и `LD_LIBRARY_PATH`.
3. До исправления воспроизведены результаты CI: сборка успешна,
   8 тестов падают, проверка форматирования завершается с кодом 1.
4. Код открыт в Vim, включено форматирование при сохранении через `.vimrc`.
5. В Vim исправлено удвоение; сохранение автоматически отформатировало файл.
6. Командой `./scripts/format.sh` отформатированы все C-файлы и заголовки.
7. Повторены проверки: сборка успешна, все 24 теста проходят,
   проверка форматирования и `git diff --check` успешны.

## Format-on-save

Из корня репозитория открыть файл командой:

```bash
vim -u .vimrc src/math_utils.c
```

В системе, где команда редактора называется `vi`, используется
`vi -u .vimrc src/math_utils.c`. Требуется Vim с поддержкой autocommands
и установленный `clang-format` в `PATH`.

Конфигурация в `.vimrc`:

```vim
augroup mathlib_format_on_save
    autocmd!
    autocmd BufWritePre *.c,*.h silent keepjumps %!clang-format --style=file
augroup END
```

Перед записью `.c` и `.h` Vim запускает clang-format. При запуске из корня
проекта используется его `.clang-format` со стилем WebKit.
Работа настройки проверена сохранением `src/math_utils.c` в Vim и последующим
`clang-format --dry-run --Werror --style=file src/math_utils.c`.

## Команды проверки

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./scripts/check-format.sh
git diff --check
```

Результат тестов после исправления:

```text
100% tests passed, 0 tests failed out of 24
```
