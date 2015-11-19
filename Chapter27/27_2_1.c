#include <stdio.h>

struct Shape2;

typedef void (*Pfct0)(struct Shape2*);
typedef void (*Pfct1int)(struct Shape2*, int);	/* 未使用 */

struct Shape2{
	Pfct0 draw;
	Pfct1int rotate;	/* 未使用 */
	/* ... */
};

void draw(struct Shape2* p){
	(p->draw)(p);
}

/* 未使用 */
void rotate(struct Shape2* p, int d){
	(p->rotate)(p, d);
}

int f(struct Shape2* pp){
	draw(pp);
	/* ... */
}

void draw_shape2(struct Shape2* p){
	printf("Shape2\n");
}

int main(){
	struct Shape2 s2;
	s2.draw = draw_shape2;
	f(&s2);
}