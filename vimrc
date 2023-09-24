set incsearch
set showcmd
set showmatch
set ignorecase
set autowrite
set nocompatible
filetype off
set encoding=utf-8

call plug#begin('~/.vim/plugged')

Plug 'rust-lang/rust.vim'
Plug 'dense-analysis/ale'

call plug#end()

let g:rustfmt_autosave = 1
let g:rustfmt_emit_files = 1
let g:rustfmt_fail_silently = 0
let g:ale_fixers = {
			\ 'rust': ['rustfmt'],
			\ }
