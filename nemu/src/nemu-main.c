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

#include <common.h>
#include "monitor/sdb/sdb.h"
void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  /* Start engine. */
  engine_start();
  
  /* Start
  FILE *file = fopen("/home/yuan/Documents/ysyx-workbench/nemu/tools/gen-expr/input", "r");
  if (file == NULL) {
    printf("Unable to open the file.\n");
    return 1;
  }
  char line[70000];
  bool flag = false;
  while (fgets(line, sizeof(line), file) != NULL) {
    char *token1 = strtok(line, " ");
    char *token2 = strtok(NULL, " ");
    int length = strlen(token2);
    token2[length - 1] = '\0';
    uint32_t result1 = strtoul(token1, NULL, 10);
    uint32_t result2 = expr(token2, &flag);
    printf("Correct: %u\t Test: %u\n", result1, result2);
  }
  fclose(file);
  */
  // End

  return is_exit_status_bad();
}
