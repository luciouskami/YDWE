#include <ctype.h>
#include <BlizzardStorm.h>
#include "ConvertString.h"

static unsigned char ConvertToAlnum[] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 
  'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z',
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 
  'H', 'I', 'J', 'K', 'L', 'M', 'N',
  'O', 'P', 'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X', 'Y', 'Z',
};

void _fastcall
ConvertString(const char* src, char* dst, unsigned int limit)
{
	unsigned int i, j, n;
	unsigned int addup = 0;

	for (n = BLZSStrLen(src) - 1; n >= 0; n--)
	{
		if (src[n] != ' ') break;
	}

	for (i = 0, j = 0; (i <= n) && (j < limit - 2); i++)
	{
		if (isalnum(src[i]) || (src[i] == '_'))
		{
			dst[j++] = src[i];
			continue;
		}

		if (src[i] == ' ')
		{
			dst[j++] = '_';
			continue;
		}

		addup = addup * 256 + src[i];
		while ((j < limit - 2) && (addup > 62))
		{
			dst[j++] = ConvertToAlnum[addup % 62];
			addup /= 62;
		}
	}

	if (addup != 0) dst[j++] = ConvertToAlnum[addup % 62];
	dst[j] = '\0';
}
