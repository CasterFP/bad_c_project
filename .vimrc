" Open from the repository root: vim -u .vimrc src/math_utils.c
" Requires clang-format in PATH; uses the repository's .clang-format.
set expandtab
set shiftwidth=4
set tabstop=4

augroup mathlib_format_on_save
    autocmd!
    autocmd BufWritePre *.c,*.h silent keepjumps %!clang-format --style=file
augroup END
