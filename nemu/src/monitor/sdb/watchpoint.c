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

#include "sdb.h"

#define NR_WP 32


static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
static char *wp_result[32]= {
  "string 0", "string 1", "string 2",
  "string 3", "string 4", "string 5",
  "string 6", "string 7", "string 8",
  "string 9", "string 10", "string 11",
  "string 12", "string 13", "string 14",
  "string 15", "string 16", "string 17",
  "string 18", "string 19", "string 20",
  "string 21", "string 22", "string 23",
  "string 24", "string 25", "string 26",
  "string 27", "string 28", "string 29",
  "string 30", "string 31"
};

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].expression = wp_result[i];
    wp_pool[i].result = -1;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp(){
  if(free_ == NULL){
    printf("No space for watchpoint.\n");
    assert(0);
  }
  WP *tmp = free_;
  free_ = free_->next;
  if(head == NULL){
    head = wp_pool;
    head->next = NULL;
  }else{
    WP *cur = head;
    while(cur->next != NULL){
      cur = cur->next;
    }
    cur->next = tmp;
    tmp->next = NULL;
  }
  return tmp;
}

void free_wp(WP *wp){
  if(head == NULL){
    printf("No watchpoint to free.\n");
    return;
  }
  WP *cur = head;
  WP *prev = NULL;
  while(cur != wp){
    if(cur->next == NULL){
      printf("No matching watchpoint.\n");
      return;
    }
    prev = cur;
    cur = cur->next;
  }

  if(prev == NULL){
    head = NULL;
    free_ = wp_pool;
  }else{
    prev->next = cur->next;
    cur->next = free_;
    free_ = cur;
  }
  wp->expression = '\0';
  wp->result = -1;
}

bool cal_wp(){
  bool flag = false;
  bool flag_cal = false;
  if(head == NULL){
    return false;
  }
  WP *tmp = head;
  while(tmp != NULL){
    int result = expr(tmp->expression, &flag_cal);
    if (flag_cal == false){assert(0);}
    if(tmp->result != -1 && result != tmp->result){flag = true;}
  }
  return flag;

}