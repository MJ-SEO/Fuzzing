typedef struct prunner{
	char* outcome;
	char* program;
	char* sout;
	char* serr;
	int returncode;
}prunner;

prunner* R_init(prunner* self, char* program);

void R_child_proc(prunner* self);

void R_parent_proc(prunner* self, char* input);
// void parent_proc(prunner* self); FUZZER

void R_run_process(prunner* self, char* input);
// void run_process(prunner* self);

void runn(prunner* self, char* input);
// void runn(prunner* self, char* program);






