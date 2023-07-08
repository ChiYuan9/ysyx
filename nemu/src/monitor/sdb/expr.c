/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
static bool check_parentheses(int p, int q);
static int get_pos(int p, int q);
static uint32_t eval(int p, int q);
enum {
  TK_NOTYPE = 256, TK_EQ,
  TK_NUM = 255,
  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */
  {"[0-9]+", TK_NUM}, // decimal numbers
  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},          // plus
  {"\\-", '-'},          // minus
  {"\\*", '*'},          // multiply
  {"\\/", '/'},          // devide
  {"\\(", '('},          // left bracket
  {"\\)", ')'},          // right bracket
  {"==", TK_EQ},        // equal
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;
        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        tokens[nr_token].type = rules[i].token_type;
        if(tokens[nr_token].type == TK_NOTYPE){
          break;
        } else if(tokens[nr_token].type == TK_NUM){
          for(int count = 0; count < substr_len; count++){
            tokens[nr_token].str[count] = e[position - substr_len + count];
          }
          tokens[nr_token].str[substr_len] = '\0';
        }
        nr_token++;
        
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  *success = true;
  return eval(0,nr_token - 1);
}

static uint32_t eval(int p, int q){
  if(p > q){
    printf("Bad expression.\n");
    return 0;
  }
  else if(p == q){
    char *endptr;
    return strtoul(tokens[p].str, &endptr, 10);
  }
  else if(check_parentheses(p, q) == true){
    return eval(p+1, q-1);
  }
  else{
    int op = get_pos(p, q);
    uint32_t val1 = eval(p, op-1);
    uint32_t val2 = eval(op+1, q);

    switch(tokens[op].type){
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      default: assert(0);
    }
  }
}

static bool check_parentheses(int p, int q){
  int count = 0;
  if(tokens[p].type != '(' || tokens[q].type != ')'){
    return false;
  }
  for(int i = p; i <= q; i++){
    if(tokens[i].type == '('){
      count++;
    } else if(tokens[i].type == ')'){
      count--;
    }
    if(count < 0){  // bad expression
      assert(0);
    }
    if(count == 0 && i != q){
      return false;
    }
   
  }
  return true;

}

static int get_pos(int p, int q){
  int bricket_count = 0;
  int pos = 0;
  bool is_addsub = false;

  for(int i = p; i <= q; i++){
    if(tokens[i].type == '('){
      bricket_count++;
    } else if(tokens[i].type == ')'){
      bricket_count--;
    } else if(tokens[i].type == '+' || tokens[i].type == '-'){
      if(bricket_count == 0){
        pos = i;
        is_addsub = true;
      }
    } else if(tokens[i].type == '*' || tokens[i].type == '/'){
      if(bricket_count == 0 && is_addsub == false){
        pos = i;
      }
    }
  }
  return pos;

}