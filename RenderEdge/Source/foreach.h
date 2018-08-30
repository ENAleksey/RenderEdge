#pragma once

#if defined(_MSC_VER) && (_MSC_VER > 1500 || (_MSC_VER == 1500 && defined (_HAS_TR1)))
#	if _MSC_VER >= 1700
#		define foreach(VAR, COL) for(VAR : COL)
#	endif
#	endif
