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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static uint32_t nr_exp = 0;
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

static void gen_num(){
  for(int i = nr_exp; i < nr_exp + 10; i++){
    if(i == nr_exp){
      buf[i] = '1' + rand() % 9;
    }else{
      buf[i] = '0' + rand()% 10;
    }
  }
  nr_exp += 10;
}

static void gen_rand_op(){
  switch(rand() % 3){
    case 0: 
        buf[nr_exp] = '+';
        break;
    case 1:
        buf[nr_exp] = '-';
        break;
    case 2:
        buf[nr_exp] = '*';
        break;
    case 3:
        buf[nr_exp] = '/';
        break;
    default:
        break;
  }
  nr_exp++;
}
static void gen_rand_expr() {
  int choose = rand() % 3;
  if(nr_exp > 100){
    choose = 0;
  }
  switch(choose){
    case 0: 
          gen_num();
          break;
    case 1:
          buf[nr_exp] = '(';
          nr_exp++;
          gen_rand_expr();
          buf[nr_exp] = ')';
          nr_exp++;
          break;
    default:
          gen_rand_expr();
          gen_rand_op();
          gen_rand_expr();
          break;
  }

  buf[nr_exp] = '\0';
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    gen_rand_expr();
    nr_exp = 0;

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%u", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
