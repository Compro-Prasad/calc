#include <str.cpp"
#include <stdlib.h>
#define NON 0
#define BIN 1
#define OCT 2
#define DEC 4
#define HEX 8
#define Hex (HEX)
#define Dec (Hex | DEC)
#define Oct (Dec | OCT)
#define Bin (Oct | BIN)

void shift_forward(char *c, int pos, int steps)
{
	for (int i = strlen(c); i >= pos; i--)
		c[i + steps] = c[i];
}

void shift_backward(char *c, int pos, int steps)
{
	if (steps)
		for (int i = pos; i < strlen(c); i++)
			c[i] = c[i + steps];
}

void trim_number(char *c)
{
	if (c[0] == '.')
	{
		shift_forward(c, 0, 1);
		c[0] = '0';
	}
	int i = 0;
	for (; c[i] == '0' && c[i + 1] && c[i + 1] != '.'; i++);
	int k = i;
	while (c[i] != '.' && c[i])
		i++;
	if (c[i] == '.')
	{
		if (c[i + 1] == 0)
			strcat(c, "0");
		int j = strlen(c) - 1;
		for (; j > 1 && c[j - 1] != '.' && c[j] == '0'; j--);
		if (j != strlen(c) - 1)
			c[j + 1] = 0;
	}
	shift_backward(c, 0, k);
	k = strlen(c) - 1;
	if (c[k] == '0' && c[k - 1] == '.')
		c[k - 1] = 0;
}

const unsigned char check_no(const char *c)
{
	unsigned char type = 0, f = 0;
	for (unsigned int i = 0; c[i]; i++)
	{
		if (c[i] == '.')
		{
			f++;
			if (f > 1)
				return NON;
			continue;
		}

		if (c[i] >= '0' && c[i] <= '1' && (type > Bin || !type))
			type = Bin;

		if (c[i] >= '2' && c[i] <= '7' && (type > Oct || !type))
			type = Oct;

		if (c[i] >= '8' && c[i] <= '9' && (type > Dec || !type))
			type = Dec;

		if (toupper(c[i]) >= 'A' && toupper(c[i]) <= 'F' && (type > Hex || !type))
			type = Hex;

		if (!((c[i] >= '0' && c[i] <= '9') || (toupper(c[i]) >= 'A' && toupper(c[i]) <= 'F')))
			return NON;
	}
	return type;
}

void add(const char *a, const char *b, char *c)
{
	int i = strlen(a) - 1, j = strlen(b) - 1, k = i > j ? i : j;
	c[k + 1] = 0;
	unsigned char carry = 0;
	for (;;)
	{
		if (i >= 0 && j >= 0)
		{
			c[k] = a[i] + b[j] - 96 + carry;
			carry = c[k] / 10;
			c[k] = c[k] % 10 + 48;
			i--, j--, k--;
		}
		else if (i >= 0)
		{
			c[k] = a[i] - 48 + carry;
			carry = c[k] / 10;
			c[k] = c[k] % 10 + 48;
			i--, k--;
		}
		else if (j >= 0)
		{
			c[k] = b[j] - 48 + carry;
			carry = c[k] / 10;
			c[k] = c[k] % 10 + 48;
			j--, k--;
		}
		else if (i == -1 && j == -1)
			break;
	}
}

void multiply(const char *a, const char *b, char *c)
{
	int acount = 0, bcount = 0;
	int lena = strlen(a), lenb = strlen(b);
	bool stop_acount = false, stop_bcount = false;
	char sum[100] = "0";
	int i = lena - 1, j = lenb - 1, u = 0, v = 0, k;
	for (; i >= 0 || j >= 0;)
	{
		if (a[i] == '.')
			stop_acount = true, v = 1;
		if (b[j] == '.')
			stop_bcount = true;
		if (stop_acount && stop_bcount)
			break;
		if (stop_acount == false)
			acount++, i--;
		if (stop_bcount == false)
			bcount++, j--;
	}
	if (stop_acount == false)
		acount = 0;
	if (stop_bcount == false)
		bcount = 0;
	for (i = lenb - 1; i >= 0; i--)
	{
		if (b[i] == '.')
		{
			u = 1;
			continue;
		}
		char *t = new char[lenb - i - u], temp[1000];
		unsigned char carry = 0;
		for (j = 0; j < lenb - 1 - i - u; j++)
			t[j] = '0';
		t[j] = 0;
		k = lena - v;
		temp[k--] = 0;
		for (j = lena - 1; j >= 0; j--)
		{
			if (a[j] == '.')
				continue;
			temp[k] = (a[j] - 48) * (b[i] - 48) + carry;
			carry = temp[k] / 10;
			temp[k] = temp[k] % 10 + 48;
			k--;
		}
		if (carry)
		{
			shift_forward(temp, 0, 1);
			temp[0] = carry + 48;
		}
		strcat(temp, t);
		delete t;
		char tempsum[1000];
		strcpy(tempsum, sum);
		add(tempsum, temp, sum);
	}
	strcpy(c, sum);
	shift_forward(c, strlen(c) - acount - bcount + 1, acount + bcount == 0 ? 0 : 1);
	if (acount + bcount != 0)
		c[strlen(c) - acount - bcount - 1] = '.';
}

const char *bin_to_hex(const unsigned int n)
{
	switch (n)
	{
	case 0:return "0";
	case 1:return "1";
	case 10:return "2";
	case 11:return "3";
	case 100:return "4";
	case 101:return "5";
	case 110:
		return "6";
	case 111:
		return "7";
	case 1000:
		return "8";
	case 1001:
		return "9";
	case 1010:
		return "A";
	case 1011:
		return "B";
	case 1100:
		return "C";
	case 1101:
		return "D";
	case 1110:
		return "E";
	case 1111:
		return "F";
	}
	return "";
}

bool B2OH(char *c, const unsigned char div)
{
	if (check_no(c) == Bin && (div == 3 || div == 4))
	{
		size_t lenc = strlen(c) + div, len = lenc / div + div;
		char *oct = new char[len];
		if (oct)
		{
			int i = 0, l, n;
			oct[0] = 0;

			for (; c[i] && c[i] != '.'; i++);

			if (i % div)
			{
				char *ch = new char[lenc];
				strncpy(ch, "0", lenc);
				if (i % div == 1 && div == 3 || i % div == 2 && div == 4)
					strncat(ch, "0", lenc);
				if (i % div == 1 && div == 4)
					strncat(ch, "00", lenc);
				strncat(ch, c, lenc);
				strncpy(c, ch, lenc);
			}

			for (i = 0; c[i] && c[i] != '.';)
			{
				l = i, n = 0;
				for (; i - l != div; i++)
					n = n + (c[i] - 48) * pow(10, div - i + l - 1);
				strncat(oct, bin_to_hex(n), len);
			}

			if (c[i++] == '.')
			{
				int j = i;
				lenc += div;
				strncat(oct, ".", 400);
				for (; c[j]; j++);
				int k = (j - i) % div;
				if (k == 2 && div == 3 || k == 3 && div == 4)
					strncat(c, "0", lenc);
				if (k == 1 && div == 3 || k == 2 && div == 4)
					strncat(c, "00", lenc);
				if (k == 1 && div == 4)
					strncat(c, "000", lenc);
				for (; c[i] && c[i] != '.';)
				{
					l = i, n = 0;
					for (; i - l != div; i++)
						n = n + (c[i] - 48) * pow(10, div - i + l - 1);
					strncat(oct, bin_to_hex(n), len);
				}
			}
			fprintf(PRINTFAST, "%s", oct);
			delete oct;
		}
		else
#ifdef CALC_COLORS
		{
			change_color("err");
#endif
			fprintf(PRINTFAST, "!!Memory Full!!");
#ifdef CALC_COLORS
			change_color();
		}
#endif
		return 1;
	}
	return 0;
}

const char *hex_to_bin(unsigned char c)
{
	switch (toupper(c))
	{
	case '0':
		return "0000";
	case '1':
		return "0001";
	case '2':
		return "0010";
	case '3':
		return "0011";
	case '4':
		return "0100";
	case '5':
		return "0101";
	case '6':
		return "0110";
	case '7':
		return "0111";
	case '8':
		return "1000";
	case '9':
		return "1001";
	case 'A':
		return "1010";
	case 'B':
		return "1011";
	case 'C':
		return "1100";
	case 'D':
		return "1101";
	case 'E':
		return "1110";
	case 'F':
		return "1111";
	case '.':
		return ".";
	}
	return "";
}

const char *oct_to_bin(unsigned char c)
{
	switch (c)
	{
	case '0':
		return "000";
	case '1':
		return "001";
	case '2':
		return "010";
	case '3':
		return "011";
	case '4':
		return "100";
	case '5':
		return "101";
	case '6':
		return "110";
	case '7':
		return "111";
	case '.':
		return ".";
	}
	return "";
}

bool OH2B(const char *c, const unsigned char div)
{
	int *check = new int;
	*check = check_no(c);
	if (*check == Hex && div == 4 || *check == Oct && div == 3)
	{
		delete check;
		int i = 0;
		size_t len = strlen(c) * div;
		char *bin = new char[len];
		if (bin)
		{
			bin[0] = 0;
			if (c[0] == '.')
				strncat(bin, "0", len);
			if (div == 4)
				for (; c[i]; i++)
					strncat(bin, hex_to_bin(c[i]), len);
			else
				for (; c[i]; i++)
					strncat(bin, oct_to_bin(c[i]), len);
			if (c[i - 1] == '.')
				strncat(bin, "0", len);
			fprintf(PRINTFAST, "%s", bin);
		}
		else
#ifdef CALC_COLORS
		{
			change_color("err");
#endif
			fprintf(PRINTFAST, "!!Memory Full!!");
#ifdef CALC_COLORS
			change_color();
		}
#endif
		return 1;
	}
	delete check;
	return 0;
}

bool D2B(char *c)
{
	int x, y;
	trim_number(c);
	char number[200], fraction[200];
}

int main()
{
	char a[1000] = "", b[1000] = "", c[1000];
	while (strcasecmp(c, "quit"))
	{
		cin.getline(a, 1000);
		cin.getline(b, 1000);
		trim_number(a);
		trim_number(b);
		/* unsigned char x = check_no(c); if (x == Bin) B2OH(c, 4); if (x ==
		   Oct) OH2B(c, 3); if (x == Dec) printf("d,h\n"); if (x == Hex)
		   OH2B(c, 4); */
		multiply(a, b, c);
		printf("%s\n", c);
	}
	return 0;
}
