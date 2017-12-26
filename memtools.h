/** 
* @file 	memtools.h
* @brief 	基于标准内存管理(malloc/free)封装库，记录分配/释放内存节点
* @author 	zhunian0322@163.com
* @date 	17:44 2017/12/26
* @version 	1
*/

#ifndef MEMTOOLS_H_
#define MEMTOOLS_H_

#include <stdio.h>

// 分配内存，s为需要的内存块大小，单位为Byte
#define MEMTOOLS_MALLOC(s)	memtools_malloc(s, __FILE__, __LINE__)

// 释放内存
#define MEMTOOLS_FREE(p) memtools_free(p)

/** 
 *  @breif					分配内存
 *  @param[in] size  		字节数
 *  @param[in] fileName   	文件名
 *	@param[in] line			文件所在行
 *  @return   				成功分配内存地址
 */
void *memtools_malloc(size_t size, char *fileName, size_t line);

/** 
 *  @breif					释放内存
 *  @param[in] ptr			需释放内存地址
 */
void memtools_free(void *ptr);

/** 
 *  @breif					打印分配/释放内存报告
 */
void memtools_report();

#endif

