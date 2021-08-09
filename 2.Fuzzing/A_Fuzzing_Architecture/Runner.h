typedef struct prunner{
	char* outcome;
	char* program;
	char* sout;
	char* serr;
	int returncode;
}prunner;

prunner* init(prunner* self, char* program);

void free_prunner();

void child_proc(prunner* self);

void parent_proc(prunner* self, char* input);
// void parent_proc(prunner* self); FUZZER

void run_process(prunner* self, char* input);
// void run_process(prunner* self);

void runn(prunner* self, char* input);
// void runn(prunner* self, char* program);






