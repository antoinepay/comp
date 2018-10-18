void print(int32_t n)
{
	int32_t val = n/10;//*
	int32_t mod = n%10; //%
	if(n == mod)
	{
		putchar('0'+mod);
		return ;	
	}
	print(val);
	putchar('0'+mod);
}

void main() {
	int32_t a;
	for(a=0;a<10;a++)
	{
		print(a);
		putchar('\n');
	}
	for(a=10;a>0;a/=2)
	{
		print(a);
		putchar('\n');
	}
	putchar('f');
	putchar('i');
	putchar('n');
	putchar('\n'); 
}

