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
#include <memory/vaddr.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
enum {
  TK_NOTYPE = 256,
  TK_EQ = 257,
  TK_NUM = 255,
  TK_NE = 254,
  TK_AND = 253,
  TK_HEX = 252,
  TK_REG = 251,
  TK_DEREF = 250,
  TK_NEG = 249
  /* TODO: Add more token types */

};
static uint64_t eval(int p, int q);
static bool check_parentheses(int p, int q);
static int get_pos(int p, int q);

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */
  {"[1-9][0-9]*", TK_NUM}, // decimal numbers
  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},          // plus
  {"\\-", '-'},          // minus
  {"\\*", '*'},          // multiply
  {"\\/", '/'},          // devide
  {"\\(", '('},          // left bracket
  {"\\)", ')'},          // right bracket
  {"==", TK_EQ},        // equal
  {"!=", TK_NE},          // not equal
  {"&&", TK_AND},         // and
  {"0x[0-9|a-f|A_F]+", TK_HEX},   // hex numbers
  {"\\$..", TK_REG},      // register
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

static Token tokens[100] __attribute__((used)) = {};
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
        //char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        /*
        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);
        */

        position += substr_len;
        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        tokens[nr_token].type = rules[i].token_type;
        switch(tokens[nr_token].type){
          case TK_NOTYPE: 
                break;
          case TK_HEX:
          case TK_NUM:
                for(int count = 0; count < substr_len && count < 32; count++){
                  tokens[nr_token].str[count] = e[position - substr_len + count];
                }
                if(substr_len > 32){
                    printf("Number longer than 32 bits are treated as %s\n.",tokens[nr_token].str);
                }else {
                    tokens[nr_token].str[substr_len] = '\0';
                }
                nr_token++;
                break;
          case TK_REG:
                for(int count = 1; count < 3; count++){
                  tokens[nr_token].str[count-1] = e[position - substr_len + count];
                }
                tokens[nr_token].str[2] = '\0';
                nr_token++;
                break;
          default:
                nr_token++;
                break;
        }
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


uint64_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  for(int i = 0; i < nr_token; i++){
    if(tokens[i].type == '-' && (i == 0 || (tokens[i-1].type < 200 && tokens[i-1].type != ')'))){
      tokens[i].type = TK_NEG;
    }else if(tokens[i].type == '*' && (i == 0 || (tokens[i-1].type < 200 && tokens[i-1].type != ')'))){
      tokens[i].type = TK_DEREF;
    }
  }
  *success = true;
  return eval(0,nr_token - 1);
}

static uint64_t eval(int p, int q){
  if(p > q){
    printf("Bad expression.\n");
    return 0;
  }
  else if(p == q){
    char *endptr;
    bool success;
    switch(tokens[p].type){
      case TK_NUM: return strtol(tokens[p].str, &endptr, 10);
      case TK_HEX: return strtol(tokens[p].str, &endptr, 16);
      case TK_REG: return isa_reg_str2val(tokens[p].str, &success);

      default: assert(0);
    }
  }
  else if(check_parentheses(p, q) == true){
    return eval(p+1, q-1);
  }
  else if((q - p) == 1){
    switch(tokens[p].type){
      case TK_NEG: return -1*eval(q,q);
      case TK_DEREF: 
              int addr = eval(q,q);
              return vaddr_read(addr, 4);
      default: assert(0);
    }
  }
  else{
    int op = get_pos(p, q);
    uint64_t val1 = eval(p, op-1);
    uint64_t val2 = eval(op+1, q);

    switch(tokens[op].type){
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      case TK_AND: return val1 && val2;
      case TK_EQ: return val1 == val2;
      case TK_NE: return val1 != val2;
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
  bool is_muldiv = false;
  bool is_equal = false;
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
        is_muldiv = true;
      }
    } else if(tokens[i].type == TK_EQ || tokens[i].type == TK_NE){
      if(bricket_count == 0 && is_addsub == false && is_muldiv == false){
        pos = i;
        is_equal = true;
      }
    } else if(tokens[i].type == TK_AND){
      if(bricket_count == 0 && !is_addsub && !is_muldiv && !is_equal){
        pos = i;
      }
    }
  }
  return pos;

}