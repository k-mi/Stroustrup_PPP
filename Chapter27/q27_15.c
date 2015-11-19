#include <stdio.h>

struct Shape;
typedef void (*Pfct0)(struct Shape*);

struct Shape{
	Pfct0 draw;
};

struct Circle{
	struct Shape shape;
};

void draw_shape(struct Shape* p){
	printf("Shape\n");
}

void draw_circle(struct Shape* p){
	printf("Circle\n");
}

void init_shape(struct Shape* p){
	p->draw = draw_shape;
}

void init_circle(struct Circle* p){
	p->shape.draw = draw_circle;
}

void draw(struct Shape* p){
	(p->draw)(p);
}

int main(){
	struct Shape s;
	struct Circle c;
	struct Shape* p;
	
	init_shape(&s);
	init_circle(&c);

	draw(&s);
	draw((struct Shape*)&c);

	p = &s;
	draw(p);
	p = (struct Shape*)&c;
	draw(p);
}