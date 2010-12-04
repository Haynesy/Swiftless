using System;
		
namespace VimCommands
{
	/*
	Command Mode
		:sp = Horizontal Separtion;
		:vsp = Verticle Separtion;

		h = left; add number to move faster e.g. 7k
		k = up;
		j = down;
		l = right;
		
		w = words (2w: move 2 words);
		$ = move to end;
		a = insert mode next character;

		H = highest point on the page;
		M = middle point of the page;
		L = lowest point of the page;
		
		/[word] = search for word; 
	
		:e index.html = create new file and edit it;

		:tabnew = make a new tab;

		a = insert mode after character;
		A = insert mode at the end of the line;

		d = delete;
		dd = deltet line;
		dw = delete word;

		cw = change word;
		c$ = change to the end of the line;

		b = back a word e.g 3b back 3 words;
		w = forward a word e.g 3w forward 3words;
		B = back a word to the next character after 
			the space;
		W = forward a word to the next char after 
			the space;
		u = undo;
		o = new line underneath current line 
			and switch to insert mode;
		O = new line above current line and 
			switch to insert mode;

		ct = change til e.g ct. change til you get 
			a period;
		:bd = close buffer;
		:buffers = list buffers;
		:ls = list buffers;

		[file] Ctrl w f = Hover over file and open;

	Explore Mode ( :e . )
		d = make directory;		
		:pwd = current directory
		:cd [directory] = change current directory;
		:n *= open all files in directory;
		
	.vimrc
		syntax on
		set number
		colorscheme desert
		set tabstop=3
		set shiftwidth=3
		set guifont=Courier:h15
		set smartindent
		set autoindent

		"For autocompletion
		set wildmode=list:longest

		set foldenable
		" Add a colon when ever you press space;
		nmap <space> :
		
		" Auto move current directory to that of the 
			file in the buffer; 
		autocmd BufEnter * cd %:p:h

	NERDTree
		:bookmark = will bookmark a folder;
		B = to see all bookmarks;

	Surround
	Snipmate
	*/


}
