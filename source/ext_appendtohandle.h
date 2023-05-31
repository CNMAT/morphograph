// ext_appendtohandle.h
//
// Created by Jeff Lubow on 5/31/23
// code from Jeremy Bernstein (c74) 

#ifndef ext_appendtohandle_h
#define ext_appendtohandle_h

t_max_err my_sysmem_appendtextptrtohand(char *text, t_handle h)
{
	t_ptr_size i, oldsize, size;
	char fudge = 0;
	t_max_err rv = -1;
	char *dst;

	if (text && h) {
		size = strlen(text) + 1;	// ensure zero termination
		oldsize = sysmem_handlesize(h);
		if (oldsize && !(*h)[oldsize - 1])
			fudge = 1;
		if (!(rv = sysmem_resizehandle(h, oldsize + size - fudge))) {
			dst = (*h) + oldsize - fudge;
			for (i = 0; i < size; i++, dst++)
				*dst = text[i];
		}
	}
	return rv;
}

#endif /* ext_appendtohandle_h */
