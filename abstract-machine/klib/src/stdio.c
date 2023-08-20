#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int int_to_str(char *str, int num){
  if(num < 0){
    *str = '-';
    str++;
    num = -num;
  }
  
  int len = 0;
  int temp = num;
  
  do{
    str[len] = '0' + temp % 10;
    temp /= 10;
    len++;
  } while(temp > 0);
  
  for(int i = 0; i < len / 2; i++){
    char temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
  }
  
  str[len] = '\0';
  
  return len;
}

int string_copy(char *dest, const char *src){
  int len = 0;
  while(src[len] != '\0'){
    dest[len] = src[len];
    len++;
  }
  dest[len] = '\0';
  return len;
}

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  int write = 0;
  int index = 0;
  
  while(fmt[index] != '\0'){
    if(fmt[index] =='%'){
      index++;
      
      switch(fmt[index]){
        case 'd':
          int num = va_arg(args, int);
          write += int_to_str(&out[write], num);
          break;
        case 's':
          char *s = va_arg(args, char*);
          write += string_copy(&out[write], s);
          break;
        default:
          out[write++] = fmt[index];
      }
    } else {
      out[write++] = fmt[index];
    }
    index++;
  }
  
  va_end(args);
  out[write] = '\0';
  
  return write;
          
}


int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
