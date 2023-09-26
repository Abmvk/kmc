set number			" regelnummering aan
set incsearch			" direct zoeken
set hlsearch			" gezochte termen highlighten
set showcmd			" commando tonen tijdens invoeren
set showmatch			" highlight bijpassende haakjes
set ignorecase			" case insensitief zoeken
set autowrite			" bij openen nieuw bestand oude automatisch opslaan
set nocompatible		" niet vi compatible, daardoor alle vim mogelijkheden
filetype off			" geen automatische bestandstype herkenning
set encoding=utf-8		" gebruik utf-8 ipv ascii
				" plugin manager, plugins voor vim
call plug#begin('~/.vim/plugged')

Plug 'rust-lang/rust.vim'
Plug 'dense-analysis/ale'

call plug#end()
				" hierna instellingen voor toepassen rustfmt
let g:rustfmt_autosave = 1
let g:rustfmt_emit_files = 1
let g:rustfmt_fail_silently = 0
let g:ale_fixers = {
			\ 'rust': ['rustfmt'],
			\ }

inoremap jj <ESC>		" ESC-toets vervangen door jj 

