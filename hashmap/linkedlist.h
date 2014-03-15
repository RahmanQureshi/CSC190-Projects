typedef struct Object Object;

struct Object {
	void* data;
	Object *next;
	Object *previous;
};
