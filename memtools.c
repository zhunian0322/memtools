/** 
* @file 	memtools.c
* @brief 	基于标准内存管理(malloc/free)封装库，记录分配/释放内存节点
* @author 	zhunian0322@163.com
* @date 	17:44 2017/12/26
* @version 	1
*/


#include <stdlib.h>
#include <pthread.h>

#include "memtools.h"


static pthread_mutex_t mem_mutext = PTHREAD_MUTEX_INITIALIZER;


typedef struct _mem_node{
	void *ptr;
	size_t block;
	size_t line;
	char *filename;
	struct _mem_node *next;
}mem_node;

static mem_node *mem_head = NULL;

static void mem_node_add(void *ptr, size_t block, size_t line, char *filename){
	mem_node *node = malloc(sizeof(mem_node));
	node->ptr = ptr;
	node->block = block;
	node->line = line;
	node->filename = filename;
	node->next = NULL;

	if(mem_head){
		node->next = mem_head;
		mem_head = node;
	}
	else{
		mem_head = node;
	}
}


static void mem_node_remove(void *ptr){

	if(mem_head){
		if(mem_head->ptr == ptr){
			mem_node *pn = mem_head->next;
			free(mem_head);
			mem_head = pn;
		}else{
			mem_node *pn = mem_head->next;
			mem_node *pc = mem_head;

			while(pn){
				mem_node *pnext = pn->next;
				if(pn->ptr == ptr){
					pc->next = pnext;
					free(pn);
				}
				else{
					pc = pc->next;
				}

				pn = pnext;
			}
		}
	}
	
}

void *memtools_malloc(size_t size, char *fileName, size_t line){
	void *ptr = malloc(size);
	pthread_mutex_lock(&mem_mutext);
	mem_node_add(ptr, size, line, fileName);
	pthread_mutex_unlock(&mem_mutext);
	return ptr;
}

void memtools_free(void *ptr){
	pthread_mutex_lock(&mem_mutext);
	mem_node_remove(ptr);
	pthread_mutex_unlock(&mem_mutext);
	free(ptr);
}

void memtools_report(){
	pthread_mutex_lock(&mem_mutext);
	puts("\n\n-------------------------------mem report------------------------------------\n\n");
	if(mem_head){
		size_t total = 0;
		mem_node *pn = mem_head;

		

		while(pn){
			mem_node *pnext = pn->next;

			printf("malloc :%s(%d), ptr:%p(%dbyte)\n", pn->filename, pn->line, pn->ptr, pn->block);

			total += pn->block;
			pn = pnext;
		}

		printf("total:%dbyte\n",total);
	}
	else{
		printf("total:0byte\n");
	}

	pthread_mutex_unlock(&mem_mutext);
}

