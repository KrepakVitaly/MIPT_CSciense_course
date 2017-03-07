
// DSL Domain-specific language

DEFINE_CMD_ (nop,  {})
DEFINE_CMD_ (push, ("%d", value), ("%d", &value) )
DEFINE_CMD_ (pop,  {})

//sizeof.livejournal.com

       _push  =  1,
	   _pop   =  2,
	   _clr   =  3,
	   _ok    =  4,
	   _dump  =  5,
	   _dup   =  6,
	   _swap  =  7,
	   
	   _add   = 48,
	   _sub   = 49,
	   _div   = 50,
	   _pow   = 51,
	   _sqrt  = 52,
	   _sin   = 53,
	   _cos   = 54,
	   
	   _nop   =  63,
	   
	   _call  = 115,
	   _ret   = 116,
	   _jmp   = 117,
	   _ja    = 118,
	   _jb    = 119,
	   _je    = 120,
	   _jne   = 121,
	
	   _end   = 255
