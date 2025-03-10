# 1 "tinyprintf.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "tinyprintf.c" 2
# 22 "tinyprintf.c"
# 1 "./tinyprintf.h" 1
# 104 "./tinyprintf.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdarg.h" 1 3




# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\musl_xc8.h" 1 3
# 6 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdarg.h" 2 3


# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 12 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef void * va_list[1];
# 174 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 210 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 9 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdarg.h" 2 3

#pragma intrinsic(__va_start)
#pragma intrinsic(__va_arg)

extern void * __va_start(void);
extern void * __va_arg(void *, ...);
# 105 "./tinyprintf.h" 2
# 129 "./tinyprintf.h"
typedef unsigned int size_t;
# 145 "./tinyprintf.h"
typedef void (*putcf) (void *, char);
# 157 "./tinyprintf.h"
void tfp_format(void *putp, putcf putf, const char *fmt, va_list va);


int tfp_vsnprintf(char *str, size_t size, const char *fmt, va_list ap);
int tfp_snprintf(char *str, size_t size, const char *fmt, ...) ;

int tfp_vsprintf(char *str, const char *fmt, va_list ap);
int tfp_sprintf(char *str, const char *fmt, ...) ;
# 175 "./tinyprintf.h"
void init_printf(void *putp, putcf putf);
void tfp_printf(char *fmt, ...) ;
# 23 "tinyprintf.c" 2
# 42 "tinyprintf.c"
typedef unsigned int size_t;
# 72 "tinyprintf.c"
struct param {
    char lz:1;
    char alt:1;
    char uc:1;
    char align_left:1;
    unsigned int width;
    char sign;
    unsigned int base;
    char *bf;
};



static void ulli2a(
    unsigned long long int num, struct param *p)
{
    int n = 0;
    unsigned long long int d = 1;
    char *bf = p->bf;
    while (num / d >= p->base)
        d *= p->base;
    while (d != 0) {
        int dgt = num / d;
        num %= d;
        d /= p->base;
        if (n || dgt > 0 || d == 0) {
            *bf++ = dgt + (dgt < 10 ? '0' : (p->uc ? 'A' : 'a') - 10);
            ++n;
        }
    }
    *bf = 0;
}

static void lli2a(long long int num, struct param *p)
{
    if (num < 0) {
        num = -num;
        p->sign = '-';
    }
    ulli2a(num, p);
}



static void uli2a(unsigned long int num, struct param *p)
{
    int n = 0;
    unsigned long int d = 1;
    char *bf = p->bf;
    while (num / d >= p->base)
        d *= p->base;
    while (d != 0) {
        int dgt = num / d;
        num %= d;
        d /= p->base;
        if (n || dgt > 0 || d == 0) {
            *bf++ = dgt + (dgt < 10 ? '0' : (p->uc ? 'A' : 'a') - 10);
            ++n;
        }
    }
    *bf = 0;
}

static void li2a(long num, struct param *p)
{
    if (num < 0) {
        num = -num;
        p->sign = '-';
    }
    uli2a(num, p);
}


static void ui2a(unsigned int num, struct param *p)
{
    int n = 0;
    unsigned int d = 1;
    char *bf = p->bf;
    while (num / d >= p->base)
        d *= p->base;
    while (d != 0) {
        int dgt = num / d;
        num %= d;
        d /= p->base;
        if (n || dgt > 0 || d == 0) {
            *bf++ = dgt + (dgt < 10 ? '0' : (p->uc ? 'A' : 'a') - 10);
            ++n;
        }
    }
    *bf = 0;
}

static void i2a(int num, struct param *p)
{
    if (num < 0) {
        num = -num;
        p->sign = '-';
    }
    ui2a(num, p);
}

static int a2d(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    else if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    else if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    else
        return -1;
}

static char a2u(char ch, const char **src, int base, unsigned int *nump)
{
    const char *p = *src;
    unsigned int num = 0;
    int digit;
    while ((digit = a2d(ch)) >= 0) {
        if (digit > base)
            break;
        num = num * base + digit;
        ch = *p++;
    }
    *src = p;
    *nump = num;
    return ch;
}

static void putchw(void *putp, putcf putf, struct param *p)
{
    char ch;
    int n = p->width;
    char *bf = p->bf;


    while (*bf++ && n > 0)
        n--;
    if (p->sign)
        n--;
    if (p->alt && p->base == 16)
        n -= 2;
    else if (p->alt && p->base == 8)
        n--;


    if (!p->lz && !p->align_left) {
        while (n-- > 0)
            putf(putp, ' ');
    }


    if (p->sign)
        putf(putp, p->sign);


    if (p->alt && p->base == 16) {
        putf(putp, '0');
        putf(putp, (p->uc ? 'X' : 'x'));
    } else if (p->alt && p->base == 8) {
        putf(putp, '0');
    }


    if (p->lz) {
        while (n-- > 0)
            putf(putp, '0');
    }


    bf = p->bf;
    while ((ch = *bf++))
        putf(putp, ch);


    if (!p->lz && p->align_left) {
        while (n-- > 0)
            putf(putp, ' ');
    }
}

void tfp_format(void *putp, putcf putf, const char *fmt, va_list va)
{
    struct param p;

    char bf[23];



    char ch;
    p.bf = bf;

    while ((ch = *(fmt++))) {
        if (ch != '%') {
            putf(putp, ch);
        } else {

            char lng = 0;


            p.lz = 0;
            p.alt = 0;
            p.width = 0;
            p.align_left = 0;
            p.sign = 0;


            while ((ch = *(fmt++))) {
                switch (ch) {
                case '-':
                    p.align_left = 1;
                    continue;
                case '0':
                    p.lz = 1;
                    continue;
                case '#':
                    p.alt = 1;
                    continue;
                default:
                    break;
                }
                break;
            }


            if (ch >= '0' && ch <= '9') {
                ch = a2u(ch, &fmt, 10, &(p.width));
            }




            if (ch == '.') {
              p.lz = 1;

              do {
                ch = *(fmt++);
              } while ((ch >= '0') && (ch <= '9'));
            }



            if (ch == 'z') {
                ch = *(fmt++);
                if (sizeof(size_t) == sizeof(unsigned long int))
                    lng = 1;

                else if (sizeof(size_t) == sizeof(unsigned long long int))
                    lng = 2;

            } else




            if (ch == 'l') {
                ch = *(fmt++);
                lng = 1;

                if (ch == 'l') {
                  ch = *(fmt++);
                  lng = 2;
                }

            }

            switch (ch) {
            case 0:
                goto abort;
            case 'u':
                p.base = 10;


                if (2 == lng)
                    ulli2a((*(unsigned long long int *)__va_arg(*(unsigned long long int **)va, (unsigned long long int)0)), &p);
                else

                  if (1 == lng)
                    uli2a((*(unsigned long int *)__va_arg(*(unsigned long int **)va, (unsigned long int)0)), &p);
                else

                    ui2a((*(unsigned int *)__va_arg(*(unsigned int **)va, (unsigned int)0)), &p);
                putchw(putp, putf, &p);
                break;
            case 'd':
            case 'i':
                p.base = 10;


                if (2 == lng)
                    lli2a((*(long long int *)__va_arg(*(long long int **)va, (long long int)0)), &p);
                else

                  if (1 == lng)
                    li2a((*(long int *)__va_arg(*(long int **)va, (long int)0)), &p);
                else

                    i2a((*(int *)__va_arg(*(int **)va, (int)0)), &p);
                putchw(putp, putf, &p);
                break;

            case 'p':
                p.alt = 1;

                lng = 0;






            case 'x':
            case 'X':
                p.base = 16;
                p.uc = (ch == 'X')?1:0;


                if (2 == lng)
                    ulli2a((*(unsigned long long int *)__va_arg(*(unsigned long long int **)va, (unsigned long long int)0)), &p);
                else

                  if (1 == lng)
                    uli2a((*(unsigned long int *)__va_arg(*(unsigned long int **)va, (unsigned long int)0)), &p);
                else

                    ui2a((*(unsigned int *)__va_arg(*(unsigned int **)va, (unsigned int)0)), &p);
                putchw(putp, putf, &p);
                break;
            case 'o':
                p.base = 8;
                ui2a((*(unsigned int *)__va_arg(*(unsigned int **)va, (unsigned int)0)), &p);
                putchw(putp, putf, &p);
                break;
            case 'c':
                putf(putp, (char)((*(int *)__va_arg(*(int **)va, (int)0))));
                break;
            case 's':
                p.bf = (*(char * *)__va_arg(*(char * **)va, (char *)0));
                putchw(putp, putf, &p);
                p.bf = bf;
                break;
            case '%':
                putf(putp, ch);
            default:
                break;
            }
        }
    }
 abort:;
}


static putcf stdout_putf;
static void *stdout_putp;

void init_printf(void *putp, putcf putf)
{
    stdout_putf = putf;
    stdout_putp = putp;
}

void tfp_printf(char *fmt, ...)
{
    va_list va;
    *va = __va_start();
    tfp_format(stdout_putp, stdout_putf, fmt, va);
    ((void)0);
}



struct _vsnprintf_putcf_data
{
  size_t dest_capacity;
  char *dest;
  size_t num_chars;
};

static void _vsnprintf_putcf(void *p, char c)
{
  struct _vsnprintf_putcf_data *data = (struct _vsnprintf_putcf_data*)p;
  if (data->num_chars < data->dest_capacity)
    data->dest[data->num_chars] = c;
  data->num_chars ++;
}

int tfp_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
  struct _vsnprintf_putcf_data data;

  if (size < 1)
    return 0;

  data.dest = str;
  data.dest_capacity = size-1;
  data.num_chars = 0;
  tfp_format(&data, _vsnprintf_putcf, format, ap);

  if (data.num_chars < data.dest_capacity)
    data.dest[data.num_chars] = '\0';
  else
    data.dest[data.dest_capacity] = '\0';

  return data.num_chars;
}

int tfp_snprintf(char *str, size_t size, const char *format, ...)
{
  va_list ap;
  int retval;

  *ap = __va_start();
  retval = tfp_vsnprintf(str, size, format, ap);
  ((void)0);
  return retval;
}

struct _vsprintf_putcf_data
{
  char *dest;
  size_t num_chars;
};

static void _vsprintf_putcf(void *p, char c)
{
  struct _vsprintf_putcf_data *data = (struct _vsprintf_putcf_data*)p;
  data->dest[data->num_chars++] = c;
}

int tfp_vsprintf(char *str, const char *format, va_list ap)
{
  struct _vsprintf_putcf_data data;
  data.dest = str;
  data.num_chars = 0;
  tfp_format(&data, _vsprintf_putcf, format, ap);
  data.dest[data.num_chars] = '\0';
  return data.num_chars;
}

int tfp_sprintf(char *str, const char *format, ...)
{
  va_list ap;
  int retval;

  *ap = __va_start();
  retval = tfp_vsprintf(str, format, ap);
  ((void)0);
  return retval;
}
