/*
 * Copyright (c) 2019-2022, Xilinx, Inc. All rights reserved.
 * Copyright (c) 2022-2023, Advanced Micro Devices, Inc. All rights reserved.
 */

#ifndef __QDMA_ACCESS_VERSION_H_
#define __QDMA_ACCESS_VERSION_H_


#define QDMA_VERSION_MAJOR	2023
#define QDMA_VERSION_MINOR	2
#define QDMA_VERSION_PATCH	0

#define QDMA_VERSION_STR	\
	__stringify(QDMA_VERSION_MAJOR) "." \
	__stringify(QDMA_VERSION_MINOR) "." \
	__stringify(QDMA_VERSION_PATCH)

#define QDMA_VERSION  \
	((QDMA_VERSION_MAJOR)*1000 + \
	 (QDMA_VERSION_MINOR)*100 + \
	  QDMA_VERSION_PATCH)


#endif /* __QDMA_ACCESS_VERSION_H_ */
