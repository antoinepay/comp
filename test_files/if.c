void print(char c,char d)
{
	putchar(c);
	putchar(d);
}

void main() {
	int32_t a = 1;
	int32_t b = a+111;
	char c = b < 3;
	if( a-1)
	{
		putchar('0');
	}
	if( a > 0)
	{
		putchar('1');
		if(b != 1)
		{
			putchar('2');
		}
		else
		{
			putchar('g');
		}
		a = 4;
		if(b < 3)
		{
			putchar('e');
		}
		else
		{
			putchar('3');
			if (1 < 3 )
			{
				putchar('4');
			}
			else
			{
				putchar('f');
			}
			putchar('5');
		} 
	}
	else
	{
		putchar('j');
	}
	putchar('\n'); 
}

