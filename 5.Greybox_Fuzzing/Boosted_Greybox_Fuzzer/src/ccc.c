int
lookup(unsigned short hash_num, char* hash_table, seed_t* seed){
	
	if(hash_table[hash_num] == '0'){
		hash_table[hash_num] = '1';
		return 1;
	}

	return 0;
}

unsigned short
hashing(char* bitmap){
	unsigned short hash = 0;
	int c;
	while (c = *bitmap++)
		hash = c + (hash << 6) + (hash << 16) - hash;

	return hash;
}

int
read_gcov_coverage(char* c_file, gcov_t** curr_info, int trial, int n_src, gcov_src_t* gcov_info, seed_t* seed, int greybox){
	char gcov_file[64];
	strcpy(gcov_file, c_file);
	strcat(gcov_file, ".gcov");

	FILE* fp;
	fp = fopen(gcov_file, "rb");
	if(fp == NULL){
		perror("read_gcov_coverage: File Open Error!");
		exit(1);
	}

	int add_seed = 0;

	ssize_t ret;
	char* line = NULL;
	size_t size = 0;
	int branch_bit = 0;
	int n_bit = 0;
	int n_line = 0;
	int n_branch = 0;

	char* curr_mask = (char*)malloc(sizeof(char) * gcov_info->gcov_line+1);
	memset(curr_mask, '0', sizeof(char) * gcov_info->gcov_line);
	curr_mask[gcov_info->gcov_line] = '\0';

	char* branch_mask = (char*)malloc(sizeof(char) * gcov_info->gcov_line+1);
	memset(branch_mask, '0', sizeof(char) * gcov_info->gcov_line);
	branch_mask[gcov_info->gcov_line] = '\0';

	while((ret = getline(&line, &size, fp)) != -1){
		char* ptr = strtok(line, ":");
		int flag = 0;
		while(ptr != NULL){
			if(flag == 0 && atoi(ptr) > 0){
				curr_mask[n_bit] = '1';
				n_line++;			
			}
			if(flag == 0 && strstr(ptr, "branch") != NULL){
				char* btok = strtok(ptr, " ");
				int b_flag = 0;
				while(btok != NULL){
					if(b_flag == 3 && atoi(btok) > 0){
						branch_mask[branch_bit] = '1';
						n_branch++;
					}
					btok = strtok(NULL, " ");		
					b_flag++;
				}
				branch_bit++;
			}
			ptr = strtok(NULL, ":");
			flag++;
		}
		n_bit++;
	}
	
	branch_mask[n_branch] = 0;

#ifdef DEBUG
	printf("[BRANCH] %s\n", branch_mask);
	printf("[HASHING] %u\n", hashing(branch_mask));
#endif
	if(greybox == 1)		
		add_seed = lookup(hashing(branch_mask), gcov_info->hash_table, seed);

//	printf("[DEBUG] size: %d\n", gcov_info->hash_size);
//	printf("[DEBUG] ht: %u\n", gcov_info->hash_table[0]);

	curr_info[trial][n_src].line = n_line;
	if(trial == 0){
		curr_info[trial][n_src].union_line = union_bits(gcov_info->bitmap, curr_mask, gcov_info->gcov_line);
	}
	else{
		int before_lines = curr_info[trial-1][n_src].union_line;
		curr_info[trial][n_src].union_line = union_bits(gcov_info->bitmap, curr_mask, gcov_info->gcov_line);
		int after_lines = curr_info[trial][n_src].union_line;
		if(after_lines > before_lines){	
			//			*new_mutate = 1;	// Not use line
		}
	}

	curr_info[trial][n_src].branch_line = n_branch;
	if(trial == 0){
		curr_info[trial][n_src].branch_union_line = union_bits(gcov_info->branch_bitmap, branch_mask, gcov_info->gcov_line);
	}
	else{
		int before_branch_lines = curr_info[trial-1][n_src].branch_union_line;
		curr_info[trial][n_src].branch_union_line = union_bits(gcov_info->branch_bitmap, branch_mask, gcov_info->gcov_line);
		int after_branch_lines = curr_info[trial][n_src].branch_union_line;
		if(after_branch_lines > before_branch_lines){
		//	add_seed = 1;
		}	
	}

	free(curr_mask);
	free(branch_mask);	
	fclose(fp);

	return add_seed;
}

void
gcda_remove(char* c_file, char* path){
	char* gcda_file = (char*)malloc(sizeof(char) * strlen(c_file) + 4);

	strcpy(gcda_file, c_file);
	char* ptr = strtok(gcda_file, ".");

	sprintf(gcda_file, "%s.gcda", ptr);

	if(path == 0x0){
		if(remove(gcda_file) != 0){
			perror("gcda_remove: GCDA delete failed");
		}
	}
	else{
		char* gcda_path = (char*)malloc(sizeof(char) * 1024);
		sprintf(gcda_path, "%s%s", path, gcda_file);

		printf("[DEBUG] gcda_path: %s\n", gcda_path);

		if(remove(gcda_path) != 0){
			perror("gcda_remove: GCDA PATH delete failed");
		}
		free(gcda_path);
	}

	free(gcda_file);
}

/*
   int
   main(){			// TEST DRIVER for Coverage

   }

 */
