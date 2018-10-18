
void main() {
	int32_t b = 3;
	char c = b && 1;
	int32_t d = b && 0;
	int32_t e = b || c;
	int32_t f = b || 0;
	int32_t g = d || 0;
	putchar('0' + c);
	putchar('\n');
	putchar('0' + d);
	putchar('\n');
	putchar('0' + e);
	putchar('\n');
	putchar('0' + f);
	putchar('\n');
	putchar('0' + g);
	putchar('\n');
}

